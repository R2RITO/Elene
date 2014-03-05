%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.2"

%defines
%define parser_class_name {elene_parser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires
{
# include <string>
class calcxx_driver;
}
