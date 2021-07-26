#include "computer.h"
#include <sstream>

Computer::Computer(uint32_t i) : data(i) {}

void Computer::perform_declarations(std::shared_ptr<Program> prog){
    auto prog_size = prog->getProgramSize();
    for(uint32_t i = 0; i < prog_size; ++i){
        auto ins = prog->getInstruction(i);
        if(ins->priority())
            ins->perform(data);
    }
}

void Computer::perform_operations(std::shared_ptr<Program> prog){
    auto prog_size = prog->getProgramSize();
    for(uint32_t i = 0; i < prog_size; ++i){
        auto ins = prog->getInstruction(i);
        if(!(ins->priority()))
            ins->perform(data);
    }
}

void Computer::boot(std::shared_ptr<Program> prog) {
    perform_declarations(prog);
    perform_operations(prog);

}

void Computer::memory_dump(std::stringstream &s) const{
    for (int i = 0; i < data.get_memory_size(); i++) {
        s << data.get_memory_at(i);
        s << " ";
    }
}


