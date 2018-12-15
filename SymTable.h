//
// Created by Assaf-Haik-Barouch on 10/12/2018.
//

#ifndef HW3_SYMTABLE_H
#define HW3_SYMTABLE_H

#include <string>
#include <vector>
#include "Exceptions.h"
#include "StructType.h"

typedef std::pair<std::vector<varType>, varType> FunctionType;

struct SymEntry {
    const std::string ID;
    const varType type;
    const int offset;
    FunctionType func_type;
    std::string struct_type;

    SymEntry() : type(NOTYPE), offset(0) {}

    SymEntry(const std::string &ID, const std::string &struct_type, int offset) : ID(std::string(ID)), type(STRUCTTYPE),
                                                                                  offset(offset),
                                                                                  struct_type(
                                                                                          std::string(struct_type)) {}

    SymEntry(const std::string &ID, varType type, int offset) : ID(std::string(ID)), type(type), offset(offset) {}

    SymEntry(const std::string &ID, int offset, const std::vector<varType> &func_params, varType ret_type) : ID(
            std::string(ID)),
                                                                                                             type(FUNCTYPE),
                                                                                                             offset(offset),
                                                                                                             func_type(
                                                                                                                     FunctionType(
                                                                                                                             func_params,
                                                                                                                             ret_type)) {}
    bool isVariable(){
        return (type == BOOLTYPE || type == BYTETYPE || type == INTTYPE || type == STRUCTTYPE);
    }
};

class SymTable {
private:
    int table_offset;
    std::vector<SymEntry> scope_entries;
    const std::vector<std::vector<StructType> > &structs_stack;
    SymTable *parent;

    int typeOffset(SymEntry entry);


public:
    SymTable(const std::vector<std::vector<StructType> > &structs_stack, int offset = 0, SymTable *parent = NULL) : table_offset(offset),
                                                                                                scope_entries(
                                                                                                        std::vector<SymEntry>()),
                                                                                                parent(parent), structs_stack(structs_stack){}

    void addEntry(SymEntry e);

    void addEntry(const std::string &ID, const std::string &struct_type);

    void addEntry(const std::string &ID, varType type);

    void addEntry(const std::string &ID, const std::vector<varType> &func_params, varType ret_type);

    SymEntry getSymbolEntry(const std::string &ID);

    bool isSymInTable(const std::string &ID);

    varType getSymType(const std::string &ID);

    FunctionType getFunctionType(const std::string &ID);

    std::string getStructType(const std::string &ID);

    int structTypeOffset(const std::string &ID);
};


#endif //HW3_SYMTABLE_H
