#include "../include/game_engine.h"

GameEngine::GameEngine(){
	background.setTexture(&AssetManager::GetTexture("image/Tetris.png"));
	if (!icon.loadFromFile("image/game.png")) window->close();
	window->setIcon(256, 256, icon.getPixelsPtr());
	text.setFont(AssetManager::GetFont("font/Godzilla.ttf"));
	text.setFillColor(sf::Color::Green);
	/// next figure preview position
	figure.setNextFigurePos(sf::Vector2f(70, 20));
};


void GameEngine::input(){

	sf::Event event;
	while (window->pollEvent(event)){
		if (event.type == sf::Event::Closed)
            window->close();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            figure.setHorizDir(Figure::horizDir::left);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            figure.setHorizDir(Figure::horizDir::right);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            figure.speedDown();
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            figure.rotate();

		if (event.type == sf::Event::MouseWheelMoved){
			if ((event.mouseWheel.delta == -1) || (event.mouseWheel.delta == 1))
				figure.speedDown();
        }

		if (event.type == sf::Event::MouseButtonPressed){
			if (event.mouseButton.button == sf::Mouse::Left){
				if (pause.checkClick(sf::Mouse::getPosition(*window)))
                    mypause = !mypause;
				if (sound.checkClick(sf::Mouse::getPosition(*window))){
					if (mus)    mus = false; /// false
					else        mus = true; /// true
					figure.musicControl(mus);
				}
				if (restart.checkClick(sf::Mouse::getPosition(*window)))
                    figure.restart();
				if (exit.checkClick(sf::Mouse::getPosition(*window)))
                    myexit = true;
				if ((sf::Mouse::getPosition(*window).x < figure.getPosition().x)
					&& (sf::Mouse::getPosition(*window).x > 208) && (sf::Mouse::getPosition(*window).x < 609))
                    figure.setHorizDir(Figure::horizDir::left);
				if (sf::Mouse::getPosition(*window).x >= figure.getPosition().x
					&& sf::Mouse::getPosition(*window).x > 208 && sf::Mouse::getPosition(*window).x < 609)
                    figure.setHorizDir(Figure::horizDir::right);
			}
			if (event.mouseButton.button == sf::Mouse::Right){
				if (sf::Mouse::getPosition(*window).x > 208 && sf::Mouse::getPosition(*window).x < 609)
                    figure.rotate();
			}
		}
		if (event.type == sf::Event::MouseButtonReleased){
			if (event.mouseButton.button == sf::Mouse::Left){
				restart.checkClick();
				exit.checkClick();
			}
		}
    }
};

void GameEngine::update(sf::Time const& deltaTime){
	if (!mypause)
        figure.update(deltaTime);

	if (myexit) {
		tm += deltaTime;
		if (myexit && tm > sf::seconds(1))
            window->close();
    }
};

void GameEngine::draw(){
	window->clear(sf::Color::Black);
	figure.draw();
	window->draw(background);
	window->draw(*pause.getSprite());
	window->draw(*restart.getSprite());
	window->draw(*sound.getSprite());
	window->draw(*exit.getSprite());
	text.setPosition(15, 515);
	text.setString(" < score > ");
	window->draw(text);
	text.setString(std::to_string(figure.getScore()));
	text.setPosition(100 - text.getGlobalBounds().width / 2, 555);
	window->draw(text);
	window->display();
};


void GameEngine::run(){
	sf::Clock clock;

	while (window->isOpen()){
		sf::Time dt = clock.restart();
		input();
		update(dt);
		draw();
	}
};
