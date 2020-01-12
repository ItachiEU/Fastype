#include "player.hpp"

//Private functions
void Player::initTexture(){
	if(!this->texture.loadFromFile("/home/itachi/Desktop/Programowanie/C/Projekt/ProjektC/Resources/Sprites/player.png"))
		std::cout<<"ERROR LOADING TEXTURE FOR PLAYER!\n";
}
void Player::initSprite(){
	this->sprite.setTexture(this->texture);
	this->sprite.scale(0.1f, 0.1f);
	this->sprite.setPosition(600,800-(sprite.getGlobalBounds().height /2.f));
}
void Player::initVariables(){
	this->writeCooldownMax = 10.f;
	this->writeCooldown = this->writeCooldownMax;
	this->hpMax = 15;
	this->hp = hpMax;
}

//Constructors
Player::Player(){
	this->initTexture();
	this->initSprite();
	this->initVariables();
}
Player::~Player(){

}

//Accessors
int Player::getHp(){
	return this->hp;
}


//Functions
bool Player::canWrite(){
	if(this->writeCooldown >= writeCooldownMax){
		this->writeCooldown = 0.f;
		return true;
	}
	return false;
}
void Player::updateCooldown(){
	if(this->writeCooldown < this->writeCooldownMax)
		this->writeCooldown += 1.f;
}
void Player::update(){
	this->updateCooldown();
}
void Player::render(sf::RenderTarget* target){
	target->draw(this->sprite);
}