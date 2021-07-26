#include "ooasm.h"

/*
 *  l_var r_var
 */

///Num

Num::Num(const int64_t val) : v(val) {}

int64_t Num::getRVar(datapack&) const {
    return v;
}

///Lea

Lea::Lea(const char* id) : ID(id){};

int64_t Lea::getRVar(datapack& data) const {
    return data.get_address(ID);
}

///Mem

Mem::Mem(const std::shared_ptr<r_var> var) {
    rVar = var;
}

void Mem::setLVar(datapack& data, int64_t val) {
    data.set_memory_at(rVar->getRVar(data), val);
}

int64_t Mem::getLVar(datapack& data) const {
    return data.get_memory_at(rVar->getRVar(data));
}

int64_t Mem::getRVar(datapack& data) const {
    return getLVar(data);
}

/// Factories

std::shared_ptr<Num> num(const int64_t val) {
    return std::make_shared<Num>(val);
}

std::shared_ptr<Lea> lea(const char* i) {
    return std::make_shared<Lea>(i);
}

std::shared_ptr<Mem> mem(const std::shared_ptr<r_var> var) {
    return std::make_shared<Mem>(var);
}

/*
 *  Instructons
 */

/// data

Data::Data(const char* id, const std::shared_ptr<Num> value) : ID(id), val(value) {}

void Data::perform(datapack& data) const {
    data.set_memory_at(data.add_address(ID), val->getRVar(data));
    data.increase_var_count();
}

/// mov

void Mov::perform(datapack& data) const {
    dst->setLVar(data, src->getRVar(data));
}

/// add

void Add::perform(datapack& data) const {
    int64_t result = dst->getLVar(data) + src->getRVar(data);
    dst->setLVar(data, result);
    data.set_SF(result < 0);
    data.set_ZF(result == 0);
}

/// sub

void Sub::perform(datapack& data) const {
    int64_t result = dst->getLVar(data) - src->getRVar(data);
    dst->setLVar(data, result);
    data.set_SF(result < 0);
    data.set_ZF(result == 0);
}

/// inc

void Inc::perform(datapack& data) const {
    int64_t result = dst->getLVar(data) + 1;
    dst->setLVar(data, result);
    data.set_SF(result < 0);
    data.set_ZF(result == 0);
}

/// dec

void Dec::perform(datapack& data) const {
    int64_t result = dst->getLVar(data) - 1;
    dst->setLVar(data, result);
    data.set_SF(result < 0);
    data.set_ZF(result == 0);
}

/// one

void One::perform(datapack& data) const {
    dst->setLVar(data, 1);
}

/// ones

void Ones::perform(datapack& data) const {
    if (data.get_SF())
        dst->setLVar(data, 1);
}

/// onez

void Onez::perform(datapack& data) const {
    if (data.get_ZF())
        dst->setLVar(data, 1);
}

/// Factories

std::shared_ptr<Data> data(const char* id, const std::shared_ptr<Num> value) {
    return std::make_shared<Data>(id, value);
}
std::shared_ptr<Mov> mov(const std::shared_ptr<l_var> dst, const std::shared_ptr<r_var> src) {
    return std::make_shared<Mov>(dst, src);
}
std::shared_ptr<Add> add(const std::shared_ptr<l_var> dst, const std::shared_ptr<r_var> src) {
    return std::make_shared<Add>(dst, src);
}
std::shared_ptr<Sub> sub(const std::shared_ptr<l_var> dst, const std::shared_ptr<r_var> src) {
    return std::make_shared<Sub>(dst, src);
}
std::shared_ptr<Inc> inc(const std::shared_ptr<l_var> dst) {
    return std::make_shared<Inc>(dst);
}
std::shared_ptr<Dec> dec(const std::shared_ptr<l_var> dst) {
    return std::make_shared<Dec>(dst);
}
std::shared_ptr<One> one(const std::shared_ptr<l_var> dst) {
    return std::make_shared<One>(dst);
}
std::shared_ptr<Ones> ones(const std::shared_ptr<l_var> dst) {
    return std::make_shared<Ones>(dst);
}
std::shared_ptr<Onez> onez(const std::shared_ptr<l_var> dst) {
    return std::make_shared<Onez>(dst);
}

/*
 *  Program
 */

Program::Program(std::initializer_list<std::shared_ptr<instruction>> l) : input(l) {}

std::shared_ptr<instruction> Program::getInstruction(uint32_t i) const {
    return input[i];
}

size_t Program::getProgramSize() const {
    return input.size();
}

std::shared_ptr<Program> program(std::initializer_list<std::shared_ptr<instruction>> l) {
    return std::make_shared<Program>(l);
}
