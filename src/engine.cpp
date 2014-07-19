#include "D:\Coding\C++\AGDG\indieOne 1.1\include\engine.h"
#include <iostream>

//Ideas borrowed from: http://gameprogrammingpatterns.com/game-loop.html

Engine::Engine()
{
	view.reset(sf::FloatRect(0,0,640,480));
	window = new sf::RenderWindow(sf::VideoMode(640, 480), "indieOne");
	window->setView(view);
	inputs = new InputManager(window);
}

Engine::~Engine()
{
	delete focus;
	delete inputs;
}

bool Engine::loop()
{
	//background
	entities.push_back(new Environment(&resources.getTexture("bg.jpg"), sf::Vector2f(0,0)));
	//player
	entities.push_back(new Player(&resources.getTexture("alucard.png"), &inputs->getControls()));
	player = entities[1];
	player->setPosition(sf::Vector2f(320,180));
	focus = entities[1];
	//platforms
	platforms.push_back(new Platform(&resources.getTexture("plat.png"), sf::Vector2f(270,300)));
	platforms.push_back(new Platform(&resources.getTexture("plat.png"), sf::Vector2f(400,300)));
	platforms.push_back(new Platform(&resources.getTexture("plat.png"), sf::Vector2f(600,400)));

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

		//Debugging
		if (inputs->getControls().debug.reset) {
			window->close();
			return true;
		}
	}
	return false;
}

void Engine::update()
{
	for (vector<Entity *>::iterator it = platforms.begin(); it!=platforms.end(); it++) {
		if((*it)->getGlobalBounds().intersects(player->getGlobalBounds())) {
			player->collide(*it);
		}
	}

	for (vector<Entity *>::iterator it = entities.begin(); it!=entities.end(); it++)
	{
		(*it)->update(UPDATE_SPAN);
	}
}

void Engine::render()
{
	window->clear();
	handleView();
	for (vector<Entity *>::iterator it = entities.begin(); it!=entities.end(); it++)
	{
		(*it)->draw(window);
		if(inputs->getControls().debug.hboxes) //Debugging
			(*it)->debugInfo(window);
	}
	for (vector<Entity *>::iterator it = platforms.begin(); it!=platforms.end(); it++)
	{
		(*it)->draw(window);

		if(inputs->getControls().debug.hboxes) //Debugging
			(*it)->debugInfo(window);
	}
	window->display();
}

void Engine::handleView()
{
	view.setCenter(focus->getPosition());
	window->setView(view);
}
