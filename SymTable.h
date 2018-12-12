//
// Created by Assaf-Haik-Barouch on 10/12/2018.
//

#ifndef HW3_SYMTABLE_H
#define HW3_SYMTABLE_H

#include <string>
#include <vector>
#include "Exceptions.h"

enum varType {
    INTTYPE, BYTETYPE, BOOLTYPE, STRUCTTYPE, FUNCTYPE, NOTYPE
};

typedef std::pair<std::vector<varType>, varType> FunctionType;

struct StructType {
    const std::string type_name;
    const std::vector<std::pair<std::string, varType> > fields;

    StructType() : type_name(std::string("")), fields(std::vector<std::pair<std::string, varType> >()) {}

//    StructType(StructType &t) : type_name(std::string(t.type_name)), fields(t.fields) {}

    StructType(const std::string &name, const std::vector<std::pair<std::string, varType> > &fields)
            : type_name(std::string(name)), fields(std::vector<std::pair<std::string, varType> >(fields)) {}
};


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
};

class SymTable {
private:
    int table_offset;
    std::vector<SymEntry> scope_entries;
    std::vector<StructType> scope_structs;
    SymTable *parent;

    int typeOffset(SymEntry entry);


public:
    SymTable(int offset, SymTable *parent = NULL) : table_offset(offset), scope_entries(std::vector<SymEntry>()),
                                                    parent(parent) {}

    void addEntry(SymEntry e);

    void addEntry(std::string ID, std::string struct_type);

    void addEntry(std::string ID, varType type);

    void addEntry(std::string ID, std::vector<varType> func_params, varType ret_type);

    void addStructType(StructType t);

    void addStructType(std::string ID, std::vector<std::pair<std::string, varType> > fields);

    SymEntry getSymbolEntry(std::string ID);

    bool isSymInTable(std::string ID);

    varType getSymType(std::string ID);

    FunctionType getFunctionType(std::string ID);

    std::string getStructType(std::string ID);

    StructType getStructTypeEntry(std::string ID);

    bool isStructTypeInTable(std::string ID);

    int structTypeOffset(std::string ID);
};


#endif //HW3_SYMTABLE_H
