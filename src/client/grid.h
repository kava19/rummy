#pragma once 

#include "common.h"
#include <raylib.h>
#include "brick.h"

class pair{
public:
	pair();
	~pair();

	std::vector<int> brick_ids;
	std::vector<brick> bricks;
	
	bool check();

};

extern void grid_init(int position_x, int position_y);
extern void grid_draw();

extern int grid_put(int brick_id, int mouse_x, int mouse_y);
extern int grid_take_out(int brick_id);

extern bool grid_check_pairs();

extern std::vector<int> grid_get_bricks();
extern void grid_set_bricks(std::vector<int> br);

























