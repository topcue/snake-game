#include "StateHandler.h"

int current_width;
int current_height;
string cause_of_death = "NULL";
chrono::steady_clock::time_point start_time;
BaseState *current_state;
Display* display;

void ExecuteDriver() {
	InitState();
	while(true) {
		Update(GetTic());
		Render();
		DelayState();
	}
	ExitProcess();
}

void InitState() {
	InitGlobalTimer();
	current_state = new GameMenuState();
}

void DelayState() {
	usleep(STATE_DELAY_TIME);
}

void ExitProcess() {
	delete current_state;
	exit(1);
}

void Update(float tic) {
	current_state->Update(tic);
}

void Render() {
	current_state->Render();
}

void InitGlobalTimer() {
	start_time = chrono::steady_clock::now();
}

float GetTic() {
	auto endTime = chrono::steady_clock::now();
	chrono::duration<float> elapsed_seconds = endTime - start_time;
	float tic_toc = (float)elapsed_seconds.count();

	return tic_toc;
}

void ChangeState(BaseState* state) {
	delete current_state;
	current_state = state;
}

// EOF
