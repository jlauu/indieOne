#ifndef PHYSICSMODULE_H
#define PHYSICSMODULE_H

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

const float gnot = 1; //gravity
const float x_fric = .2; //horizontal friction
const float y_fric = .2; //vertical friction

class PhysicsModule
{
    public:
        PhysicsModule();
		PhysicsModule(const PhysicsModule& other);
		PhysicsModule& operator=(const PhysicsModule& rhs);
		
		void update(sf::Time deltaT);
		
		sf::Vector2f getPos() {return sf::Vector2f(x,y);};
		sf::Vector2f getVel() {return sf::Vector2f(x_v,y_v);};
		sf::Vector2f getAccel() {return sf::Vector2f(x_a,y_a);};
		
		void setPos(sf::Vector2f pp){x=pp.x;y=pp.y;};
		void setVel(sf::Vector2f vv){x_v=vv.x;y_v=vv.y;};
		void setAccel(sf::Vector2f aa){x_a=aa.x;y_a=aa.y;};
		
		void addPos(float xx, float yy) {x+=xx;y+=yy;};
		void addPos(sf::Vector2f pp){x+=pp.x;y+=pp.y;};
		void addVel(float xx_v, float yy_v) {x_v+=xx_v;y_v+=yy_v;};
		void addVel(sf::Vector2f vv) {x_v+=vv.x;y_v+=vv.y;};
		void addAccel(float xx_a, float yy_a){x_a+=xx_a;y_a+=yy_a;};
		void addAccel(sf::Vector2f aa) {x_a+=aa.x;y_a+=aa.y;};
		
    private:
		float x;
		float y;
		float x_v;
		float y_v;
		float x_a;
		float y_a;
};

#endif // PHYSICSMODULE_H
