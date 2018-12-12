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

SymEntry SymTable::getSymbolEntry(std::string ID) {
    //find the entry with the same ID in this table
    for (std::vector<SymEntry>::iterator it = scope_entries.begin(); it != scope_entries.end(); ++it) {
        if (ID.compare((*it).ID) == 0) {
            return (*it);
        }
    }

    //if there is non, try the parent table, and if this table has no parent return an entry with type of NOTYPE
    return (parent == NULL) ? SymEntry() : parent->getSymbolEntry(ID);
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

std::string SymTable::getStructType(std::string ID) {
    return getSymbolEntry(ID).struct_type;
}

void SymTable::addEntry(SymEntry e) {
    if (isSymInTable(e.ID)) {
        throw ShadowingException(e.ID);
    }

    scope_entries.push_back(e);
}

void SymTable::addEntry(std::string ID, std::string struct_type) {
    addEntry(SymEntry(ID, struct_type, CALCOFFSET()));
}

void SymTable::addEntry(std::string ID, varType type) {
    addEntry(SymEntry(ID, type, CALCOFFSET()));
}

void SymTable::addEntry(std::string ID, std::vector<varType> func_params, varType ret_type) {
    addEntry(SymEntry(ID, CALCOFFSET(), func_params, ret_type));
}

StructType SymTable::getStructTypeEntry(std::string ID) {
    //find the struct type with the same ID in this table
    for (std::vector<StructType>::iterator it = scope_structs.begin(); it != scope_structs.end(); ++it) {
        if (ID.compare((*it).type_name) == 0) {
            return (*it);
        }
    }

    //if there is non, try the parent table, and if this table has no parent return an entry with type of NOTYPE
    return (parent == NULL) ? StructType() : parent->getStructTypeEntry(ID);
}

int SymTable::structTypeOffset(std::string ID) {
    return getStructTypeEntry(ID).fields.size();
}

void SymTable::addStructType(StructType t) {
    if (isStructTypeInTable(t.type_name)) {
        throw ShadowingException(t.type_name);
    }

    scope_structs.push_back(t);
}

void SymTable::addStructType(std::string ID, std::vector<std::pair<std::string, varType> > fields) {
    addStructType(StructType(ID, fields));
}

bool SymTable::isStructTypeInTable(std::string ID) {
    return !getStructTypeEntry(ID).fields.empty();
}