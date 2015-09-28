/*
file: game.cpp
*/

#include "game_globals.h"
#include "sound_manager.h"
#include "xbox_gamepad.h"
#include "gs_menu.h"
#include "game.h"

// IMPORTANT TODO: make this robust against failures
void Game::ReadLevelList(void) {
	FILE* file = fopen("res/lvl/list.txt", "r");
	char buffer[512];
	while(!feof(file)) {
		fgets(buffer, 512, file);
		std::string filename;
		for(int i = 0; i < 512; ++i) {
			if('\n' == buffer[i]) break;
			filename.push_back(buffer[i]);
		}
		_levelList.push_back(std::string(buffer));
	}
	fclose(file);
}

levelNameIt_t Game::GetLevelIterator(void) {
	return _levelList.begin();
}

levelNameIt_t Game::GetNextLevelIterator(levelNameIt_t currentLevel) {
	++currentLevel;
	if(_levelList.end() == currentLevel) {
		return _levelList.begin();
	}
	return currentLevel;
}

Game::Game(sf::RenderTarget& renderTarget) {
	_running = true;
	_view = sf::View(sf::FloatRect(0, 0, VSCREEN_WIDTH, VSCREEN_HEIGHT));

	ReadLevelList();

	statePtr_t state(new GS_Menu(*this));
	state->SetState(GS_ACTIVE | GS_FOCUS);
	_states.push_back(state);

	soundPtr_t theme = SoundManager::Instance().GetSound("res/bgmusic3.mid", true);
	theme->Play();
}

void Game::Move(float secsPassed, const sf::Input& input) {
	SoundManager::Instance().Update();
	XBOX::Update(secsPassed);

	_background.Move(secsPassed);

	for(std::list<statePtr_t>::iterator stateIt(_states.begin());
		stateIt != _states.end(); ++stateIt)
	{
		if(GS_DEAD & (*stateIt)->GetState()) {
			stateIt = _states.erase(stateIt);
			if(stateIt == _states.end()) break;
			continue;
		}
		GS_Return ret = (*stateIt)->Move(secsPassed, input);
		if(GS_POP == ret) {
			statePtr_t state = _states.back();
			state->SetState(GS_FADEOUT);
			// _states.pop_back();
			if(_states.size() == 1) {
				_running = false;
				return;
			}
		}
		if(GS_PUSH == ret) {
			(*stateIt)->Unfocus();
			statePtr_t state = (*stateIt)->GetNextState();
			state->SetState(GS_FADEIN);
			_states.push_back(state);
		}
		if(GS_REPLACE == ret) {
			(*stateIt)->SetState(GS_FADEOUT);
			statePtr_t state = (*stateIt)->GetNextState();
			state->SetState(GS_FADEIN);
			_states.push_back(state);
		}
		if(!_states.empty() && _states.back()->GetState() == GS_ACTIVE) {
			_states.back()->Focus();
		}
	}
}

void Game::Draw(sf::RenderTarget& renderTarget) {
	renderTarget.SetView(_view);
	_background.Draw(renderTarget);

	for(std::list<statePtr_t>::iterator stateIt(_states.begin());
		stateIt != _states.end(); ++stateIt)
	{
		renderTarget.SetView((*stateIt)->GetView());
		(*stateIt)->Draw(renderTarget);
	}
}