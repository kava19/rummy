#pragma once

#include "common.h"
#include <raylib.h>


struct button{
	int x, y;
	int width, height;
	std::function<void(void)> func;
	
	bool is_clicked;
};

void button_draw(std::string id, int x, int y, int width, int height, 
					std::function<void(void)> func);
void button_update_all(int mouse_x, int mouse_y);
































