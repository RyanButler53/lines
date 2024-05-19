#include <vector>
#include <ostream>

#ifndef LINES_HPP_INCLUDED
#define LINES_HPP_INCLUDED

struct Line
{
    double slope_;
    double intercept_;

    Line(double slope, double intercept);
    bool operator<(const Line &l) const;
    double operator()(const double x) const;
    bool operator==(const Line &other) const;
};

struct Point
{
    double x_;
    double y_;

    Point(double x, double y);
    bool operator<(const Point &p) const;
    bool operator==(const Point &p) const;
};

struct TopLines
{
    std::vector<Line> lines_;
    std::vector<Point> points_;

    TopLines() = default;
    TopLines(std::string filename);
    TopLines(std::vector<Line> lns, std::vector<Point> pts);
    void add(Point p);
    void add(Line l);
    bool operator==(const TopLines &other) const;
};

// Finds the intersection point between two lines
Point intersect(const Line& l1, const Line& l2);

// Solves the problem
TopLines intersecting_lines(std::vector<Line>& lines, size_t startInd, size_t endInd);

// Combines 
TopLines combine_lines(TopLines &left, TopLines &right);

// Lines From File
std::vector<Line> linesFromFile(std::string filename);

// Printing Operators
std::ostream &operator<<(std::ostream& os, const Line &l);

std::ostream &operator<<(std::ostream& os, const Point &p);

std::ostream &operator<<(std::ostream& os, const TopLines &tl);

#endif // LINES_HPP_INCLUDED