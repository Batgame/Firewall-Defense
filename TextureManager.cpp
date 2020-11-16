#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Spritesheet.h"

sf::Font font;

void TextureManager::loadAllFont()
{
    if (!font.loadFromFile("addons/font.ttf")) {

        std::cout << "Impossible de charger les font." << std::endl;
    }
}