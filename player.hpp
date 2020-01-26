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
	//Score
	int points;
	int tempPoints;

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
	void setCooldown(float val);
	void addPoints(int val);
	int getTempPoints();
	void addTempPoints(int val);
	int getPoints();
	sf::Vector2f getPos();

	//Functions
	void updateCooldown();
	bool canWrite();

	void render(sf::RenderTarget* target);
	void update();
};