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

void Entity::update()
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
}

Player::Player(const sf::Texture *texture, Controls *c) :
	Character(texture)
{
	type = "Player";
	controller = c;
	controlled = true;
}

void Player::update()
{
	if(controller->events.mousemove)
		setPosition(controller->mouse.pos);
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
