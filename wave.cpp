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
	//Spawning
	this->spawnedEnemies = 0;
	this->difficultyFactor = 1.f;
	this->frequencyBase = 40.f;
	this->frequencyMin = 20.f;
	this->frequency = std::max(frequencyBase - difficulty*difficultyFactor, frequencyMin);
	this->time = frequency;
	this->maxEnemiesBase = 3;
	this->maxEnemies = maxEnemiesBase + (int)difficulty*(int)difficultyFactor;

	//Input
	this->wordActive = false;
	this->currentWord = "";
	this->currentEnemy = this->enemies.size();
}

//Constructors
Wave::Wave(sf::RenderWindow* window,Player* player, sf::Font* enemyFont, std::vector<std::vector<std::string> >* WORDS, float difficulty): State(window, states){
	this->player = player;
	this->enemyFont = enemyFont;
	this->window = window;
	this->difficulty = difficulty;
	this->WORDS = WORDS;
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
	//Temporary quit option - need to add some option to prevent quitting by accident and we can move it to update Input
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		this->endState();
}

void Wave::enemySpawning(){
	if(this->time >= this->frequency){
		if(this->spawnedEnemies < this->maxEnemies ) {
			this->enemies.push_back(new Enemy(this->window, this->WORDS, &this->usedKey, this->difficulty, this->enemyFont));
			this->spawnedEnemies++;
		}

		this->time = 0;
	}
}
void Wave::updateHpBar(int val){
	std::string temp = this->player->getHpStatus(), result = "";
	int currHp;
	if(temp.size() == 7)
		currHp = (temp[0]-'0')*10+(temp[1]-'0');
	else
		currHp = temp[0]-'0';
	std::cout<<temp<<" & curr hp: "<<currHp<<std::endl;
	currHp = std::max(0, currHp+val);
	result += std::to_string(currHp);
	result += " / ";
	result += std::to_string(this->player->getHpMax());
	this->player->setHpStatus(result);
	sf::RectangleShape* temporaryShape = this->player->getHpBar();
	float percentage = (float)((float)(std::abs(val))/(float)(this->player->getHpMax()));
	std::cout<<percentage<<std::endl;
	if(val < 0)
		temporaryShape->setSize(sf::Vector2f(std::max(0.f,(*temporaryShape).getSize().x - 100.f*percentage), (*temporaryShape).getSize().y));
	else
		temporaryShape->setSize(sf::Vector2f(std::min((float)this->player->getHpMax(),(*temporaryShape).getSize().x + 100.f*percentage), (*temporaryShape).getSize().y));
}
void Wave::updateBorderCheck(){
	int pointer = 0;
	for(auto *i: this->enemies){
		if(i->getShapePos().y + i->getShapeSize().y > this->window->getSize().y){
			std::cout<<"Deleting: "<<i->getEnemyText()<<std::endl;

			this->player->addHp(-i->getEnemyText().size());
			this->updateHpBar(-i->getEnemyText().size());

			this->usedKey[i->getEnemyText()[0]] = 0;

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
	if(this->enemies.size() == 0 && this->spawnedEnemies==this->maxEnemies)
		this->endState();
}
void Wave::useInput(char input){
	if(this->wordActive){
		if(this->currentWord[this->currentWord.size()-1] == input){
			this->currentWord.pop_back();

			//Updating the displaying word on enemy
			std::string fordisplay = this->currentWord;
			std::reverse(fordisplay.begin(), fordisplay.end());
			this->enemies.at(this->currentEnemy)->setEnemyText(fordisplay);

			if(this->currentWord.size()==0){
				//Deleting the enemy
				delete this->enemies.at(this->currentEnemy);
				this->enemies.erase(this->enemies.begin() + this->currentEnemy);

				//Setting back to default
				this->currentEnemy = this->enemies.size();
				this->wordActive = false;

				//Here we can also give points to the player
			}
		}
	}
	else{
		for(unsigned i=0; i<enemies.size(); i++){
			std::string temp = enemies[i]->getEnemyText();
			if(input == temp[0]){
				std::reverse(temp.begin(), temp.end());
				temp.pop_back();
				
				this->currentWord = temp;

				//Updating the displaying word on enemy
				std::string fordisplay = this->currentWord;
				std::reverse(fordisplay.begin(), fordisplay.end());
				this->enemies.at(this->currentEnemy)->setEnemyText(fordisplay);

				this->wordActive = true;
				this->currentEnemy = i;
				break;	
			}
		}
	}
}
void Wave::updateInput(){
	if(this->player->canWrite()){
		char input = '#';
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			input = 'a';
		else
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
			input = 'b';
		else
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
			input = 'c';
		else
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			input = 'd';
		else
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			input = 'e';
		else
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
			input = 'f';
		else
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
			input = 'g';
		else
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::H))
			input = 'h';
		else
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))
			input = 'i';
		else
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::J))
			input = 'j';
		else
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
			input = 'k';
		else
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::L))
			input = 'l';
		else
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
			input = 'm';
		else
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::N))
			input = 'n';
		else
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::O))
			input = 'o';
		else
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			input = 'p';
		else
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			input = 'q';
		else
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			input = 'r';
		else
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			input = 's';
		else
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::T))
			input = 't';
		else
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::U))
			input = 'u';
		else
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::V))
			input = 'v';
		else
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			input = 'w';
		else
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
			input = 'x';
		else
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
			input = 'y';
		else
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			input = 'z';
		this->useInput(input);
	}
}
void Wave::updateTime(){
	this->time +=0.1f;
	//std::cout<<this->time<<std::endl;
}
void Wave::update(){
	//Updating writing cooldown
	this->player->update();

	this->updateTime();

	this->enemySpawning();

	//Moving enemies
	for(auto i: enemies)
		i->update();

	this->updateBorderCheck();

	//Checking if Player health below 0
	this->checkHealth();

	//Checking if there are any enemies left
	this->checkEnemiesCount();

	this->updateInput();

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