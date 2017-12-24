#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_OPTIONS 3

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

}

MenuNode* init_menu_with_parent_node(MenuOption options[], int parent_option_id, MenuNode* parent_node) {

	MenuNode* previous_node = NULL;
	MenuNode* first_node = NULL;

	for(int i=0; i<TOTAL_OPTIONS; i++)
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
			init_menu_with_parent_node(options, options[i].id, node);
		}
	}

	return first_node;
}

void init_menu_with_options(LCDMenu* lcd_menu, MenuOption options[]) {
	MenuNode* root_node = init_menu_with_parent_node(options, 0, NULL);
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
  unsigned int key;
	printf("LCDMenu\n\n");
	LCDMenu *menu = create_empty_menu_with_title("Menu principal");

	MenuOption options[TOTAL_OPTIONS] = {{ .id = 1, .parent_id = 0, .title = "Option A\0", .on_select = NULL },
				 	     { .id = 2, .parent_id = 0, .title = "Option B\0", .on_select = NULL },
				 	     { .id = 3, .parent_id = 1, .title = "Option C\0", .on_select = NULL }};

	init_menu_with_options(menu, options);

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
