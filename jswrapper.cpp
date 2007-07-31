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

#include "jswrapper.h"
#include <QGraphicsLineItem>

JSWrapper::JSWrapper(QGraphicsScene *scene) {
  this->scene = scene;
}

void JSWrapper::setColor(QColor color1, QColor color2, QColor color3) {
  this->color1 = color1;
  this->color2 = color2;
  this->color3 = color3;
}

void JSWrapper::addLine(int x1, int y1, int x2, int y2, int color, int z) {
  QPen pen;
  pen.setWidth(0);

  if (color == 1) {
    pen.setColor(this->color1);
  } else if (color == 2) {
    pen.setColor(this->color2);
  } else if (color == 3) {
    pen.setColor(this->color3);
  }

  QGraphicsLineItem *line;
  line = scene->addLine(QLineF(x1,y1,x2,y2), pen);
  line->setZValue(z);
}
