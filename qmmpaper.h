#ifndef __QMMPAPER_H__
#define __QMMPAPER_H__

#include "ui_qmmpaper.h"

class QMMPaper : public QMainWindow
{
    Q_OBJECT

public:
    QMMPaper(QMainWindow *parent = 0);
	void generate();

private slots:
	void on_menuPrint_triggered();
	void on_menuPrintSettings_triggered();
	void on_color1button_clicked();
	void on_color2button_clicked();
	void on_color3button_clicked();
	void on_predefined1button_clicked();
	void on_predefined2button_clicked();
	void on_predefined3button_clicked();

private:
    Ui::MainWindow ui;
	QGraphicsScene *scene;
	QPrinter *printer;
	QColor color1;
	QColor color2;
	QColor color3;
};

#endif