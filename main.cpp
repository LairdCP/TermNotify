/******************************************************************************
** Copyright (C) 2014-2015 Ezurio Ltd
**
** Project: TermNotify
**
** Module: mainwindow.cpp
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
#include "mainwindow.h"
#include <QApplication>

/******************************************************************************/
// Local Functions or Private Members
/******************************************************************************/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow MySerial;
//    MainWindow w;

    return a.exec();
}
