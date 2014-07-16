#include "D:\Coding\C++\AGDG\indieOne 1.1\include\engine.h"
#include <iostream>

Engine::Engine()
{
	window = new sf::RenderWindow(sf::VideoMode(640, 480), "indieOne");
	inputs = new InputManager(window);
}

void Engine::loop()
{
	//background
	entities.push_back(new Environment(&resources.getTexture("bg.jpg"), sf::Vector2f(0,0)));
	//player
	entities.push_back(new Player(&resources.getTexture("myship.png"), &inputs->getControls()));

    while (window->isOpen())
    {
		//Window check
        sf::Event event;
        while (window->pollEvent(event))
        {
            inputs->processEvent(event);
        }
		inputs->processInputs();

		//Time processing
		sf::Time elapsed = clock.restart();

		update(elapsed);
		render();
		
		inputs->clearAll();
   }
}

void Engine::update(sf::Time t)
{
	for (vector<Entity *>::iterator it = entities.begin(); it!=entities.end(); it++) {
		(*it)->update();
	}
}

void Engine::render()
{
	window->clear();
	for (vector<Entity *>::iterator it = entities.begin(); it!=entities.end(); it++) {
		(*it)->draw(window);
	}
	window->display();
}
