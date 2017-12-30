PiLCDmenuController
==================

A controllable text menu to use with standard 16x2 LCD and Joystick on Raspberry Pi devices.

Features
========

A menu driven application template for 16x2LCD on a Raspberry Pi.

It provides a simple way to navigate a nested set of textual menus, and run specific user functions on select menu options,
by pressing joystick buttons connected to the GPIO pins. Allows the user to select from a large list of choices, by cycling
through options vertically.


Install
=======

The easiest way is to use the supplied 'build' script:

```
./build
```

that will compile the source code and all third party dependencies and then install the libraries and headers for you.

To un-install PiLCDmenuController:

```
./build uninstall
```

Usage
=====

To compile programs with PiLCDMenuController, you need to add:
    -lpiLCDMenuController
to your compile line(s).
 
