#include "wave.hpp"

//Private functions
void Wave::initBackground(){
	this->background.setSize(sf::Vector2f((float)this->window->getSize().x, (float)this->window->getSize().x));
	if(!this->texture.loadFromFile("Resources/Backgrounds/gamebackground.png")){
		std::cout<<"ERROR: FAILED TO LOAD BACKGROUND TEXTURE IN MAIN MENU\n";
	}
	this->texture.setSmooth(true);
	this->background.setTexture(&this->texture);
}
void Wave::initVariables(float difficulty){
	//Spawning
	this->spawnedEnemies = 0;
	this->difficultyFactor = 1.f;
	this->frequencyBase = 30.f;
	this->frequencyMin = 15.f;
	this->frequency = std::max(frequencyBase - difficulty*(difficultyFactor+1.f), frequencyMin);
	this->time = frequency;
	this->maxEnemiesBase = 3;
	this->maxEnemies = maxEnemiesBase + (int)difficulty*(int)difficultyFactor;

	//Input
	this->wordActive = false;
	this->currentWord = "";
	this->currentEnemy = this->enemies.size();
}

//Constructors
Wave::Wave(sf::RenderWindow* window,Player* player, sf::Font* enemyFont, std::vector<std::string>* WORDS, float difficulty, sf::Text* scoreText): State(window, states){
	this->player = player;
	this->enemyFont = enemyFont;
	this->window = window;
	this->difficulty = difficulty;
	this->WORDS = WORDS;
	this->scoreText = scoreText;
	this->initVariables(difficulty);
	this->initBackground();
}
Wave::~Wave(){
	for(auto *i: this->enemies){
		delete i;
	}
	//for(auto i: this->lasers)
	//	delete i;
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

	currHp = std::max(0, currHp+val);
	result += std::to_string(currHp);
	result += " / ";
	result += std::to_string(this->player->getHpMax());
	this->player->setHpStatus(result);
	sf::RectangleShape* temporaryShape = this->player->getHpBar();
	float percentage = (float)((float)(std::abs(val))/(float)(this->player->getHpMax()));

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

			//Setting back to deafult to look for a new target
			this->wordActive = false;
			this->currentWord = "";

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
void Wave::spawnLaser(Enemy* enemy){
	sf::Vertex start, end;
	sf::Color color(255, 0, 0, 250);
	start =sf::Vertex(sf::Vector2f(this->player->getPos().x+30, this->player->getPos().y), color);
	end =sf::Vertex(sf::Vector2f(enemy->getShapePos().x+50, enemy->getShapePos().y+30), color);
	lines.push_back(std::make_pair(std::make_pair(start, end), 250));
	//({enemy->getShapePos().x, enemy->getShapePos().y}, {0.f, 0.f});
	//lasers.push_back(line);
	//(*lasers[lasers.size()-1]).setPosition(550, 300);

}
void Wave::useInput(char input){
	if(this->wordActive){
		if(this->currentWord[this->currentWord.size()-1] == input){
			this->currentWord.pop_back();

			//Updating the displaying word on enemy
			std::string fordisplay = this->currentWord;
			std::reverse(fordisplay.begin(), fordisplay.end());
			this->enemies.at(this->currentEnemy)->setEnemyText(fordisplay);

			this->spawnLaser(enemies.at(this->currentEnemy));

			//Updating temp score
			this->player->addTempPoints(1);

			if(this->currentWord.size()==0){
				//Deleting the enemy
				delete this->enemies.at(this->currentEnemy);
				this->enemies.erase(this->enemies.begin() + this->currentEnemy);

				//Setting back to default
				this->currentEnemy = this->enemies.size();
				this->wordActive = false;

				//little cooldown
				this->player->setCooldown(-14.f);

				//Here we can also give points
				this->player->addPoints(this->player->getTempPoints());
				this->updatePoints();

				//setting temp back to 0
				this->player->addTempPoints(-this->player->getTempPoints());

			}
		}
	}
	else{
		if(this->enemies.size() > 0){
			unsigned pointer = 0;
			for(auto *i: this->enemies){
				std::string temp = i->getEnemyText();
				if(input == temp[0]){
					std::reverse(temp.begin(), temp.end());
					temp.pop_back();
					
					this->currentWord = temp;

					//updating score
					this->player->addTempPoints(1);

					//BUG FIX - WAS DECLARING CURRENT ENEMY AFTER USE!!!
					this->wordActive = true;
					this->currentEnemy = pointer;

					//Updating the displaying word on enemy
					std::string fordisplay = this->currentWord;
					std::reverse(fordisplay.begin(), fordisplay.end());

					this->enemies.at(this->currentEnemy)->setEnemyText(fordisplay);
					this->enemies.at(this->currentEnemy)->activate();

					this->spawnLaser(enemies.at(this->currentEnemy));

					break;	
				}
				pointer++;
			}
		}
	}
}
void Wave::updateLaser(){
	int pointer = 0;

	for(auto &i: lines){

		i.second -= 20;

		if(i.second <= 0){
			this->lines.erase(this->lines.begin() + pointer);
			pointer--;
		}
		i.first.first.color = sf::Color(255, 0, 0, i.second);
		i.first.second.color = sf::Color(255, 0, 0, i.second);
		pointer++;
	}
}
void Wave::updatePoints(){
	std::stringstream text;
	text << "Points: "<< this->player->getPoints();
	this->scoreText->setString(text.str());
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

		if(input != '#')
			this->useInput(input);
	}
}
void Wave::updateTime(){
	this->time +=0.1f;
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

	this->updateLaser();

	this->checkQuit();

	//debug
}
void Wave::render(sf::RenderTarget* target){
	if(!target)
		target = this->window;
	target->draw(this->background);
	for(auto i: enemies)
		i->render(target);
	this->player->render(target);

	for(auto i: lines){
		sf::Vertex line[2];
		line[0] = i.first.first;
		line[1] = i.first.second;
		target->draw(line, 2, sf::Lines);
	}

	target->draw(*this->scoreText);
}