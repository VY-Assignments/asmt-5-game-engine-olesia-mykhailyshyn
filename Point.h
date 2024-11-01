#pragma once

class Point {
private:
    int x;
    int y;

public:
    Point();
    Point(int x, int y);

    [[nodiscard]] int getX() const;
    [[nodiscard]] int getY() const;

    void setX(int x);
    void setY(int y);
    void setPoint(int x, int y);

    [[nodiscard]] bool isEqual(const Point &other) const;
    bool operator==(const Point &other) const;
};