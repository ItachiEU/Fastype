#include "GameState.hpp"
#include "wave.hpp"
#include "gameover.hpp"

//Private functions
void GameState::initBackground(){
	this->background.setSize(sf::Vector2f((float)this->window->getSize().x, (float)this->window->getSize().x));
	if(!this->texture.loadFromFile("Resources/Backgrounds/gamebackground.png")){
		std::cout<<"ERROR: FAILED TO LOAD BACKGROUND TEXTURE IN MAIN MENU\n";
	}
	this->texture.setSmooth(true);
	this->background.setTexture(&this->texture);
}
void GameState::initFonts(){
	if(!this->font.loadFromFile("../Fonts/FFF_Tusj.ttf"))
		std::cout<<"ERROR: FAILED TO LOAD FONT IN GAME STATE1!\n";
	if(!this->enemyFont.loadFromFile("../Fonts/Sansation-Light.ttf"))
		std::cout<<"ERROR: FAILED TO LOAD FONT IN GAME STATE2!\n";
	if(!this->scoreFont.loadFromFile("../Fonts/CaviarDreams.ttf"))
		std::cout<<"ERROR: FAILED TO LOAD FONT IN GAME STATE3!\n";
}
void GameState::initText(){
	//Wave Text
	std::stringstream text;
	text << "WAVE " << this->waveNumber << " INCOMING!\n";
	this->waveText.setFont(this->font);
	this->waveText.setString(text.str());
	this->waveText.setFillColor(sf::Color::White);
	this->waveText.setCharacterSize(84);
	this->waveText.setPosition(270, 300);

	//Score
	std::stringstream scoreTxt;
	scoreTxt << "Points: 0";
	this->scoreText.setFont(this->scoreFont);
	this->scoreText.setString(scoreTxt.str());
	this->scoreText.setCharacterSize(48);
	this->scoreText.setPosition(30, 25);

}
void GameState::initVariables(){
	//Wave
	this->maxTime = 30.f;
	this->time = 0.f;
	this->difficulty = 1;
	this->waveNumber = 1;
	this->justLost = true;
}
void GameState::initDictionary(){
	std::ifstream input("donelist.txt");
	if(input.is_open()){
		std::string temp;
		while(input >> temp){
			this->WORDS[temp.size()].push_back(temp);
		}
	}
	input.close();
}

//Constructors
GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states)
 : State(window, states){
 	this->initBackground();
 	this->initFonts();
 	this->initVariables();
 	this->initDictionary();
 	this->initText();
 	this->player = new Player();
}
GameState::~GameState(){
	delete this->player;
}

//Accessors

//Functions
void GameState::updateWaveTimer(){
	this->time += 0.1f;
}
void GameState::initWave(){
		if(this->time >= this->maxTime){
			this->time = 0.f;
			if(this->player->getHp()>=0){
				//Aktywowac wave'a
				this->states->push(new Wave(this->window, this->player, &this->enemyFont, this->WORDS, this->difficulty, &this->scoreText));
				this->difficulty++;
				this->waveNumber++;
				this->updateWaveText();
			}
	}
}
void GameState::updateWaveText(){
	std::stringstream text;
	text << "WAVE " << this->waveNumber << " INCOMING!\n";
	this->waveText.setString(text.str());
}
void GameState::updateInput(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		this->endState();
}
void GameState::updateHighscores(){
	std::set< int > temporary;
	temporary.insert(-this->player->getPoints());
	std::ifstream input("highscores.txt");
	if(input.is_open()){
		//read stuff
		int line;
		while(input >> line){
			temporary.insert(-line);
			std::cout<<line<<std::endl;
		}
	}
	input.close();
	std::ofstream output("highscores.txt");
	if(output.is_open()){
		//write results 
		int licz = 1;
		for(auto i: temporary){
			if(licz<=5)
				output << -i << "\n";
			else
				break;
			licz++;
		}
	}
	output.close();
	this->endState();
}
void GameState::updateGameStatus(){
	if(this->player->getHp() <= 0 && !justLost)
		this->endState();
	if(this->player->getHp() <= 0 && justLost){
		this->justLost = false;
		this->states->push(new GameOver(this->window, this->states, this->scoreText, this->player));
		//Write the score into a file
		this->updateHighscores();
	}
}
void GameState::update(){
	this->updateMousePositions();

	this->updateInput();

	this->updateWaveTimer();

	this->initWave();

	this->updateGameStatus();
}
void GameState::render(sf::RenderTarget* target){
	if(!target)
		target = this->window;
	target->draw(this->background);

	if(this->player->getHp() > 0)
		target->draw(this->waveText);
	this->player->render(target);
}