#include "Calculator.h"

Calculator::Calculator(QWidget* pwgt/*= 0 */) : QWidget(pwgt) {
    pvbxLayout = new QVBoxLayout;
    m_plcd = new QLCDNumber(12);
    m_plcd->setMinimumSize(150, 50);
    m_plcd->setMaximumSize(1100, 50);
    pvbxLayout->addWidget(m_plcd);
    pvbxLayout->setContentsMargins(3, 3, 3, 3);
    pvbxLayout->setSpacing(10);
    phbxLayout = new QHBoxLayout;
    ptopLayoutE = new QGridLayout;
    QString aButtonsE[5][4] = {{"sinh", "sin", "e", "x²"},
                               { "cosh", "cos", "ln", "x³"},
                               {"tanh", "tan", "log", "x^y"},
                               {"n!", "pi", "√", "؆"},
                               {"pi^x", "Mod", "∛", "e^x"}
                              };
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 4; ++j) {
            ptopLayoutE->addWidget(createButtonNormal(aButtonsE[i][j]), i+1, j);
        }
    }
    QChar aButtons[4][4] = {{'7', '8', '9', '/'},
                            {'4', '5', '6', '*'},
                            {'3', '2', '1', '-'},
                            {'0', '.', '=', '+'}
                            };
    ptopLayout = new QGridLayout;
    ptopLayout->addWidget(createButtonNormal("%"), 0, 0);
    ptopLayout->addWidget(createButtonNormal("√"), 0, 1);
    ptopLayout->addWidget(createButtonNormal("CE"), 0, 3);
    ptopLayout->addWidget(createButtonNormal("+/-"), 0, 2);
    m_pradNormal = new QRadioButton("&Normal");
    m_pradEngineer = new QRadioButton("&Engineer");
    m_pradNormal->setChecked(true);
    connect(m_pradNormal, SIGNAL(clicked()), SLOT(slotButtonSwitched()));
    connect(m_pradEngineer, SIGNAL(clicked()), SLOT(slotButtonSwitched()));
    pvbxLayout->addWidget(m_pradNormal, 0);
    pvbxLayout->addWidget(m_pradEngineer, 1);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            ptopLayout->addWidget(createButtonNormal(aButtons[i][j]), i+1, j);
        }
    }

    wgt1.setLayout(ptopLayout);
    wgt2.setLayout(ptopLayoutE);
    m_pradNormal->click();
    phbxLayout->addWidget(&wgt2);
    phbxLayout->addWidget(&wgt1);
    wgt2.setVisible(false);
    wgt3.setLayout(phbxLayout);
    pvbxLayout->addWidget(&wgt3);
    wgt4.setWindowTitle("Calculator (ordinary)");
    wgt4.setMinimumSize(550, 400);
    wgt4.setMaximumSize(550, 400);
    wgt4.setLayout(pvbxLayout);
    wgt4.show();
}

QPushButton* Calculator::createButtonNormal(const QString& str) {
    QPushButton* pcmd = new QPushButton(str);
    pcmd->setMinimumSize(120, 40);
    pcmd->setMaximumSize(120, 40);
    connect(pcmd, SIGNAL(clicked()), SLOT(slotButtonClicked()));
    return pcmd;
}

void Calculator::slotButtonSwitched() {
    if (m_pradEngineer->isChecked()) {
        wgt2.setVisible(true);
        wgt4.setWindowTitle("Calculator (engineer)");
        wgt4.resize(1100, 320);
        wgt4.setMinimumSize(1100, 400);
        wgt4.setMaximumSize(1100, 400);
        return;
    }
    if (m_pradNormal->isChecked()) {
        wgt2.setVisible(false);
        wgt4.setWindowTitle("Calculator (ordinary)");
        wgt4.resize(550, 320);
        wgt4.setMinimumSize(550, 400);
        wgt4.setMaximumSize(550, 400);
        return;
    }
}

void Calculator::calculate() {
    qreal helper = 0;
    qreal fOperand2 = m_stk.pop().toFloat();
    QString strOperation = m_stk.pop();
    qreal fOperand1 = m_stk.pop().toFloat();
    qreal fResult = 0;
    if (strOperation == "Mod") {
        int a = fOperand1;
        int b = fOperand2;
        fResult = a % b;
    }
    if (strOperation == "x^y") {
        fResult = pow(fOperand1, fOperand2);
    }
    if (strOperation == "؆") {
        fResult = pow(fOperand1, 1/fOperand2);
    }
    if (strOperation == "+") {
        fResult = fOperand1 + fOperand2;
    }
    if (strOperation == "-") {
        fResult = fOperand1 - fOperand2;
    }
    if (strOperation == "/") {
        fResult = fOperand1 / fOperand2;
    }
    if (strOperation == "*") {
        fResult = fOperand1 * fOperand2;
    }
    m_strDisplay = fResult;
    m_plcd->display(fResult);
}

void Calculator::calculate1() {
    qreal helper = 0;
    QString strOperation = m_stk.pop();
    qreal fOperand1 = m_stk.pop().toFloat();
    qreal fResult = 0;
    if (strOperation == "n!") {
        int lock = 1;
        helper++;
        for (int i = 0; i < fOperand1; ++i) {
            helper *= lock;
            lock++;
        }
        fResult = helper;
    }
    if (strOperation == "∛") {
        helper = pow(fOperand1, 1/3);
        fResult = helper;
    }
    if (strOperation == "log") {
        helper = log10(fOperand1);
        fResult = helper;
    }
    if (strOperation == "ln") {
        helper = log(fOperand1);
        fResult = helper;
    }
    if (strOperation == "pi^x") {
        helper = pow(3.1415926535, fOperand1);
        fResult = helper;
    }
    if (strOperation == "tanh") {
        helper = tanh(fOperand1);
        fResult = helper;
    }
    if (strOperation == "tan") {
        helper = tan(fOperand1);
        fResult = helper;
    }
    if (strOperation == "cosh") {
        helper = cosh(fOperand1);
        fResult = helper;
    }
    if (strOperation == "sinh") {
        helper = sinh(fOperand1);
        fResult = helper;
    }
    if (strOperation == "cos") {
        helper = cos(fOperand1);
        fResult = helper;
    }
    if (strOperation == "sin") {
        helper = sin(fOperand1);
        fResult = helper;
    }
    if (strOperation == "e^x") {
        helper++;
        for (int i = 0; i < fOperand1; ++i) {
            helper *= 2.71828182845904523536;
        }
        fResult = helper;
    }
    if (strOperation == "pi") {
        helper = 3.1415926535;
        fResult = helper;
    }
    if (strOperation == "e") {
        helper = 2.71828182845904523536;
        fResult = helper;
    }

    if (strOperation == "%") {
        helper = fOperand1 / 100;
        fResult = helper;
    }
    if (strOperation == "√") {
        helper = sqrt(fOperand1);
        fResult = helper;
    }

    if (strOperation == "x²") {
        helper = fOperand1 * fOperand1;
        fResult = helper;
    }
    if (strOperation == "x³") {
        helper = fOperand1 * fOperand1 * fOperand1;
        fResult = helper;
    }
    if (strOperation == "+/-") {
        helper = -1 * fOperand1;
        fResult = helper;
    }
    m_strDisplay = fResult;
    m_plcd->display(fResult);
}

void Calculator::slotButtonClicked() {
    QString str = ((QPushButton*)sender())->text();
    if (str == "CE") {
        m_stk.clear();
        m_strDisplay = "";
        m_plcd->display("0");
        return;
    }
    if (str.contains(QRegExp("[0-9]")) || str == ".") {
        m_strDisplay += str;
        m_plcd->display(m_strDisplay);
    }
    else {
        if (m_stk.count() >= 2) {
            m_stk.push(QString().setNum(m_plcd->value()));
            calculate();
            m_stk.clear();
            m_stk.push(QString().setNum(m_plcd->value()));
            if (str != "=") {
                m_stk.push(str);
            }
        }
        else {
            m_stk.push(QString().setNum(m_plcd->value()));
            m_stk.push(str);
            if (m_stk[1] != "+" && m_stk[1] != "-" && m_stk[1] != "/" && m_stk[1] != "*" && m_stk[1] != "x^y"
                                && m_stk[1] != "x^(1/y)" && m_stk[1] != "Mod" && m_stk[1] != "؆") {
                calculate1();
                m_stk.clear();
            }
            m_strDisplay = "";
        }
    }
}
