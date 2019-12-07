#include "mainwindow.h"
#include <QApplication>
#include "Calculator.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   /* Buttons calculator;
    calculator.setWindowTitle("Calculator");
    calculator.resize(600, 300);
    calculator.show();*/
    Calculator calculator;
    //calculator.setWindowTitle("Calculator");
    //calculator.resize(700, 400);
   // calculator.show();
    return a.exec();
}
