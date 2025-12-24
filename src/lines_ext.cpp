#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/filesystem.h>
#include <sstream>
#include <string>
#include "lines.hpp"
namespace nb = nanobind;

using namespace nb::literals;

NB_MODULE(lines_ext, m) {
    m.doc() = "Bindings for the lines problem with nanobind";

    // toplines 
    nb::class_<Fraction>(m, "Fraction")
    .def(nb::init<long long, long long>()) // No function body needed. Forwards to the constructor
    .def(nb::init<long long>())
    .def(nb::init<std::string>())
    .def("__repr__", [](const Fraction &f){ 
        std::stringstream s; 
        s << f; 
        return s.str();
     })
    .def("simplify", &Fraction::simplify)
    .def_rw("num", &Fraction::num_)
    .def_rw("den", &Fraction::den_);

    nb::class_<Point>(m, "Point")
    .def(nb::init<Fraction, Fraction>())
    .def("__repr__", [](const Point &p) -> std::string { 
        std::stringstream s; 
        s << p; 
        return s.str();
     })
    .def_rw("x", &Point::x_)
    .def_rw("y", &Point::y_);

    nb::class_<Line>(m, "Line")
    .def(nb::init<Fraction, Fraction>())
    .def(nb::init<long long, long long>())
    .def("__repr__", [](const Line &l){ 
        std::stringstream s; 
        s << l; 
        return s.str();
     })
    .def_rw("slope", &Line::slope_)
    .def_rw("intercept", &Line::intercept_);


    nb::class_<TopLines>(m, "TopLines")
    .def(nb::init<>())
    .def(nb::init<std::string>())
    .def(nb::init<std::vector<Line>, std::vector<Point>>())
    .def("__repr__", [](const Fraction &t) -> std::string { 
        std::stringstream s; 
        s << t; 
        return s.str();
     })
    .def("add", nb::overload_cast<Point>(&TopLines::add), "Add a Point to the top line")
    .def("add", nb::overload_cast<Line>(&TopLines::add), "Add a Line to the top lines")
    .def_ro("lines", &TopLines::lines_)
    .def_ro("points", &TopLines::points_);

    m.def("toplines", [](std::filesystem::path filename){
        std::vector<Line> lines = linesFromFile(filename);
        TopLines soln = intersecting_lines(lines);
        return soln;
    }, "filename"_a);
}
