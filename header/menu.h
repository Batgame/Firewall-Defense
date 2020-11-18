#pragma once

//Dessin le menu principale
void drawMenu(sf::RenderWindow& window, sf::Vector2i& posSouris, sf::View view); //Fonction dessine 
//Dessine les regles
void drowRegles(sf::RenderWindow& window, sf::Vector2i& posSouris, sf::View view);
//Detecte si un bouton est en subbrillance ou pas
bool isButtonSelect(sf::RenderWindow& window, sf::Vector2i& posSouris, sf::Vector2f posButton); //Fonction permetant de vérifier si la souris passe sur le bouton
