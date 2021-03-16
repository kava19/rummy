#include "bag.h"
#include <algorithm>
#include <raylib.h>

static std::vector<int> bricks;

std::vector<int> bag_get_all_bricks(){
	return bricks;
}

void bag_set_all_bricks(std::vector<int> br){
	bricks = br;
}

void bag_reset(){
	bricks.resize(NUM_OF_BRICKS_IN_GAME);

	for(int i = 0; i < NUM_OF_BRICKS_IN_GAME; ++i){
		bricks[i] = i;
	}
	
	std::random_shuffle(bricks.begin(), bricks.end());
}

void bag_draw_content(int pos_x, int pos_y){
	for(int i = 0; i<bricks.size(); ++i){
		int c = i / 30;
		DrawText(TextFormat("%i", bricks[i]), pos_x + (c * 20), pos_y + ((i-(c*30)) * 10),
			 10, BLACK);
	}
}

void bag_put_back(int brick_id){
	bricks.push_back(brick_id);
}

int bag_get_next_id(){
	if(bricks.size() <= 0)
		return -1;
	int ret = bricks.back();

	bricks.pop_back();

	return ret;
}



























