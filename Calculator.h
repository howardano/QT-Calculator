#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QStackedWidget>
#include <QtWidgets>
#include <QStack>
#include <QApplication>
#include <QLCDNumber>
#include <QGridLayout>
#include <QPalette>
#include <math.h>
#include <QStyle>
//#include "Buttons.h"

class QLCDNumber;
class QPushButton;

class Calculator : public QWidget {
    Q_OBJECT
private:
    QGridLayout* ptopLayout;
    QWidget wgt1;
    QWidget wgt2;
    QWidget wgt3;
    QWidget wgt4;
    QGridLayout* ptopLayoutE;
    QHBoxLayout * phbxLayout;
    QVBoxLayout * pvbxLayout;
    QCheckBox* m_pchk;
    QRadioButton* m_pradNormal;
    QRadioButton* m_pradEngineer;
    QLCDNumber * m_plcd;
    QStack<QString> m_stk;
    QString m_strDisplay;
public:
    Calculator(QWidget* pwgt = 0);
    QPushButton* createButtonNormal(const QString& str);
    void calculate();
    void calculate1();
public slots:
    void slotButtonClicked();
    void slotButtonSwitched();
    //void slotRadioButtonClicked();
};

#endif // CALCULATOR_H
