#ifndef GEOMETRY_H
#define GEOMETRY_H

#include<vector>

class Vector;
class Position;
class Rectangle;
class Rectangles;

class Vector
{
private:
    // Atrybuty
    int arg_x;
    int arg_y;

public:
    // Konstruktory
    Vector(int x, int y);
    explicit Vector(const Position &pos);

    // Gettery
    int x() const;
    int y() const;

    // Operator Porownania
    bool operator==(const Vector &rhs) const;

    // Odbicie
    Vector reflection() const;

    // Modyfikacje
    Vector & operator+=(const Vector &rhs);

};

class Position
{
private:
    // Atrybuty
    int arg_x;
    int arg_y;

public:
    // Konstruktory
    Position(int x, int y);
    explicit Position(const Vector &vec);

    // Gettery
    int x() const;
    int y() const;

    // Operator Porownania
    bool operator==(const Position &rhs) const;

    // Odbicie
    Position reflection() const;

    // Modyfikacje
    Position & operator+=(const Vector &rhs);

    // Punkt (0,0)
    static const Position & origin();

};

class Rectangle
{
private:
    // Atrybuty
    Vector vec;
    Position p_pos;

public:
    // Konstruktory
    Rectangle(int width, int height, const Position& pos);
    Rectangle(int width, int height);

    // Gettery
    int width() const;
    int height() const;
    const Position& pos() const;

    // Operator Porownania
    bool operator==(const Rectangle &rhs) const;

    // Odbicie
    Rectangle reflection() const;

    // Modyfikacje
    Rectangle & operator+=(const Vector &rhs);

    // Pole
    int area() const;

};

class Rectangles
{
private:
    //Atrybuty
    std::vector<Rectangle> rec;

public:
    //Konstruktory
    Rectangles();
    Rectangles(const std::initializer_list<Rectangle>& list);

    size_t size() const;

    //Operator Porownania
    bool operator==(const Rectangles &rhs) const;

    // Gettery
    Rectangle & operator[](unsigned index);
    const Rectangle& operator[](unsigned index) const;

    // Modyfikacje
    Rectangles & operator+=(const Vector &rhs);

};

// Sumy
const Vector operator+(const Vector& vec1, const Vector& vec2);

const Position operator+(const Position& pos, const Vector& vec);
const Position operator+(const Vector& vec, const Position& pos);

const Rectangle operator+(const Rectangle& rec, const Vector& vec);
const Rectangle operator+(const Vector& vec, const Rectangle& rec);

const Rectangles operator+(const Rectangles& recs, const Vector& vec);
const Rectangles operator+(const Vector& vec, const Rectangles& recs);

// Merge
Rectangle merge_horizontally(const Rectangle& rec1, const Rectangle& rec2);
Rectangle merge_vertically(const Rectangle& rec1, const Rectangle& rec2);

Rectangle merge_all(const Rectangles& recs);

#endif