#include "grab.h"
#include "grid.h"
#include "holder.h"

brick grabbed_brick;
int grabbed_id = -1;
int origin_x = -100;
int origin_y = -100;


void grab(){
	Vector2 m_pos = GetMousePosition();

	grabbed_id = brick_get_id_by_pos(m_pos.x, m_pos.y);
	if(grabbed_id == -1) return;

	holder_take_out(grabbed_id);
	grid_take_out(grabbed_id);
	
	grabbed_brick = brick_get_by_id(grabbed_id);
	origin_x = grabbed_brick.x;
	origin_y = grabbed_brick.y;
}

void update(){
	if(grabbed_id == -1)
		return;
	
	Vector2 m_pos = GetMousePosition();

	grabbed_brick.x = m_pos.x - (BRICK_WIDTH / 2);
	grabbed_brick.y = m_pos.y - (BRICK_HEIGHT / 2);

	brick_update(grabbed_id, grabbed_brick);
	brick_draw(grabbed_brick);
}

void put_grabbed_back_to_origin(){
	grabbed_brick.x = origin_x;
	grabbed_brick.y = origin_y;
	origin_x = -100;
	origin_y = -100;
	brick_update(grabbed_id, grabbed_brick);
	if(holder_put(grabbed_id, grabbed_brick.x, grabbed_brick.y) == -1){
		printf("CANNOT PUT BACK TO ORIGIN HOLDER\n");
	}
	if(grid_put(grabbed_id, grabbed_brick.x, grabbed_brick.y) == -1){
		printf("CANNOT PUT BACK TO ORIGIN GRID\n");
	}
}

void release(){
	if(grabbed_id == -1)
		return;
	update();

	if(holder_put(grabbed_id, GetMousePosition().x, GetMousePosition().y) == -1
		&& grid_put(grabbed_id, GetMousePosition().x, GetMousePosition().y) == -1){
		put_grabbed_back_to_origin();
	}

	grabbed_id = -1;
}




void grab_update(){
	if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		grab();
	if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		update();
	if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		release();

}































