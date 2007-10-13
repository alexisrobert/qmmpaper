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

#include "dynamicbutton.h"

DynamicButton::DynamicButton(QString text, QObject* data, QWidget *parent) : QPushButton(text,parent) {
  this->data(data);
  QObject::connect(this, SIGNAL(clicked()), this, SLOT(on_clicked()));
}

void DynamicButton::simulate() {
  emit clicked(this->_data);
}

QObject* DynamicButton::data() {
  return this->_data;
}

void DynamicButton::data(QObject* data) {
  this->_data = data;
}

void DynamicButton::on_clicked() {
  emit clicked(this->_data);
}
