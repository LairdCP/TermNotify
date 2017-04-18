# Laird TermNotify

## About

TermNotify is a companian application for [UwTerminalX](https://github.com/LairdCP/UwTerminalX) (it can also be used with any other application by editing the ini file) which will alert you to new serial ports being added to the computer and allow you to launch a new UwTerminalX (or other program) instance if needed.

## Downloading

Pre-compiled builds can be found by clicking the [Releases](https://github.com/LairdCP/TermNotify/releases) tab on Github, builds are available for Linux (32 bit build), Mac and Windows (32 bit build).

## Setup

### Windows

Download the zip and extract the executable file to the folder where UwTerminalX was extracted then simply run the TermNotify executable and plug in a USB-Serial device or module, then click the notification when it shows to open a new UwTerminalX instance.

### Mac

Download the dmg disk image and mount it, then copy the TermNotify application to the same folder where UwTerminalX is installed. Simple double click TermNotify to run the application and plug in a USB-Serial device or module, then click the notification when it shows to open a new UwTerminalX instance.

### Linux

Download the tar and extract the executable file to the folder where UwTerminalX was extracted then simply run the TermNotify executable either by double clicking and selecting 'run' or executing it from a terminal and plug in a USB-Serial device or module, then click the notification when it shows to open a new UwTerminalX instance.

Extracting the archive can either be done in the GUI or by using a terminal:

	tar xf TermNotify.tar ~/

Executing TermNotify from a terminal can be achieved using:

	./TermNotify

## Compiling

Compiling TermNotify is a similar process to compiling UwTerminalX, please refer to the [UwTerminalX compilation wiki page](https://github.com/LairdCP/UwTerminalX/wiki/Compiling), replacing the UwTerminalX source code tree with the TermNotify source code tree.

## License

TermNotify is released under the [GPLv3 license](https://github.com/LairdCP/TermNotify/blob/master/LICENSE).