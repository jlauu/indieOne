#ifndef ENGINE_H
#define ENGINE_H

#include "D:\Coding\C++\AGDG\indieOne 1.1\include\entities.h"
using namespace std;

class Engine
{
	public:
		Engine();

		void loop();

		void update(sf::Time t); //updates physics based on time elapsed
		void render(); //draws after updates


	private:
		sf::Clock clock;
		sf::RenderWindow *window;
		InputManager *inputs;
		ResourceManager resources;
		vector<Entity *> entities;

};

#endif // ENGINE_H
