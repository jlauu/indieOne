#include "D:\Coding\C++\AGDG\indieOne 1.1\include\inputmanager.h"

InputManager::InputManager(sf::RenderWindow *w)
{
    window = w;
}

void InputManager::processEvent(sf::Event event)
{
    //event checking
    switch (event.type)
		{
			case sf::Event::Closed:
				controller.events.windowclose = true;
				window->close();
				break;
			case sf::Event::LostFocus:
				controller.events.focus = false;
				break;
			case sf::Event::GainedFocus:
				controller.events.focus = true;
				break;
			case sf::Event::KeyPressed:
				controller.events.keypress = true;
				//Debug
				switch (event.key.code)
				{
					case sf::Keyboard::F1:
						controller.debug.reset = !controller.debug.reset;
						break;
					case sf::Keyboard::F2:
						controller.debug.hboxes = !controller.debug.hboxes;
						break;
				}
				break;
			case sf::Event::MouseMoved:
				controller.events.mousemove = true;
				controller.mouse.pos = sf::Vector2f(sf::Mouse::getPosition(*window));
				break;
			default:
				break;
		}
}

void InputManager::processInputs()
{
	//Left Click
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		controller.mouse.lclick = true;
	//Right Click
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		controller.mouse.rclick = true;
	//Left Arrow
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		controller.keys.left = true;
	//Right Arrow
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		controller.keys.right = true;
	//Up Arrow
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		controller.keys.up = true;
	//Down Arrow
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		controller.keys.down = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		controller.keys.space = true;

}

void InputManager::clearEvents()
{
	Events newevents;
	controller.events = newevents;
}

void InputManager::clearKeys()
{
	Keys newkeys;
	controller.keys = newkeys;
}

void InputManager::clearMouse()
{
	Mouse newmouse;
	controller.mouse = newmouse;
}


void InputManager::clearAll()
{
	clearEvents();
	clearKeys();
	clearMouse();
}
