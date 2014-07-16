#include "D:\Coding\C++\AGDG\indieOne 1.1\include\resourcemanager.h"

ResourceManager::ResourceManager()
{
	getTexture("broken.png");
}

ResourceManager::~ResourceManager()
{
	textures.clear();
}

const sf::Texture &ResourceManager::getTexture(string filename)
{
    for(map<string, sf::Texture *>::const_iterator it = textures.begin();
         it != textures.end(); 
         ++it)
    {
        if( filename == it->first )
        {
            return *it->second;
        }
    }
	
	sf::Texture *nTexture = new sf::Texture;
	nTexture->loadFromFile(filename);
	textures[filename] = nTexture;
	return *textures[filename];
}
