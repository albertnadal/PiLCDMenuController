#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef const struct menu_option {
        const int id;
        const int parent_id;
	const char title[16];
	void (*on_select)(void);
} MenuOption;

typedef const struct menu_node {
	const char title[16];
        const struct menu_node *next_node;
        const struct menu_node *previous_node;
        const struct menu_node *parent_node;
        const struct menu_node *child_node;
	void (*on_select)(void);
} MenuNode;

typedef struct lcd_menu {
	char title[16];
	struct menu_node *current_node;
	struct menu_node *root_node;
} LCDMenu;

void move_to_next_option(LCDMenu* lcd_menu) {
	
}

void move_to_previous_option(LCDMenu* lcd_menu) {

}

void move_to_parent_option(LCDMenu* lcd_menu) {

}

void move_to_child_option(LCDMenu* lcd_menu) {

}

void select_current_option(LCDMenu* lcd_menu) {

}

void init_menu_with_options(LCDMenu* lcd_menu, MenuOption *options[]) {

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

int main(int argc, char *argv[]) {
	printf("LCDMenu\n\n");
	LCDMenu *menu = create_empty_menu_with_title("Menu principal");

	return 0;
}

