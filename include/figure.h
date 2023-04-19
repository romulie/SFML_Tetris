#ifndef FIGURE_H_INCLUDED
#define FIGURE_H_INCLUDED

#include "asset_manager.h"
#include "sounds.h"
#include <vector>
#include <chrono>
#include <random>
#include <cmath>

class Figure{
public:
    enum class horizDir {left = -1, center, right}; /// movement directions along x for figure
    enum class checkDir {x, y, rotation};           /// directions to check movement for figure
    explicit Figure(sf::RenderWindow &window, sf::Vector2f pos, sf::Vector2i gameFieldSize, float scale);
    void setHorizDir(horizDir);
    void draw();
    void update(sf::Time const&);
    void rotate();
    sf::Vector2f getPosition();
    void speedDown();
    void restart();
    int getScore() const;
    void musicControl(bool playFlag);
    void setNextFigurePos(sf::Vector2f);

private:
    const int height;              /// game field height
	const int width;               /// game field width
	const float click_dy = 1.0f;   /// elementary dy step
	float click_dx;                /// elementary dx step

	std::vector<std::vector<sf::Color>> gameField;
	/// all allowed figures' filled cells in 2-by-4 rectangle with indexes: 0-1/n 2-3/n 4-5/n 6-7/n
	std::vector<std::vector<int>> figures{{1,3,5,7},{2,4,5,7},{3,4,5,6},{3,4,5,7},{2,3,5,7},{3,5,6,7},{2,3,4,5}};
	/// real x and y relative coordinates of figure's filled cells
	std::vector<sf::Vector2f> figureCoord{{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}};
	/// all possible colors for figures
	std::vector<sf::Color> colorPalete {{sf::Color::Blue,sf::Color::Cyan,sf::Color::Yellow,sf::Color::Green,sf::Color::Magenta,sf::Color::Red,sf::Color::White} }; /// former tetcolor
	/// rectangle for figure
	std::unique_ptr<sf::RectangleShape> cube = std::make_unique<sf::RectangleShape>();
	/// random generator seed, engine and distribution for random figure and color generation
	long long seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine rnd = std::default_random_engine(static_cast<long>(seed));
	std::uniform_int_distribution<int> distribution = std::uniform_int_distribution<int>(0, figures.size() - 1);
	sf::RenderWindow& window;

	const sf::Vector2f startPos;  /// figure's starting position
	sf::Time frameRate;
	sf::Vector2i figureType;
	sf::Vector2i figureColor;
	void makeFigure();
	void killFilledLine(int);
	bool check(checkDir dir);	  /// checking for the possibility of a figure movement
	sf::Int32 delay;
	int score;
	bool playMusic = true;       /// background music playing from the start of the game
	Sounds music;
	float scale;                 /// scale factor
	sf::Vector2f nextFigurePreviewPos = sf::Vector2f(-1, -1);
};


#endif // FIGURE_H_INCLUDED
