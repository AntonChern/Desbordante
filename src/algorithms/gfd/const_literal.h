#pragma once
#include "literal.h"

class ConstLiteral : public Literal {
public:
    ConstLiteral(std::pair<int, std::string> node, std::string value) {
        this->vars.push_back(node.first);

        this->values.push_back(node.second);
        this->values.push_back(value);
    }
};
