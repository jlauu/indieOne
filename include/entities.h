#ifndef ENTITIES_H_INCLUDED
#define ENTITIES_H_INCLUDED

#include "D:\Coding\C++\AGDG\indieOne 1.1\include\resourcemanager.h"
#include "D:\Coding\C++\AGDG\indieOne 1.1\include\inputmanager.h"
#include "D:\Coding\C++\AGDG\indieOne 1.1\include\animationmodule.h"
#include "D:\Coding\C++\AGDG\indieOne 1.1\include\physicsmodule.h"

struct Stats
{
	int health;
	float speed;
	int attack;
	int defense;
};

/////////////////////////////////
////////// Base Class ///////////
/////////////////////////////////

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
		
		virtual sf::FloatRect getGlobalBounds(){return sprite.getGlobalBounds();};

		virtual void collide(Entity *object);
		virtual void update(sf::Time deltaT);
		virtual void draw(sf::RenderWindow *window);
		
		virtual void debugInfo(sf::RenderWindow *window);
	protected:
		sf::Sprite sprite;
		bool active;
		string type;
		string state;
		int frame;
		
};

/////////////////////////////////
////////Neutral Objects//////////
/////////////////////////////////

class Environment : public Entity
{
	public:
		Environment(const sf::Texture *texture, sf::Vector2f pos);
		bool isCollision() {return collision;};
	protected:
		bool collision;
};

class Platform : public Environment
{
	public:
		Platform(const sf::Texture *texture, sf::Vector2f pos);
		~Platform();
		sf::FloatRect getGlobalBounds() {return *bounds;};
	private:
		sf::FloatRect *bounds;
};
/////////////////////////////////
////////Live Actors//////////////
/////////////////////////////////
class Character : public Entity
{
	public:
		Character(const sf::Texture *texture);
		bool isAlive() {return alive;};
		bool toggleAlive() {return alive = !alive;};

	protected:
		bool alive;
		Stats stats;
		AnimationModule *currAnimation;
		virtual void updateState(sf::Time deltaT);
		virtual void updateMotion(sf::Time deltaT);
	
};

class Player : public Character
{
	public:
		Player(const sf::Texture *texture, Controls *controller);
		bool isControlled() {return controlled;};
		void collide(Entity *object);
		void update(sf::Time deltaT);
	private:
		Controls *controller;
		Entity *floor;
		AnimationModule walk;
		AnimationModule idle;
		PhysicsModule physics;
		bool controlled;
		void buildAnimations(); //Utility
		void updateState(sf::Time deltaT);
		void updateMotion(sf::Time deltaT);
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
