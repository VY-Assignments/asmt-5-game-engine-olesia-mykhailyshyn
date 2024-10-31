#include <SFML/Graphics.hpp>
#include "Point.h"
#include "Food.h"
#include <vector>

class Board {
private:
    int width;
    int height;
    sf::RenderWindow &window;
    std::vector<Food *> foods;

public:
    Board(int w, int h, sf::RenderWindow &win);
    ~Board();

    void addFood(Food *food);
    void clear();
    void draw() const;
};