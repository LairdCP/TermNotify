/******************************************************************************
** Copyright (C) 2015 Laird
**
** Project: TermNotify
**
** Module: TNMainWindow.cpp
**
** Notes:
**
** License: This program is free software: you can redistribute it and/or
**          modify it under the terms of the GNU General Public License as
**          published by the Free Software Foundation, version 3.
**
**          This program is distributed in the hope that it will be useful,
**          but WITHOUT ANY WARRANTY; without even the implied warranty of
**          MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**          GNU General Public License for more details.
**
**          You should have received a copy of the GNU General Public License
**          along with this program.  If not, see http://www.gnu.org/licenses/
**
*******************************************************************************/

/******************************************************************************/
// Include Files
/******************************************************************************/
#include "TNMainWindow.h"

/******************************************************************************/
// Local Functions or Private Members
/******************************************************************************/
TNMainWindow::TNMainWindow(QObject *parent) : QObject(parent){
#if TARGET_OS_MAC
    //On mac, get the directory of the bundle (which will be <location>/TermNotify.app/Contents/MacOS) and go up to the folder with the file in
    QDir BundleDir(QCoreApplication::applicationDirPath());
    BundleDir.cdUp();
    BundleDir.cdUp();
    BundleDir.cdUp();
    QString strMacBundlePath = BundleDir.path().append("/");
    QSettings stgSettings(QString(strMacBundlePath).append("TermNotify.ini"), QSettings::IniFormat);
#else
    QSettings stgSettings("TermNotify.ini", QSettings::IniFormat);
#endif

    //Load settings
    gstrExecutable = stgSettings.value("RunFile",
#ifdef _WIN32
        //Windows
        "UwTerminalX"
#elif TARGET_OS_MAC
        //Mac
        "%DIRPATH%/UwTerminalX.app/Contents/MacOS/UwTerminalX"
#else
        //Linux
        "./UwTerminalX"
#endif
    ).toString();
    gstrArgumentList = stgSettings.value("ArgumentList", "ACCEPT COM=%PORT% NOCONNECT").toString();
    gintDisplayTime = stgSettings.value("DisplayTime", DefaultDisplayTime).toUInt();
    gintScanTime = stgSettings.value("ScanTime", DefaultScanTime).toUInt();

    //Set defaults if not found in configuration file
    if (stgSettings.value("RunFile").isNull())
    {
        stgSettings.setValue("RunFile", gstrExecutable);
    }
    if (stgSettings.value("ArgumentList").isNull())
    {
        stgSettings.setValue("ArgumentList", gstrArgumentList);
    }
    if (stgSettings.value("DisplayTime").isNull())
    {
        stgSettings.setValue("DisplayTime", gintDisplayTime);
    }
    if (stgSettings.value("ScanTime").isNull())
    {
        stgSettings.setValue("ScanTime", gintScanTime);
    }

#ifdef TARGET_OS_MAC
    //Replaces instances of %DIRPATH% with the folder location that TermNotify is in
    gstrExecutable.replace("%DIRPATH%", strMacBundlePath);
#endif

    //Create system tray menu
    gpContextMenu = new QMenu;
    gpContextMenu->addAction(new QAction("Laird TermNotify", this));
    gpContextMenu->addAction(new QAction(TermNotifyVer, this));
    gpContextMenu->addSeparator();
    gpContextMenu->addAction(new QAction("Edit Configuration", this));
    gpContextMenu->addAction(new QAction("Exit", this));
    gpContextMenu->actions()[0]->setDisabled(true);
    gpContextMenu->actions()[1]->setDisabled(true);
#ifdef TARGET_OS_MAC
    //Disabled due to Mac not associating .ini files with text editor
    gpContextMenu->actions()[2]->setDisabled(true);
#endif

    //Create system tray object
#ifdef _WIN32
    giUw16Image = QImage(":/images/TermNotify.ico");
#else
    giUw16Image = QImage(":/images/TermNotify.png");
#endif
    gpUw16Pixmap = new QPixmap(QPixmap::fromImage(giUw16Image));
    gstSysTrayIcon.setIcon(QIcon(*gpUw16Pixmap));
    gstSysTrayIcon.setContextMenu(gpContextMenu);
    gstSysTrayIcon.show();

    //Connect up the context menu
    connect(gpContextMenu, SIGNAL(triggered(QAction*)), this, SLOT(ContextMenuClicked(QAction*)));

    //Connect balloon meesage clicked event
    connect(&gstSysTrayIcon, SIGNAL(messageClicked()), this, SLOT(OpenProgram()));

    //Connect timer
    connect(&gtSerialCheckTimer, SIGNAL(timeout()), this, SLOT(SerialCheck()));

    //Default list
    glPorts.clear();
    gbInitialScan = false;

    //Start the timer
    gtSerialCheckTimer.setInterval(gintScanTime);
    gtSerialCheckTimer.start();
}

//=============================================================================
//=============================================================================
TNMainWindow::~TNMainWindow(
    )
{
    //Disconnect events
    disconnect(this, SLOT(ContextMenuClicked(QAction*)));
    disconnect(this, SLOT(OpenProgram()));
    disconnect(this, SLOT(SerialCheck()));

    //Delete context menu
    delete gpContextMenu;

    //Remove system tray icon
    gstSysTrayIcon.hide();

    //Delete pixmap
    delete gpUw16Pixmap;
}

//=============================================================================
//=============================================================================
void
TNMainWindow::SerialCheck(
    )
{
    //Checks is a new serial device has been detected
    QList<QSerialPortInfo> lSerialPorts = gspiSerialPortInfo.availablePorts();
    QSerialPortInfo spiThisSerialPort;
    if (gbInitialScan == true)
    {
        QList<QString> lTempList;
        lTempList.clear();
        foreach(spiThisSerialPort, lSerialPorts)
        {
            if (glPorts.indexOf(spiThisSerialPort.portName()) == -1)
            {
                //New port!
                gstSysTrayIcon.showMessage("Detected new serial port!", QString("New port; ").append(spiThisSerialPort.portName()).append(". Click to open UwTerminalX!"), QSystemTrayIcon::Information, gintDisplayTime);
                gstrSerialName = spiThisSerialPort.portName();
            }
            lTempList << spiThisSerialPort.portName();
        }
        glPorts = lTempList;
    }
    else
    {
        //Populate initial list
        foreach(spiThisSerialPort, lSerialPorts)
        {
            glPorts << spiThisSerialPort.portName();
        }
        gbInitialScan = true;
    }
}

//=============================================================================
//=============================================================================
void
TNMainWindow::OpenProgram(
    )
{
    //Opens UwTerminalX when clicked
    QString strArguments = QString(gstrArgumentList).replace("%PORT%", gstrSerialName);
    gpTerminalProcess.startDetached(gstrExecutable, strArguments.split(" "));
}

//=============================================================================
//=============================================================================
void
TNMainWindow::ContextMenuClicked(
    QAction *actAction
    )
{
    if (actAction->text() == "Exit")
    {
        //Closes the application
        QApplication::quit();
    }
#ifndef TARGET_OS_MAC
    else if (actAction->text() == "Edit Configuration")
    {
        //Open INI for editing
        QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo("TermNotify.ini").absoluteFilePath()));
    }
#endif
}
