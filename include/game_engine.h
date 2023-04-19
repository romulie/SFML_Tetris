#ifndef GAME_ENGINE_H_INCLUDED
#define GAME_ENGINE_H_INCLUDED

#include "button.h"
#include "figure.h"

class GameEngine
{
public:
	GameEngine();
	void run();
private:
	AssetManager manager;
	std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>
		(sf::VideoMode(640, 640), L"TETRIS", sf::Style::Close);
	sf::Image icon;
	sf::RectangleShape background = sf::RectangleShape(sf::Vector2f(640, 640));

	Button pause = Button(sf::Vector2f(13, 140), AssetManager::GetTexture("image/play1.png"), AssetManager::GetTexture("image/pause2.png"));
	Button restart = Button(sf::Vector2f(13, 220), AssetManager::GetTexture("image/restart1.png"), AssetManager::GetTexture("image/restart2.png"));
	Button sound = Button(sf::Vector2f(13, 300), AssetManager::GetTexture("image/sound.png"), AssetManager::GetTexture("image/nosound.png"));
	Button exit = Button(sf::Vector2f(13, 380), AssetManager::GetTexture("image/exit1.png"), AssetManager::GetTexture("image/exit2.png"));

	sf::Text text;

	Figure figure = Figure(*window, sf::Vector2f(210, -42), sf::Vector2i(20,33), 20); //(210, -42), (20,33), 20
	void input();
	void update(sf::Time const& deltaTime);
	void draw();
	bool myexit = false;
	bool mypause = false;
	bool mus = true; /// background music playing after start
	sf::Time tm;
};

#endif // GAME_ENGINE_H_INCLUDED
