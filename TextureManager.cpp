#include "header/TextureManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "header/Spritesheet.h"

sf::Font font;

void TextureManager::loadAllFont()
{
    if (!font.loadFromFile("addons/font2.ttf")) {

        std::cout << "Impossible de charger les font." << std::endl;
    }
}