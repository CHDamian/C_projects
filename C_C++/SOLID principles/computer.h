#ifndef FIRST_COMPUTER_H
#define FIRST_COMPUTER_H

#include <iostream>
#include <map>
#include <vector>

#include "datapack.h"
#include "ooasm.h"

class Computer {
private:
    datapack data;
    void perform_declarations(std::shared_ptr<Program> prog);
    void perform_operations(std::shared_ptr<Program> prog);

public:
    Computer(uint32_t i);
    void boot(std::shared_ptr<Program> prog);
    void memory_dump(std::stringstream &s) const;
};

#endif  //FIRST_COMPUTER_H
