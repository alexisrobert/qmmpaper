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

void JSWrapper::addLine(int x1, int y1, int x2, int y2, QList<QVariant> color, int z) {
  QPen pen;
  pen.setWidth(0);
  pen.setColor(QColor(color[0].toInt(),color[1].toInt(),color[2].toInt()));

  QGraphicsLineItem *line;
  line = scene->addLine(QLineF(x1,y1,x2,y2), pen);
  line->setZValue(z);
}
