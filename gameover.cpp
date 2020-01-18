#include "gameover.hpp"

//Private functions

void GameOver::initFonts(){
	if(!this->font.loadFromFile("/home/itachi/Desktop/Programowanie/C/Projekt/Fonts/shangri-la.ttf"))
		std::cout<<"ERROR: FAILED TO LOAD FONT IN Game over STATE!\n";
	if(!this->scoreFont.loadFromFile("/home/itachi/Desktop/Programowanie/C/Projekt/Fonts/CaviarDreams.ttf"))
		std::cout<<"ERROR: FAILED TO LOAD FONT IN GAME OVER STATE\n";
	if(!this->overFont.loadFromFile("/home/itachi/Desktop/Programowanie/C/Projekt/Fonts/FFF_Tusj.ttf"))
		std::cout<<"ERROR: FAILED TO LOAD FONT IN GAME OVER_STATE\n";
}

void GameOver::initButtons(){
	this->exit= new Button(550, 550, 150, 50,
		&this->font, "Main Menu",
		sf::Color(100,100,100,200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}
void GameOver::initBackground(){
	this->background.setSize(sf::Vector2f((float)this->window->getSize().x, (float)this->window->getSize().x));
	if(!this->backgroundTexture.loadFromFile("/home/itachi/Desktop/Programowanie/C/Projekt/ProjektC/Resources/Backgrounds/gameover.jpg")){
		std::cout<<"ERROR: FAILED TO LOAD BACKGROUND TEXTURE IN Gameover\n";
	}
	this->backgroundTexture.setSmooth(true);
	this->background.setTexture(&this->backgroundTexture);
}
void GameOver::initScore(){
	//Game over
	std::stringstream txt; 
	txt << "GAME OVER!";
	this->overText.setFont(this->overFont);
	this->overText.setString(txt.str());
	this->overText.setPosition(340, 100);
	this->overText.setCharacterSize(100);

	//Score
	this->scoreText.setPosition(480, 260);
	this->scoreText.setCharacterSize(86);
}

//Constructors
GameOver::GameOver(sf::RenderWindow* window, std::stack<State*>* states, sf::Text Text) : State(window, states){
	this->scoreText = Text;
	this->initFonts();
	this->initBackground();
	this->initButtons();
	this->initScore();
}
GameOver::~GameOver(){
	delete this->exit;
}

//Accessors


//Functions
void GameOver::updateButtons(){
	this->exit->update(this->mousePosView);

	if(this->exit->isPressed())
		this->endState();
}
void GameOver::updateInput(){
}
void GameOver::update(){
	this->updateMousePositions();
	this->updateButtons();
}
void GameOver::render(sf::RenderTarget* target){
	target->draw(this->background);

	target->draw(this->overText);
	target->draw(this->scoreText);

	this->exit->render(target);
}
