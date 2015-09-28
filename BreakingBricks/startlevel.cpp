/*
file: startlevel.cpp
*/

#include "gs_game.h"
#include "log.h"
#include "game_globals.h"
#include "gs_game.h"

#include "ent_block.h"
#include "ent_paddle.h"
#include "ent_ball.h"

sf::Color colorTable[] = {
	sf::Color(243, 199, 218),
	sf::Color(199, 243, 239),
	sf::Color(251, 211, 159),
	sf::Color(255, 0, 0)
};

int CharToInt(char c) {
	return c - '0';
}

/*
format for a level file entry:
tch, where
t = block type
c = block color
h = block health

with:
t = 0 is empty space
t = 1 is normal block
*/

// IMPORTANT TODO: make this robost against failures
void GS_Game::LoadLevel(void) {
	std::string filename = (*_levelNameIt);
	FILE* file = fopen(filename.c_str(), "r");

	_levelCount++;
	
	MATH::Vector2 offset(BOARD_OFFSET_X, BOARD_OFFSET_Y);

	char buffer[512];
	int row = 0;
	int col = 0;

	_rules.numBlocks = 0;
	_rules.numBalls = 0;

	while(!feof(file)) {
		fgets(buffer, 512, file);
		char* cursor = buffer;

		MATH::Vector2 offset(BOARD_OFFSET_X, BOARD_OFFSET_Y);

		while('\0' != *cursor && '\n' != *cursor) {
			int type = CharToInt(cursor[0]);
			int color = CharToInt(cursor[1]);
			int health = CharToInt(cursor[2]);
			cursor += 4;

			if(0 < type) {
				entPtr_t entity;
				if(1 == type) {
					entity = entPtr_t(new ENT::Block(_rules, colorTable[color], health));
					_rules.numBlocks++;
				}
				entity->SetPosition(offset +
					MATH::Vector2(col * BLOCK_WIDTH, row * BLOCK_HEIGHT));
				Entity::LinkToWorld(entity);
			}

			col++;
			if(col >= 10) {
				row++;
				col = 0;
			}
		}
	}
	Log::Instance().Info() << "num blocks: " << _rules.numBlocks;
	fclose(file);
}

void GS_Game::StartLevel(void) {
	_gameLost = false;
	_showInfo = false;

	_paddle = entPtr_t(new ENT::Paddle(_rules));
	_paddle->SetPosition(MATH::Vector2(500, BOARD_BOTTOMLINE - (PADDLE_HEIGHT + 1.0f)));
	Entity::LinkToWorld(_paddle);

	_ball = entPtr_t(new ENT::Ball(_rules));
	_ball->SetPosition(_paddle->GetPosition() + 
			MATH::Vector2((_paddle->GetBBox().lowerRight.x / 2.0f) - (BALL_SIZE / 2.0f), 
			-(BALL_SIZE + 1.0f)));
	Entity::LinkToWorld(_ball);

	_paddle->AttachEntity(_ball);
}