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

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDir>

#include "qmmpaper.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  QApplication::setOrganizationName("Alexis ROBERT");
  QApplication::setOrganizationDomain("qmmpaper.googlecode.com");
  QApplication::setApplicationName("QMMPaper");

  // Init i18n
  QString locale = QLocale::system().name();
  QTranslator translator;

  QDir appdir(QApplication::applicationDirPath());
  appdir.cd("lang");
  translator.load(appdir.filePath(QString("qmmpaper_")+locale));
  app.installTranslator(&translator);

  QMMPaper form;
  form.show();
  return app.exec();
}
