#include "input_box.h"


input_box::input_box(int px, int py, int pw, int ph){
	rect = {px, py, pw, ph};
	memset(data, 0, sizeof(char)*MAX_CHAR_IN_INPUT_BOX);
	char_count = 0;
	is_mouse_over = false;
	frames_passed = 0;
}

input_box::~input_box(){


}

std::string input_box::get_input(){
	return std::string(data);
}

void input_box::update(){
		is_mouse_over = CheckCollisionPointRec(GetMousePosition(), rect);
        if (is_mouse_over)
        {
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            int key = GetCharPressed();

            while (key > 0)
            {
                if ((key >= 32) && (key <= 125) && (char_count < MAX_CHAR_IN_INPUT_BOX - 1))
                {
                    data[char_count] = (char)key;
                    char_count++;
                }
                
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                char_count--;
                if (char_count < 0) char_count = 0;
                data[char_count] = '\0';
            }
        }
        else if (GetMouseCursor() != MOUSE_CURSOR_DEFAULT) SetMouseCursor(MOUSE_CURSOR_DEFAULT);
		if(is_mouse_over) frames_passed++;
		else frames_passed = 0;
}

void input_box::draw(){


            DrawText("ENTER YOUR NAME!", rect.x, 140, 20, GRAY);

            DrawRectangleRec(rect, LIGHTGRAY);
            if (is_mouse_over) DrawRectangleLines(rect.x, rect.y, rect.width, rect.height, RED);
            else DrawRectangleLines(rect.x, rect.y, rect.width, rect.height, DARKGRAY);

            DrawText(data, rect.x + 5, rect.y + 8, 40, MAROON);

            DrawText(TextFormat("INPUT CHARS: %i/%i", char_count, MAX_CHAR_IN_INPUT_BOX), rect.x, 250, 20, DARKGRAY);

            if (is_mouse_over)
            {
                if (char_count < MAX_CHAR_IN_INPUT_BOX)
                {
                    if (((frames_passed/20)%2) == 0) DrawText("_", rect.x + 8 + MeasureText(data, 40), 
															rect.y + 12, 40, MAROON);
                }
                else DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
            }
}













