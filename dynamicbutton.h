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

#ifndef __DYNAMICBUTTON_H__
#define __DYNAMICBUTTON_H__

#include <QPushButton>

class DynamicButton : public QPushButton {
  Q_OBJECT
  
public:
  DynamicButton(QString text, QObject* data, QWidget *parent = 0);

  QObject* data();
  void data(QObject* data);
  void simulate();

signals:
  void clicked(QObject* data);

private slots:
  void on_clicked();

private:
  QObject* _data;
};

#endif
