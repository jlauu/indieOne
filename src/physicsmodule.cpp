#include "D:\Coding\C++\AGDG\indieOne 1.1\include\physicsmodule.h"

PhysicsModule::PhysicsModule() :
	x(0), y(0), x_v(0), y_v(0), x_a(0), y_a(0)
{

}

PhysicsModule::PhysicsModule(const PhysicsModule& other) :
	x(other.x), y(other.y), x_v(other.x_v), y_v(other.y_v), x_a(other.x_a), y_a(other.y_a)
{

}

PhysicsModule& PhysicsModule::operator=(const PhysicsModule& rhs)
{
	x = rhs.x;
	y = rhs.y;
	x_v = rhs.x_v;
	y_v = rhs.y_v;
	x_a = rhs.x_a;
	y_a = rhs.y_a;

	return *this;
}
//      A       B         C
// x = xnot + vnot*t + .5*a*t^2

void PhysicsModule::update(sf::Time deltaT)
{
	float t = 1;
	//C
	float c = t*t*.5;
	setAccel(getAccel() * c);
	//B
	setVel(getVel() * t);
	//B&C
	addVel(getAccel());
	//A&B&C
	addPos(getVel());
	setAccel(sf::Vector2f(0,0));
}
