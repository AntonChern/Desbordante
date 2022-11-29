#pragma once
#include <vector>

#include "pattern.h"
#include "literal.h"

class GFD {
private:
    Pattern pattern;
    std::vector<Literal> premises;
    std::vector<Literal> conclusion;
public:
    GFD(Pattern& pattern_, std::vector<Literal>& premises_, std::vector<Literal>& conclusion_) : pattern(pattern_), premises(premises_), conclusion(conclusion_) {}

    Pattern getPattern() const { return this->pattern; }
    std::vector<Literal> getPremises() const { return this->premises; }
    std::vector<Literal> getConclusion() const { return this->conclusion; }

    void print() const;
};
