#pragma once


void drawMenu(sf::RenderWindow& window, sf::Vector2i& posSouris, sf::View view); //Fonction dessine 
void drowRegles(sf::RenderWindow& window, sf::Vector2i& posSouris, sf::View view);
bool isButtonSelect(sf::RenderWindow& window, sf::Vector2i& posSouris, sf::Vector2f posButton); //Fonction permetant de vérifier si la souris passe sur le bouton