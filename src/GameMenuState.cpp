#include "GameMenuState.h"

Stage* stage;

extern Display* display;
extern int current_width;
extern int current_height;

GameMenuState::GameMenuState() {
	stage = new Stage();
}

GameMenuState::~GameMenuState() {
	NULL;
}

void GameMenuState::Update(float tic) {
	char answer = '\x00';
	int stage_level = -1;

	while (stage_level < 0 || stage_level > 3) {
		answer = SelectMenu();
		if (answer == INPUT_NO) {
			ExitProcess();
		}
		stage_level = answer-'0'-1;
	}
	stage->SetNowStage(stage_level);

	ChangeState(new GameState());
}

void GameMenuState::Render() {
	NULL;
}

void GameMenuState::Load() {
	int height = 0;
	ifstream data_file;
	char line[WIDTH+1];

	string file_path = "state/GameMenuState.dat";
	data_file.open(file_path);
	
	while (!data_file.eof()) {
		data_file.getline(line, WIDTH+1);
		for (int width = 0; width < WIDTH; width++) {
			move(height, width);
			if (line[width] == ' ') {
				addch(char(' '));
			} else if (line[width] == '1') {
				addch(char(219));
			} else if (line[width] == '2') {
				addch(char(219));
			}
		}
		height++;
	}
}

int GameMenuState::SelectMenu() {
	string msg1 = "[Welcome to the Snake Game]";
	string msg2 = "[Press (1) to start level 1]";
	string msg3 = "[Press (2) to start level 2]";
	string msg4 = "[Press (3) to start level 3]";
	string msg5 = "[Press (4) to start level 4]";
	
	initscr();
	noecho();
	getmaxyx(stdscr, max_height, max_width);
	getmaxyx(stdscr, current_height, current_width);

	Load();

	display->DisplayMessage(msg1, 20);
	display->DisplayMessage(msg2, 22);
	display->DisplayMessage(msg3, 23);
	display->DisplayMessage(msg4, 24);
	display->DisplayMessage(msg5, 25);

	return GetUserInput();
}

int GameMenuState::GetUserInput() {
	int input = getch();
	refresh();
	endwin();
	clear();

	return input;
}

// EOF
