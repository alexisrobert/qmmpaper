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

private:
    Ui::MainWindow ui;
	QGraphicsScene *scene;
	QPrinter *printer;
};

#endif