/******************************************************************************
** Copyright (C) 2015 LAIRD
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
#ifndef TNMAINWINDOW_H
#define TNMAINWINDOW_H

/******************************************************************************/
// Include Files
/******************************************************************************/
#include <QApplication>
#include <QSerialPortInfo>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QList>
#include <QMenu>
#include <QProcess>
#include <QSettings>
#include <QDesktopServices>
#include <QUrl>
#include <QFileInfo>
#ifdef TARGET_OS_MAC
//QDir needed for Mac OS X
#include <QDir>
#endif

/******************************************************************************/
// Defines
/******************************************************************************/
#define DefaultDisplayTime 5000 //Time in mS to display a balloon message for (OS's can override this value)
#define DefaultScanTime 800 //Time in mS to scan for new devices
#define TermNotifyVer "Version 0.65" //Version string

/******************************************************************************/
// Local Functions or Private Members
/******************************************************************************/
class TNMainWindow : public QObject
{
    Q_OBJECT

public:
    explicit
    TNMainWindow
        (
        QObject *parent = 0
        );
    ~TNMainWindow
        (
        );

private slots:
    void
    SerialCheck
        (
        );
    void
    ContextMenuClicked
        (
        QAction *actAction
        );
    void
    OpenProgram
        (
        );

private:
    QSystemTrayIcon gstSysTrayIcon; //System tray icon
    QTimer gtSerialCheckTimer; //Serial port check timer
    QSerialPortInfo gspiSerialPortInfo; //Serial port information
    QList<QString> glPorts; //List of cached serial ports
    bool gbInitialScan; //True when the initial scan has been completed
    QMenu *gpContextMenu; //Pointer to context menu
    QString gstrSerialName; //Selected serial port name
    QProcess gpTerminalProcess; //Process spawner
    QImage giUw16Image; //Holder for 16x16 icon
    QPixmap *gpUw16Pixmap; //Pointer to pixmap for 16x16 icon
    QString gstrExecutable; //Holds the executable name
    QString gstrArgumentList; //Holds the arguments to be supplied to the executable
    unsigned int gintDisplayTime; //Time (in mS) to display a balloon message for
    unsigned int gintScanTime; //Time (in mS) between each serial port scan
};

#endif // TNMAINWINDOW_H
