//
// Created by Assaf-Haik-Barouch on 10/12/2018.
//

#include "SymTable.h"

SymEntry SymTable::getSymbolEntry(std::string ID) {
    //find the entry with the same ID in this table
    for(std::vector<SymEntry>::iterator it = entries.begin(); it != entries.end(); ++it){
        if(ID.compare((*it).ID) == 0){
            return (*it);
        }
    }

    //if there is non, return an entry with type of NOTYPE
    return SymEntry();
}



varType SymTable::getSymType(std::string ID) {
    return getSymbolEntry(ID).type;
}

bool SymTable::isSymInTable(std::string ID) {
    return (getSymbolEntry(ID).type != NOTYPE);
}

FunctionType SymTable::getFunctionType(std::string ID) {
    return getSymbolEntry(ID).func_type;
}