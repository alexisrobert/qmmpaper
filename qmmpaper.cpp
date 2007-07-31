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
#include "colors.h"

#include <QColorDialog>
#include <QPrintDialog>
#include <QPrinter>

QMMPaper::QMMPaper(QMainWindow *parent) : QMainWindow(parent)
{
  ui.setupUi(this);
  printer = new QPrinter();
  
  scene = new QGraphicsScene(this);
  ui.graphicsView->setScene(scene);

  paper = NULL;
  jswrapper = NULL;
  jsengine = NULL;
  text = "";

  loadScript(settings.value("default/script", "millimetered.js").toString());

  setColor(BW_COLOR1, BW_COLOR2, BW_COLOR3);
}

QMMPaper::~QMMPaper() {
  if (paper != NULL)
    delete paper;

  if (jswrapper != NULL)
    delete jswrapper;

  if (jsengine != NULL)
    delete jsengine;
}

void QMMPaper::setColor(QColor color1, QColor color2, QColor color3) {
  this->color1 = color1;
  this->color2 = color2;
  this->color3 = color3;

  if (jswrapper != NULL)
    jswrapper->setColor(color1, color2, color3);

  generate();
}

void QMMPaper::loadScript(QString filename) {
  // Open script file
  QFile file(filename);
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  
  // Evaluate it
  if (jsengine != NULL)
    delete jsengine;

  jsengine = new QScriptEngine();
  jsengine->evaluate(file.readAll());
  file.close();

  // Inject wrapper object inside script engine
  if (jswrapper == NULL)
    jswrapper = new JSWrapper(scene);

  jsengine->globalObject().setProperty("wrapper", jsengine->newQObject(jswrapper));
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

  // Little hack to show the page like it will be printed
  scene->addLine(0,0,1,0,QPen(Qt::white));
  scene->addLine(0,height,1,height,QPen(Qt::white));
}

void QMMPaper::on_menuLoadScript_triggered() {
  QString filename = QFileDialog::getOpenFileName(this, "Open script", "", "Scripts (*.js)");

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

void QMMPaper::on_color1button_clicked() {
  setColor(QColorDialog::getColor(color1), color2, color3);
}

void QMMPaper::on_color2button_clicked() {
  setColor(color1, QColorDialog::getColor(color2), color3);
}

void QMMPaper::on_color3button_clicked() {
  setColor(color1, color2, QColorDialog::getColor(color3));
}

void QMMPaper::on_predefined1button_clicked() {
  setColor(BW_COLOR1, BW_COLOR2, BW_COLOR3);
}

void QMMPaper::on_predefined2button_clicked() {
  setColor(ORANGE_COLOR1, ORANGE_COLOR2, ORANGE_COLOR3);
}

void QMMPaper::on_predefined3button_clicked() {
  setColor(BLUE_COLOR1, BLUE_COLOR2, BLUE_COLOR3);
}

void QMMPaper::on_text_returnPressed() {
  text = ui.text->text();
  QMMPaper::generate();
}

void QMMPaper::on_about_triggered() {
  QMessageBox::about(this, "QMMPaper", "Copyright (c) 2007 Alexis ROBERT");
}
