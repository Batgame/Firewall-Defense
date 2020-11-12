#include <SFML/Graphics.hpp>
#define WIDTH 1280
#define HEIGHT 720

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Firewall-Defense");
	sf::Texture img_background;
	sf::Font font;
	sf::Text text;
	
	if (!font.loadFromFile("./addons/font.ttf")) {

		printf("Impossible de charger les font.\n");
	}

	text.setFont(font);
	text.setString("Firewall-Defense");
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::Black);
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(WIDTH/2.0f, 100));

	if (!img_background.loadFromFile("./addons/background.jpg"))
	{
		printf("Pb de chargement de l'image.\n");
	}

	sf::Sprite background;
	background.setScale(0.5f, 0.5f);
	background.setOrigin(0, 0);
	background.setTexture(img_background);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(background);
		window.draw(text);
		window.display();
	}

	return 0;
}