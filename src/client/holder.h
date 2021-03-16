#pragma once

#include "common.h"
#include <raylib.h>


extern void holder_init(int position_x, int position_y);
extern int holder_put(int brick_id, int mouse_x, int mouse_y);
extern void holder_draw();
extern int holder_put_in_free_space(int brick_id);
extern int holder_take_out(int brick_id);
extern std::vector<int> holder_get_bricks();
extern void holder_set_bricks(std::vector<int> br);










