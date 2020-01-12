#pragma once

#include "state.hpp"


class GameState : public State{
protected:
	//Game
	sf::RectangleShape background;
	sf::Texture texture;
	sf::Text waveText;
	sf::Font font;
	sf::Font enemyFont;

	//Dictionary
	std::vector<std::vector<std::string> > WORDS = std::vector<std::vector<std::string> >(13);
	//Player
	Player* player;

	//Wave timing stuff
	double time;
	double maxTime;

	//Wave conditioning 
	int waveNumber;
	float difficulty;

	//Functions
	void initBackground();
	void initVariables();
	void initFonts();
	void initText();
	void initDictionary();
public:
	//Constructors
	GameState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~GameState();
	//Accessors

	//Functions
	void updateWaveText();
	void initWave();
	void updateWaveTimer();
	void updateInput();
	void update();
	void render(sf::RenderTarget* target = nullptr);
};