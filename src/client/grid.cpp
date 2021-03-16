#include "grid.h"
#include "brick.h"



static std::vector<int> bricks;
static int pos_x = 0;
static int pos_y = 0;
static int width = GRID_WIDTH * BRICK_WIDTH;
static int height = GRID_HEIGHT * BRICK_HEIGHT;

pair::pair(){}
pair::~pair(){}

std::vector<int> grid_get_bricks(){
	return bricks;
}

void grid_set_bricks(std::vector<int> br){
	bricks = br;
}

bool pair::check(){
	int len = brick_ids.size();

	if(len < 3)
		return false;

	for(int i = 0; i < len; ++i){
		bricks.push_back(brick_get_by_id(brick_ids[i]));
	}

	std::vector<int> colors;
	std::vector<int> numbers;

	bool same_color = false;
	bool same_number = false;

	for(int i = 0; i < len; ++i){
		colors.push_back(bricks[i].color_id);
		numbers.push_back(bricks[i].number);
	}	

	if (std::adjacent_find( colors.begin(), colors.end(), 
		std::not_equal_to<>() ) == colors.end()){
    	same_color = true;
	}

	
	if (std::adjacent_find( numbers.begin(), numbers.end(), 
		std::not_equal_to<>() ) == numbers.end()){
    	same_number = true;
	}

	if(same_color == true && same_number == false){		
		for(int i = 0; i < len; ++i){
			if(numbers[i] - i != numbers[0])
				return false;
		}
		return true;
	}
	
	if(same_color == false && same_number == true && len <= 4){
		std::sort(colors.begin(), colors.end());
		colors.erase(std::unique(colors.begin(), colors.end() ), colors.end());
		if(colors.size() != len)
			return false;
		return true;
	}

	return false;
}

bool grid_check_pairs(){
	std::vector<std::shared_ptr<pair>> pairs;
	
	for(int h = 0; h < GRID_HEIGHT; ++h){
		std::shared_ptr<pair> one_pair = nullptr;
		for(int w = 0; w < GRID_WIDTH; ++w){
			int br_id = bricks[(h*GRID_WIDTH) + w];
			if(br_id == -1){
				if(one_pair != nullptr){
					pairs.push_back(one_pair);
					one_pair = nullptr;
				}
			}	
			else{
				if(one_pair == nullptr)
					one_pair = std::make_shared<pair>();
				one_pair->brick_ids.push_back(br_id);
			}	
		}
		if(one_pair != nullptr)
			pairs.push_back(one_pair);
	}

	bool valid = true;
	for(int p = 0; p < pairs.size(); ++p){
		if(!pairs[p]->check())
			valid = false;
	}

	
	for(int i = 0; i < pairs.size(); ++i){
		printf("PAIR(%i) = ", i);
		for(int j = 0; j < pairs[i]->brick_ids.size(); ++j){
			printf("%i, ", pairs[i]->brick_ids[j]);
		}
		if(pairs[i]->check())
			printf(" VALID");
		else
			printf(" NOT VALID");
		printf("\n");
	}

	return valid;
}

void grid_draw(){
	for(int y = 0; y < GRID_HEIGHT; ++y){
		for(int x = 0; x < GRID_WIDTH; ++x){
			DrawRectangleLines(pos_x + (x*BRICK_WIDTH), pos_y + (y*BRICK_HEIGHT),
							 BRICK_WIDTH, BRICK_HEIGHT, BLACK);
		}
	}
}


void grid_init(int position_x, int position_y){
	pos_x = position_x;
	pos_y = position_y;
	bricks.resize(GRID_CAPACITY);
	std::fill(bricks.begin(), bricks.end(), -1);
}

int grid_take_out(int brick_id){
	for(int i = 0; i < GRID_CAPACITY; ++i){
		if(bricks[i] == -1 || bricks[i] != brick_id)
			continue;
		else{
			bricks[i] = -1;
			return brick_id;
		}
	}
	return -1;
}

int grid_put(int brick_id, int mouse_x, int mouse_y){
	if(!is_point_in_bound(mouse_x, mouse_y, pos_x, pos_y, width, height)){
	return -1;
	}

	int local_x = mouse_x - pos_x;
	int local_y = mouse_y - pos_y;
	
	int tile_x = local_x / BRICK_WIDTH;
	int tile_y = local_y / BRICK_HEIGHT;
	
	printf("MOUSE(%ix%i), LOCAL(%ix%i), TILE(%ix%i)\n", 
			mouse_x, mouse_y, local_x, local_y, tile_x, tile_y);

	if(bricks[(tile_y * GRID_WIDTH) + tile_x] == -1){
		bricks[(tile_y * GRID_WIDTH) + tile_x] = brick_id;
		brick br = brick_get_by_id(brick_id);
	
		br.x = (tile_x * BRICK_WIDTH) + pos_x;	
		br.y = (tile_y * BRICK_HEIGHT) + pos_y;
		
		brick_update(brick_id, br);

		return (tile_y * GRID_WIDTH) + tile_x;		
	}
	printf("CANNOT PUT IN ALREADY TAKEN SPACE\n");
	printf("GRID SAPCE: ");
	for(int i = 0; i < GRID_CAPACITY; ++i){
		printf("%i,", bricks[i]);
	}
	printf("\n");
	return -1;
}

























