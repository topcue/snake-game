#include "GateHandler.h"

extern Map *map;
extern Snake *snake;

Gate pair_gate;

GateHandler::GateHandler() {
	NULL;
}

GateHandler::~GateHandler() {
	NULL;
}

void GateHandler::Update(float tic) {
	if(is_in_use) {
		if(IsExitGate()) {
			DeleteGate();
			SpawnGate(tic);
			is_in_use = false;
		}
		return;
	}
	if (tic - last_drop_time < DROP_GATE_INTERVAL) {
		return;
	}
	if (is_created) {
		DeleteGate();
	} else {
		SpawnGate(tic);
	}	
}

void GateHandler::Render() {
	NULL;
}

Position GateHandler::GetRandomPosition() {
	while (true) {
		int x = rand() % WIDTH;
		int y = rand() % HEIGHT;
		if (map->GetBlock(x, y) == BLOCK_WALL) {
			return Position(x, y);
		}
	}
}

Gate GateHandler::GetGatePair() {
	int pair_x, pair_y;
	char direction;
	bool is_left_space = false;
	bool is_right_space = false;
	bool is_up_space = false;
	bool is_down_space = false;

	Gate gate = gate_a;
	if(gate.ComparePosition(snake->GetHead().x, snake->GetHead().y)) {
		pair_x = gate_b.X();
		pair_y = gate_b.Y();
	} else {
		pair_x = gate_a.X();
		pair_y = gate_a.Y();
	}

	if (map->GetBlock(pair_x, pair_y + 1) == BLOCK_SPACE) {
		is_down_space = true;
	} if (map->GetBlock(pair_x + 1, pair_y) == BLOCK_SPACE) {
		is_right_space = true;
	} if (map->GetBlock(pair_x, pair_y - 1) == BLOCK_SPACE) {
		is_up_space = true;
	} if (map->GetBlock(pair_x - 1, pair_y) == BLOCK_SPACE) {
		is_left_space = true;
	}
	
	direction = snake->direction;
	if (is_left_space && (direction == DIR_LEFT)) {
		pair_x -= 1;
	} else if (is_right_space && (direction == DIR_RIGHT)) {
		pair_x += 1;
	} else if (is_up_space && (direction == DIR_UP)) {
		pair_y -= 1;
	} else if (is_down_space && (direction == DIR_DOWN)) {
		pair_y += 1;
	}
	
	else if (direction == DIR_UP || direction == DIR_DOWN) {
		if (is_left_space){
			pair_x -= 1;
			snake->SetDirection(DIR_LEFT);
		} else if (is_right_space) {
			pair_x += 1;
			snake->SetDirection(DIR_RIGHT);
		} else if (is_up_space) {
			pair_y -= 1;
			snake->SetDirection(DIR_UP);
		} else if (is_down_space) {
			pair_y += 1;
			snake->SetDirection(DIR_DOWN);
		}
	} else if (direction == DIR_LEFT || direction == DIR_RIGHT) {
		if (is_down_space) {
			pair_y += 1;
			snake->SetDirection(DIR_DOWN);
		} else if (is_up_space) {
			pair_y -= 1;
			snake->SetDirection(DIR_UP);
		} else if (is_left_space) {
			pair_x -= 1;
			snake->SetDirection(DIR_LEFT);
		} else if (is_right_space) {
			pair_x += 1;
			snake->SetDirection(DIR_RIGHT);
		}
	}
	pair_gate.SetPosition(pair_x, pair_y);

	return pair_gate;
}

void GateHandler::SpawnGate(float tic) {
	Gate gate_a_tmp(GetRandomPosition());
	Gate gate_b_tmp(GetRandomPosition());
	
	gate_a = gate_a_tmp;
	gate_b = gate_b_tmp;
	
	ApplyBlock();
	ApplyBlock();

	last_drop_time = tic;
	is_created = true;
}

void GateHandler::DeleteGate() {
	map->SetBlock(gate_a.GetPosition(), BLOCK_WALL);
	map->SetBlock(gate_b.GetPosition(), BLOCK_WALL);

	is_created = false;
}

void GateHandler::ApplyBlock() {
	map->SetBlock(gate_a.GetPosition(), BLOCK_GATE);
	map->SetBlock(gate_b.GetPosition(), BLOCK_GATE);
}

bool GateHandler::IsExitGate() {
	Position tail = snake->GetTail();
	return (pair_gate.X() == tail.x && pair_gate.Y() == tail.y);
}

// EOF
