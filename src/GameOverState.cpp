#include "GameOverState.h"

extern Display* display;
extern string cause_of_death;

GameOverState::GameOverState() {
	NULL;
}

GameOverState::~GameOverState() {
	NULL;
}

void GameOverState::Update(float tic) {
	refresh();
	Load();

	ShowCauseOfDeath();
	
	char answer = AskRetry();
	if (answer == INPUT_YES) {
		ChangeState(new GameState());
	} else if (answer == INPUT_NO) {
		ExitProcess();
	}
}

void GameOverState::Render() {
	display->Render();
}

void GameOverState::Load() {
	int height = 0;
	char line[WIDTH+1];
	ifstream data_file;
	
	string file_path = "State/GameOverState.dat";
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

char GameOverState::AskRetry() {
	string msg = "[ Game Over....! Retry? (y/n) ]";
	display->DisplayMessage(msg, 26);

	return UserInput();
}

char GameOverState::UserInput() {
	char input = getch();
	endwin();
	clear();

	return input;
}

void GameOverState::ShowCauseOfDeath() {
	string msg = "[ Cause of Game Over ]  ";
	display->DisplayMessage(msg, 19);
	display->DisplayMessage(cause_of_death, 21);
}

// EOF
