#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/filesystem.h>
#include <nanobind/operators.h>
#include <sstream>
#include <string>
#include "lines/lines.hpp"
namespace nb = nanobind;

using namespace nb::literals;

NB_MODULE(lines_ext, m) {
    m.doc() = "Bindings for the lines problem with nanobind";

    // toplines 
    nb::class_<Fraction>(m, "Fraction", "Class Representing a Fraction")
    .def(nb::init<long long, long long>(), "Initializes from integer numerator and denominator") // No function body needed. Forwards to the constructor
    .def(nb::init<long long>(), "Initializes from integer numerator only")
    .def(nb::init<std::string>(), "Converts string to fractional type. Must not have a decimal")
    .def("__repr__", [](const Fraction &f){ 
        std::stringstream s; 
        s << f; 
        return s.str();
     })
    .def("simplify", &Fraction::simplify, "Simplifies a fraction through GCD")
    .def("to_float", &Fraction::toFloat, "Converts to a floating point")
    .def_rw("num", &Fraction::num_, "numerator")
    .def_rw("den", &Fraction::den_, "denominator")
    .def(nb::self + nb::self)
    .def(nb::self - nb::self)
    .def(nb::self * nb::self)
    .def(nb::self / nb::self)
    .def(nb::self == nb::self, nb::is_operator(), "Check equality with cross multiply");

    nb::class_<Point>(m, "Point", "An XY Point where the XY are fractional values")
    .def(nb::init<Fraction, Fraction>(), "Initializes a point from 2 fractions")
    .def("__repr__", [](const Point &p) -> std::string { 
        std::stringstream s; 
        s << p; 
        return s.str();
     })
    .def(nb::self == nb::self, nb::is_operator())
    .def_rw("x", &Point::x_, "x")
    .def_rw("y", &Point::y_, "y");

    nb::class_<Line>(m, "Line", "Slope Intercept line where slope and intercept are fractional")
    .def(nb::init<Fraction, Fraction>(), "Initialize slope and intercept from 2 Fractions")
    .def(nb::init<long long, long long>(), "Initialize slope and intercept from 2 integers")
    .def("__repr__", [](const Line &l){ 
        std::stringstream s; 
        s << l; 
        return s.str();
     })
    .def(nb::self == nb::self, nb::is_operator())
    .def_rw("slope", &Line::slope_, "slope")
    .def_rw("intercept", &Line::intercept_, "intercept");


    nb::class_<TopLines>(m, "TopLines", "Class representing the set of lines at the highest Y value for gi")
    .def(nb::init<>(), "Constructs an empty top lines with no lines or points")
    .def(nb::init<std::string>(), "Constructs from a filename. Often used for testing purposes")
    .def(nb::init<std::vector<Line>, std::vector<Point>>(), "Constructs from a vector of lines and points")
    .def("__repr__", [](const TopLines &t) -> std::string { 
        std::stringstream s; 
        s << t; 
        return s.str();
     })
     .def(nb::self == nb::self, nb::is_operator())
    .def("add", nb::overload_cast<Point>(&TopLines::add), "Add a Point to the top line")
    .def("add", nb::overload_cast<Line>(&TopLines::add), "Add a Line to the top lines")
    .def_ro("lines", &TopLines::lines_, "Lines on top")
    .def_ro("points", &TopLines::points_, "Points where the top line switches from the current line to next line");


    // Free Functions
    m.def("toplines", [](std::filesystem::path filename){
        std::vector<Line> lines = linesFromFile(filename);
        return intersecting_lines(lines);
    }, "filename"_a, "Reads lines from a file and returns the top lines and points for the problem");

    m.def("lines_from_file", &linesFromFile, "filename"_a, "Filename to read lines from");

    m.def("intersecting_lines", [](std::vector<Line>& lines){
        return intersecting_lines(lines);
    }, "lines"_a, "Takes the list of lines and solves for the top lines.");

    m.def("trails", &trails, "lines"_a, "num_trails"_a, "separate"_a,
         "Solves numTrails top lines problems to create trails through the lines");
}
