//
// Created by Assaf-Haik-Barouch on 12/12/2018.
//

#include "StructType.h"

void addStructType(std::vector<StructType> &structs, StructType t) {
    if (isStructTypeInTable(structs, t.type_name)) {
        throw ShadowingException(t.type_name);
    }
    structs.push_back(t);
}

void addStructType(std::vector<StructType> &structs, const std::string &ID,
                   const StructFieldsType &fields) {
    addStructType(structs, StructType(ID, fields));
}

bool isStructTypeInTable(const std::vector<StructType> &structs, const std::string &ID) {
    return !getStructTypeEntry(structs, ID).fields.empty();
}

StructType getStructTypeEntry(const std::vector<StructType> &structs, const std::string &ID) {
    //find the struct type with the same ID in this table
    for (std::vector<StructType>::const_iterator it = structs.begin(); it != structs.end(); ++it) {
        if (ID == (*it).type_name) {
            return (*it);
        }
    }

    //if there is non, return an empty entry with type of NOTYPE
    return StructType(); //TODO: Not a bug! the grammar does not allow structs without fields
}

varType StructType::getFieldType(const std::string& field_name){
    //find the field with the inputted name
    for(StructFieldsType::const_iterator it = fields.begin(); it != fields.end(); ++it){
        if(field_name == (*it).first){
            return (*it).second;
        }
    }

    //if there is now field with that name
    return NOTYPE;
}


