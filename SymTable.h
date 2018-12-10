//
// Created by Assaf-Haik-Barouch on 10/12/2018.
//

#ifndef HW3_SYMTABLE_H
#define HW3_SYMTABLE_H

#include <string>
#include <vector>

enum varType {
    INTTYPE, BYTETYPE, BOOLTYPE, STRUCTTYPE, FUNCTYPE, NOTYPE
};

typedef std::pair<std::vector<varType>, varType> FunctionType;


struct SymEntry {
    std::string ID;
    varType type;
    int offset;
    FunctionType func_type;

    SymEntry():type(NOTYPE),offset(0){}

    SymEntry(std::string ID, varType type, int offset) : ID(std::string(ID)), type(type), offset(offset) {}

    SymEntry(std::string ID, int offset, std::vector<varType> func_params, varType ret_type) : ID(std::string(ID)),
                                                                                               type(FUNCTYPE),
                                                                                               offset(offset),
                                                                                               func_type(FunctionType(
                                                                                                       func_params,
                                                                                                       ret_type)) {}

};

class SymTable;

class SymTable {
private:
    int table_offset;
    std::vector<SymEntry> entries;

    SymEntry getSymbolEntry(std::string ID);


public:
    SymTable(int offset) : table_offset(offset), entries(std::vector<SymEntry>()) {}

    bool isSymInTable(std::string ID);

    varType getSymType(std::string ID);

    FunctionType getFunctionType(std::string ID);

};


#endif //HW3_SYMTABLE_H
