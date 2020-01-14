#include "enemy.hpp"

//Private functions
void Enemy::initVariables(){
	this->movementSpeed = 0.8f;
	this->posX = rand()%(this->window->getSize().x);
	this->isActive = false;
}
void Enemy::initShape(){
	this->shape.setSize(sf::Vector2f(100.f, 30.f));
	this->shape.setFillColor(sf::Color::Red);
	if((float)this->posX > (float)((float)this->window->getSize().x-(1.5f)*(float)this->shape.getSize().x))
		this->posX-=(1.5f)*this->shape.getSize().x;
	this->shape.setPosition(sf::Vector2f((float)this->posX, 0));
}
void Enemy::initText(){
	this->enemyText.setFont(*this->font);
	std::string text;
	if(this->difficulty < 5){
			int i = (rand()%(this->difficulty+1))+3;
			int j = rand()%(int)(*this->WORDS)[i].size();
			while((*this->usedKey)[(*this->WORDS)[i][j][0]]==1){
				i = (rand()%(this->difficulty+1))+3;
				j = rand()%(int)(*this->WORDS)[i].size();
			}
			(*this->usedKey)[(*this->WORDS)[i][j][0]]=1;
			text = (*this->WORDS)[i][j];
	}
	else
	if(this->difficulty < 10){
			int i = (rand()%std::min(this->difficulty+2, 11))+2;
			int j = rand()%(int)(*this->WORDS)[i].size();
			while((*this->usedKey)[(*this->WORDS)[i][j][0]]==1){
				i = (rand()%std::min(this->difficulty+2, 11))+2;
				j = rand()%(int)(*this->WORDS)[i].size();
			}
			(*this->usedKey)[(*this->WORDS)[i][j][0]]=1;
			text = (*this->WORDS)[i][j];
	}
	else
	if(this->difficulty >=10){
			int i = (rand()%std::min(this->difficulty+2, 11))+2;
			int j = rand()%(int)(*this->WORDS)[i].size();
			while((*this->usedKey)[(*this->WORDS)[i][j][0]]==1){
				i = (rand()%std::min(this->difficulty+2, 11))+2;
				j = rand()%(int)(*this->WORDS)[i].size();
			}
			(*this->usedKey)[(*this->WORDS)[i][j][0]]=1;
			text = (*this->WORDS)[i][j];
	}
	this->enemyText.setString(text);
	this->enemyText.setCharacterSize(18);
	this->enemyText.setOutlineThickness(0.8f);
	this->enemyText.setOutlineColor(sf::Color::White);
	this->enemyText.setPosition(this->shape.getPosition().x+this->shape.getGlobalBounds().width/2-this->enemyText.getGlobalBounds().width/2, this->shape.getPosition().y+3);
}
//Constructors
Enemy::Enemy(sf::RenderWindow* window, std::vector<std::vector<std::string> >* WORDS, std::unordered_map<char, int>* usedKey, int difficulty, sf::Font* font){
	this->window = window;
	this->font = font;
	this->difficulty = difficulty;
	this->WORDS = WORDS;
	this->usedKey = usedKey;
	this->initVariables();
	this->initShape();
	this->initText();
}
Enemy::~Enemy(){
	
}

//Accessors
sf::Vector2f Enemy::getShapePos(){
	return this->shape.getPosition();
}
sf::Vector2f Enemy::getShapeSize(){
	return this->shape.getSize();
}
std::string Enemy::getEnemyText(){
	return this->enemyText.getString();
}
void Enemy::setEnemyText(std::string updating){
	this->enemyText.setString(updating);
}
void Enemy::activate(){
	this->isActive = true;
}

//Functions
void Enemy::updateTextPos(){
	this->enemyText.setPosition(this->shape.getPosition().x+this->shape.getGlobalBounds().width/2-this->enemyText.getGlobalBounds().width/2, this->shape.getPosition().y+3);
}
void Enemy::updateEnemyPos(){
	this->shape.move(0, this->movementSpeed);
	this->enemyText.move(0, this->movementSpeed);
}
void Enemy::updateTextColor(){
	if(this->isActive){
		this->enemyText.setOutlineThickness(1.f);
		this->enemyText.setOutlineColor(sf::Color::Cyan);
		this->enemyText.setFillColor(sf::Color::Green);
		this->isActive = false;
	}
}
void Enemy::update(){
	this->updateEnemyPos();
	this->updateTextPos();
	this->updateTextColor();
}

void Enemy::render(sf::RenderTarget* target){
	target->draw(this->shape);
	target->draw(this->enemyText);
}