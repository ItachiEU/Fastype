#include "player.hpp"

//Private functions
void Player::initTexture(){
	if(!this->texture.loadFromFile("Resources/Sprites/player.png"))
		std::cout<<"ERROR LOADING TEXTURE FOR PLAYER!\n";
	if(!this->font.loadFromFile("../Fonts/Roboto-Black.ttf"))
		std::cout<<"ERROR LOADING FONT IN PLAYER.CPP\n";
}
void Player::initSprite(){
	//Player
	this->sprite.setTexture(this->texture);
	this->sprite.scale(0.1f, 0.1f);
	this->sprite.setPosition(600,800-(sprite.getGlobalBounds().height /2.f));
	//Hp bar
	this->hpBarFull.setPosition(650,this->sprite.getPosition().y);
	this->hpBarCurrent.setPosition(650, this->sprite.getPosition().y);
	this->hpStatus.setPosition(673, this->sprite.getPosition().y + 16);
}
void Player::initVariables(){
	//input
	this->writeCooldownMax = 3.f;
	this->writeCooldown = this->writeCooldownMax;
	this->hpMax = 20;
	this->hp = hpMax;
	//HP BAR
	std::stringstream ss;
	this->hpStatus.setFont(this->font);
	this->hpStatus.setCharacterSize(18);
	ss << hp << " / " << hpMax;
	this->hpStatus.setString(ss.str());
	this->hpBarFull.setFillColor(sf::Color::Transparent);
	this->hpBarFull.setOutlineColor(sf::Color::White);
	this->hpBarFull.setOutlineThickness(0.8f);
	this->hpBarCurrent.setFillColor(sf::Color::Red);
	this->hpBarFull.setSize(sf::Vector2f(100.f, 14.f));
	this->hpBarCurrent.setSize(sf::Vector2f(100.f, 13.f));
	//score
	this->tempPoints = 0;
	this->points = 0;
}

//Constructors
Player::Player(){
	this->initTexture();
	this->initVariables();
	this->initSprite();
}
Player::~Player(){

}

//Accessors and Modifiers
int Player::getHpMax(){
	return this->hpMax;
}
int Player::getHp(){
	return this->hp;
}
void Player::addHp(int amount){
	this->hp +=amount;
}
void Player::setHpStatus(std::string status){
	this->hpStatus.setString(status);
}
std::string Player::getHpStatus(){
	return this->hpStatus.getString();
}
sf::RectangleShape* Player::getHpBar(){
	return &this->hpBarCurrent;
}
void Player::setHpBar(sf::RectangleShape* hpBarCurrent){
	this->hpBarCurrent = *hpBarCurrent;
}
void Player::setCooldown(float val){
	this->writeCooldown = val;
}
void Player::addPoints(int val){
	this->points += val;
}
int Player::getTempPoints(){
	return this->tempPoints;
}
void Player::addTempPoints(int val){
	this->tempPoints += val;
}
int Player::getPoints(){
	return this->points;
}
sf::Vector2f Player::getPos(){
	return this->sprite.getPosition();
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
	target->draw(this->hpBarCurrent);
	target->draw(this->hpBarFull);
	target->draw(this->hpStatus);
}