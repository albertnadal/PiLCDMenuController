/*
 *  LCDMenu.h:
 *	Controllable text menu to use with standard 16x2 LCD screen
 *  and Joystick on Raspberry Pi devices.
 *	This is designed to drive the parallel interface LCD drivers
 *	based in the Hitachi HD44780U controller and compatables.
 *
 * Copyright (c) 2018 Albert Nadal Garriga.
 ***********************************************************************
 *  This file is part of PiLCDMenuController:
 *	https://github.com/albertnadal/PiLCDMenuController
 *
 *    PiLCDMenuController is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    PiLCDMenuController is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with PiLCDMenuController.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */

#ifdef __cplusplus
extern "C" {
#endif

#define UNUSED(x) (void)(x)

typedef const struct menu_option {
  const int id;
  const int parent_id;
	const char title[16];
	void (*on_select)(void);
} MenuOption;

typedef struct menu_node {
  char title[16];
  struct menu_node *next_node;
  struct menu_node *previous_node;
  struct menu_node *parent_node;
  struct menu_node *child_node;
	void (*on_select)(void);
} MenuNode;

typedef struct lcd_menu {
	char title[16];
	struct menu_node *current_node;
	struct menu_node *root_node;
} LCDMenu;

extern void move_to_next_option(LCDMenu* lcd_menu);
extern void move_to_previous_option(LCDMenu* lcd_menu);
extern void move_to_parent_option(LCDMenu* lcd_menu);
extern void move_to_child_option(LCDMenu* lcd_menu);
extern void select_current_option(LCDMenu* lcd_menu);
extern void init_menu_with_options(LCDMenu* lcd_menu, MenuOption options[], int total_options);
extern LCDMenu* create_empty_menu();
extern LCDMenu* create_empty_menu_with_title(char* title);
extern void show_menu(LCDMenu* lcd_menu);

#ifdef __cplusplus
}
#endif
