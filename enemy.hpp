#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<string>
#include<vector>

class Enemy{
private:
	//Sf stuff
	sf::RectangleShape shape;
	sf::Text enemyText;
	sf::Font* font;
	sf::RenderWindow* window;

	//Text handling	
	int difficulty;
	std::vector<std::string>* WORDS;
	std::unordered_map<char, int>* usedKey;

	//Properties
	float movementSpeed;
	int posX;
	bool isActive;

	//Functions
	void initVariables();
	void initShape();
	void initText();
public:
	//Constructors
	Enemy(sf::RenderWindow* window, std::vector<std::string>* WORDS, std::unordered_map<char, int>* usedKey, int difficulty, sf::Font* font);
	virtual ~Enemy();

	//Accessors
	sf::Vector2f getShapePos();
	sf::Vector2f getShapeSize();
	std::string getEnemyText();
	void setEnemyText(std::string updating);
	void activate();

	//Functions
	void updateTextColor();
	void updateTextPos();
	void updateEnemyPos();
	void update();
	void render(sf::RenderTarget* target);
};