#include "ItemHandler.h"

extern Map *map;

ItemHandler::ItemHandler() {
	getmaxyx(stdscr, max_height, max_width);
}

ItemHandler::~ItemHandler() {
	NULL;
}

void ItemHandler::Update(float tic) {
	DeleteExpiredItems(tic);

	if (tic - last_drop_time > DROP_ITEM_INTERVAL && item_list.size() < MAX_ITEMS) {
		int rand_num = rand();
		if (rand_num & 0x1) {
			AddItem(ITEM_POISON, tic);
		} else {
			AddItem(ITEM_FRUIT, tic);
		}
		ApplyBlock();
		last_drop_time = tic;
	}
}

void ItemHandler::Render() {
	NULL;
}

bool IsExceedTime(Item item, float tic) {
	return (tic - item.GetDropType() > DROP_ITEM_EXPIRE);
}

Position ItemHandler::GetRandomPosition() {
	int x, y;
	while (true) {
		x = rand() % WIDTH;
		y = rand() % HEIGHT;
		if (map->GetBlock(x, y) == BLOCK_SPACE) {
			return Position(x, y);
		}
	}
}

void ItemHandler::AddItem(char item_type, float tic) {
	Position rand_position = GetRandomPosition();
	item_list.push_back(Item(item_type, rand_position, tic));
}

void ItemHandler::DeleteExpiredItems(float tic) {
	Item item;
	vector<int> expired_item_index;

	for (int idx = 0; idx < item_list.size(); idx++) {
		item = item_list[idx];
		if (IsExceedTime(item, tic)) {
			map->DeleteBlock(item.Y(), item.X());
			item_list.erase(item_list.begin() + idx);
		}
	}
}

void ItemHandler::DeleteBlock(int y, int x) {
	Item item;
	int delete_index;
	for (int i = 0; i < item_list.size(); i++) {
		item = item_list[i];
		if (item.ComparePosition(x, y)) {
			delete_index = i;
		}
	}
	item_list.erase(item_list.begin() + delete_index);
}

void ItemHandler::ApplyBlock() {
	int x, y;
	char item_type;
	Item item;
	for (int i = 0; i < item_list.size(); i++) {
		item = item_list[i];
		x = item.X();
		y = item.Y();
		item_type = item.GetType();

		map->SetBlock(y, x, item_type);
	}
}

// EOF
