#pragma once

#include "GameState.hpp"
#include "enemy.hpp"

class Wave : public State{
private:
	sf::RenderWindow* window;
	sf::RectangleShape background;
	sf::Texture texture;
	sf::Font* enemyFont;

	//Timer
	float time;

	//Level
	float difficulty;
	float difficultyFactor;
	std::vector<std::vector<std::string> >* WORDS;

	//Pointer to the player we have from gamestate
	Player* player;

	//Enemies
	std::vector<Enemy* > enemies;
	int maxEnemies;
	int maxEnemiesBase;
	float frequencyBase;
	float frequencyMin;
	float frequency;

	//Functions
	void initVariables(float difficulty);
	void initBackground();
public:
	//Constructors
	Wave(sf::RenderWindow* window, Player* player,sf::Font* enemyFont, std::vector<std::vector<std::string> >* WORDS, float difficulty);
	virtual ~Wave();
	//Accessors

	//Functions
	void enemySpawning();
	void checkQuit();
	void updateTime();
	void updateInput();
	void update();
	void render(sf::RenderTarget* target = nullptr);
};