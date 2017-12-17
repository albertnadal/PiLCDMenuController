#include <stdio.h>

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

typedef const struct lcd_menu {
	const char main_title[16];
	const struct menu_node *current_node;
	const struct menu_node *root_node;
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

int main(int argc, char *argv[]) {
	printf("LCDMenu\n\n");
	
	return 0;
}

