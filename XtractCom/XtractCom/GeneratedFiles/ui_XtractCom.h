/********************************************************************************
** Form generated from reading UI file 'XtractCom.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XTRACTCOM_H
#define UI_XTRACTCOM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_XtractComClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *XtractComClass)
    {
        if (XtractComClass->objectName().isEmpty())
            XtractComClass->setObjectName(QStringLiteral("XtractComClass"));
        XtractComClass->resize(600, 400);
        menuBar = new QMenuBar(XtractComClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        XtractComClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(XtractComClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        XtractComClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(XtractComClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        XtractComClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(XtractComClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        XtractComClass->setStatusBar(statusBar);

        retranslateUi(XtractComClass);

        QMetaObject::connectSlotsByName(XtractComClass);
    } // setupUi

    void retranslateUi(QMainWindow *XtractComClass)
    {
        XtractComClass->setWindowTitle(QApplication::translate("XtractComClass", "XtractCom", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class XtractComClass: public Ui_XtractComClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XTRACTCOM_H
