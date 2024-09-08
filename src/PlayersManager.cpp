#include "raylib.h"
#include "raymath.h"
#include "PlayersManager.hpp"
#include "Player.hpp"
#include "EnemyBlock.hpp"
#include "global_resources.hpp"

PlayersManager::PlayersManager ()
{
	p[0] = new Player ({1200, 1200}, {3600, 3600}, 1, RED);
	p[1] = new Player ({1200, 1200}, {3600, 3600}, 1, BLUE);
	p[2] = new Player ({1200, 1200}, {3600, 3600}, 1, DARKGREEN);
	
	p[0]->set_keyboard_control ({KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT});
	p[1]->set_keyboard_control ({KEY_W, KEY_S, KEY_A, KEY_D});
	p[2]->set_mouse_control ();
}

PlayersManager::~PlayersManager ()
{
	delete p[0];
	delete p[1];
	delete p[2];
}

void PlayersManager::collide_EnemyBlock_with_players (EnemyBlock& block)
{
	Rectangle body = {block.get_posX(), block.get_posY(), (float)block.get_width(), (float)block.get_height()};
	for (size_t i = 0; i < 3; i++){
		if (CheckCollisionCircleRec (p[i]->get_pos(), p[i]->get_radius(), body) && !p[i]->is_dead()){
			p[i]->kill();
		}
	}
}

Player& PlayersManager::pick_target_for_enemy (Vector2 enemyPosition)
{
	Player* target = p[0]; // default is p[0] to avoid undefined behaviour, but should take a meaningfull value at the end.
	float shortestDistance = 999999999;
	for (size_t i = 0; i < 3; i++){
		float dis = Vector2DistanceSqr (enemyPosition, p[i]->get_pos());
		if (p[i]->is_available() && (dis < shortestDistance))
		{
				target = p[i];
				shortestDistance = dis;
		}
	}
	return *target;
}

void PlayersManager::update (float dt)
{
	short availablePlayers = 0; // numbers of players available in the game
	for (size_t i = 0; i < 3; i++){
		if (p[i]->is_available()) {p[i]->update (dt);}
		availablePlayers += p[i]->is_available();
	}
	if (0 == availablePlayers) {GAME_WORLD.terminate();}
}

void PlayersManager::draw ()
{
	for (size_t i = 0; i < 3; i++){
		if (p[i]->is_available()) {p[i]->draw();}
	}
}
