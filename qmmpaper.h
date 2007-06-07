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
  void on_menuExit_triggered();
  void on_menuPrint_triggered();
  void on_menuPrintSettings_triggered();
  void on_color1button_clicked();
  void on_color2button_clicked();
  void on_color3button_clicked();
  void on_predefined1button_clicked();
  void on_predefined2button_clicked();
  void on_predefined3button_clicked();
  void on_text_returnPressed();
  void on_about_triggered();
  
private:
  Ui::MainWindow ui;
  QGraphicsScene *scene;
  QPrinter *printer;
  QColor color1;
  QColor color2;
  QColor color3;
  QString text;
  void drawLine(int lineno, float mm, int height, int width, bool horizontal = TRUE);
};

#endif
