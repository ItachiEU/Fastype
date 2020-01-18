#pragma once

#include "GameState.hpp"

class MainMenuState : public State{
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, Button*> buttons;

	//Functions
	void initFonts();
	void initButtons();
	void initBackground();
	void initVariables();
public:
	//Constructors
	MainMenuState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~MainMenuState();
	//Accessors

	//Functions
	void updateButtons();
	void updateInput();
	void update();

	void render(sf::RenderTarget* target = nullptr);
	void renderButtons(sf::RenderTarget* target=nullptr);
};