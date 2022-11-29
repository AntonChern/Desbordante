#pragma once
#include "literal.h"

class VarLiteral : public Literal {
public:
    VarLiteral(std::pair<int, std::string> node1, std::pair<int, std::string> node2) {
        this->vars.push_back(node1.first);
        this->vars.push_back(node2.first);

        this->values.push_back(node1.second);
        this->values.push_back(node2.second);
    }
};
