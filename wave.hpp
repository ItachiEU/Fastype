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
	std::vector<std::string>* WORDS;
	std::unordered_map<char, int> usedKey;

	//Input processing
	bool wordActive;
	std::string currentWord;
	unsigned currentEnemy;

	//Pointer to the player we have from gamestate
	Player* player;
	sf::Text* scoreText;

	//Enemies
	std::vector<Enemy* > enemies;
	int spawnedEnemies;
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
	Wave(sf::RenderWindow* window, Player* player,sf::Font* enemyFont, std::vector<std::string>* WORDS, float difficulty, sf::Text* scoreText);
	virtual ~Wave();
	//Accessors

	//Functions
	void enemySpawning();
	void checkQuit();
	void checkHealth();
	void useInput(char input);
	void checkEnemiesCount();
	void updateBorderCheck();
	void updateHpBar(int val);
	void updatePoints();
	void updateTime();
	void updateInput();
	void update();
	void render(sf::RenderTarget* target = nullptr);
};