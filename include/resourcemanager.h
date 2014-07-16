#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
using namespace std;

const int CAP = 30;

class ResourceManager //Misnomer, only handles textures
{
    public:
        ResourceManager();
		~ResourceManager();
		const sf::Texture& getTexture(string filename);
	
    private:
		map<string, sf::Texture *> textures;
		
};

#endif // RESOURCEMANAGER_H
