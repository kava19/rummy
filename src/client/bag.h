#pragma once

#include "common.h"


extern void bag_reset();
extern int bag_get_next_id();
extern void bag_draw_content(int pos_x, int pos_y);
extern void bag_put_back(int brick_id);
extern std::vector<int> bag_get_all_bricks();
extern void bag_set_all_bricks(std::vector<int> br);














