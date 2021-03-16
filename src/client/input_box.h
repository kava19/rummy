#pragma once
#include "common.h"
#include <raylib.h>

const int MAX_CHAR_IN_INPUT_BOX = 32;

class input_box{
public:
	input_box(int px, int py, int pw, int ph);
	~input_box();
	

	std::string get_input();	
	
	void update();
	void draw();


	char data[MAX_CHAR_IN_INPUT_BOX];
	int char_count;
	Rectangle rect;
	bool is_mouse_over;
	int frames_passed;
};







