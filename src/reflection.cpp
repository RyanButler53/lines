#include "lines/lines.hpp"
#include "lines/fraction.hpp"
#include <print>
#include <meta>
#include <iostream>

template <typename T>
void printMembers(){
    constexpr std::meta::info r = ^^T;
    constexpr auto ctx1 = std::meta::access_context::current();

    template for (constexpr std::meta::info member : std::define_static_array(std::meta::members_of(r, ctx1))){

        if constexpr (std::meta::has_identifier(member)){
            // std::cout << "Name: " << std::meta::identifier_of(member) << std::endl;
            std::println("Name: {}",std::meta::identifier_of(member) );
        } else if constexpr (std::meta::is_operator_function(member)){
            std::println ("Member is an operator overload!");
        } else if constexpr (std::meta::is_constructor(member)){
            std::println(" Member is a constructor");
        } else if constexpr (std::meta::is_destructor(member)){
            std::println("Found the destructor");
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


int main(){
    // std::println();
    printMembers<Line>();
//     std::println();
//     printMembers<Point>();
//     std::println();
//     printMembers<TopLines>();
//     std::println();
//     printMembers<Fraction>();
}