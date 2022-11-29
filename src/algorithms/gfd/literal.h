#pragma once
#include <vector>
#include <string>

class Literal {
protected:
    std::vector<int> vars;
    std::vector<std::string> values;
public:
    Literal() = default;
    Literal(std::vector<int>& vars_, std::vector<std::string>& values_) : vars(vars_), values(values_) {}

    std::vector<int> getVars() const { return this->vars; }
    std::vector<std::string> getValues() const { return this->values; }
};