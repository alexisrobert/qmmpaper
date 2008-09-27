TEMPLATE = app
TARGET = 

CONFIG += qt x86
CONFIG += release

ICON = icon/osx/qmmpaper.icns
RESOURCES += qmmpaper.qrc

QT += script

# Input
HEADERS += jswrapper.h dynamicbutton.h paper.h qmmpaper.h
FORMS += qmmpaper.ui
SOURCES += main.cpp dynamicbutton.cpp jswrapper.cpp qmmpaper.cpp paper.cpp
TRANSLATIONS += lang/qmmpaper_fr.ts
