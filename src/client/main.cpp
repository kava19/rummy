#include "raylib.h"
#include "common.h"

#include "brick.h"
#include "grid.h"
#include "grab.h"
#include "holder.h"
#include "bag.h"
#include "state.h"
#include "button.h"
#include "conn.h"
#include "input_box.h"

input_box *ib;
bool is_first_player;
bool is_game_screen = false;
bool is_my_turn = false;

void create_window(int width, int height, std::string title, int fps){
    InitWindow(width, height, title.c_str());
    SetTargetFPS(fps);
}


void add_brick_callback(){
	printf("Clicked!\n");
}

void loop_game_screen(){
	BeginDrawing();
	ClearBackground(RAYWHITE);
	
	brick_draw_all();

	if(is_my_turn)grab_update();

	holder_draw();
	grid_draw();	

	DrawText(TextFormat("%i", brick_get_id_by_pos(GetMousePosition().x, GetMousePosition().y)), 10, 10, 15, BLACK);	
	bag_draw_content(10, 30);

	if(is_my_turn)button_draw("Add brick", 10, 10, 50, 50, add_brick_callback);

    EndDrawing();

	if(is_my_turn){
	if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
		button_update_all(GetMousePosition().x, GetMousePosition().y);
	}
	if(IsKeyPressed(KEY_S)){
		state_save();
	}
	if(IsKeyPressed(KEY_R)){
		state_restore();
	}
	if(IsKeyPressed(KEY_C)){
		if(!grid_check_pairs())
			state_restore();
		else{
			state_save();
			
		}
	}
	if(IsKeyPressed(KEY_N)){
		int n_id = bag_get_next_id();
		if(holder_put_in_free_space(n_id) == -1)
			bag_put_back(n_id);
		state_save();
	}
	}
}
void begin_game_screen();
void loop_login_screen(){
	ib->update();

	if(IsKeyPressed(KEY_ENTER)){
		if(connect_to_server(50000) != -1){
			std::string users = server_get_users_connected();
			std::string user1;
			std::string user2;

			user1 = users.substr(0, users.find(":"));
			user2 = users.substr(users.find(":") + 1, users.size() - user1.size());

			printf("1: '%s', 2: '%s'\n", user1.c_str(), user2.c_str());

			
			if(user1 == "EMPT"){
				server_enter_room(ib->get_input());
				is_first_player = true;
				is_my_turn = true;
			}
			else if(user2 == "EMPT"){
				server_enter_room(ib->get_input());
				is_first_player = false;
			}
			else{
				printf("SERVER IS FULL\n");
			}

			begin_game_screen();
			is_game_screen = true;
		}	
	}	

	BeginDrawing();
	ClearBackground(RAYWHITE);

	ib->draw();

	EndDrawing();
}

void begin_game_screen(){

	brick_generate_all();
	bag_reset();

	if(is_first_player){
		std::string bag_content = "SETB";
		std::vector<int> bagc = bag_get_all_bricks();
		for(int i = 0; i < NUM_OF_BRICKS_IN_GAME; ++i){
			bag_content.append(std::to_string(bagc[i]));
			bag_content.append(":");		
		}
		server_send(bag_content);
	}
	else{
		std::string bag_content = server_chck();
		printf("BAG CONTENT RECIVED: '%s'\n", bag_content.c_str());
	}
	

	holder_init((SCREEN_WIDTH - (BRICK_WIDTH * HOLDER_WIDTH)) / 2, SCREEN_HEIGHT - (BRICK_HEIGHT * HOLDER_HEIGHT));
	grid_init((SCREEN_WIDTH - (BRICK_WIDTH * GRID_WIDTH)) / 2, 0);
	for(int i = 0; i < NUM_OF_BRICKS_AT_START; ++i){
		holder_put_in_free_space(bag_get_next_id());
	}

}

void begin_login_screen(){
	ib = new input_box(SCREEN_WIDTH/2 - 100, 180, 225, 50);
}

void loop(){
    while (!WindowShouldClose())    {
		if(!is_game_screen)loop_login_screen();
		else loop_game_screen();
		
    }
}

int main(void)
{
	create_window(SCREEN_WIDTH, SCREEN_HEIGHT, "Rummy", 60);
	begin_login_screen();

	
	loop();
    CloseWindow();
    return 0;
}








