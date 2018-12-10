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

std::string SymTable::getStructType(std::string ID){
    return getSymbolEntry(ID).struct_type;
}

void SymTable::addEntry(SymEntry e){
    entries.push_back(e);
}

void SymTable::addEntry(std::string ID, std::string struct_type, int offset){
    addEntry(SymEntry(ID,struct_type, offset + entries.empty() ? table_offset : entries.back().offset));
}

void SymTable::addEntry(std::string ID, varType type){
    addEntry(SymEntry(ID,type,1 + entries.empty() ? table_offset : entries.back().offset));
}

void SymTable::addEntry(std::string ID, std::vector<varType> func_params, varType ret_type){
    addEntry(SymEntry(ID, entries.empty() ? table_offset : entries.back().offset, func_params, ret_type));
}
