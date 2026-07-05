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

nb::class_<Point> bindPoint(nb::module_ m){
    nb::class_<Point> cls(m, "Point", "An XY Point where the XY are fractional values");
    cls.def(nb::init<Fraction, Fraction>(), "Initializes a point from 2 fractions");
    cls.def("__repr__", [](const Point &p) -> std::string { 
        std::stringstream s; 
        s << p; 
        return s.str();
        });
    cls.def(nb::self == nb::self, nb::is_operator());
    cls.def_rw("x", &Point::x_, "x");
    cls.def_rw("y", &Point::y_, "y");

    return cls;
}

constexpr std::string_view operatorName(std::meta::operators op) {
    switch (op) {
        case std::meta::operators::plus:       return "__add__";
        case std::meta::operators::minus:      return "__sub__";
        case std::meta::operators::star:       return "__mul__";
        case std::meta::operators::slash:      return "__truediv__";
        case std::meta::operators::equal_equal: return "__eq__";
        default: return "";
    }
}

template <typename T>
nb::class_<T> bindStruct(nb::module_ m){
    nb::class_<T> cls(m, std::meta::identifier_of(^^T));
    constexpr auto ctx = std::meta::access_context::unchecked();

    static constexpr auto members = std::define_static_array(std::meta::members_of(r, ctx));
    template for (constexpr std::meta::info member : members){

        // Constructors
        if constexpr (std::meta::is_constructor(member)){
            static constexpr auto params = std::define_static_array(std::meta::parameters_of(member));
            // Need to pull the types of the reflection out with the splice? 
            cls.def(nb::init<[:params:]>(), "");
        }

        // Member Variables
        if (constexpr (std::meta::is_nonstatic_data_member(member))){
            cls.def_rw(std::meta::identifier_of(member), [:member:]);
        }

        // Operators: 
        if (constexpr (std::meta::is_operator_function(member))){
            constexpr auto op = std::meta::operator_of(member);
            constexpr auto py_operator = operatorName(op);
            cls.def(py_name.data(), [:member:], nb::is_operator());
        }
    }
}



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
    .def(nb::self + nb::self, nb::is_operator())
    .def(nb::self - nb::self, nb::is_operator())
    .def(nb::self * nb::self, nb::is_operator())
    .def(nb::self / nb::self, nb::is_operator())
    .def(nb::self == nb::self, nb::is_operator(), "Check equality with cross multiply");

    bindPoint(m);
    // nb::class_<Point>(m, "Point", "An XY Point where the XY are fractional values")
    // .def(nb::init<Fraction, Fraction>(), "Initializes a point from 2 fractions")
    // .def("__repr__", [](const Point &p) -> std::string { 
    //     std::stringstream s; 
    //     s << p; 
    //     return s.str();
    //  })
    // .def(nb::self == nb::self, nb::is_operator())
    // .def_rw("x", &Point::x_, "x")
    // .def_rw("y", &Point::y_, "y");

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
