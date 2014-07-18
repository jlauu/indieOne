#include "D:\Coding\C++\AGDG\indieOne 1.1\include\animationmodule.h"
#include <iostream>

AnimationModule::AnimationModule()
{
	size = 0;
	loop_frame = 0;
	cur_frame = 0;
	cur_time = sf::Time::Zero;
	frame_interval = sf::milliseconds(50);
	active = true;
	looped = true;
}

AnimationModule::~AnimationModule()
{
    delete [] frames;
}

void AnimationModule::load(sf::Sprite *s, int f)
{
	sprite = s;
	cap = f;
	frames = new sf::IntRect[cap];
}

void AnimationModule::addFrame(sf::IntRect rect)
{
	if(size<cap)
		frames[size++] = rect;
}

void AnimationModule::reset()
{
	active = true;
	cur_frame = 0;
	cur_time = sf::Time::Zero;
}

void AnimationModule::animate(sf::Time deltaT)
{
	if(!active) return;
	cur_time += deltaT;
	if(cur_time >= frame_interval)
	{
		cur_time = sf::microseconds(cur_time.asMicroseconds() % frame_interval.asMicroseconds());
		if (cur_frame + 1 < size) {
			cur_frame++;
		} else {
			cur_frame = loop_frame;
			if (!looped) active = false;
		}
	}
	
	sprite->setTextureRect(frames[cur_frame]);
	std::cout << type << " " << cur_frame << std::endl;
}
