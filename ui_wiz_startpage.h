/********************************************************************************
** Form generated from reading ui file 'wiz_startpage.ui'
**
** Created: Thu 22. Oct 16:11:59 2009
**      by: Qt User Interface Compiler version 4.5.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_WIZ_STARTPAGE_H
#define UI_WIZ_STARTPAGE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QWizardPage>

QT_BEGIN_NAMESPACE

class Ui_StartPage
{
public:
    QPlainTextEdit *plainTextEdit;
    QPlainTextEdit *plainTextEdit_2;

    void setupUi(QWizardPage *StartPage)
    {
        if (StartPage->objectName().isEmpty())
            StartPage->setObjectName(QString::fromUtf8("StartPage"));
        StartPage->resize(400, 300);
        StartPage->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        plainTextEdit = new QPlainTextEdit(StartPage);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(10, 10, 371, 101));
        plainTextEdit->setAutoFillBackground(false);
        plainTextEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        plainTextEdit->setFrameShape(QFrame::NoFrame);
        plainTextEdit->setFrameShadow(QFrame::Plain);
        plainTextEdit_2 = new QPlainTextEdit(StartPage);
        plainTextEdit_2->setObjectName(QString::fromUtf8("plainTextEdit_2"));
        plainTextEdit_2->setEnabled(true);
        plainTextEdit_2->setGeometry(QRect(11, 149, 371, 141));
        plainTextEdit_2->setContextMenuPolicy(Qt::NoContextMenu);
        plainTextEdit_2->setStyleSheet(QString::fromUtf8("background-color: rgb(197, 197, 197);"));
        plainTextEdit_2->setFrameShape(QFrame::Box);
        plainTextEdit_2->setFrameShadow(QFrame::Plain);
        plainTextEdit_2->setReadOnly(true);

        retranslateUi(StartPage);

        QMetaObject::connectSlotsByName(StartPage);
    } // setupUi

    void retranslateUi(QWizardPage *StartPage)
    {
        StartPage->setWindowTitle(QApplication::translate("StartPage", "WizardPage", 0, QApplication::UnicodeUTF8));
        StartPage->setTitle(QString());
        StartPage->setSubTitle(QString());
        plainTextEdit->setPlainText(QApplication::translate("StartPage", "This wizard will guides you through your way to generate a new OpenVPN config. You simply need to specify the fields you want include into the new config and your server properties.", 0, QApplication::UnicodeUTF8));
        plainTextEdit_2->setPlainText(QApplication::translate("StartPage", "Please notice. If you create a OpenVPN config in portable mode, the new config will be automatically created in the application directory. In the installation mode the default is to create the new config in the home directory of the user. \n"
"\n"
"Attention:\n"
"The Securepoint OpenVPN client will only searching for config files in the application directory in portable mode and furthermore in the home directory on installation mode.", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(StartPage);
    } // retranslateUi

};

namespace Ui {
    class StartPage: public Ui_StartPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIZ_STARTPAGE_H