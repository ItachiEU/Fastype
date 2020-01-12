#pragma once

#include "MainMenuState.hpp"

class Game{
private:
	//variables
	sf::Event event;
	sf::RenderWindow* window;

	std::stack<State*> states;

	//init functions
	void initWindow();
	void initStates();
public:
	//Constructors
	Game();
	~Game();
	//Accessors

	//Functions

	void run();
	void updateEvents();
	void updateDt();
	void update();
	void render();
};