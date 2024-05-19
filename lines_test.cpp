#include <gtest/gtest.h>
#include "lines.hpp"  
#include "lines.cpp"  


TEST(Lines, LineClass) {
    Line l1 = Line(1, 3);
    Line l2 = Line(1.5, 3);
    Line l3 = Line(-3, 0);

    EXPECT_TRUE(l1 < l2);
    EXPECT_FALSE(l2 < l3);

    EXPECT_DOUBLE_EQ(l1(5), 8);
    EXPECT_DOUBLE_EQ(l2(4), 9);
    EXPECT_DOUBLE_EQ(l3(-4), 12);
}
TEST(Points, LineIntersect) {
    Point P1 = Point(0.0, 3.0);
    Point P2 = Point(4, 7);

    Line l1 = Line(1, 3);
    Line l2 = Line(2, 3);
    Line l3 = Line(0, 7);

    EXPECT_EQ(intersect(l1, l2), P1);
    EXPECT_EQ(intersect(l1, l3), P2);
}

// Individual Test Cases for Top Lines
TEST(Solutions1, BaseCase2Lines1) {
    // Base Case with 2 lines
    std::vector<Line> input{Line{-1.0 / 3, 2}, Line{2, -5}};
    std::vector<Point> pts{Point{3, 1}};
    TopLines expected{input, pts};
    TopLines soln = intersecting_lines(input, 0, 2);
    EXPECT_EQ(expected, soln);
}

TEST(Solutions2, BaseCase2Lines2) {
    // Base case with 2 lines 2
    std::vector<Line> input{Line{1.0 ,-4}, Line{2, -6}};
    TopLines expected{input, {Point{2,-2}}};
    TopLines soln = intersecting_lines(input, 0, 2);
    EXPECT_EQ(expected, soln);
}

// Base Case with 3 lines, 3 visible
TEST(Solutions3, BaseCase3Lines1) {
    std::vector<Line> input{Line{-0.5,2}, Line{0.25, -1}, Line{1,-7}};
    TopLines expected{input, {Point{4,0}, Point{8,1}}};
    TopLines soln = intersecting_lines(input, 0, 3);
    EXPECT_EQ(expected, soln);
}

// Base Case with 3 lines 2 visible
TEST(Solutions4, BaseCase3Lines2) {
    std::vector<Line> input{Line{-0.5,2}, Line{0.25, -1}, Line{1,-1}};
    std::vector<Line> exp_lines{Line{-0.5, 2}, Line{1, -1}};
    std::vector<Point> exp_points{Point{2,1}};
    TopLines expected{exp_lines, exp_points};
    TopLines soln = intersecting_lines(input, 0, 3);
    EXPECT_EQ(expected, soln);
}
TEST(Solutions5, BaseCase2AllIntersect){
    std::vector<Line> input{Line{-0.5,2.5}, Line{0, 2}, Line{1,1}};

    std::vector<Line> exp_lines{Line{-0.5, 2.5}, Line{1, 1}};
    std::vector<Point> exp_points{Point{1,2}};
    TopLines expected{exp_lines, exp_points};

    TopLines soln = intersecting_lines(input, 0, 3);
    EXPECT_EQ(expected, soln);
}

TEST(Solutions6, FloatingPointError) {
    // Base Case with 2 lines and floating point error

    // std::vector<Line> input{Line{-1.0, 2}, Line{2/3, 1}};
    // std::vector<Point> pts{Point{-3, 1}};
    Point p = intersect(Line{-1.0, 2}, Line{-2.0/3, 1});
    Point expected = Point(3, -1);
    EXPECT_NEAR(expected.x_, p.x_, 0.0001);
    EXPECT_NEAR(expected.y_, p.y_, 0.0001);
}

TEST(Combine1, Test1){
    TopLines left{"../inputs/combine1l.txt"};
    TopLines right{"../inputs/combine1r.txt"};
    TopLines expected{"../inputs/combine1-soln.txt"};
    TopLines soln = combine_lines(left, right);
    EXPECT_EQ(expected, soln);
}

TEST(Combine2, Test2){
    TopLines left{"../inputs/combine2l.txt"};
    TopLines right{"../inputs/combine2r.txt"};
    TopLines expected{"../inputs/combine2-soln.txt"};
    TopLines soln = combine_lines(left, right);
    EXPECT_EQ(expected, soln);
}

TEST(Combine3, Test3){
    TopLines left{"../inputs/combine3l.txt"};
    TopLines right{"../inputs/combine3r.txt"};
    TopLines expected{"../inputs/combine3-soln.txt"};
    TopLines soln = combine_lines(left, right);
    EXPECT_EQ(expected, soln);
}

TEST(Combine4, Test4){
    TopLines left{"../inputs/combine4l.txt"};
    TopLines right{"../inputs/combine4r.txt"};
    TopLines expected{"../inputs/combine4-soln.txt"};
    TopLines soln = combine_lines(left, right);
    EXPECT_EQ(expected, soln);
}

TEST(Combine5, Test5){
    TopLines left{"../inputs/combine5l.txt"};
    TopLines right{"../inputs/combine5r.txt"};
    TopLines expected{"../inputs/combine5-soln.txt"};
    TopLines soln = combine_lines(left, right);
    EXPECT_EQ(expected, soln);
}

TEST(DC4Overlap3, TripleOverlapCase){
    std::vector<Line> input = linesFromFile("../inputs/4lines2.txt");
    std::sort(input.begin(), input.end());

    TopLines expected{"../inputs/4lines2-soln.txt"};
    TopLines soln = intersecting_lines(input, 0, 4);
    EXPECT_EQ(expected, soln);
}

// recursive case 4 lines
TEST(FullDC4, Recursive4lines) {
    std::vector<Line> input = linesFromFile("../inputs/4lines.txt");
    std::sort(input.begin(), input.end());

    TopLines expected{"../inputs/4lines-soln.txt"};
    TopLines soln = intersecting_lines(input, 0, 4);
    // EXPECT_EQ(expected, soln);
    for (size_t i = 0; i < soln.points_.size();++i)
    {
        EXPECT_EQ(soln.lines_[i], expected.lines_[i]);
        EXPECT_NEAR(soln.points_[i].x_, expected.points_[i].x_, 0.0000001);
        EXPECT_NEAR(soln.points_[i].y_, expected.points_[i].y_, 0.0000001);
    }
    EXPECT_EQ(soln.lines_.back(), expected.lines_.back());
}

// recursive case 9 lines
TEST(FullDC9, Recursive9lines) {
    std::vector<Line> input = linesFromFile("../inputs/9lines.txt");
    std::sort(input.begin(), input.end());

    TopLines expected{"../inputs/9lines-soln.txt"};
    TopLines soln = intersecting_lines(input, 0, 9);
    EXPECT_EQ(expected, soln);
}