#include <vector>
#include <ostream>
#include "fraction.hpp"

#pragma once

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

/// @brief Finds the intersection point between two lines
Point intersect(const Line& l1, const Line& l2);

/// @brief Sorts the lines and removes lines with duplicate slopes
std::vector<Line> clean_lines(std::vector<Line>& lines);

/// @brief Solves the intersecting lines problem
TopLines intersecting_lines(std::vector<Line> &lines);

/// @brief Recursive Helper
TopLines intersecting_lines(const std::vector<Line>& lines, size_t startInd, size_t endInd);

/// @brief Combines 2 solutions
TopLines combine_lines(TopLines &left, TopLines &right);

/**
 * @brief Splits the lines up and creates different "trails" of top lines
 * @details There are two ways to split: Separate (separate = true) and Compounding (separate = false)
 * Separate means splitting up by solving different chunks of size n/t.
 * Compounding means getting the first n/t, then first n/t + second n/t and so on
 * @param lines All lines. n
 * @param numTrails Number of topline trails to get (t)
 * @param separate True
 * @return std::vector<TopLines> Toplines of the split up toplines problem
 */
std::vector<TopLines> trails(std::vector<Line>& lines, int numTrails, bool separate);

/// @brief Lines From File or Stdin
std::vector<Line> linesFromFile(std::string filename);
void processLine(std::string &line, std::vector<Line> &lines);

// Printing Operators
std::ostream &operator<<(std::ostream& os, const Line &l);

std::ostream &operator<<(std::ostream& os, const Point &p);

std::ostream &operator<<(std::ostream& os, const TopLines &tl);

