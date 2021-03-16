#pragma once

#include "common.h"
#include <raylib.h>

struct brick{
	int number;
	int color_id;
	int x, y;
};



extern int brick_get_id_by_pos(int x, int y);
extern brick brick_get_by_id(int id);
extern void brick_update(int id, brick br);

extern void brick_draw_all();
extern void brick_generate_all();
extern void brick_draw(brick br);




















