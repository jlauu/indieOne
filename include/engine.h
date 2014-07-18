#ifndef ENGINE_H
#define ENGINE_H

#include "D:\Coding\C++\AGDG\indieOne 1.1\include\entities.h"
using namespace std;

const sf::Time UPDATE_SPAN = sf::milliseconds(10);

class Engine
{
	public:
		Engine();

		void loop();

		void update(); //updates physics based on time elapsed
		void render(); //draws after updates


	private:
		sf::Clock clock;
		sf::RenderWindow *window;
		sf::View view;
		Entity *focus;
		InputManager *inputs;
		ResourceManager resources;
		vector<Entity *> entities;
		
		void handleView();
};

#endif // ENGINE_H
