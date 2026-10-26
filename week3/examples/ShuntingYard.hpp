#ifndef __SHUNTING_YARD_HPP_INCLUDED__
#define __SHUNTING_YARD_HPP_INCLUDED__

#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <stack>

enum class tokenType
{
    INVALID_TOKEN = -1,

    LITERAL,

    OPEN_BRACKET,
    CLOSE_BRACKET,

    PLUS_BINARY,
    MINUS_BINARY,

    MULT,
    DIV,

    MINUS_UNARY,
    PLUS_UNARY,

    POW,

    TOKENS_CNT
};

struct token
{
    tokenType t;
    double val;
};

static tokenType lastTokenType  = tokenType::INVALID_TOKEN; 

#endif