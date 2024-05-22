#include <gtest/gtest.h>
#include "lines.hpp"  
#include "fraction.hpp"

TEST(Lines, LineClass) {
    Line l1 = Line(1, 3);
    Line l2 = Line(Fraction{"3/2"}, Fraction{3});
    Line l3 = Line(-3, 0);

    EXPECT_TRUE(l1 < l2);
    EXPECT_FALSE(l2 < l3);

    EXPECT_EQ(l1(5), Fraction{8});
    EXPECT_EQ(l2(4), Fraction{9});
    EXPECT_EQ(l3(-4), Fraction{12});
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
TEST(BaseCases, BaseCase2Lines1) {
    // Base Case with 2 lines
    std::vector<Line> input{Line{Fraction{"-1/3"}, Fraction(2)}, Line{2, -5}};
    std::vector<Point> pts{Point{3, 1}};
    TopLines expected{input, pts};
    TopLines soln = intersecting_lines(input, 0, 2);
    EXPECT_EQ(expected, soln);
}

TEST(BaseCases, BaseCase2Lines2) {
    // Base case with 2 lines 2
    std::vector<Line> input{Line{Fraction(1) ,Fraction(-4)}, Line{2, -6}};
    TopLines expected{input, {Point{2,-2}}};
    TopLines soln = intersecting_lines(input, 0, 2);
    EXPECT_EQ(expected, soln);
}

// Base Case with 3 lines, 3 visible
TEST(BaseCases, BaseCase3Lines1) {
    std::vector<Line> input{Line{Fraction{"-1/2"},Fraction(2)}, Line{Fraction("1/4"), Fraction(-1)}, Line{1,-7}};
    TopLines expected{input, {Point{4,0}, Point{8,1}}};
    TopLines soln = intersecting_lines(input, 0, 3);
    EXPECT_EQ(expected, soln);
}

// Base Case with 3 lines 2 visible
TEST(BaseCases, BaseCase3Lines2) {
    std::vector<Line> input{Line{Fraction{"-1/2"},2}, Line{Fraction{"1/4"}, Fraction(-1)}, Line{1,-1}};
    std::vector<Line> exp_lines{Line{Fraction{"-1/2"}, 2}, Line{1, -1}};
    std::vector<Point> exp_points{Point{2,1}};
    TopLines expected{exp_lines, exp_points};
    TopLines soln = intersecting_lines(input, 0, 3);
    EXPECT_EQ(expected, soln);
}
TEST(BaseCases, BaseCase2AllIntersect){
    std::vector<Line> input{Line{Fraction{"-1/2"},Fraction{"5/2"}}, Line{0, 2}, Line{1,1}};

    std::vector<Line> exp_lines{Line{Fraction{"-1/2"},Fraction{"5/2"}}, Line{1, 1}};
    std::vector<Point> exp_points{Point{1,2}};
    TopLines expected{exp_lines, exp_points};
    TopLines soln = intersecting_lines(input, 0, 3);
    EXPECT_EQ(expected, soln);
}

TEST(CombineLines, Test1){
    TopLines left{"../inputs/combine1l.txt"};
    TopLines right{"../inputs/combine1r.txt"};
    TopLines expected{"../inputs/combine1-soln.txt"};
    TopLines soln = combine_lines(left, right);
    EXPECT_EQ(expected, soln);
}

TEST(CombineLines, Test2){
    TopLines left{"../inputs/combine2l.txt"};
    TopLines right{"../inputs/combine2r.txt"};
    TopLines expected{"../inputs/combine2-soln.txt"};
    TopLines soln = combine_lines(left, right);
    EXPECT_EQ(expected, soln);
}

TEST(CombineLines, Test3){
    TopLines left{"../inputs/combine3l.txt"};
    TopLines right{"../inputs/combine3r.txt"};
    TopLines expected{"../inputs/combine3-soln.txt"};
    TopLines soln = combine_lines(left, right);
    EXPECT_EQ(expected, soln);
}

TEST(CombineLines, Test4){
    TopLines left{"../inputs/combine4l.txt"};
    TopLines right{"../inputs/combine4r.txt"};
    TopLines expected{"../inputs/combine4-soln.txt"};
    TopLines soln = combine_lines(left, right);
    EXPECT_EQ(expected, soln);
}

TEST(CombineLines, Test5){
    TopLines left{"../inputs/combine5l.txt"};
    TopLines right{"../inputs/combine5r.txt"};
    TopLines expected{"../inputs/combine5-soln.txt"};
    TopLines soln = combine_lines(left, right);
    EXPECT_EQ(expected, soln);
}

TEST(CombineLines, Test6){
    TopLines left{"../inputs/combine6l.txt"};
    TopLines right{"../inputs/combine6r.txt"};
    TopLines expected{"../inputs/combine6-soln.txt"};
    TopLines soln = combine_lines(left, right);
    EXPECT_EQ(expected, soln);
}

TEST(CombineLines, Test7){
    TopLines left{"../inputs/combine7l.txt"};
    TopLines right{"../inputs/combine7r.txt"};
    TopLines expected{"../inputs/combine7-soln.txt"};
    TopLines soln = combine_lines(left, right);
    EXPECT_EQ(expected, soln);
}

TEST(CombineLines, Test8){
    TopLines left{"../inputs/combine8l.txt"};
    TopLines right{"../inputs/combine8r.txt"};
    TopLines expected{"../inputs/combine8-soln.txt"};
    TopLines soln = combine_lines(left, right);
    EXPECT_EQ(expected, soln);
}

TEST(CombineLines, Test9){
    TopLines left{"../inputs/combine9l.txt"};
    TopLines right{"../inputs/combine9r.txt"};
    TopLines expected{"../inputs/combine9-soln.txt"};
    TopLines soln = combine_lines(left, right);
    EXPECT_EQ(expected, soln);
}

TEST(FullDC, TripleOverlapCase){
    std::vector<Line> input = linesFromFile("../inputs/4lines2.txt");
    std::sort(input.begin(), input.end());

    TopLines expected{"../inputs/4lines2-soln.txt"};
    TopLines soln = intersecting_lines(input, 0, 4);
    EXPECT_EQ(expected, soln);
}

// recursive case 4 lines
TEST(FullDC, Recursive4lines) {
    std::vector<Line> input = linesFromFile("../inputs/4lines.txt");
    std::sort(input.begin(), input.end());

    TopLines expected{"../inputs/4lines-soln.txt"};
    TopLines soln = intersecting_lines(input, 0, 4);
    EXPECT_EQ(expected, soln);
}

// recursive case 9 lines
TEST(FullDC, Recursive9lines) {
    std::vector<Line> input = linesFromFile("../inputs/9lines.txt");
    std::sort(input.begin(), input.end());

    TopLines expected{"../inputs/9lines-soln.txt"};
    TopLines soln = intersecting_lines(input, 0, 9);
    EXPECT_EQ(expected, soln);
}
