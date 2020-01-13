#include "wave.hpp"

//Private functions
void Wave::initBackground(){
	this->background.setSize(sf::Vector2f((float)this->window->getSize().x, (float)this->window->getSize().x));
	if(!this->texture.loadFromFile("/home/itachi/Desktop/Programowanie/C/Projekt/ProjektC/Resources/Backgrounds/gamebackground.png")){
		std::cout<<"ERROR: FAILED TO LOAD BACKGROUND TEXTURE IN MAIN MENU\n";
	}
	this->texture.setSmooth(true);
	this->background.setTexture(&this->texture);
}
void Wave::initVariables(float difficulty){
	this->spawnedEnemies = 0;
	this->difficultyFactor = 1.f;
	this->frequencyBase = 50.f;
	this->frequencyMin = 20.f;
	this->frequency = std::max(frequencyBase - difficulty*difficultyFactor, frequencyMin);
	this->time = frequency;
	this->maxEnemiesBase = 3;
	this->maxEnemies = maxEnemiesBase + (int)difficulty*(int)difficultyFactor;
}

//Constructors
Wave::Wave(sf::RenderWindow* window,Player* player, sf::Font* enemyFont, std::vector<std::vector<std::string> >* WORDS, float difficulty): State(window, states){
	this->player = player;
	this->enemyFont = enemyFont;
	this->window = window;
	this->difficulty = difficulty;
	this->WORDS = WORDS;
	/*for(int i=2; i<13; i++){
		for(int j=0; j<(int)(*WORDS)[i].size(); j++)
			std::cout<<(*WORDS)[i][j];
		std::cout<<std::endl;
	}*/
	this->initVariables(difficulty);
	this->initBackground();
}
Wave::~Wave(){
	for(auto *i: this->enemies){
		delete i;
	}
}

//Accessors

//Functions
void Wave::checkQuit(){
	//We die
	if(this->player->getHp()<=0)
		this->endState();
	//Temporary quit option - need to add some option to prevent quitting
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		this->endState();
}

void Wave::enemySpawning(){
	if(this->time >= this->frequency){
		if(this->spawnedEnemies < this->maxEnemies ) {
			this->enemies.push_back(new Enemy(this->window, this->WORDS, this->difficulty, this->enemyFont));
			this->spawnedEnemies++;
		}

		this->time = 0;
	}
}
void Wave::updateBorderCheck(){
	int pointer = 0;
	for(auto *i: this->enemies){
		if(i->getShapePos().y + i->getShapeSize().y > this->window->getSize().y){
			std::cout<<"Deleting: "<<i->getEnemyText()<<std::endl;
			this->player->addHp(-i->getEnemyText().size());
			delete this->enemies.at(pointer);
			this->enemies.erase(this->enemies.begin() + pointer);
			pointer--;
		}
		pointer++;
	}
}
void Wave::checkHealth(){
	if(this->player->getHp() <= 0)
		this->endState();
}
void Wave::checkEnemiesCount(){
	if(this->enemies.size() == 0)
		this->endState();
}
void Wave::updateInput(){

}
void Wave::updateTime(){
	this->time +=0.1f;
	std::cout<<this->time<<std::endl;
}
void Wave::update(){
	this->updateTime();

	this->enemySpawning();

	//Zmienic to na vector!!!
	for(auto i: enemies)
		i->update();

	this->updateBorderCheck();

	std::cout<<this->player->getHp()<<std::endl;

	this->checkHealth();

	this->checkEnemiesCount();

	this->checkQuit();
}
void Wave::render(sf::RenderTarget* target){
	if(!target)
		target = this->window;
	target->draw(this->background);
	for(auto i: enemies)
		i->render(target);
	this->player->render(target);
}