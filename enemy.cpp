#include "enemy.hpp"

//Private functions
void Enemy::initVariables(){
	this->movementSpeed = 0.5f;
	this->posX = rand()%(this->window->getSize().x);
}
void Enemy::initShape(){
	this->shape.setPosition(sf::Vector2f((float)this->posX, 0));
	this->shape.setSize(sf::Vector2f(100.f, 30.f));
	this->shape.setFillColor(sf::Color::Red);

	if((float)this->posX > (float)(this->window->getSize().x-(2.f)*this->shape.getSize().x))
		this->posX-=2*(int)this->shape.getSize().x;
}
void Enemy::initText(){
	this->enemyText.setFont(*this->font);
	std::string text;
	if(this->difficulty < 5){
			int i = rand()%this->difficulty+4;
			int j = rand()%(int)(*this->WORDS)[i].size();
			while(this->usedKey[(*this->WORDS)[i][j][0]]==1){
				i = rand()%this->difficulty+4;
				j = rand()%(int)(*this->WORDS)[i].size();
			}
			this->usedKey[(*this->WORDS)[i][j][0]]=1;
			text = (*this->WORDS)[i][j];
	}
	else
	if(this->difficulty < 10){
			int i = rand()%std::min(this->difficulty+2, 12);
			int j = rand()%(int)(*this->WORDS)[i].size();
			while(this->usedKey[(*this->WORDS)[i][j][0]]==1){
				i = rand()%std::min(this->difficulty+2, 12);
				j = rand()%(int)(*this->WORDS)[i].size();
			}
			this->usedKey[(*this->WORDS)[i][j][0]]=1;
			text = (*this->WORDS)[i][j];
	}
	else
	if(this->difficulty >=10){
			int i = rand()%std::min(this->difficulty+2, 12);
			int j = rand()%(int)(*this->WORDS)[i].size();
			while(this->usedKey[(*this->WORDS)[i][j][0]]==1){
				i = rand()%std::min(this->difficulty+2, 12);
				j = rand()%(int)(*this->WORDS)[i].size();
			}
			this->usedKey[(*this->WORDS)[i][j][0]]=1;
			text = (*this->WORDS)[i][j];
	}
	this->enemyText.setString(text);
	this->enemyText.setCharacterSize(18);
	this->enemyText.setOutlineThickness(1.f);
	this->enemyText.setOutlineColor(sf::Color::White);
	this->enemyText.setPosition(this->shape.getPosition().x+this->shape.getGlobalBounds().width/2-this->enemyText.getGlobalBounds().width/2, this->shape.getPosition().y);
}
//Constructors
Enemy::Enemy(sf::RenderWindow* window, std::vector<std::vector<std::string> >* WORDS, int difficulty, sf::Font* font){
	this->window = window;
	this->font = font;
	this->difficulty = difficulty;
	this->WORDS = WORDS;
	this->initVariables();
	this->initShape();
	this->initText();
}
Enemy::~Enemy(){
	
}

//Accessors

//Functions
void Enemy::updateEnemyPos(){
	this->shape.move(0, this->movementSpeed);
	this->enemyText.move(0, this->movementSpeed);
}
void Enemy::update(){
	this->updateEnemyPos();
}

void Enemy::render(sf::RenderTarget* target){
	target->draw(this->shape);
	target->draw(this->enemyText);
}