#pragma once

#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<stack>
#include<ctime>
#include<map>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#include "player.hpp"
#include "button.hpp"

class State{
private:

protected:
	//Variables
	std::stack<State*>* states; 
	sf::RenderWindow* window;
	bool quit;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//resources
	std::map<std::string, sf::Texture> textures;

	//Functions
public:
	//Constructors
	State(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~State();
	//Accessors
	const bool& getQuit() const;

	//Functions

	virtual void updateMousePositions();
	virtual void endState();

	virtual void updateInput() = 0;
	virtual void update() = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};