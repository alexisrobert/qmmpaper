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
	
	color1 = QColor(255,0,0);
	color2 = QColor(0,0,0);
	
	QMMPaper::generate();
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
		if (i%10 == 0) {
			pen->setColor(this->color1);
			pen->setWidth(1);
		} else {
			pen->setColor(this->color2);
			pen->setWidth(0);
		}
		QGraphicsLineItem *text = scene->addLine(QLineF(i*mm,0,i*mm,((int)(height/mm))*mm),*pen);
		if (i%10 == 0) text->setZValue(1);
	}
	for (int i = 0; i*mm < height; i++) {
		QPen *pen = new QPen;
		if (i%10 == 0) {
			pen->setColor(this->color1);
			pen->setWidth(1);
		} else {
			pen->setColor(this->color2);
			pen->setWidth(0);
		}
		QGraphicsLineItem *text = scene->addLine(QLineF(0,i*mm,((int)(width/mm))*mm,i*mm),*pen);
		if (i%10 == 0) text->setZValue(1);
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