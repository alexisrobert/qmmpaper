#include <QtGui>

#include "qmmpaper.h"

#include <QColorDialog>
#include <QPrintDialog>
#include <QPrinter>

QMMPaper::QMMPaper(QMainWindow *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
	printer = new QPrinter();
	printer->setPageSize(QPrinter::A4);
	
	text = "";
	on_predefined1button_clicked(); // Little hack :)
}

void QMMPaper::generate() {
	scene = new QGraphicsScene(this);
	
	// Now we have printer's resolution in inches
	// 25.4mm => 1 inch
	// 1mm => 1/25.4 inch
	printf("Printer resolution : %d DPI\n",printer->resolution());
	printf("Canvas size (paper without margin): %d x %d\n",printer->pageRect().height(),printer->pageRect().width());
	
	float mm = (printer->resolution())/25.4;
	ui.graphicsView->setScene(scene);
	
	int width, height;
	for (width = printer->pageRect().width(); (int)(width/mm) % 10 != 0; width--){}
	for (height = printer->pageRect().height(); (int)(height/mm) % 10 != 0; height--){}
	
	for (int i = 0; i*mm < width; i++) {
		QPen *pen = new QPen;
		pen->setWidth(0);
		
		if (i%10 == 0) {
			pen->setColor(this->color1);
		} else if (i%5 == 0) {
			pen->setColor(this->color3);
		} else {
			pen->setColor(this->color2);
		}
		QGraphicsLineItem *line = scene->addLine(QLineF(i*mm,0,i*mm,((int)(height/mm))*mm),*pen);
		if (i%10 == 0) line->setZValue(1);
	}
	for (int i = 0; i*mm < height; i++) {
		QPen *pen = new QPen;
		pen->setWidth(0);
		if (i%10 == 0) {
			pen->setColor(this->color1);
		} else if (i%5 == 0) {
			pen->setColor(this->color3);
		} else {
			pen->setColor(this->color2);
		}
		QGraphicsLineItem *line = scene->addLine(QLineF(0,i*mm,((int)(width/mm))*mm,i*mm),*pen);
		if (i%10 == 0) line->setZValue(1);
	}
	
	// Add text
	if (text != "") {
		QGraphicsTextItem *textitem = scene->addText(text);
		textitem->setPos((width/2)-(textitem->boundingRect().width()/2), 
							(height-(5*mm))-(textitem->boundingRect().height()/2)); // Centers the text
		textitem->setZValue(3);
		scene->addRect(textitem->sceneBoundingRect(), QPen(Qt::white), QBrush(Qt::white))->setZValue(2);
	}
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
	color1 = QColorDialog::getColor(color1);
	QMMPaper::generate();
}

void QMMPaper::on_color2button_clicked() {
	color2 = QColorDialog::getColor(color2);
	QMMPaper::generate();
}

void QMMPaper::on_color3button_clicked() {
	color3 = QColorDialog::getColor(color3);
	QMMPaper::generate();
}

void QMMPaper::on_predefined1button_clicked() {
	color1 = QColor(127,127,127);
	color2 = QColor(208,208,208);
	color3 = QColor(173,173,173);
	QMMPaper::generate();
}
void QMMPaper::on_predefined2button_clicked() {
	color1 = QColor(255,144,0);
	color2 = QColor(255,207,77);
	color3 = QColor(255,184,29);
	QMMPaper::generate();
}

void QMMPaper::on_predefined3button_clicked() {
	color1 = QColor(79,121,255);
	color2 = QColor(156,198,255);
	color3 = QColor(144,153,255);
	QMMPaper::generate();
}

void QMMPaper::on_text_returnPressed() {
	text = ui.text->text();
	QMMPaper::generate();
}

void QMMPaper::on_about_triggered() {
	QMessageBox::about(this, "QMmPaper", "Copyright (c) 2007 Alexis ROBERT");
}