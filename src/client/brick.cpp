
#include "brick.h"

brick brick_conteiner[NUM_OF_BRICKS_IN_GAME] = {0};

Color brick_color_id_to_color(int id){
	if(id == 0) return BLUE;
	if(id == 1) return RED;
	if(id == 2) return ORANGE;
	if(id == 3) return BLACK;
	return YELLOW;
}


void brick_draw(brick br){
	DrawRectangle(br.x, br.y, BRICK_WIDTH, BRICK_HEIGHT, LIGHTGRAY);
	if(br.number <= 8){	
		DrawText(TextFormat("%01i", br.number + 1), br.x + 20, br.y + 20, 50, 
			brick_color_id_to_color(br.color_id));
		}
	else{		
		DrawText(TextFormat("%02i", br.number + 1), br.x + 10, br.y + 20, 50, 
			brick_color_id_to_color(br.color_id) );
		}
}

void brick_draw_all(){
	for(int c = 0; c < 8; ++c){
		for(int b = 0; b < 13; ++b){
			brick_draw(brick_conteiner[(c*13) + b]);
		}
	}
}



void brick_generate_all(){
	for(int t = 0; t < 2; ++t){
		for(int c = 0; c < 4; ++c){
			for(int n = 0; n < 13; ++n){
				int act_brick = ((c*13)+n) + (t*13*4); 				
				brick_conteiner[act_brick].number = n;
				brick_conteiner[act_brick].color_id = c;
				//brick_conteiner[act_brick].x = (n*(BRICK_WIDTH + 5)); 
				//brick_conteiner[act_brick].y = ((c+(t*4))*(BRICK_HEIGHT + 5));
				brick_conteiner[act_brick].x = -100;
				brick_conteiner[act_brick].y = -100;		
			}	
		}
	}	
}


int brick_get_id_by_pos(int x, int y){
	for(int b = 0; b < NUM_OF_BRICKS_IN_GAME; ++b){
		if(is_point_in_bound(x, y, brick_conteiner[b].x, brick_conteiner[b].y, BRICK_WIDTH, BRICK_HEIGHT))
			return b;	
	}
	
	return -1;
}

brick brick_get_by_id(int id){
	return brick_conteiner[id];
}

void brick_update(int id, brick br){
	brick_conteiner[id] = br;
}












