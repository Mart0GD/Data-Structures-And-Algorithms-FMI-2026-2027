#include "ShuntingYard.hpp"

int getPriority(const tokenType& operand)
{
    switch (operand)
    {
        case tokenType::OPEN_BRACKET: return 0;

        case tokenType::PLUS_BINARY:  return 2;
        case tokenType::MINUS_BINARY: return 2;

        case tokenType::MULT:         return 4;
        case tokenType::DIV:          return 4;
        
        case tokenType::POW:          return 8;

        case tokenType::MINUS_UNARY:  return 16;
        case tokenType::PLUS_UNARY:   return 16;
        
        default: throw std::logic_error("Unknown operand!");
    }   
}

void applyOperand(std::stack<double>& args, const tokenType& operand)
{
    switch (operand)
    {

        case tokenType::PLUS_BINARY:  
        {
            double arg1, arg2;

            if(args.empty()) throw std::logic_error("Invalid expression!");
            arg1 = args.top(); args.pop();

            if(args.empty()) throw std::logic_error("Invalid expression!");
            arg2 = args.top(); args.pop();

            args.push(arg1 + arg2);
        }
        break;

        case tokenType::MINUS_BINARY: 
        {
            double arg1, arg2;

            if(args.empty()) throw std::logic_error("Invalid expression!");
            arg1 = args.top(); args.pop();

            if(args.empty()) throw std::logic_error("Invalid expression!");
            arg2 = args.top(); args.pop();

            args.push(arg2 - arg1);
        }
        break;

        case tokenType::MULT:
        {   
            double arg1, arg2;

            if(args.empty()) throw std::logic_error("Invalid expression!");
            arg1 = args.top(); args.pop();

            if(args.empty()) throw std::logic_error("Invalid expression!");
            arg2 = args.top(); args.pop();

            args.push(arg2 * arg1);
        }
        break;

        case tokenType::DIV:          
        {
            double arg1, arg2;

            if(args.empty()) throw std::logic_error("Invalid expression!");
            arg1 = args.top(); args.pop();

            if(args.empty()) throw std::logic_error("Invalid expression!");
            arg2 = args.top(); args.pop();

            if(std::abs(arg1) <= 1e-9) throw std::logic_error("Division by zero!");

            args.push(arg2 / arg1);
        }
        break;

        case tokenType::POW:
        {
            double arg1, arg2;

            if(args.empty()) throw std::logic_error("Invalid expression!");
            arg1 = args.top(); args.pop();

            if(args.empty()) throw std::logic_error("Invalid expression!");
            arg2 = args.top(); args.pop();

            args.push(powf64(arg2, arg1));
        }
        break;

        case tokenType::MINUS_UNARY:  
        {
            double arg1;

            if(args.empty()) throw std::logic_error("Invalid expression!");
            arg1 = args.top(); args.pop();

            args.push(-arg1);
        }
        break;
        
        case tokenType::PLUS_UNARY:   break;    // nothing

        default: throw std::logic_error("Unknown operand!");
    }   
}

tokenType getOperandType(std::istream& is)
{
    char symb = static_cast<char>(is.get());

    switch (symb)
    {
        case '+':

            if(lastTokenType == tokenType::LITERAL || 
               lastTokenType == tokenType::CLOSE_BRACKET) 
            {
                return tokenType::PLUS_BINARY;
            }
            else return tokenType::PLUS_UNARY;

        break;

        case '-':

            if(lastTokenType == tokenType::LITERAL || 
               lastTokenType == tokenType::CLOSE_BRACKET) 
            {
                return tokenType::MINUS_BINARY;
            }
            else return tokenType::MINUS_UNARY;

        break;

        case '*': return tokenType::MULT;

        case '/': return tokenType::DIV;

        case '^': return tokenType::POW;

        case '(': return tokenType::OPEN_BRACKET;

        case ')': return tokenType::CLOSE_BRACKET;


        default: throw std::logic_error("Unknown operand!");
    }
}

bool isOperand(std::istream& is)
{
    char symb = static_cast<char>(is.peek());

    switch (symb)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case '(':
        case ')':
        
        return true;

        default: return false;
    }
}

token getNextTkn(std::istream& is)
{
    std::streampos checkpoint = is.tellg();

    // Skip whitespace
    is >> std::ws;
    token tkn;

    if(isdigit(is.peek()))
    {
        is >> tkn.val;
        tkn.t = tokenType::LITERAL;
    }
    else if(isOperand(is))
    {
        tkn.t = getOperandType(is);
    }
    else throw std::logic_error("Unknown operator!");

    return tkn;
}
    
int main()
{
    std::string input;

    std::cout << "Enter expression to calculate:";
    std::getline(std::cin, input);

    // Open Stream to proccess
    std::istringstream is(input);
    if(!is) return -1;

    std::stack<double> arguments;
    std::stack<tokenType>  operands;

    // Parse the input
    while (is.peek() != EOF)
    {
        token tkn = getNextTkn(is);

        if(tkn.t == tokenType::LITERAL) arguments.push(tkn.val);
        else if(tkn.t == tokenType::OPEN_BRACKET) operands.push(tkn.t);
        else if(tkn.t == tokenType::CLOSE_BRACKET)
        {
            while(!operands.empty() && operands.top() != tokenType::OPEN_BRACKET)
            {
                tokenType operand = operands.top(); 
                operands.pop();

                applyOperand(arguments, operand);
            }

            // We must have an open bracket on the top
            if(operands.empty())
            {
                throw std::logic_error("No closing bracket!");
            }

            // remove the bracket
            operands.pop(); 
        }
        else
        {
            /*
                Left associative operators use >=
                Right associative operators use >

                OOP approach will do very fine here but for now it's hard coded
            */
            while(!operands.empty()                                 && 
                 (getPriority(operands.top()) > getPriority(tkn.t)  ||
                  getPriority(operands.top()) == getPriority(tkn.t) && 
                  tkn.t != tokenType::POW                           && 
                  tkn.t != tokenType::MINUS_UNARY && tkn.t != tokenType::PLUS_UNARY
            ))
            {
                tokenType operand = operands.top(); 
                operands.pop();

                applyOperand(arguments, operand);
            }

            operands.push(tkn.t);
        }

        lastTokenType = tkn.t;
    }

    while (!operands.empty())
    {
        tokenType operand = operands.top(); 
        operands.pop();

        applyOperand(arguments, operand);
    }

    std::cout << "Result: " << arguments.top() << std::endl;
}