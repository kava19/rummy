#include "state.h"

#include "brick.h"
#include "grid.h"
#include "holder.h"


static std::vector<int> holder_data;
static std::vector<int> grid_data;
static std::vector<brick> brick_data;

void state_save(){
	holder_data = holder_get_bricks();
	grid_data = grid_get_bricks();

	brick_data.clear();
	for(int i = 0; i < NUM_OF_BRICKS_IN_GAME; ++i){
		brick br = brick_get_by_id(i);
		brick_data.push_back(br);
	}
}


void state_restore(){
	holder_set_bricks(holder_data);
	grid_set_bricks(grid_data);

	
	for(int i = 0; i < NUM_OF_BRICKS_IN_GAME; ++i){
		brick_update(i, brick_data[i]);
	}
}




























