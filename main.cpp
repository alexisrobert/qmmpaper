#include <QApplication>

#include "qmmpaper.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  QMMPaper form;
  form.show();
  return app.exec();
}
