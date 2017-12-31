# Makefile
#       Simple PiLCDMenuController build and install script
#
#       Copyright (c) 2017-2018 Albert Nadal Garriga
#################################################################################
# This file is part of PiLCDMenuController:
#       A controllable text menu to run with a standard 16x2 LCD and a Joystick on
#       Raspberry Pi devices
#
#    PiLCDMenuController is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    PiLCDMenuController is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public License
#    along with PiLCDMenuController.  If not, see <http://www.gnu.org/licenses/>.
#################################################################################

VERSION=$(shell cat ./VERSION)
DESTDIR?=/usr
PREFIX?=/local

LDCONFIG?=ldconfig

ifneq ($V,1)
Q ?= @
endif

STATIC=libpiLCDMenuController.a
DYNAMIC=libpiLCDMenuController.so.$(VERSION)

#DEBUG	= -g -O0
DEBUG	= -O3
CC	= gcc
INCLUDE	= -I. -I./third_parties/wiringPi/include
DEFS	= -D_GNU_SOURCE
LIBS_PATH = -L./third_parties/wiringPi/lib
CFLAGS	= $(DEBUG) $(DEFS) -std=c99 -Wformat=2 -Wall -Wextra -Winline -Wunused-function $(INCLUDE) -pipe -fPIC

LIBS    = -lwiringPi -lwiringPiDev

###############################################################################

SRC	=	LCDMenu.c

HEADERS =	$(shell ls *.h)

OBJ	=	$(SRC:.c=.o)

all:		$(DYNAMIC)

static:		$(STATIC)

lcdmenu:	LCDMenu.o
	$Q echo "[Building Executable]"
	$Q $(CC) -o $@ LCDMenu.o $(LIBS_PATH) $(LIBS)

$(STATIC):	$(OBJ)
	$Q echo "[Link (Static)]"
	$Q ar rcs $(STATIC) $(OBJ)
	$Q ranlib $(STATIC)
#	@size   $(STATIC)

$(DYNAMIC):	$(OBJ)
	$Q echo "[Link (Dynamic)]"
	$Q $(CC) -shared -Wl,-soname,libpiLCDMenuController.so -o libpiLCDMenuController.so.$(VERSION) $(LIBS_PATH) $(LIBS) $(OBJ)

.c.o:
	$Q echo [Compile] $<
	$Q $(CC) -c $(CFLAGS) $< -o $@

.PHONY:	clean
clean:
	$Q echo "[Clean]"
	$Q rm -f $(OBJ) $(OBJ_I2C) *~ core tags Makefile.bak lcdmenu libpiLCDMenuController.* ./lib/libpiLCDMenuController.*

.PHONY:	tags
tags:	$(SRC)
	$Q echo [ctags]
	$Q ctags $(SRC)

.PHONY: copy-files
copy-files:	$(DYNAMIC)
	$Q echo "[Copy Headers]"
	$Q install -m 0755 -d							./include
	$Q install -m 0644 $(HEADERS)						./include
	$Q echo "[Copy Dynamic Lib]"
	$Q install -m 0755 -d							./lib
	$Q install -m 0755 libpiLCDMenuController.so.$(VERSION)			./lib/libpiLCDMenuController.so.$(VERSION)
	$Q echo "[Copy Static Lib]"
	$Q install -m 0755 libpiLCDMenuController.a				./lib/libpiLCDMenuController.a
	$Q rm -rf libpiLCDMenuController.*

.PHONY:	install
install:	$(DYNAMIC)
	$Q echo "[Install Headers]"
	$Q install -m 0755 -d							$(DESTDIR)$(PREFIX)/include
	$Q install -m 0644 $(HEADERS)						$(DESTDIR)$(PREFIX)/include
	$Q echo "[Install Dynamic Lib]"
	$Q install -m 0755 -d							$(DESTDIR)$(PREFIX)/lib
	$Q install -m 0755 libpiLCDMenuController.so.$(VERSION)			$(DESTDIR)$(PREFIX)/lib/libpiLCDMenuController.so.$(VERSION)
	$Q ln -sf $(DESTDIR)$(PREFIX)/lib/libpiLCDMenuController.so.$(VERSION)	$(DESTDIR)/lib/libpiLCDMenuController.so
	$Q $(LDCONFIG)

.PHONY:	install-static
install-static:	$(STATIC)
	$Q echo "[Install Headers]"
	$Q install -m 0755 -d							$(DESTDIR)$(PREFIX)/include
	$Q install -m 0644 $(HEADERS)						$(DESTDIR)$(PREFIX)/include
	$Q echo "[Install Static Lib]"
	$Q install -m 0755 -d							$(DESTDIR)$(PREFIX)/lib
	$Q install -m 0755 libpiLCDMenuController.a				$(DESTDIR)$(PREFIX)/lib

.PHONY:	uninstall
uninstall:
	$Q echo "[UnInstall]"
	$Q cd $(DESTDIR)$(PREFIX)/include/ && rm -f $(HEADERS)
	$Q cd $(DESTDIR)$(PREFIX)/lib/     && rm -f libpiLCDMenuController.*
	$Q $(LDCONFIG)


.PHONY:	depend
depend:
	makedepend -Y $(SRC) $(SRC_I2C)

# DO NOT DELETE

LCDMenu.o: LCDMenu.h

