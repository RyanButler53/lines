#include <vector>
#include <ostream>
#include "fraction.hpp"

#ifndef LINES_HPP_INCLUDED
#define LINES_HPP_INCLUDED

struct Line
{
    Fraction slope_;
    Fraction intercept_;

    // Line Constructors
    Line(Fraction slope, Fraction intercept);
    Line(long long slope, long long intercept);

    // Line comparison operators
    bool operator<(const Line &l) const;
    bool operator==(const Line &other) const;

    // Line Evaluation operators
    Fraction operator()(const Fraction x) const;
    Fraction operator()(const long long x) const;

};

struct Point
{
    Fraction x_;
    Fraction y_;

    Point(Fraction x, Fraction y);
    bool operator<(const Point &p) const;
    bool operator==(const Point &p) const;
    bool operator!=(const Point &p) const;
};

struct TopLines
{
    std::vector<Line> lines_;
    std::vector<Point> points_;

    // Constructors 
    TopLines() = default;
    TopLines(std::string filename);
    TopLines(std::vector<Line> lns, std::vector<Point> pts);

    // Overloaded adding
    void add(Point p);
    void add(Line l);

    // Comparison for testing
    bool operator==(const TopLines &other) const;
};

// Finds the intersection point between two lines
Point intersect(const Line& l1, const Line& l2);

// Solves the intersecting lines problem
TopLines intersecting_lines(std::vector<Line> &lines);

// Recursive Helper
TopLines intersecting_lines(std::vector<Line>& lines, size_t startInd, size_t endInd);

// Combines 2 solutions
TopLines combine_lines(TopLines &left, TopLines &right);

// Lines From File or Stdin
std::vector<Line> linesFromFile(std::string filename);
void processLine(std::string &line, std::vector<Line> &lines);

// Printing Operators
std::ostream &operator<<(std::ostream& os, const Line &l);

std::ostream &operator<<(std::ostream& os, const Point &p);

std::ostream &operator<<(std::ostream& os, const TopLines &tl);

#endif // LINES_HPP_INCLUDED