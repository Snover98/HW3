//
// Created by Assaf-Haik-Barouch on 13/12/2018.
//

#ifndef HW3_NODE_H
#define HW3_NODE_H

#include <string>

//the type of the expression
enum ExpType {
    INTEXP, BYTEEXP, BOOLEXP, STRUCTEXP, FUNCEXP, STRINGEXP
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

//checks if an expression is a number
inline bool isNumExp(Expression* e){
    return (e->exp_type == INTEXP || e->exp_type == BYTEEXP);
}

//returns the type of a binary operator between nums (like +,-,/,*)
inline ExpType operatorType(Expression* num1, Expression* num2){
    return ((num1->exp_type == INTEXP || num2->exp_type == INTEXP) ? INTEXP : BYTEEXP);
}




#endif //HW3_NODE_H
