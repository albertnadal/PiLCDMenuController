/*
 *  LCDMenu.c:
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LCDMenu.h"

void move_to_next_option(LCDMenu* lcd_menu) {
  if(lcd_menu->current_node->next_node != NULL) {
    lcd_menu->current_node = lcd_menu->current_node->next_node;
  }
}

void move_to_previous_option(LCDMenu* lcd_menu) {
  if(lcd_menu->current_node->previous_node != NULL) {
    lcd_menu->current_node = lcd_menu->current_node->previous_node;
  }
}

void move_to_parent_option(LCDMenu* lcd_menu) {
  if(lcd_menu->current_node->parent_node != NULL) {
    lcd_menu->current_node = lcd_menu->current_node->parent_node;
  }
}

void move_to_child_option(LCDMenu* lcd_menu) {
  if(lcd_menu->current_node->child_node != NULL) {
    lcd_menu->current_node = lcd_menu->current_node->child_node;
  }
}

void select_current_option(LCDMenu* lcd_menu) {
  if(lcd_menu->current_node->on_select == NULL) {
    return;
  }

  void (*on_select)(void) = lcd_menu->current_node->on_select;

  if(on_select) {
    on_select();
  }
}

void sample_function() {
  printf("HELLO WORLD");
}

MenuNode* init_menu_with_parent_node(MenuOption options[], int parent_option_id, MenuNode* parent_node, int total_options) {

	MenuNode* previous_node = NULL;
	MenuNode* first_node = NULL;

	for(int i=0; i<total_options; i++)
	{
		if(options[i].parent_id == parent_option_id)
		{
			MenuNode *node = malloc(sizeof(MenuNode));

			strcpy(node->title, options[i].title);
			if(previous_node != NULL) {
				previous_node->next_node = node;
			} else if (parent_node != NULL) {
				parent_node->child_node = node;
			} else {
				first_node = node;
			}
      node->next_node = NULL;
			node->previous_node = previous_node;
			node->parent_node = parent_node;
			node->on_select = options[i].on_select;
			previous_node = node;
			init_menu_with_parent_node(options, options[i].id, node, total_options);
		}
	}

	return first_node;
}

void init_menu_with_options(LCDMenu* lcd_menu, MenuOption options[], int total_options) {
	MenuNode* root_node = init_menu_with_parent_node(options, 0, NULL, total_options);
	lcd_menu->root_node = root_node;
	lcd_menu->current_node = root_node;
}

void show_menu(LCDMenu* lcd_menu) {
  MenuNode* current_node = lcd_menu->current_node;
  if(current_node != NULL) {
    printf("%s\n", lcd_menu->title);
    printf("%s\n", current_node->title);
  }
}

LCDMenu* create_empty_menu() {
	LCDMenu *menu = malloc(sizeof(struct lcd_menu));
	menu->title[0] = '\0';
	menu->current_node = NULL;
	menu->root_node = NULL;
	return menu;
}

LCDMenu* create_empty_menu_with_title(char* title) {
  LCDMenu *menu = create_empty_menu();
	strcpy(menu->title, title);
  return menu;
}

unsigned int get_pressed_key() {
  unsigned int ch;
  while(1) {
    ch = getchar();
    if(ch != '\n') {
      return ch;
    }
  }
}

int main(int argc, char *argv[]) {
  UNUSED(argc);
  UNUSED(argv);

  unsigned int key;
  printf("LCDMenu\n\n");
  LCDMenu *menu = create_empty_menu_with_title("Menu principal");

  MenuOption options[3] = {{ .id = 1, .parent_id = 0, .title = "Option A\0", .on_select = NULL },
                           { .id = 2, .parent_id = 0, .title = "Option B\0", .on_select = sample_function },
                           { .id = 3, .parent_id = 1, .title = "Option C\0", .on_select = sample_function }};

  unsigned int total_options = sizeof(options) / sizeof(MenuOption);
  init_menu_with_options(menu, options, total_options);

  while(1) {
    show_menu(menu);
    switch(key = get_pressed_key()) {
      case 119: printf("w\n"); // UP
                move_to_previous_option(menu);
                break;
      case 115: printf("s\n"); // DOWN
                move_to_next_option(menu);
                break;
      case 97:  printf("a\n"); // LEFT
                move_to_parent_option(menu);
                break;
      case 100: printf("d\n"); // RIGHT
                move_to_child_option(menu);
                break;
      case 32:  printf("space\n"); // SPACE
                select_current_option(menu);
                break;

    }

  }

	return 0;
}
