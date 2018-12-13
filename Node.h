//
// Created by Assaf-Haik-Barouch on 13/12/2018.
//

#ifndef HW3_NODE_H
#define HW3_NODE_H

#include <string>

enum ExpType {
    INTEXP, BYTEEXP, BOOLEXP, STRUCTEXP, FUNCEXP, STRINGEXP
};

struct Node {

};

struct Expression : public Node {
    const ExpType exp_type;

    Expression(const ExpType exp_type) : Node(), exp_type(exp_type) {}
};

struct Structure : public Expression {
    const std::string struct_type;

    Structure(const std::string &struct_type) : Expression(STRUCTEXP), struct_type(struct_type) {}
};

struct Identifier : public Node{
    const std::string ID;

    Identifier(const std::string &ID) : Node(), ID(ID) {}
};

#endif //HW3_NODE_H
