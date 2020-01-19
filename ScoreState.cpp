#include "ScoreState.hpp"

//Private functions

void ScoreState::initFonts(){
	if(!this->font.loadFromFile("/home/itachi/Desktop/Programowanie/C/Projekt/Fonts/shangri-la.ttf"))
		std::cout<<"ERROR: FAILED TO LOAD FONT IN Score STATE!\n";
	if(!this->scoreFont.loadFromFile("/home/itachi/Desktop/Programowanie/C/Projekt/Fonts/CaviarDreams.ttf"))
		std::cout<<"ERROR: FAILED TO LOAD FONT IN ScorE STATE!\n";
	if(!this->titleFont.loadFromFile("/home/itachi/Desktop/Programowanie/C/Projekt/Fonts/FFF_Tusj.ttf"))
		std::cout<<"ERROR: FAILED TO LOAD FONT IN ScoRE STATE!\n";
}

void ScoreState::initButtons(){
	this->exit= new Button(525, 650, 150, 50,
		&this->font, "Main Menu",
		sf::Color(100,100,100,200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}
void ScoreState::initBackground(){
	this->background.setSize(sf::Vector2f((float)this->window->getSize().x, (float)this->window->getSize().x));
	if(!this->backgroundTexture.loadFromFile("/home/itachi/Desktop/Programowanie/C/Projekt/ProjektC/Resources/Backgrounds/scores.jpg")){
		std::cout<<"ERROR: FAILED TO LOAD BACKGROUND TEXTURE IN Gameover\n";
	}
	this->backgroundTexture.setSmooth(true);
	this->background.setTexture(&this->backgroundTexture);
}
void ScoreState::initScoreTexts(){
	std::ifstream input("highscores.txt");
	int temp;
	if(input.is_open()){
		while(input >> temp){
			sf::Text tempText;
			tempText.setString(std::to_string(temp));
			tempText.setFont(this->scoreFont);
			tempText.setCharacterSize(56);
			std::cout<<"Width: "<<tempText.getGlobalBounds().width<<std::endl;
			tempText.setPosition(600-tempText.getGlobalBounds().width/4, 250+this->counter);
			this->counter+=80;
			this->scoreTexts.push_back(tempText);
		}
	}
	input.close();
}
void ScoreState::initTitle(){
		this->title.setString("HIGH SCORES: ");
		this->title.setFont(this->titleFont);
		this->title.setCharacterSize(84);
		this->title.setPosition(330,80);
}
//Constructors
ScoreState::ScoreState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states){
	this->counter = 0;
	this->initFonts();
	this->initBackground();
	this->initButtons();
	this->initScoreTexts();
	this->initTitle();
}
ScoreState::~ScoreState(){
	delete this->exit;
}

//Accessors


//Functions
void ScoreState::renderScores(sf::RenderTarget* target){
	for(auto i: this->scoreTexts){
		target->draw(i);
	}
}
void ScoreState::updateButtons(){
	this->exit->update(this->mousePosView);

	if(this->exit->isPressed())
		this->endState();
}
void ScoreState::updateInput(){

}
void ScoreState::update(){
	this->updateMousePositions();
	this->updateButtons();
}
void ScoreState::render(sf::RenderTarget* target){
	target->draw(this->background);

	target->draw(this->title);

	this->renderScores(target);

	this->exit->render(target);
}
