#include "D:\Coding\C++\AGDG\indieOne 1.1\include\engine.h"
#include <iostream>

Engine::Engine()
{
	view.reset(sf::FloatRect(0,0,640,480));
	window = new sf::RenderWindow(sf::VideoMode(640, 480), "indieOne");
	window->setView(view);
	inputs = new InputManager(window);
}

void Engine::loop()
{
	//background
	entities.push_back(new Environment(&resources.getTexture("bg.jpg"), sf::Vector2f(0,0)));
	//player
	entities.push_back(new Player(&resources.getTexture("alucard.png"), &inputs->getControls()));
	
	focus = entities[1];


	clock.restart();
	sf::Time lag = sf::milliseconds(0);
    while (window->isOpen())
    {
		sf::Time elapsed = clock.restart();
		lag += elapsed;
		//Window check
        sf::Event event;
        while (window->pollEvent(event))
        {
            inputs->processEvent(event);
        }
		inputs->processInputs();

		//Update catch-up
		while(lag >= UPDATE_SPAN)
		{
			update();
			lag -= UPDATE_SPAN;
		}
		render();
		inputs->clearAll();
   }
}

void Engine::update()
{
	for (vector<Entity *>::iterator it = entities.begin(); it!=entities.end(); it++) {
		(*it)->update(UPDATE_SPAN);
	}
}

void Engine::render()
{
	window->clear();
	handleView();
	for (vector<Entity *>::iterator it = entities.begin(); it!=entities.end(); it++) {
		(*it)->draw(window);
	}
	window->display();
}

void Engine::handleView()
{
	view.setCenter(focus->getPosition());
	window->setView(view);
}
