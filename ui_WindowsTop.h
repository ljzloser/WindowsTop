/********************************************************************************
** Form generated from reading UI file 'WindowsTop.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWSTOP_H
#define UI_WINDOWSTOP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WindowsTopClass
{
public:

    void setupUi(QWidget *WindowsTopClass)
    {
        if (WindowsTopClass->objectName().isEmpty())
            WindowsTopClass->setObjectName("WindowsTopClass");
        WindowsTopClass->resize(600, 400);

        retranslateUi(WindowsTopClass);

        QMetaObject::connectSlotsByName(WindowsTopClass);
    } // setupUi

    void retranslateUi(QWidget *WindowsTopClass)
    {
        WindowsTopClass->setWindowTitle(QCoreApplication::translate("WindowsTopClass", "WindowsTop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowsTopClass: public Ui_WindowsTopClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWSTOP_H
