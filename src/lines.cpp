// THE LINES PROBLEM
#include <iostream>
#include "lines.hpp"
#include "fraction.hpp"
#include <algorithm>
#include <fstream>
#include <cassert>
using namespace std;

// Line Class
Line::Line(Fraction slope, Fraction intercept):
    slope_{slope}, intercept_{intercept}{}

Line::Line(long long slope, long long intercept):
    slope_{slope}, intercept_{intercept}{}

// If same slope, orders the higher intercept one SMALLER
bool Line::operator<(const Line& l) const{
    if (slope_ == l.slope_){
        return intercept_ > l.intercept_;
    } else {
        return slope_ < l.slope_;
    }
}

Fraction Line::operator()(const Fraction x) const{
    return slope_ * x + intercept_;
}

Fraction Line::operator()(const long long x) const{
    return slope_ * Fraction(x) + intercept_;
}

bool Line::operator==(const Line& other) const {
    return (slope_ == other.slope_) and (intercept_ == other.intercept_);
}

std::ostream &operator<<(std::ostream& os, const Line &l){
    // os << "y = " << l.slope_ << "x + " << l.intercept_
    os << "(" << l.slope_ << "," << l.intercept_ << ")";
    return os;
}

// Point Class
Point::Point(Fraction x, Fraction y):
    x_{x}, y_{y}{}

bool Point::operator<(const Point& p) const{
    return y_ < p.y_;
}

bool Point::operator==(const Point& p) const{
    return (x_ == p.x_) and (y_ == p.y_);
}

bool Point::operator!=(const Point& p) const{
    return !(*this==p);
}

std::ostream &operator<<(std::ostream& os, const Point &p){
    os << "(" << p.x_ << "," << p.y_ << ")";
    return os;
}

void processLine(std::string& line, std::vector<Line>& lines){
    size_t spaceInd = line.find(" ");
    if (spaceInd != string::npos){
        string slope = line.substr(0, spaceInd);
        string intercept = line.substr(spaceInd + 1);
        Fraction lineSlope = Fraction(slope);
        Fraction lineIntercept = Fraction(intercept);

        lines.push_back(Line{lineSlope, lineIntercept});
    } else {
        Fraction slope = Fraction(line);
        lines.push_back(Line{slope, Fraction{0,1}});
    }
}

std::vector<Line> linesFromFile(std::string filename){

    ifstream input;
    string line;
    std::vector<Line> lines;
    if (filename != "") {
        ifstream input = ifstream{filename};
        if (!input.is_open()){
            cerr << "Unable to open " << filename << endl;
            exit(1);
        }
        while (getline(input, line)) {
            processLine(line, lines);
        }
    } else {
        while (getline(std::cin, line)) {
            processLine(line, lines);
        }
    }
    return lines;
}

// Finds the point line 1 and line 2 intersect at. 
Point intersect(const Line& l1, const Line& l2){
    Fraction x = (l1.intercept_ - l2.intercept_) / (l2.slope_ - l1.slope_);
    Fraction y = l1(x);
    return Point(x,y);
}

// Top Lines Class (Solution)
TopLines::TopLines(vector<Line> lns, vector<Point> pts):
     lines_{lns}, points_{pts}{}

TopLines::TopLines(std::string filename):
    lines_{vector<Line>()}, points_{vector<Point>()}
    {
    // TopLines solution;
    ifstream input{filename};
    string line;
    bool points = false;
    while (getline(input, line))
    {
        if (line == ""){
            points = true;
            continue;
        }
        size_t spaceInd = line.find(" ");
        if (spaceInd != string::npos){
            string part1 = line.substr(0, spaceInd); // slope or x
            string part2 = line.substr(spaceInd + 1); // intercept or y

            Fraction part1frac = Fraction(part1);
            Fraction part2frac = Fraction(part2);
    
            if (points){
                points_.push_back(Point{part1frac, part2frac});
            } else {
                lines_.push_back(Line{part1frac, part2frac});
            }
        } else {
            assert(!points);
            Fraction slope{line};
            lines_.push_back(Line{slope, Fraction{0,1}});
        }
    }
}

void TopLines::add(Point p){
    points_.push_back(p);
}

void TopLines::add(Line l){
    lines_.push_back(l);
}

bool TopLines::operator==(const TopLines &other) const{
    return (points_ == other.points_) and (other.lines_ == lines_);
}

std::ostream &operator<<(std::ostream& os, const TopLines &tl){
    for (const Line& l: tl.lines_){
        os << l << "| ";
    }
    os << endl;
    for (const Point& p : tl.points_){
        os << p << "| ";
    }
    return os;
}

TopLines intersecting_lines(vector<Line> &lines){
    std::sort(lines.begin(), lines.end());

    // No two lines can have the same slope. 
    std::vector<Line> uniqueLines;
    for (size_t i = 0; i < lines.size()-1;++i){
        if (lines[i].slope_ == lines[i+1].slope_){
            cerr << "Lines " << "y = " << lines[i].slope_
                 << "x + " << lines[i].intercept_ << " and y = "
                 << lines[i + 1].slope_ << "x + " << lines[i + 1].intercept_
                 << " have the same slope" << endl;
            uniqueLines.push_back(lines[i]);
            ++i;
        } else {
            uniqueLines.push_back(lines[i]);
        }
    }
    if (lines.back().slope_ != uniqueLines.back().slope_){
        uniqueLines.push_back(lines.back());
    }
    return intersecting_lines(uniqueLines, 0, uniqueLines.size());
}

TopLines intersecting_lines(vector<Line>& lines, size_t startInd, size_t endInd){
    // Base Cases: 2 and 3 lines
    if (endInd - startInd == 2){
        vector<Line> solnLines{lines[startInd], lines[startInd + 1]};
        Point intPoint = intersect(lines[startInd], lines[startInd + 1]);
        return TopLines(solnLines, vector<Point>{intPoint});
    } else if (endInd - startInd == 3){
        Line &l1 = lines[startInd];
        Line &l2 = lines[startInd+1];
        Line &l3 = lines[startInd+2];
        Point l1l3_intersect = intersect(l1, l3);
        if (l1l3_intersect.y_ >= l2(l1l3_intersect.x_)){
            // 2 lines case
            return TopLines(vector<Line>{l1, l3}, vector<Point>{l1l3_intersect});
        } else { // 3 lines case
            Point l1l2 = intersect(l1, l2);
            Point l2l3 = intersect(l2, l3);
            assert(l1l2.x_ < l2l3.x_);
            return TopLines(vector<Line>{l1, l2, l3}, vector<Point>{l1l2, l2l3});
        }
    } else {
        // Recursive Case
        size_t mid = startInd + (endInd - startInd) / 2;
        TopLines left = intersecting_lines(lines, startInd, mid);
        TopLines right = intersecting_lines(lines, mid, endInd);
        return combine_lines(left, right);
    }
}

TopLines combine_lines(TopLines& left, TopLines& right){
    // Setup
    TopLines soln;
    size_t left_i = 0; 
    size_t right_i = 0;
    size_t numLeftPts = left.points_.size();
    size_t numRightPts = right.points_.size();
    assert(right_i < numRightPts);
    assert(left_i < numLeftPts);
    Fraction curr_x = min(right.points_[right_i].x_, left.points_[left_i].x_);
    while (true){
        // Evaluate at current x
        Fraction left_y = left.lines_[left_i](curr_x);
        Fraction right_y = right.lines_[right_i](curr_x);

        // Left line on top
        if (left_y > right_y) {

            // No more left points. But there COULD be right points
            if((left_i == numLeftPts) and (right_i != numRightPts)){
                ++right_i;
            } // No more of either points left
            else if (left_i == numLeftPts and right_i == numRightPts) {
                soln.add(left.lines_.back());
                soln.add(intersect(left.lines_.back(), right.lines_.back()));
                break;
            }// 2 cases: Right is out of event points or left point is next
            else if ((numRightPts == right_i) or left.points_[left_i].x_ < right.points_[right_i].x_) {
                // Increment the left line and add to solution
                soln.add(left.lines_[left_i]);
                soln.add(left.points_[left_i]);
                ++left_i;
            }// Both lines intersect at the same place
            else if (left.points_[left_i].x_ == right.points_[right_i].x_) {
                // Increment the left line and add to solution (its on top)
                soln.add(left.lines_[left_i]);
                soln.add(left.points_[left_i]);
                ++left_i;
                // Increment Right line
                ++right_i;
            } else { // Right line is next -  update right without updating soln
                ++right_i;
            }

            // Update Current X value
            if (left_i == numLeftPts and right_i == numRightPts){
                // Never found a crossing. Code duplicated. 
                Line l = left.lines_[left_i];
                Line r = right.lines_[right_i];
                soln.add(l);

                Point intersection = intersect(l, r);
                soln.add(intersection);
                break;
            } else if (left_i == numLeftPts) {
                curr_x = right.points_[right_i].x_;
            } else if (right_i == numRightPts) {
                curr_x = left.points_[left_i].x_;
            } else{
                curr_x = min(left.points_[left_i].x_, right.points_[right_i].x_);

            }
        } else { // Right line on top -- add left line and terminate. 
            Line l = left.lines_[left_i];
            Line r = right.lines_[right_i];
            soln.add(l);

            Point intersection = intersect(l, r);
            soln.add(intersection);
            // assert(right_i < numRightPts);
            if (right_i < numRightPts and intersection == right.points_[right_i])
            {
                ++right_i;
            }
            break;
        }
    }

    // Finish by adding all right points and lines
    for (; right_i < numRightPts; ++right_i){
        soln.add(right.points_[right_i]);
        soln.add(right.lines_[right_i]);
    }
    soln.add(right.lines_.back());
    return soln;
}

  