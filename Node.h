//
// Created by Assaf-Haik-Barouch on 13/12/2018.
//

#ifndef HW3_NODE_H
#define HW3_NODE_H

#include <string>
#include <vector>

//the type of the expression
enum ExpType {
    INTEXP, BYTEEXP, BOOLEXP, STRUCTEXP, FUNCEXP, STRINGEXP, VOIDEXP
};

//general type for lex output
struct Node {

};

//struct for expressions, we need to know their type
struct Expression : public Node {
    const ExpType exp_type;

    Expression(const ExpType exp_type) : Node(), exp_type(exp_type) {}
};

//struct for structures, the extra string field is so we can now what kind of struct it is
struct Structure : public Expression {
    const std::string struct_type;

    Structure(const std::string &struct_type) : Expression(STRUCTEXP), struct_type(struct_type) {}
};

//used when there is an identifier read by lex, only used to create the relevant Expression and than deleted
struct Identifier : public Node{
    const std::string ID;

    Identifier(const std::string &ID) : Node(), ID(ID) {}
};

struct ExpressionList : public Node{
    std::vector<Expression> expressions;

    ExpressionList() : Node(), expressions(std::vector<Expression>()){}
};

//checks if an expression is a number
inline bool isNumExp(Expression* e){
    return (e->exp_type == INTEXP || e->exp_type == BYTEEXP);
}

//returns the type of a binary operator between nums (like +,-,/,*)
inline ExpType operatorType(Expression* num1, Expression* num2){
    return ((num1->exp_type == INTEXP || num2->exp_type == INTEXP) ? INTEXP : BYTEEXP);
}

bool isLegalExpType(Expression* actual, Expression* expected){
    if(expected->exp_type == INTEXP){
        return (actual->exp_type == INTEXP || actual->exp_type == BYTEEXP);
    }

    if(expected->exp_type == STRUCTEXP){
        return (((Structure*)actual)->struct_type == ((Structure*)expected)->struct_type);
    }

    return (expected->exp_type == actual->exp_type);
}

bool isLegalExpType(Expression* actual, ExpType expected){
    Expression e = Expression(expected);
    return isLegalExpType(actual, &e);
}

bool isLegalExpType(Expression* actual, std::string &expected){
    Structure s = Structure(expected);
    return isLegalExpType(actual, &s);
}


#endif //HW3_NODE_H
