#include "D:\Coding\C++\AGDG\indieOne 1.1\include\entities.h"

#include <iostream>

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

void Entity::update(sf::Time deltaT)
{
	//
}

void Entity::draw(sf::RenderWindow *window)
{
	window->draw(sprite);
}

Environment::Environment(const sf::Texture *texture, sf::Vector2f pos) :
	Entity(texture)
{
	sprite.setPosition(pos);
	type = "Environment";
	collision = true;
}

Character::Character(const sf::Texture *texture) :
	Entity(texture)
{
	type = "default";
	alive = true;
	sprite.setTextureRect(sf::IntRect(0,0,50,50));
	sprite.setOrigin(sf::Vector2f(25,25));

	stats.health = 100;
	stats.speed = 1;
	stats.attack = 2;
	stats.defense = 1;
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

	buildAnimations();
}

void Player::buildAnimations()
{
	idle.load(&sprite,14);
	idle.toggleLooped();
	idle.setType("idle");
	for (int i=0;i<9; i++) {
		idle.addFrame(sf::IntRect(57*i,0,28,57));
	}

	int x[31] = { 	0   , 	28  , 	56  , 	88  , 	125 , 	171 , 	218 , 	265 , 	314 , 	365 , 	415 , 	468 , 	520 , 	574 , 	624 , 	670 , 	705 , 	742 , 	776 , 	809 , 	843 , 	874 , 	906 , 	935 , 	967 , 	1004, 	1046, 	1087, 	1130, 	1170, 	1214};
	walk.load(&sprite,32);
	walk.setType("walk");
	walk.setLoopFrame(16);
	int xs=28;
	for (int i=0;i<31;i++) {
		xs = x[i+1] - x[i];
		walk.addFrame(sf::IntRect(x[i], 114, xs, 60));
	}
	walk.addFrame(sf::IntRect(1214, 114, 1252-1214, 60));
}

void Player::update(sf::Time deltaT)
{
	updateMotion(deltaT);
}

void Player::updateMotion(sf::Time deltaT)
{
	float s = stats.speed;
	bool checkIdle = true;
	if (controller->keys.left) {
		sprite.move(-s,0);
		idle.reset();
		walk.animate(deltaT);
		checkIdle = false;
	} else if (controller->keys.right) {
		sprite.move(s,0);
		idle.reset();
		walk.animate(deltaT);
		checkIdle = false;
	}
	if (controller->keys.up) {
		sprite.move(0,-s);
		checkIdle = false;
	}else if (controller->keys.down) {
		sprite.move(0,s);
		checkIdle = false;
	}
	if (checkIdle){
		walk.reset();
		idle.animate(deltaT);
	}
}

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
