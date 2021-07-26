#ifndef FIRST_OOASM_H
#define FIRST_OOASM_H
#include <memory>

#include "datapack.h"

/*
 *  Ooasm elements
 */

/// L-value interface.
class l_var {
public:
    l_var() = default;

    /// Get variable.
    virtual int64_t getLVar(datapack& data) const = 0;
    /// Set new variable into Computer memory.
    virtual void setLVar(datapack& data, int64_t val) = 0;
};

/// R-val interface.
class r_var {
public:
    r_var() = default;
    /// Get variable.
    virtual int64_t getRVar(datapack& data) const = 0;
};

/// Operation classes from task.

class Num : public r_var {
private:
    /// Numeric value
    int64_t v;

public:
    Num(const int64_t val);

    virtual int64_t getRVar(datapack&) const override;
};

class Lea : public r_var {
private:
    /// Variable id.
    std::string ID;

public:
    Lea(const char* id);

    virtual int64_t getRVar(datapack& data) const override;
};

class Mem : public r_var, public l_var {
private:
    /// Operation used by mem.
    std::shared_ptr<r_var> rVar;

public:
    Mem(const std::shared_ptr<r_var> var);

    virtual void setLVar(datapack& data, int64_t val) override;
    virtual int64_t getLVar(datapack& data) const override;
    virtual int64_t getRVar(datapack& data) const override;
};

/// Operation classes factories.

std::shared_ptr<Num> num(const int64_t val);

std::shared_ptr<Lea> lea(const char* i);

std::shared_ptr<Mem> mem(const std::shared_ptr<r_var> var);

/*
 *  Ooasm instructions
 */

/// Basic instruction interface.
class instruction {
public:
    instruction() = default;

    /// Perform instruction.
    virtual void perform(datapack& data) const = 0;
    /// Check instruction priority (if Computer has to do it before others).
    virtual bool priority() const = 0;
};

/// Variable declaration interface.
class declaration : public instruction {
public:
    declaration() = default;

    virtual void perform(datapack& data) const = 0;
    /// Declaration has priority.
    virtual bool priority() const override {
        return true;
    }
};

/// Operation on Computer interface.
class operation : public instruction {
public:
    operation() = default;

    virtual void perform(datapack& data) const = 0;
    /// Perform after declarations.
    virtual bool priority() const override {
        return false;
    }
};

/// Operations that need only one argument (l_var).
class one_argument : public operation {
protected:
    /// Result destination.
    std::shared_ptr<l_var> dst;

public:
    one_argument(const std::shared_ptr<l_var> dst) : dst(dst) {}

    virtual void perform(datapack& data) const = 0;
};

/// Operations that need two arguments (l_var and r_var).
class two_argument : public operation {
protected:
    /// Result destination.
    std::shared_ptr<l_var> dst;
    /// Additional source.
    std::shared_ptr<r_var> src;

public:
    two_argument(const std::shared_ptr<l_var> dst, const std::shared_ptr<r_var> src) : dst(dst), src(src) {}

    virtual void perform(datapack& data) const = 0;
};

/// Instruction classes from task.

class Data : public declaration {
private:
    std::string ID;
    std::shared_ptr<Num> val;

public:
    Data(const char* id, const std::shared_ptr<Num> value);
    virtual void perform(datapack& data) const override;
};

class Mov : public two_argument {
    using two_argument::two_argument;
    virtual void perform(datapack& data) const override;
};

class Add : public two_argument {
    using two_argument::two_argument;
    virtual void perform(datapack& data) const override;
};

class Sub : public two_argument {
    using two_argument::two_argument;
    virtual void perform(datapack& data) const override;
};

class Inc : public one_argument {
    using one_argument::one_argument;
    virtual void perform(datapack& data) const override;
};

class Dec : public one_argument {
    using one_argument::one_argument;
    virtual void perform(datapack& data) const override;
};

class One : public one_argument {
    using one_argument::one_argument;
    virtual void perform(datapack& data) const override;
};

class Ones : public one_argument {
    using one_argument::one_argument;
    virtual void perform(datapack& data) const override;
};

class Onez : public one_argument {
    using one_argument::one_argument;
    virtual void perform(datapack& data) const override;
};

/// Instruction classes factories.

std::shared_ptr<Data> data(const char* id, const std::shared_ptr<Num> value);
std::shared_ptr<Mov> mov(const std::shared_ptr<l_var> dst, const std::shared_ptr<r_var> src);
std::shared_ptr<Add> add(const std::shared_ptr<l_var> dst, const std::shared_ptr<r_var> src);
std::shared_ptr<Sub> sub(const std::shared_ptr<l_var> dst, const std::shared_ptr<r_var> src);
std::shared_ptr<Inc> inc(const std::shared_ptr<l_var> dst);
std::shared_ptr<Dec> dec(const std::shared_ptr<l_var> dst);
std::shared_ptr<One> one(const std::shared_ptr<l_var> dst);
std::shared_ptr<Ones> ones(const std::shared_ptr<l_var> dst);
std::shared_ptr<Onez> onez(const std::shared_ptr<l_var> dst);

/*
 *  Program
 */

/// Program class declaration.
class Program {
private:
    /// Program instructions.
    std::vector<std::shared_ptr<instruction>> input;

public:
    Program(std::initializer_list<std::shared_ptr<instruction>> l);

    /// Get pointer to instruction by ID.
    std::shared_ptr<instruction> getInstruction(uint32_t i) const;
    /// Number of instructions in program.
    size_t getProgramSize() const;
};

/// Program factory.
std::shared_ptr<Program> program(std::initializer_list<std::shared_ptr<instruction>> l);

#endif  //FIRST_OOASM_H