#ifndef ENTITIES_H_INCLUDED
#define ENTITIES_H_INCLUDED

#include "D:\Coding\C++\AGDG\indieOne 1.1\include\resourcemanager.h"
#include "D:\Coding\C++\AGDG\indieOne 1.1\include\inputmanager.h"

typedef sf::Sprite Object;

class Entity
{
	public:
		Entity(const sf::Texture *texture);

		bool isActive(){return active;};
		bool toggleActive(){return active = !active;};

		string getType() {return type;};
		void setType(string t) {type = t;};

		string getState() {return state;};
		void setState(string s) {state = s;};

		sf::Vector2f getPosition();
		void setPosition(sf::Vector2f pos);

		virtual void update();
		virtual void draw(sf::RenderWindow *window);

	protected:
		Object sprite;
		bool active;
		string type;
		string state;
		int frame;
};

class Environment : public Entity
{
	public:
		Environment(const sf::Texture *texture, sf::Vector2f pos);
		bool isCollision() {return collision;};
	protected:
		bool collision;
};

class Character : public Entity
{
	public:
		Character(const sf::Texture *texture);
		bool isAlive() {return alive;};
		bool toggleAlive() {return alive = !alive;};

	protected:
		bool alive;
};

class Player : public Character
{
	public:
		Player(const sf::Texture *texture, Controls *controller);
		bool isControlled() {return controlled;};
		void update();
	private:
		Controls *controller;
		bool controlled;
};

class Enemy : public Character
{
	public:
		Enemy(const sf::Texture *texture);

		void setTarget(Entity &entity){target = &entity;};
		void findTarget();
		Entity *getTarget() {return target;};
	protected:
		Entity *target;
};


#endif // ENTITIES_H_INCLUDED
