#ifndef FIRST_DATAPACK_H
#define FIRST_DATAPACK_H

#ifndef DATAPACK_H
#define DATAPACK_H
#include <map>
#include <string>
#include <vector>

/// Exceptions


class MemoryOverloadException : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return "Can't declare another variable!";
    }
};

class InvalidArgException : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return "Invalid argument value!";
    }
};
/// Class

class datapack {
private:
    std::map<std::string, uint32_t> addresses;
    std::vector<int64_t> memory;
    uint32_t size, var_count;
    bool ZF, SF;

public:
    datapack(uint32_t size);

    uint32_t get_memory_size() const;

    uint32_t add_address(std::string id);
    uint32_t get_address(std::string id);

    void increase_var_count();

    void set_memory_at(uint32_t address, int64_t val);
    int64_t get_memory_at(uint32_t address) const;

    void set_ZF(bool val);
    void set_SF(bool val);
    bool get_ZF() const;
    bool get_SF() const;
};

#endif  //DATAPACK_H

#endif  //FIRST_DATAPACK_H
