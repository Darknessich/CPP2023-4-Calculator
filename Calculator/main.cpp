#include "Calculator.h"

int main(int argc, char* argv[]) {
  Calculator app(argc, argv);
  app.init();
  return app.exec();
}