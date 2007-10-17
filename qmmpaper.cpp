/*
 * QMMPaper, a Qt4 millimetered paper generator
 * Copyright (c) 2007 Alexis ROBERT <alexis.robert@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <QtGui>

#include "qmmpaper.h"
#include "dynamicbutton.h"

#include <QColorDialog>
#include <QPrintDialog>
#include <QPrinter>
#include <QScriptValueIterator>

QMMPaper::QMMPaper(QMainWindow *parent) : QMainWindow(parent)
{
  ui.setupUi(this);
  printer = new QPrinter();
  
  scene = new QGraphicsScene(this);
  ui.graphicsView->setScene(scene);

  paper = NULL;
  jswrapper = NULL;
  jsengine = NULL;
  misccolors_number = 0;
  text = "";

  QDir appdir(QApplication::applicationDirPath());
  loadScript(settings.value("default/script", appdir.filePath("millimetered.js")).toString());
}

QMMPaper::~QMMPaper() {
  if (paper != NULL)
    delete paper;

  if (jswrapper != NULL)
    delete jswrapper;

  if (jsengine != NULL)
    delete jsengine;

  delete printer;
  delete scene;
}

void QMMPaper::loadScript(QString filename) {
  // Open script file
  QFile file(filename);
  if (!file.exists()) {
    QMessageBox::critical(this, tr("Script not found"), tr("The script couldn't be found."));
    on_menuLoadScript_triggered();
  }

  file.open(QIODevice::ReadOnly | QIODevice::Text);
  
  // Evaluate it
  if (jsengine != NULL)
    delete jsengine;

  jsengine = new QScriptEngine();
  jsengine->evaluate(file.readAll());
  file.close();

  // Delete all current color buttons
  foreach(QObject *obj, ui.color1GBox->children()) {
    if (obj->isWidgetType())
      delete obj;
  }

  this->currentcolors.clear();

  // Create color buttons
  if (jsengine->globalObject().property("colors").isValid()) {
    QScriptValue colorbuttons_list = jsengine->globalObject().property("colors");

    QScriptValueIterator colorbuttons_it(colorbuttons_list);
    while (colorbuttons_it.hasNext()) {
      colorbuttons_it.next();

      QList<QColor> *colors = new QList<QColor>;
      
      QScriptValueIterator colors_it(colorbuttons_it.value());
      while (colors_it.hasNext()) {
	colors_it.next();
	colors->append(QColor((int)colors_it.value().property(0).toInteger(),
			      (int)colors_it.value().property(1).toInteger(),
			      (int)colors_it.value().property(2).toInteger()));
      }
      
      DynamicButton *predefinedbutton = new DynamicButton(colorbuttons_it.name(), (QObject*)colors, ui.color1GBox);
      ui.vboxLayout1->addWidget(predefinedbutton);
      
      QObject::connect(predefinedbutton, SIGNAL(clicked(QObject*)), this, SLOT(predefinedbutton_clicked(QObject*)));
    }
  }

  // Inject wrapper object inside script engine
  if (jswrapper == NULL)
    jswrapper = new JSWrapper(scene);

  jsengine->globalObject().setProperty("wrapper", jsengine->newQObject(jswrapper));

  // Choose the first color and generates
  if (ui.color1GBox->children().count() < 2) {
    generate();
  } else {
    ((DynamicButton *)ui.color1GBox->children()[1])->simulate();
  }

  // If there is no colors (like for the music script), hide color boxes
  if (ui.color1GBox->children().count() == 1) {
    ui.color1GBox->hide();
    ui.color2GBox->hide();
  } else {
    ui.color1GBox->show();
    ui.color2GBox->show();
  }
}

void QMMPaper::generate() {
  // Empty the QGraphicsScene
  foreach(QGraphicsItem *item,scene->items()) {
    scene->removeItem(item);
    delete item;
  }

  // Delete old Paper before recreate it
  if (paper != NULL)
    delete paper;
  paper = new Paper(printer->resolution(), printer->pageRect().height(), printer->pageRect().width());
  
  float mm = paper->getDpm();
  int width = paper->getWidth();
  int height = paper->getHeight();

  jsengine->globalObject().setProperty("paper", jsengine->newQObject(paper));

  // Now we fill the colors
  QScriptValue colors = jsengine->newArray();
  int colors_idx = 0;
  foreach(QColor color, this->currentcolors) {
    QScriptValue color_array = jsengine->newArray();

    color_array.setProperty(0,jsengine->toScriptValue(color.red()));
    color_array.setProperty(1,jsengine->toScriptValue(color.green()));
    color_array.setProperty(2,jsengine->toScriptValue(color.blue()));

    colors.setProperty(colors_idx,color_array);
    colors_idx++;
  }
  jsengine->globalObject().setProperty("current_color", colors);

  if (colors_idx != misccolors_number) { // Here is a very simple cache :)

    // The number of colors of the selected scheme are now in color_idx
    // so, create the custom color buttons.
    foreach(QObject *obj, ui.color2GBox->children()) {
      if (obj->isWidgetType())
	delete obj;
    }
    
    for (int i=0; i < colors_idx; i++) {
      QString *id = new QString(QString::number(i));
      
      DynamicButton *colorbutton = new DynamicButton(QString("&Color %1").arg(i+1), (QObject*)id, ui.color1GBox);
      ui.vboxLayout2->addWidget(colorbutton);
      
      QObject::connect(colorbutton, SIGNAL(clicked(QObject*)), this, SLOT(colorbutton_clicked(QObject*)));
    }

    misccolors_number = colors_idx;
  }

  // Before drawing, tell graphicsview where we'll draw
  ui.graphicsView->setSceneRect(0,0,width,height);

  // Tell script file to draw the paper
  QScriptValue result = jsengine->evaluate("draw();");

  if (jsengine->hasUncaughtException()) {
    int line = jsengine->uncaughtExceptionLineNumber();
    qDebug() << "uncaught exception at line" << line << ":" << result.toString();
  }

  // Add text
  if (!text.isEmpty()) {
    QGraphicsTextItem *textitem = scene->addText(text);
    textitem->setPos((width/2)-(textitem->boundingRect().width()/2), 
		     (height-(5*mm))-(textitem->boundingRect().height()/2)); // Centers the text
    textitem->setZValue(5);
    scene->addRect(textitem->sceneBoundingRect(), QPen(Qt::white), QBrush(Qt::white))->setZValue(4);
  }
}

void QMMPaper::on_menuLoadScript_triggered() {
  QString filename = QFileDialog::getOpenFileName(this, tr("Open script"), "", "Scripts (*.js)");

  if (filename != NULL) {
    loadScript(filename);
    generate();

    settings.setValue("default/script", filename);
  }
}

void QMMPaper::on_menuExit_triggered() {
  this->close();
}

void QMMPaper::on_menuPrint_triggered() {
  QPainter painter(printer);
  scene->render(&painter, QRectF(0,0,printer->width(),printer->height()));
  painter.end();
}

void QMMPaper::on_menuPrintSettings_triggered() {
  QPrintDialog printdialog(printer, NULL);
  printdialog.exec();
  QMMPaper::generate();
}

void QMMPaper::colorbutton_clicked(QObject *data) {
  int id = ((QString*)data)->toInt();
  QColor newcolor = QColorDialog::getColor(currentcolors[id]);
  
  if (newcolor.isValid())
    currentcolors[id] = newcolor;
  
  generate();
}

void QMMPaper::predefinedbutton_clicked(QObject *data) {
  QList<QColor> *colorlist = (QList<QColor>*)data;

  if ((*colorlist) != currentcolors) { // Here is another simple cache :)
    currentcolors.clear();
    foreach(QColor color, *colorlist)
      currentcolors << color;

    generate();
  }
}

void QMMPaper::on_text_returnPressed() {
  text = ui.text->text();
  generate();
}

void QMMPaper::on_about_triggered() {
  QMessageBox::about(this, "QMMPaper", "Copyright (c) 2007 Alexis ROBERT");
}
