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

#ifndef __JSWRAPPER_H__
#define __JSWRAPPER_H__

#include <QObject>
#include <QGraphicsScene>

class JSWrapper : public QObject {
  Q_OBJECT

  public:
    JSWrapper(QGraphicsScene *scene);
    void setColor(QColor color1, QColor color2, QColor color3);

  public slots:
    void addLine(int x1, int y1, int x2, int y2, int color = 0, int z = 0);

  private:
    QGraphicsScene *scene;
    QColor color1;
    QColor color2;
    QColor color3;
};

#endif
