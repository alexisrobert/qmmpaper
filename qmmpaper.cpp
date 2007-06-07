#include <QtGui>

#include "qmmpaper.h"

// TODO: Remove
#include <QPrintDialog>
#include <QPrinter>

QMMPaper::QMMPaper(QMainWindow *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
	scene = new QGraphicsScene(this);
	printer = new QPrinter();
	printer->setPageSize(QPrinter::A4);
	
	// Now we have printer's resolution in inches
	// 25.4mm => 1 inch
	// 1mm => 1/25.4 inch
	printf("Printer resolution : %d DPI\n",printer->resolution());
	printf("Canvas size (paper without margin): %d x %d\n",printer->pageRect().height(),printer->pageRect().width());
	
	float mm = (printer->resolution())/25.4;
	ui.graphicsView->setScene(scene);
	
	int width;
	for (width = printer->pageRect().width(); (int)(width/mm) % 10 != 0; width--){}
	int height;
	for (height = printer->pageRect().height(); (int)(height/mm) % 10 != 0; height--){}
	printf("%d x %d\n",height,width);
	
	for (int i = 0; i*mm < width; i++) {
		QPen *pen = new QPen;
		if (i%10 == 0) pen->setColor(Qt::red);
		pen->setWidth(1);
		QGraphicsLineItem *text = scene->addLine(i*mm,0,i*mm,((int)(height/mm))*mm,*pen);
		if (i%10 == 0) text->setZValue(1);
	}
	for (int i = 0; i*mm < height; i++) {
		QPen *pen = new QPen;
		if (i%10 == 0) pen->setColor(Qt::red);
		pen->setWidth(1);
		QGraphicsLineItem *text = scene->addLine(0,i*mm,((int)(width/mm))*mm,i*mm,*pen);
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
}
