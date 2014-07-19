#include "include/engine.h"

int main()
{
	bool reset = true;
	
	while (reset) {
		Engine game;
		reset = game.loop();
	}

    return 0;
}
