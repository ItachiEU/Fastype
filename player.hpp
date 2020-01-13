#pragma once

#include "state.hpp"

class Player{
private:
	//Variables
	sf::Sprite sprite;
	sf::Texture texture;
	
	//Player mechanics
	float writeCooldown;
	float writeCooldownMax;
	int hpMax;
	int hp;
		//Health Bar
		sf::Font font;
		sf::RectangleShape hpBarFull;
		sf::RectangleShape hpBarCurrent;
		sf::Text hpStatus;

	//Init functions
	void initTexture();
	void initSprite();
	void initVariables();
public:
	//Constructors
	Player();
	~Player();

	//Accessors
	int getHp();
	int getHpMax();
	void addHp(int amount);
	void setHpStatus(std::string status);
	std::string getHpStatus();
	sf::RectangleShape* getHpBar();
	void setHpBar(sf::RectangleShape* hpBarCurrent);

	//Functions
	void updateCooldown();
	bool canWrite();

	void render(sf::RenderTarget* target);
	void update();
};