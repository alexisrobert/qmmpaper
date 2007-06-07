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

#include "paper.h"

Paper::Paper(int dpi, int height, int width) {
  this->dpi = dpi;
  this->height = height;
  this->width = width;

  this->computeDpm();
  this->computeSize();
}

void Paper::computeDpm() {
  this->dpm = this->dpi/25.4; // 1 mm => 25.4 inch
}

void Paper::computeSize() {
  int fwidth, fheight;

  for (fwidth = this->width; (int)((this->width)/(this->dpm)) % 10 != 0; width--){}
  for (fheight = this->height; (int)((this->height)/(this->dpm)) % 10 != 0; height--){}

  this->height = fheight;
  this->width = fwidth;
}

int Paper::getHeight() {
  return this->height;
}

int Paper::getWidth() {
  return this->width;
}

int Paper::getDpi() {
  return this->dpi;
}

float Paper::getDpm() {
  return this->dpm;
}
