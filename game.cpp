#include "game.hpp"

//Init functions
void Game::initWindow(){
	sf::VideoMode videoMode(1250, 850);
	this->window = new sf::RenderWindow(videoMode, "Fastype!", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(120);
}

//Constructors
Game::Game(){
	this->initWindow();
	this->initStates();
}
Game::~Game(){
	delete this->window;
}

//Accessors


//Functions

	//Core
	void Game::run(){
		while(this->window->isOpen()){

			this->update();

			this->render();
		}
	}
void Game::initStates(){
	this->states.push(new MainMenuState(this->window, &this->states));
}
void Game::updateEvents(){
	while(this->window->pollEvent(this->event)){
		if(this->event.type == sf::Event::Closed){
			this->window->close();
		}
	}
}
void Game::update(){
	this->updateEvents();

	if(!this->states.empty()){
		this->states.top()->update();

		if(this->states.top()->getQuit()){

			this->states.top()->endState();

			delete this->states.top();
			this->states.pop();
		}
	}
	else{
		this->window->close();
	}
}

void Game::render(){
	this->window->clear();

	//Draw stuff
	if(!this->states.empty())
		this->states.top()->render(this->window);

	this->window->display();
}