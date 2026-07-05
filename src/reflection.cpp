#include "lines/lines.hpp"
#include "lines/fraction.hpp"
#include <print>
#include <meta>
#include <iostream>
#include <ranges>

template <typename T>
void printMembers(){
    constexpr std::meta::info r = ^^T;
    constexpr auto ctx1 = std::meta::access_context::current();

    static constexpr auto members = std::define_static_array(std::meta::members_of(r, ctx1));
    template for (constexpr std::meta::info member : members){

        if constexpr (std::meta::is_nonstatic_data_member(member)){
            // std::cout << "Name: " << std::meta::identifier_of(member) << std::endl;
            if constexpr  (std::meta::has_identifier(member)){
                std::println("Member Variable: {}", std::meta::identifier_of(member) );
            } else {
                std::println("Member var without identifier???");
            }
        }  else if constexpr (std::meta::is_operator_function(member)){
            constexpr auto op = std::meta::operator_of(member);
            std::println("Operator: {}", std::meta::symbol_of(op));
        } else if constexpr (std::meta::is_constructor(member)){
            std::println(std::meta::display_string_of(member));
            static constexpr auto parms = std::define_static_array(std::meta::parameters_of(member)
                                 | std::views::transform(std::meta::type_of));
            template for (constexpr auto t : parms){
                std::println("Parm Input: {}", std::meta::display_string_of(t));
            }
        } else if constexpr (std::meta::is_destructor(member)){
            std::println("Found the destructor");
        } else if constexpr (std::meta::is_function(member)){
            constexpr std::meta::info ret = std::meta::return_type_of(member);
            if constexpr (std::meta::has_identifier(member)){
                std::println("Member Function: {} returns {}", std::meta::identifier_of(member), std::meta::display_string_of(ret));
            } else {
                std::println("Member Fn without return identifier???");
            }
        } else {
            std::println("Not one of the above");
        }
        // if constexpr (std::meta::is_nonstatic_data_member(member)){
        //     using MemberType = typename [: std::meta::type_of(member) :];
        //     if constexpr (std::is_aggregate_v<MemberType> && !std::is_same_v<MemberType, std::string>){
        //         printMembers<MemberType>();
        //     }
        // }
        // if constexpr (std::meta::is_function(member)){
        //     if constexpr (std::meta::is_member_function_pointer_type(std::meta::type_of(member)) && 
        //     !std::meta::is_constructor(member) && 
            // !std::meta::is_destructor(member)) {
            // if constexpr (std::meta::is_function(member) && std::meta::is_operator_function(member)) {
                // std::println("Name: {}", );
            // } else if constexpr (std::meta::is_function(member) && std::meta::has_identifier(member)){
                // std::println("Function: {}", std::meta::identifier_of(member));
            // }
        // }
    }
}

void printGlobalNamespaceFns(){
    constexpr std::meta::info r = ^^::;
    constexpr auto ctx1 = std::meta::access_context::current();

    static constexpr auto members = std::define_static_array(std::meta::members_of(r, ctx1));
    template for (constexpr auto m : members){
        if constexpr (std::meta::is_function(m)){
            if  constexpr (std::meta::has_identifier(m)){
                std::println("Free Function {}", std::meta::identifier_of(m));
            } else {
                std::println("Free Function: {}", std::meta::display_string_of(m));
            }
        }
    }
}


int main(){
    // std::println();
    printMembers<Line>();
//     std::println();
//     printMembers<Point>();
//     std::println();
//     printMembers<TopLines>();
    std::println();
    printMembers<Fraction>();
    std::println();
    printGlobalNamespaceFns();
}