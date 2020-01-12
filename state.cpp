#include "state.hpp"

//Private functions


//Constructors
State::State(sf::RenderWindow* window, std::stack<State*>* states){
	this->window = window;
	this->quit = false;
	this->states = states;
}
State::~State(){

}

//Accessors
const bool& State::getQuit() const{
	return this->quit;
}
//Functions
void State::updateMousePositions(){
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}
void State::endState(){
	this->quit = true;
}