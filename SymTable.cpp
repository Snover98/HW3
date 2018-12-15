//
// Created by Assaf-Haik-Barouch on 10/12/2018.
//

#include "SymTable.h"

#define CALCOFFSET() scope_entries.empty() ? table_offset : scope_entries.back().offset + typeOffset(scope_entries.back())

int SymTable::typeOffset(SymEntry entry) {
    int offset = 0;

    switch (entry.type) {
        case STRUCTTYPE:
            offset += structTypeOffset(entry.struct_type) - 1;
        default:
            offset++;
        case FUNCTYPE:;
    }

    return offset;
}

SymEntry SymTable::getSymbolEntry(const std::string &ID) {
    //find the entry with the same ID in this table
    for (std::vector<SymEntry>::iterator it = scope_entries.begin(); it != scope_entries.end(); ++it) {
        if (ID == (*it).ID) {
            return (*it);
        }
    }

    //if there is non, try the parent table, and if this table has no parent return an entry with type of NOTYPE
    return (parent == NULL) ? SymEntry() : parent->getSymbolEntry(ID);
}


varType SymTable::getSymType(const std::string &ID) {
    return getSymbolEntry(ID).type;
}

bool SymTable::isSymInTable(const std::string &ID) {
    return (getSymbolEntry(ID).type != NOTYPE);
}

FunctionType SymTable::getFunctionType(const std::string &ID) {
    return getSymbolEntry(ID).func_type;
}

std::string SymTable::getStructType(const std::string &ID) {
    return getSymbolEntry(ID).struct_type;
}

void SymTable::addEntry(SymEntry e) {
    if (isSymInTable(e.ID)) {
        throw ShadowingException(e.ID);
    }

    scope_entries.push_back(e);
}

void SymTable::addEntry(const std::string &ID, const std::string &struct_type) {
    addEntry(SymEntry(ID, struct_type, CALCOFFSET()));
}

void SymTable::addEntry(const std::string &ID, varType type) {
    addEntry(SymEntry(ID, type, CALCOFFSET()));
}

void SymTable::addEntry(const std::string &ID, const std::vector<FuncParam> &func_params, varType ret_type) {
    addEntry(SymEntry(ID, func_params, ret_type));
}

int SymTable::structTypeOffset(const std::string &ID) {
    return getStructTypeEntry(structs_stack, ID).fields.size();
}

int SymTable::nextOffset(){
    return CALCOFFSET();
}
