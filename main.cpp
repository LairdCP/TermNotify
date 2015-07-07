/******************************************************************************
** Copyright (C) 2015 Laird
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
#include "TNMainWindow.h"
#include <QApplication>

/******************************************************************************/
// Local Functions or Private Members
/******************************************************************************/
int
main(
    int argc,
    char *argv[]
    )
{
    //Construct the application
    QApplication a(argc, argv);

    //Create the TermNotify class
    TNMainWindow TermSerialApp;

    //Execute the program
    return a.exec();
}
