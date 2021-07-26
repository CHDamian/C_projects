#include "datapack.h"

datapack::datapack(uint32_t size) : addresses(), memory(size), size(size), ZF(false), SF(false), var_count(0) {}

uint32_t datapack::get_memory_size() const {
    return size;
}

uint32_t datapack::add_address(std::string id) {
    if (size == var_count)
        throw MemoryOverloadException();
    if (id.size() == 0 || id.size() > 10)
        throw InvalidArgException();

    if (addresses.find(id) == addresses.end())
        addresses[id] = var_count;
    return var_count;
}

uint32_t datapack::get_address(std::string id) {
    if (addresses.find(id) == addresses.end())
        throw InvalidArgException();

    return addresses[id];
}

void datapack::increase_var_count(){
    ++var_count;
}

void datapack::set_memory_at(uint32_t address, int64_t val) {
    if (address < 0 || address >= size)
        throw InvalidArgException();

    memory[address] = val;
}

int64_t datapack::get_memory_at(uint32_t address) const {
    if (address < 0 || address >= size)
        throw InvalidArgException();

    return memory[address];
}

void datapack::set_ZF(bool val) {
    ZF = val;
}
void datapack::set_SF(bool val) {
    SF = val;
}
bool datapack::get_ZF() const {
    return ZF;
}
bool datapack::get_SF() const {
    return SF;
}