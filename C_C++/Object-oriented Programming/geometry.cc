#include"geometry.h"

#include<cstdlib>
#include<cassert>


// Czy nie wychodzi poza limit.
void anti_limit(int x, int y)
{
    if( (x^y) > 0)assert(abs(x) + abs(y) > 0);
}

// Czy mozna zmergeowac.
bool can_megre(const Rectangle& rec1, const Rectangle& rec2)
{
    return (rec1.width() == rec2.width()) && (rec1.pos() + Vector(0, rec1.height()) == rec2.pos());
}


/**********/
/* Vector */
/**********/


Vector::Vector(int x, int y) : arg_x(x), arg_y(y)
{}

Vector::Vector(const Position &pos) : arg_x(pos.x()), arg_y(pos.y())
{}

int Vector::x() const
{
    return arg_x;
}

int Vector::y() const
{
    return arg_y;
}

bool Vector::operator==(const Vector &rhs) const
{
    return (arg_x == rhs.x()) && (arg_y == rhs.y());
}

Vector Vector::reflection() const
{
    return Vector(arg_y, arg_x);
}

Vector & Vector::operator+=(const Vector &rhs)
{
    anti_limit(arg_x, rhs.x());
    anti_limit(arg_y, rhs.y());

    arg_x += rhs.x();
    arg_y += rhs.y();

    return *this;
}


/************/
/* Position */
/************/


Position::Position(int x, int y) : arg_x(x), arg_y(y)
{}

Position::Position(const Vector &vec) : arg_x(vec.x()), arg_y(vec.y())
{}

int Position::x() const
{
    return arg_x;
}

int Position::y() const
{
    return arg_y;
}

bool Position::operator==(const Position &rhs) const
{
    return (arg_x == rhs.x()) && (arg_y == rhs.y());
}

Position Position::reflection() const
{
    return Position(arg_y, arg_x);
}

Position & Position::operator+=(const Vector &rhs)
{
    anti_limit(arg_x, rhs.x());
    anti_limit(arg_y, rhs.y());

    arg_x += rhs.x();
    arg_y += rhs.y();

    return *this;
}

const Position & Position::origin()
{
    static const Position org = Position(0, 0);
    return org;
}

/*************/
/* Rectangle */
/*************/


Rectangle::Rectangle(int width, int height, const Position& pos) : vec(width, height), p_pos(pos.x(), pos.y())
{
    assert(width > 0);
    assert(height > 0);
    anti_limit(pos.x(), width);
    anti_limit(pos.y(), height);
}

Rectangle::Rectangle(int width, int height) : vec(width, height), p_pos(Position::origin())
{
    assert(width > 0);
    assert(height > 0);
}

int Rectangle::width() const
{
    return vec.x();
}


int Rectangle::height() const
{
    return vec.y();
}

const Position& Rectangle::pos() const
{
    return p_pos;
}

bool Rectangle::operator==(const Rectangle &rhs) const
{
    return (vec.x() == rhs.width()) && (vec.y() == rhs.height()) && (p_pos == rhs.pos());
}

int Rectangle::area() const
{
    int wynik = vec.x() * vec.y();

    assert(wynik > 0);

    return wynik;
}

Rectangle Rectangle::reflection() const
{
    return Rectangle(vec.y(), vec.x(), p_pos.reflection());
}

Rectangle & Rectangle::operator+=(const Vector &rhs)
{
    p_pos += rhs;

    anti_limit(vec.x(), p_pos.x());
    anti_limit(vec.y(), p_pos.y());

    return *this;
}


/**************/
/* Rectangles */
/**************/


Rectangles::Rectangles()
{}

Rectangles::Rectangles(const std::initializer_list<Rectangle>& list) : rec(list)
{}

size_t Rectangles::size() const
{
    return rec.size();
}

Rectangle & Rectangles::operator[](unsigned index)
{
    assert(index < rec.size());
    return rec[index];
}

const Rectangle & Rectangles::operator[](unsigned index) const
{
    assert(index < rec.size());
    return rec[index];
}

bool Rectangles::operator==(const Rectangles &rhs) const
{
    size_t siz = rec.size();
    if(siz != rhs.size())return false;

    for(unsigned i=0; i<siz; ++i)
    {
        if(!(rec[i] == rhs[i]) )return false;
    }

    return true;
}

Rectangles & Rectangles::operator+=(const Vector &rhs)
{
    for(auto it = rec.begin(); it != rec.end(); ++it)
    {
        *it += rhs;
    }

    return *this;
}


/********/
/* Sumy */
/********/


const Vector operator+(const Vector& vec1, const Vector& vec2)
{
    return Vector(vec1) += vec2;
}


const Position operator+(const Position& pos, const Vector& vec)
{
    return Position(pos) += vec;
}

const Position operator+(const Vector& vec, const Position& pos)
{
    return pos + vec;
}


const Rectangle operator+(const Rectangle& rec, const Vector& vec)
{
    return Rectangle(rec) += vec;
}

const Rectangle operator+(const Vector& vec, const Rectangle& rec)
{
    return rec + vec;
}


const Rectangles operator+(const Rectangles& recs, const Vector& vec)
{
    return Rectangles(recs) += vec;
}

const Rectangles operator+(const Vector& vec, const Rectangles& recs)
{
    return recs + vec;
}


/*********/
/* Merge */
/*********/


Rectangle merge_horizontally(const Rectangle& rec1, const Rectangle& rec2)
{
    assert(can_megre(rec1, rec2));

    return Rectangle(rec1.width(), rec1.height() + rec2.height(), rec1.pos());
}

Rectangle merge_vertically(const Rectangle& rec1, const Rectangle& rec2)
{
    return merge_horizontally(rec1.reflection(), rec2.reflection()).reflection();
}

Rectangle merge_all(const Rectangles& recs)
{
    size_t siz = recs.size();
    assert(siz != 0);
    Rectangle wynik(recs[0]);

    for(unsigned i=1; i<siz; ++i)
    {
        if(can_megre(wynik, recs[i]))
        {
            wynik = merge_horizontally(wynik, recs[i]);
        }
        else
        {
            wynik = merge_vertically(wynik, recs[i]);
        }
    }
    return wynik;
}