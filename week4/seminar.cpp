#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <sstream>
#include <fstream>

using std::string;

// Evaluate RPN

class Solution {
public:

    static bool is_operator(std::string& token)
    {
	// operators have only 1 symbol
        if(token.size() > 1) return false;

        char c = token[0];
        return 
        c == '+' ||
        c == '-' ||
        c == '*' ||
        c == '/'; 
    }

    static void calculate(char opp, std::stack<int>& operands)
    {
	// extract arguments 
	int b = operands.top(); operands.pop();
        int a = operands.top(); operands.pop();
 
        switch(opp)
        {
            case '+': operands.push(a + b); break;

	    case '-': operands.push(a - b); break;

            case '*': operands.push(a * b); break;

            case '/': operands.push(a / b); break;
        }
    }

    static int evalRPN(std::vector<std::string>& tokens) {
        std::stack<int> operands;

        for (std::string& token : tokens)
        {
            if (is_operator(token))
                calculate(token[0], operands);
            else
                operands.push(std::stoi(token));
        }

        return operands.top();
    }
};


// Evaluate infix expression without braces 

class Solution2 {
public:

    static int precedence(char c)
    {
        switch(c)
        {
            case '*':
            case '/':
                return 2;
            case '+':
            case '-':
                return 1;
        }

        return 0;
    }
    
    static void calc(char opp, std::stack<int>& operands)
    {
        int b = operands.top(); operands.pop();
        int a = operands.top(); operands.pop();

        switch(opp)
        {
            case '+': operands.push(a + b); break;

            case '-': operands.push(a - b); break;

            case '*': operands.push(a * b); break;

            case '/': operands.push(a / b); break;
        }
    }

    static int calculate(const std::string& s) {

	// Два стека са нужни за да направим Shunting Yard 
        std::stack<char> operators;
        std::stack<int> operands;

	/*
	*    Превръщаме низа в поток за лесна обработка
	*    Може да използваме "std::ws", което зачислява всякакви празни символи! 
	*/    
        std::istringstream ss(s);

        while((ss >> std::ws, ss.peek() != EOF))
        {
            char c = ss.peek();

            if (c == '+' || c == '-' || c == '/' || c == '*')
            {
                while(!operators.empty() && precedence(operators.top()) >= precedence(c))
                {
                    char opp = operators.top();
                    calc(opp, operands);

                    operators.pop();
                }

                operators.push(c);
                ss.get();
            }
            else 
            {
                int num;
                ss >> num;

                operands.push(num);
            } 

        }

	// Изчисляваме останалите операции
        while(!operators.empty())
        {
            char opp = operators.top();
            calc(opp, operands);

            operators.pop();
        }

        return operands.top();
    }
};


// Изчисляване на infix израз с унарни оператори и скоби

class Solution {
public:

    int read_flag;

    enum token_type {
        T_O_PLUS,
        T_O_MINUS_B,
        T_O_MINUS_U,

        T_LITERAL,

        T_LEFT_BRACE,
        T_RIGHT_BRACE,
    };

    struct token
    {
        token_type type;
        long long data;
    };
    
    token get_token(std::istringstream& ss){

        token tkn;

        char symb = ss.peek();

        if(is_number(symb)){
            long long number;
            ss >> number;

            tkn.type = T_LITERAL;
            tkn.data = number;
        }
        else{

            switch (symb)
            {
                case '(':{
                    tkn.type = T_LEFT_BRACE;
                }break;
                case ')':{
                    tkn.type = T_RIGHT_BRACE;
                }break;
                case '+': {
                    tkn.type = T_O_PLUS;
                }break;
                case '-': {
                    if(read_flag == 1) tkn.type = T_O_MINUS_B;
                    else tkn.type = T_O_MINUS_U;
                }break;
            }
            
            ss.get();    
        }

        return tkn;
    }

    int calculate(string s) {
        std::stack<long long> operands;
        std::stack<token_type> operations;

        std::istringstream ss(s);
        read_flag = 0;

        while(ss >> std::ws, ss.peek() != EOF){
            
            token tkn = get_token(ss);

            switch(tkn.type)
            {
                case T_LITERAL:
                {
                    operands.push(tkn.data);
                    read_flag = 1; // прочетено число 
                } break;

                case T_LEFT_BRACE:
                {
                    operations.push(tkn.type);
                    read_flag = 0; // прочетен оператор 
                } break;

                case T_RIGHT_BRACE:
                {
                    while(!operations.empty() && operations.top() != T_LEFT_BRACE)
                    {
                        bool res = calculate_sub_expr(operations.top(), operands);
                        if(!res) return false;
                        operations.pop();
                    }

                    if(operations.empty()) return false;
                    operations.pop();
                    read_flag = 1; // целият израз в скобите е оценен до число!

                } break;

                case T_O_MINUS_B:
                case T_O_MINUS_U:
                case T_O_PLUS:
                {
                    int priority = get_priority(tkn.type);

                    while (!operations.empty() && get_priority(operations.top()) >= priority)
                    {
                        bool res = calculate_sub_expr(operations.top(), operands);
                        if(!res) return false;
                        operations.pop();
                    }

                    operations.push(tkn.type);
                    read_flag = 0; // прочетен оператор 
                } break;

                default: return false;
            }
        }

        while (!operations.empty())
        {
            bool res = calculate_sub_expr(operations.top(), operands);
            if(!res) return false;
            operations.pop();
        }

        return operands.top();
    };

    bool is_number(char c){
        return c >= '0' && c <= '9';
    }

    int get_priority(token_type type){
        switch (type)
        {
            case T_O_PLUS   : return 20;
            case T_O_MINUS_B: return 20;
            case T_O_MINUS_U: return 40;
            default         : return 0;
        }
    }

    bool calculate_sub_expr(token_type type, std::stack<long long>& operands){

        switch (type)
        {
            case T_O_PLUS:
            {
                if(operands.empty()) return false;
                long long rhs = operands.top(); operands.pop();
                
                if(operands.empty()) return false;
                long long lhs = operands.top(); operands.pop();

                operands.push(lhs + rhs);
            }break;
            case T_O_MINUS_B:
            {
                if(operands.empty()) return false;
                long long rhs = operands.top(); operands.pop();

                if(operands.empty()) return false;
                long long lhs = operands.top(); operands.pop();

                operands.push(lhs - rhs);
            }break;
            case T_O_MINUS_U:
            {
                if(operands.empty()) return false;
                long long arg = operands.top(); operands.pop();

                operands.push(-arg);
            }break;
            default: return false;
        };
        return true;
    }
};

int main(void)
{
    std::cout << "Result: " << Solution3::calculate("-2147483648") << std::endl;
    return 0;
}    
