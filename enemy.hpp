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
	std::unordered_map<char, int> usedKey;
	int difficulty;
	std::vector<std::vector<std::string> >* WORDS;

	//Properties
	float movementSpeed;
	int posX;

	//Functions
	void initVariables();
	void initShape();
	void initText();
public:
	//Constructors
	Enemy(sf::RenderWindow* window,std::vector<std::vector<std::string> >* WORDS, int difficulty, sf::Font* font);
	virtual ~Enemy();

	//Accessors

	//Functions
	void updateEnemyPos();
	void update();
	void render(sf::RenderTarget* target);
};