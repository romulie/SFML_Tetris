#include "../include/figure.h"

/// make new game field at the position = pos with size = gameFieldSize and scale
Figure::Figure(sf::RenderWindow& window, sf::Vector2f pos, sf::Vector2i gameFieldSize, float scale)
: height(gameFieldSize.y), width(gameFieldSize.x), window(window), startPos(pos), scale(scale){

	cube->setOutlineColor(sf::Color(78, 87, 84)); /// gray game field grid
	cube->setOutlineThickness(-1);                /// inner outline
	cube->setSize(sf::Vector2f(scale, scale));

    /// fill all the empty gameField with black squares
	for (int i = 0; i < width; ++i){
		std::vector<sf::Color> v;

		for (int j = 0; j < height; ++j)
			v.push_back(sf::Color::Black);

		gameField.push_back(v);
	}
	restart();
};


void Figure::restart(){
	/// fill all the gameField with black squares after game over
	for (int i = 0; i < width; ++i){
		for (int j = 0; j < height; ++j)
            gameField[i][j] = sf::Color::Black;
	}
	/// generate new  figure with random type and color
	figureType.y = distribution(rnd);
	figureColor.y = distribution(rnd);
	makeFigure();
	/// reset score
	score = 0;
};


void Figure::makeFigure(){

	figureType.x = figureType.y;
	figureColor.x = figureColor.y;
    /// find x(from 0 to 1) and y(from 0 to 1) relative coordinates of figure's filled cells
	for (size_t i = 0; i < figureCoord.size(); ++i){
		figureCoord[i].x = figures[figureType.x][i] % 2+ static_cast<float>(floor(width/2));
		figureCoord[i].y = static_cast<float>(figures[figureType.y][i] / 2);
	}

	figureType.y = distribution(rnd);
	figureColor.y = distribution(rnd);
    delay = 250;
};


void Figure::update(sf::Time const &deltaTime){

	if (playMusic) music.play(0);
    else music.stop(0);

	frameRate += deltaTime;

	if (frameRate > sf::milliseconds(delay)){
		frameRate = sf::milliseconds(0);
		/// move horizontally after checking the possibility of such a movement
		if (check(checkDir::x) && click_dx != 0){
			for (size_t i = 0; i < figureCoord.size(); ++i)
                figureCoord[i].x += click_dx;
            music.play(3);
            click_dx = 0;
		}
        /// move vertically after checking the possibility of such a movement
		if (check(checkDir::y)){
                for (size_t i = 0; i < figureCoord.size(); ++i)
                    figureCoord[i].y += click_dy;
        }
		else {
			for (size_t i = 0; i < figureCoord.size(); ++i){
				if (static_cast<int>(figureCoord[i].y) == 2){
                        restart();
                        music.play(2);
                        return;
                }
				gameField[static_cast<size_t>(figureCoord[i].x)][static_cast<size_t>(figureCoord[i].y)] = sf::Color(colorPalete[figureColor.x]);
			}
            /// scan for filled lines and erase them
			int numLine = 0;
            for (int j = 0; j < height; ++j){
				int line = 0;
				for (int i = 0; i < width; ++i){
					if (gameField[i][j] != sf::Color::Black) line++;
					if (line == width){
                        killFilledLine(j);
                        music.play(1);
                        ++numLine;
					}
				}
            }
            /// add score if there are filled and killed lines
            if (numLine != 0)
                score += 5*(numLine * numLine);
            /// make next figure
			makeFigure();
		}
	}
};

void Figure::setHorizDir(horizDir dir){
	click_dx = static_cast<float> (dir);
};


void Figure::rotate(){

	if (check(checkDir::rotation)) { /// if rotation is possible
        sf::Vector2f centerRotation = figureCoord[1];
        for (size_t i = 0; i < figureCoord.size(); ++i) {
        /// rotation calculations are based on common formula with angles restricted to 90deg steps only
            float x = figureCoord[i].y - centerRotation.y;
            float y = figureCoord[i].x - centerRotation.x;
            figureCoord[i].x = centerRotation.x - x;
            figureCoord[i].y = centerRotation.y + y;
        }
        music.play(3);
	}
};

/// to speed a figure down lessen the delay
void Figure::speedDown(){
	music.play(4);
	delay = 10;
};


void Figure::killFilledLine(int idx) {
	for (int y = idx; y > 0; --y){
		for (int x = 0; x < width; ++x)
			gameField[x][y] = gameField[x][static_cast<size_t>(y-1)];
	}
};


bool Figure::check(checkDir dir){
	switch (dir){
	    case Figure::checkDir::x:
			for (size_t i = 0; i < figureCoord.size(); ++i){
                if ((figureCoord[i].x + click_dx < 0) ||
                    (figureCoord[i].x + click_dx >static_cast<float>(width-1)))
                    return false;
				if ((static_cast<int>(figureCoord[i].y) >= 0) &&
                    (gameField[static_cast<size_t>(figureCoord[i].x + click_dx)][static_cast<size_t>(figureCoord[i].y)] != sf::Color::Black))
                    return false;
            }
    	break;

		case Figure::checkDir::y:
	        for (size_t i = 0; i < figureCoord.size(); ++i){
                if ((figureCoord[i].y+ click_dy) > static_cast<float>(height-1))
                    return false;
				if ((static_cast<int>(figureCoord[i].y + click_dy) >= 0) &&
                    (gameField[static_cast<size_t>(figureCoord[i].x)][static_cast<size_t>(figureCoord[i].y + click_dy)] != sf::Color::Black))
                    return false;
            }
		break;

		case Figure::checkDir::rotation:
			sf::Vector2f centerRotation = figureCoord[1];
            for (size_t i = 0; i < figureCoord.size(); ++i){
				float x = figureCoord[i].y - centerRotation.y;
				float y = figureCoord[i].x - centerRotation.x;
			    if (((centerRotation.x - x) < 0) || ((centerRotation.x - x) > static_cast<float>(width-1)) ||
                    ((centerRotation.y + y)> static_cast<float>(height-1)))
                    return false;
				if ((static_cast<int>(centerRotation.y + y) >= 0) &&
				(gameField[static_cast<size_t>(centerRotation.x - x)][static_cast<size_t>(centerRotation.y + y)] != sf::Color::Black))
                    return false;
            }
		break;

        //default:
		//break;
	}
	return true;
};


void Figure::draw(){

	if (nextFigurePreviewPos.x >= 0) {
        cube->setFillColor(colorPalete[figureColor.y]);
        for (size_t i = 0; i < figureCoord.size(); ++i){
            cube->setPosition((figures[figureType.y][i] % 2)*scale, (static_cast<float>(figures[figureType.y][i] / 2))* scale);
            cube->move(nextFigurePreviewPos);
            window.draw(*cube);
        }
    }

	for (int i = 0; i < width; ++i){
		for (int j = 0; j < height; ++j){
			cube->setFillColor(gameField[i][j]);
			cube->setPosition(static_cast<float>(i)*scale, static_cast<float>(j)*scale);
			cube->move(startPos);
			window.draw(*cube);
		}
	}

	cube->setFillColor(colorPalete[figureColor.x]);
	for (size_t i = 0; i < figureCoord.size(); i++){
	    cube->setPosition(figureCoord[i].x * scale, figureCoord[i].y * scale);
		cube->move(startPos);
		window.draw(*cube);
	}
};


void Figure::musicControl(bool playFlag){
	playMusic = playFlag;
};


int Figure::getScore() const{
	return score;
};

sf::Vector2f Figure::getPosition(){
	sf::Vector2f pos;
	pos.x = figureCoord[1].x * scale + startPos.x;
	pos.y = figureCoord[1].y * scale + startPos.y;
	return pos;
};

void Figure::setNextFigurePos(sf::Vector2f pos){
	nextFigurePreviewPos = pos;
};
