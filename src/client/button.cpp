#include "button.h"

static std::unordered_map<std::string, button*> buttons;


void button_draw(std::string id, int x, int y, int width, int height, 
					std::function<void(void)> func){
	
	button* bt;
	if(buttons[id] != nullptr)
		bt = buttons[id];
	else{
		bt = new button;
		memset(bt, 0, sizeof(button));
	}

	
	bt->x = x;
	bt->y = y;
	bt-> width = width;
	bt->height = height;
	bt->func = func;
	if(bt->is_clicked){
		DrawRectangle(x, y, width, height, RED);
		bt->is_clicked = false;
	}else
		DrawRectangle(x, y, width, height, YELLOW);
	
	buttons[id] = bt;

}



void button_update_all(int mouse_x, int mouse_y){
	for(auto& c : buttons) {
		button* bt = c.second;
		if(is_point_in_bound(mouse_x, mouse_y, bt->x, bt->y, bt->width, bt->height)){
			bt->func();
			bt->is_clicked = true;
		}
    }
}
















































