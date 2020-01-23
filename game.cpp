#include "game.hpp"

//Init functions
void Game::initWindow(){
	sf::VideoMode videoMode(1250, 850);
	this->window = new sf::RenderWindow(videoMode, "Fastype!", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(100);
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

		int delta = 0;
		int sum = 9;
		while(this->window->isOpen()){

            sum += delta;
            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < sum/8; i++)
			  this->update();
			sum %= 8;
			this->render();
			auto end = std::chrono::high_resolution_clock::now();

			std::chrono::duration<double, std::milli> elapsed = end - start;
			sum += (int)elapsed.count();
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