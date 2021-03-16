

#include "holder.h"
#include "brick.h"

static std::vector<int> bricks;
static int pos_x = 0;
static int pos_y = 0;
static int width = HOLDER_WIDTH * BRICK_WIDTH;
static int height = HOLDER_HEIGHT * BRICK_HEIGHT;


std::vector<int> holder_get_bricks(){
	return bricks;
}

void holder_set_bricks(std::vector<int> br){
	bricks = br;
}

void holder_init(int position_x, int position_y){
	pos_x = position_x;
	pos_y = position_y;
	bricks.resize(HOLDER_CAPACITY);
	std::fill(bricks.begin(), bricks.end(), -1);
}

void holder_draw(){
	for(int h = 0; h < HOLDER_HEIGHT; ++h){
		for(int w = 0; w < HOLDER_WIDTH; ++w){
			DrawRectangleLines(pos_x + (w * BRICK_WIDTH), pos_y + (h * BRICK_HEIGHT),
								 BRICK_WIDTH, BRICK_HEIGHT, BLACK);		

		}
	}	

}

int holder_put_in_free_space(int brick_id){
	for(int i = 0; i < HOLDER_CAPACITY; ++i){
		if(bricks[i] == -1){
			bricks[i] = brick_id;
			brick br = brick_get_by_id(brick_id);
		
			int tile_y = i / HOLDER_WIDTH;
			int tile_x = i - (tile_y * HOLDER_WIDTH); 	

			br.x = (tile_x * BRICK_WIDTH) + pos_x;	
			br.y = (tile_y * BRICK_HEIGHT) + pos_y;
		
			brick_update(brick_id, br);

			return i;
		}
	}

	return -1;
}

int holder_take_out(int brick_id){
	for(int i = 0; i < HOLDER_CAPACITY; ++i){
		if(bricks[i] == -1 || bricks[i] != brick_id)
			continue;
		else{
			bricks[i] = -1;
			return brick_id;
		}
	}
	return -1;
}

int holder_put(int brick_id, int mouse_x, int mouse_y){
	if(!is_point_in_bound(mouse_x, mouse_y, pos_x, pos_y, width, height)){
		printf("CANNOT PUT OF BOUND OF HOLDER\n");	
	return -1;
	}

	int local_x = mouse_x - pos_x;
	int local_y = mouse_y - pos_y;
	
	int tile_x = local_x / BRICK_WIDTH;
	int tile_y = local_y / BRICK_HEIGHT;
	
	printf("MOUSE(%ix%i), LOCAL(%ix%i), TILE(%ix%i)\n", 
			mouse_x, mouse_y, local_x, local_y, tile_x, tile_y);

	if(bricks[(tile_y * HOLDER_WIDTH) + tile_x] == -1){
		bricks[(tile_y * HOLDER_WIDTH) + tile_x] = brick_id;
		brick br = brick_get_by_id(brick_id);
	
		br.x = (tile_x * BRICK_WIDTH) + pos_x;	
		br.y = (tile_y * BRICK_HEIGHT) + pos_y;
		
		brick_update(brick_id, br);

		return (tile_y * HOLDER_WIDTH) + tile_x;		
	}
	printf("CANNOT PUY IN ALREADY TAKEN SPACE\n");
	printf("HOLDER SAPCE: ");
	for(int i = 0; i < HOLDER_CAPACITY; ++i){
		printf("%i,", bricks[i]);
	}
	printf("\n");
	return -1;
}
























