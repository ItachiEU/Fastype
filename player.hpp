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
	void addHp(int amount);

	//Functions
	void updateCooldown();
	bool canWrite();

	void render(sf::RenderTarget* target);
	void update();
};