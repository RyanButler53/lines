// THE LINES PROBLEM
#include <iostream>
#include "lines.hpp"
#include <algorithm>
#include <fstream>
#include <cassert>
using namespace std;

// Line Class
Line::Line(double slope, double intercept):
    slope_{slope}, intercept_{intercept}{}

bool Line::operator<(const Line& l) const{
    return slope_ < l.slope_;
}

double Line::operator()(const double x) const{
    return slope_ * x + intercept_;
}

bool Line::operator==(const Line& other) const {
    return (slope_ == other.slope_) and (intercept_ == other.intercept_);
}

std::ostream &operator<<(std::ostream& os, const Line &l){
    os << "y = " << l.slope_ << "x + " << l.intercept_;
    return os;
}

// Point Class
Point::Point(double x, double y):
    x_{x}, y_{y}{}

bool Point::operator<(const Point& p) const{
    return y_ < p.y_;
}

bool Point::operator==(const Point& p) const{
    return (x_ == p.x_) and (y_ == p.y_);
}

std::ostream &operator<<(std::ostream& os, const Point &p){
    os << "(" << p.x_ << ", " << p.y_ << ")";
    return os;
}

double getDouble(std::string s){
    size_t slashInd = s.find("/");
    if (slashInd != string::npos){
        double numerator = stod(s.substr(0, slashInd));
        double denominator = stod(s.substr(slashInd+1));
        return numerator / denominator;
    } else {
        return stod(s);
    }
}

std::vector<Line> linesFromFile(std::string filename){
    ifstream input{filename};
    string line;
    std::vector<Line> lines;
    while (getline(input, line)) {
        // Given in slope intercept. Slope may have a slash in it
        size_t spaceInd = line.find(" ");
        if (spaceInd != string::npos){
            string slope = line.substr(0, spaceInd);
            string intercept = line.substr(spaceInd + 1);
            // Both can have decimal points and slashes
            double lineSlope = getDouble(slope);
            double lineIntercept = getDouble(intercept);
    
            lines.push_back(Line{lineSlope, lineIntercept});
        } else {
            double slope = getDouble(line);
            lines.push_back(Line{slope, 0.0});
        }
    }
    return lines;
}

// Finds the point line 1
Point intersect(const Line& l1, const Line& l2){
    double x = (l1.intercept_ - l2.intercept_) / (l2.slope_ - l1.slope_);
    double y = l1(x);
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
            // Both can have decimal points and slashes
            double part1dbl = getDouble(part1);
            double part2dbl = getDouble(part2);
    
            if (points){
                points_.push_back(Point{part1dbl, part2dbl});
            } else {
                lines_.push_back(Line{part1dbl, part2dbl});
            }
        } else {
            assert(!points);
            double slope = getDouble(line);
            lines_.push_back(Line{slope, 0.0});
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
        os << l << ", ";
    }
    os << endl;
    for (const Point& p : tl.points_){
        os << p << ", ";
    }
    return os;
}

// May have to change this fn signature
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
    // Recursive Case
}

TopLines combine_lines(TopLines& left, TopLines& right){

    TopLines soln;
    // soln.add(left.lines_[0]);
    // Iterate over 
    size_t left_li = 0; // maybe use iterators or combine? 
    size_t left_pi = 0; 
    
    size_t right_li = 0;
    size_t right_pi = 0; // right point

    double curr_x = min(right.points_[right_pi].x_, left.points_[left_pi].x_);
    while (true){
        // Evaluate
        double left_y = left.lines_[left_li](curr_x);
        double right_y = right.lines_[right_li](curr_x);
        if (left_y > right_y){ // left on top, no right on top yet
            // If left point is the next point:
            if (left.points_[left_pi].x_ < right.points_[right_pi].x_){
                // Increment the left line and add to solution
                soln.add(left.lines_[left_li]);
                soln.add(left.points_[left_pi]);
                ++left_li;
                ++left_pi;
                // If out of points, then switch to right side
                if (left_pi == left.points_.size()){
                    curr_x = right.points_[right_pi].x_; 
                } else {
                    curr_x = left.points_[left_pi].x_;
                }
            } else if (left.points_[left_pi].x_ == right.points_[right_pi].x_) {
                    // Increment the left line and add to solution
                soln.add(left.lines_[left_li]);
                soln.add(left.points_[left_pi]);
                ++left_li;
                ++left_pi;
                // Increment Right line
                ++right_li;
                ++right_pi;
                if (left_pi == left.points_.size()){
                    curr_x = right.points_[right_pi].x_; 
                } else {
                    curr_x = min(left.points_[left_pi].x_, right.points_[right_pi].x_);
                }
            }
            else
            { // right is next -  update right without updating soln
                ++right_li;
                ++right_pi;
                curr_x = right.points_[right_pi].x_;
            }
        } else { // right line on top!. Add both
            Line l = left.lines_[left_li];
            Line r = right.lines_[right_li];
            soln.add(l);
            // soln.add(r); // this gets added later 
            
            // If EQUAL don't add intersect point right away. 
            Point intersection = intersect(l, r);
            if (left_y != right_y){
                soln.add(intersection);
            }
            // Add all points
            for (; right_pi < right.points_.size(); ++right_pi){
                soln.add(right.points_[right_pi]);
            }
            // Add all lines if strictly greater than intersection. 
            for (; right_li < right.lines_.size(); ++right_li){
                // if (right.lines_[right_li](curr_x) > intersection.y_){
                    soln.add(right.lines_[right_li]);
                // }
            }
            return soln;
        }
    }
    return soln;
}

  