//
// Created by Assaf-Haik-Barouch on 12/12/2018.
//

#ifndef HW3_STRUCTTYPE_H
#define HW3_STRUCTTYPE_H

#include <vector>
#include <string>
#include "Exceptions.h"

enum varType {
    INTTYPE, BYTETYPE, BOOLTYPE, STRUCTTYPE, FUNCTYPE, NOTYPE
};

struct StructType {
    const std::string type_name;
    const std::vector<std::pair<std::string, varType> > fields;

    StructType() : type_name(std::string("")), fields(std::vector<std::pair<std::string, varType> >()) {}

//    StructType(StructType &t) : type_name(std::string(t.type_name)), fields(t.fields) {}

    StructType(const std::string &name, const std::vector<std::pair<std::string, varType> > &fields)
            : type_name(std::string(name)), fields(std::vector<std::pair<std::string, varType> >(fields)) {}
};

void addStructType(std::vector<StructType> &structs, StructType t);

void addStructType(std::vector<StructType> &structs, const std::string &ID,
                   const std::vector<std::pair<std::string, varType> > &fields);

bool isStructTypeInTable(const std::vector<StructType> &structs, const std::string &ID);

StructType getStructTypeEntry(const std::vector<StructType> &structs, const std::string &ID);


#endif //HW3_STRUCTTYPE_H
