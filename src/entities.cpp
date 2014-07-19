#include "D:\Coding\C++\AGDG\indieOne 1.1\include\entities.h"

#include <iostream>

/////////////////////////////////
////////// Base Class ///////////
/////////////////////////////////

Entity::Entity(const sf::Texture *texture)
{
	active = true;
	type = "NULL";
	state = "default";
	frame = 0;
	sprite.setTexture(*texture);
}

sf::Vector2f Entity::getPosition()
{
	return sprite.getPosition();
}

void Entity::setPosition(sf::Vector2f pos)
{
	sprite.setPosition(pos);
}


void Entity::collide(Entity *object)
{
	//std::cout << "Collision: " << type << "&" << object.getType() << std::endl;
}

void Entity::update(sf::Time deltaT)
{
	//
}

void Entity::draw(sf::RenderWindow *window)
{
	window->draw(sprite);
}

void Entity::debugInfo(sf::RenderWindow *window)
{
	sf::FloatRect ref(getGlobalBounds());
	sf::RectangleShape boundbox(sf::Vector2f(ref.width, ref.height));
	boundbox.setPosition(getPosition());
	boundbox.setFillColor(sf::Color::Transparent);
	boundbox.setOutlineColor(sf::Color(255,0,0));
	boundbox.setOutlineThickness(2);
	
	window->draw(boundbox);
}

/////////////////////////////////
////////Neutral Objects//////////
/////////////////////////////////

Environment::Environment(const sf::Texture *texture, sf::Vector2f pos) :
	Entity(texture)
{
	sprite.setPosition(pos);
	type = "environment";
	collision = false;
}

Platform::Platform(const sf::Texture *texture, sf::Vector2f pos) :
	Environment(texture, pos)
{
	type = "platform";
	sprite.setTextureRect(sf::IntRect(0,0,180,70));
	bounds = new sf::FloatRect(pos,sf::Vector2f(180,3));
}

Platform::~Platform()
{
	delete bounds;
}

/////////////////////////////////
////////Live Actors//////////////
/////////////////////////////////

Character::Character(const sf::Texture *texture) :
	Entity(texture)
{
	type = "default";
	alive = true;
	sprite.setTextureRect(sf::IntRect(0,0,50,50));

	stats.health = 100;
	stats.speed = 3;
	stats.attack = 2;
	stats.defense = 1;
}

void Character::updateState(sf::Time deltaT)
{

}

void Character::updateMotion(sf::Time deltaT)
{
	//
}

Player::Player(const sf::Texture *texture, Controls *c) :
	Character(texture)
{
	type = "Player";
	controller = c;
	controlled = true;
	floor = NULL;

	buildAnimations();
}

void Player::buildAnimations()
{
	idle.load(&sprite,14);
	idle.toggleLooped();
	idle.setType("idle");
	for (int i=0;i<14; i++) {
		idle.addFrame(sf::IntRect(28*i,0,28,57));
	}

	int x[31] = { 	0   , 	28  , 	56  , 	88  , 	125 , 	171 , 	218 , 	265 , 	314 , 	365 , 	415 , 	468 , 	520 , 	574 , 	624 , 	670 , 	705 , 	742 , 	776 , 	809 , 	843 , 	874 , 	906 , 	935 , 	967 , 	1004, 	1046, 	1087, 	1130, 	1170, 	1214};
	walk.load(&sprite,32);
	walk.setType("walk");
	walk.setLoopFrame(16);
	int xs=28;
	for (int i=0;i<29;i++) {
		xs = x[i+1] - x[i];
		walk.addFrame(sf::IntRect(x[i], 114, xs, 60));
	}
	walk.addFrame(sf::IntRect(1214, 114, 1252-1214, 60));
}

void Player::collide(Entity *object)
{
	if (object->getType() == "platform") {
		floor = object;
	}
}

void Player::update(sf::Time deltaT)
{
	physics.setPos(getPosition());
	updateState(deltaT);
	updateMotion(deltaT);
}

void Player::updateState(sf::Time deltaT)
{
	float s = stats.speed;
	bool checkIdle = true;

	//Jumping
	if(floor) {
		physics.setPos(sf::Vector2f(getPosition().x, floor->getPosition().y - getGlobalBounds().height));
		physics.setVel(sf::Vector2f(physics.getVel().x, 0));
		if (controller->keys.space) {
			physics.setVel(sf::Vector2f(0,-10));
			checkIdle = false;
		}
		floor = NULL;
	}

	//Gravity
	if (!floor) {
		physics.setAccel(sf::Vector2f(0,.5));
	}

	if (controller->keys.left) {
		physics.addPos(-s,0);
		idle.reset();
		walk.animate(deltaT);
		checkIdle = false;
	} else if (controller->keys.right) {
		physics.addPos(s,0);
		idle.reset();
		walk.animate(deltaT);
		checkIdle = false;
	}

	if (checkIdle){
		walk.reset();
		idle.animate(deltaT);
	} else {
		std::cout << getPosition().x << "," << getPosition().y << std::endl;
	}
}

void Player::updateMotion(sf::Time deltaT)
{
	physics.update(deltaT);
	setPosition(physics.getPos());
}

/////////////////////////////////
///////// Hostile AI ////////////
/////////////////////////////////

Enemy::Enemy(const sf::Texture *texture) :
	Character(texture)
{
	type = "Enemy";
	findTarget();
}

void Enemy::findTarget()
{
	target = NULL;
}
