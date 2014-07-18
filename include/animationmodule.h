#ifndef ANIMATIONMODULE_H
#define ANIMATIONMODULE_H

#include <SFML/Graphics.hpp>
#include <string>

//Borrowed a lot ideas from:https://github.com/LaurentGomila/SFML/wiki/Source:-AnimatedSprite

class AnimationModule
{
    public:
        AnimationModule();
        ~AnimationModule();

		void load(sf::Sprite *sprite, int frames);
		void addFrame(sf::IntRect rect);
		void animate(sf::Time deltaT);
		void setFrameInterval(sf::Time interval){frame_interval = interval;};
		void setLoopFrame(int i){loop_frame = i;};
		void setType(std::string id){type = id;};
		void toggleActive() {active = !active;};
		void toggleLooped() {looped = !looped;};
		
		void reset();

		int getFrame(){return cur_frame;};
		std::string getType(){return type;}; //unused
		bool isActive(){return active;}
		bool isLooped(){return looped;}

    private:
		sf::Sprite *sprite;
		sf::IntRect *frames;
		sf::Time cur_time;
		std::string type;
		bool active;
		bool looped;
		int cap;
		int size;
		int cur_frame;
		int loop_frame;
		sf::Time frame_interval;
};

#endif // ANIMATIONMODULE_H
