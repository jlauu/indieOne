#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SFML/Graphics.hpp>

struct Events
{
	bool windowclose = false;
	bool keypress = false;
	bool mousemove = false;
	bool focus = true;
	
};

struct Mouse
{
	sf::Vector2f pos;
	bool lclick = false;
	bool rclick = false;
	bool mwheelup = false;
	bool mwheeldown = false;
};

struct Keys
{
	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;
	bool space = false;
};

struct Debug // Doesn't reset
{
	bool reset = false;
	bool hboxes = false;
};

struct Controls
{
	Events events;
	Mouse mouse;
	Keys keys;
	Debug debug;
};

class InputManager
{
    public:
        InputManager(sf::RenderWindow *window);

		void processEvent(sf::Event event);
		void processInputs();

		Controls &getControls(){return controller;};
		void clearEvents();
		void clearKeys();
		void clearMouse();
		void clearAll();
    protected:
    private:
		sf::RenderWindow *window;
		Controls controller;
};

#endif // INPUTMANAGER_H
