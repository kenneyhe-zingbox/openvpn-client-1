#include "clientsettingswidget.h"
#include "ui_clientsettingswidget.h"

#include <frmmain.h>
#include <widgetfactory.h>
#include <QtGui/qpainter.h>
#include "settings.h"
#include <utils.h>
#include <service/SrvCLI.h>

#include <tapdriver.h>

#include <message.h>

ClientSettingsWidget::ClientSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientSettingsWidget)
{
    ui->setupUi(this);

    this->tapCount = 0;

    //
    ui->tabGeneral->setLayout(ui->verticalLayoutGeneral);
    //
    //ui->tabConnection->setLayout(ui->verticalLayoutConnection);
    //
    ui->tabUpdate->setLayout(ui->verticalLayoutUpdate);

    //
    ui->gbUpdateSource->setLayout(ui->verticalLayoutUpdateSource);
    //
    ui->gbDownloadSpource->setLayout(ui->verticalLayouDownloadSource);
    //
    //ui->gbMaschineConfigsDirectory->setLayout(ui->verticalLayoutMaschineConfigDirectory);
}

ClientSettingsWidget::~ClientSettingsWidget()
{
    delete ui;
}

void ClientSettingsWidget::on_cmdBack_clicked()
{
    //
    // Close me
    //
    // Save the proxy settings

    QSettings proxIni (Utils::dataDirectory() + QLatin1String("/proxy.ini"), QSettings::IniFormat);
    if (ui->rbUseConfig->isChecked()) {
        proxIni.setValue("proxy-use", "CONFIG");
    } else if (ui->rbUseIE->isChecked()) {
        proxIni.setValue("proxy-use", "IE");
    } else {
        proxIni.setValue("proxy-use", "MANUAL");
        proxIni.setValue("proxy-type", (ui->rbHttpProxy->isChecked() ? "HTTP" : "SOCKS"));
        proxIni.setValue("proxy-ip", ui->txtProxyIP->text());
        proxIni.setValue("proxy-port", ui->txtProxyPort->text());
    }

    FrmMain::instance()->mainWidget()->showWidget(MainView);
}

void ClientSettingsWidget::on_rbUseManual_toggled(bool checked)
{
    if (checked) {
        ui->rbHttpProxy->setEnabled(true);
        ui->rbSocksProxy->setEnabled(true);
        ui->txtProxyIP->setEnabled(true);
        ui->txtProxyPort->setEnabled(true);
    } else {
        ui->rbHttpProxy->setEnabled(false);
        ui->rbSocksProxy->setEnabled(false);
        ui->txtProxyIP->setEnabled(false);
        ui->txtProxyPort->setEnabled(false);
    }
}

void ClientSettingsWidget::paintEvent(QPaintEvent *pe)
{
    //
    // Draw it with stylesheet support
    // Sometimes I hate Qt!
    // For further information, take a look at
    // http://stackoverflow.com/questions/18344135/why-do-stylesheets-not-work-when-subclassing-qwidget-and-using-q-object
    //

    Q_UNUSED(pe)

    QStyleOption option;
    option.initFrom(this);
    //
    QPainter painter(this);
    //
    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}

void ClientSettingsWidget::showEvent(QShowEvent *event)
{
    //
    // Init the values
    //

    // General
    ui->cbStartOnWindows->setChecked(Settings::instance()->startOnWindows());
    ui->cbBlockShutdown->setChecked(Settings::instance()->blockShutdown());
    //ui->cbShowBallon->setChecked(Settings::instance()->showBallon());
    ui->cbAlwaysPopup->setChecked(Settings::instance()->alwaysPopup());
    //
    ui->cbShowSmallDhKeyHInt->setChecked(Settings::instance()->dhShowSmallKeyInformation());

    // Connection
    //ui->cbInteract->setChecked(Settings::instance()->useInteract());
    //ui->cbAutoRestart->setChecked(Settings::instance()->autoRestart());

    //ui->cbAutoRestart->setVisible(false);
    //ui->cbInteract->setVisible(false);

    // Update
    ui->cbCheckUpdate->setChecked(Settings::instance()->enableUpdate());
    if (Settings::instance()->useSecurepoint()) {
        ui->rbSecurepoint->setChecked(true);
    } else {
        ui->rbSourceforge->setChecked(true);
    }
    ui->txtUpdateSource->setText(Settings::instance()->updateUrl());

    //
    //ui->txtMaschineConfigDirectory->setText(Settings::instance()->maschineConfigDirectory());

    // Maschine configurations is only visible when the user has administraion permissions
    //ui->gbMaschineConfigsDirectory->setVisible(Utils::isUserAdmin());

    // Set general as default
    ui->tabWidget->setCurrentIndex(0);

    SrvCLI::instance()->send(QLatin1String("TAPCOUNT"), QLatin1String(""));
   
    ui->lbTAPCount->setText(QObject::tr("Current TAP Count: ") + QString("%1").arg(tapCount));

     QFile pINI (Utils::dataDirectory() + QLatin1String("/proxy.ini"));
    if (!pINI.exists()) {
        //Message::error(QObject::tr("No proxy config available!"), QObject::tr("Proxy Settings"));
        ui->rbUseConfig->setChecked(true);
        ui->rbUseIE->setEnabled(true);
        ui->rbUseManual->setEnabled(true);
        ui->rbHttpProxy->setEnabled(false);
        ui->rbSocksProxy->setEnabled(false);
        ui->txtProxyIP->setEnabled(false);
        ui->txtProxyPort->setEnabled(false);
    } else {
        QSettings proxIni (Utils::dataDirectory() + QLatin1String("/proxy.ini"), QSettings::IniFormat);
        if (proxIni.value("proxy-use","").toString() == "CONFIG") {
            ui->rbUseConfig->setChecked(true);
        } else if (proxIni.value("proxy-use","").toString() == "IE") {
            ui->rbUseIE->setChecked(true);
        } else {
            // MANUAL
            ui->rbHttpProxy->setEnabled(true);
            ui->rbSocksProxy->setEnabled(true);
            ui->txtProxyIP->setEnabled(true);
            ui->txtProxyPort->setEnabled(true);
            ui->rbUseManual->setChecked(true);
            ui->txtProxyPort->setText(proxIni.value("proxy-port","8080").toString());
            ui->txtProxyIP->setText(proxIni.value("proxy-ip","").toString());
            if (proxIni.value("proxy-type","").toString() == "HTTP")
                ui->rbHttpProxy->setChecked(true);
            else
                ui->rbSocksProxy->setChecked(true);

        }
        #ifdef Q_OS_WIN32
            ui->rbUseIE->setEnabled(true);
        #endif
    }
    //
    event->accept();
}

void ClientSettingsWidget::receivedTapCount(int count)
{
    this->tapCount = count;

    ui->lbTAPCount->setText(QObject::tr("Current TAP Count: ") + QString("%1").arg(count));
}

void ClientSettingsWidget::on_cbStartOnWindows_toggled(bool checked)
{

}

void ClientSettingsWidget::on_cbBlockShutdown_toggled(bool checked)
{
    //
    // Update setting
    //

    Settings::instance()->setBlockShutdown(checked);
}

void ClientSettingsWidget::on_cbShowBallon_toggled(bool checked)
{
    //
    // Update setting
    //

    Settings::instance()->setShowBallon(checked);
}

void ClientSettingsWidget::on_cbAlwaysPopup_toggled(bool checked)
{
    //
    // Update setting
    //

    Settings::instance()->setAlwaysPopup(checked);
}

void ClientSettingsWidget::on_cbShowSplash_toggled(bool checked)
{
    //
    // Update setting
    //

    Settings::instance()->setShowSplash(checked);
}

void ClientSettingsWidget::on_cbInteract_toggled(bool checked)
{
    //
    // Update setting
    //

    Settings::instance()->setUseInteract(checked);
}

void ClientSettingsWidget::on_cbAutoRestart_toggled(bool checked)
{
    //
    // Update setting
    //

    Settings::instance()->setAutoRestart(checked);
}

void ClientSettingsWidget::on_cbCheckUpdate_toggled(bool checked)
{
    //
    // Update setting
    //

    Settings::instance()->setEnableUpdate(checked);
}

void ClientSettingsWidget::on_rbSecurepoint_toggled(bool checked)
{
    //
    // Update setting
    //

    Settings::instance()->setUseSecurepoint(checked);
}

void ClientSettingsWidget::on_cmdChangeUpdateSource_clicked()
{
    //
    // Change the update check url
    //

    if (ui->cmdChangeUpdateSource->text() == QObject::tr("Change")) {
        // User want to change the url
        ui->cmdChangeUpdateSource->setText(QObject::tr("Save"));
        ui->txtUpdateSource->setReadOnly(false);
    } else {
        // Save the url and disable the field
        ui->cmdChangeUpdateSource->setText(QObject::tr("Change"));
        ui->txtUpdateSource->setReadOnly(true);
        //
        Settings::instance()->setUpdateUrl(ui->txtUpdateSource->text());
    }
}

void ClientSettingsWidget::on_rbSourceforge_toggled(bool checked)
{
    //
    // Update setting
    //

    Settings::instance()->setUseSecurepoint(!checked);
}

void ClientSettingsWidget::on_cmdAddTap_clicked()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    SrvCLI::instance()->send(QLatin1String("ADDTAP"), QLatin1String(""));
}

void ClientSettingsWidget::on_cmdRemoveTap_clicked()
{
      if(Message::confirm(QObject::tr("Do you realy want to remove all TAP device?"))) {
            // Befehl an den Dienst senden
            QApplication::setOverrideCursor(Qt::WaitCursor);
            SrvCLI::instance()->send(QLatin1String("REMOVETAP"), QLatin1String(""));
        }
}

void ClientSettingsWidget::on_cmdChangeMaschineDirectory_clicked()
{
    //
    // Change the maschine configuration dir
    //

    // User want to change the path
    //
    QString maschineDirectory (QFileDialog::getExistingDirectory(this, QObject::tr("Select import file"), Settings::instance()->maschineConfigDirectory()));
    //
    if (maschineDirectory.isEmpty()) {
        return;
    }

    // Fill ui
    //ui->txtMaschineConfigDirectory->setText(maschineDirectory);
    //
    //Settings::instance()->setMaschineConfigDirectory(ui->txtMaschineConfigDirectory->text());
}

void ClientSettingsWidget::on_cbShowSmallDhKeyHInt_toggled(bool checked)
{
   Settings::instance()->setDhShowSmallKeyInformation(checked);
}

void ClientSettingsWidget::on_cbStartOnWindows_clicked(bool checked)
{
    //
    // Update setting
    //

    Settings::instance()->setStartOnWindows(checked);
    Settings::instance()->setRegEntryStartOnWindows(checked);
}
