#include <iostream>

#include "gfd.h"

void GFD::print() const {
	this->pattern.print();
	std::cout << std::endl << "Premises:   ";
	for (const Literal& l : this->premises) {
		std::vector<int> vars = l.getVars();
		std::vector<std::string> values = l.getValues();
		if (vars.size() == 1) {
			// ConstLiteral
			std::cout << vars.at(0) << "." << values.at(0) << "=" << values.at(1) << "; ";
		} else {
			// VarLiteral
			std::cout << vars.at(0) << "." << values.at(0) << "="
				<< vars.at(1) << "." << values.at(1) << "; ";
		}
	}
	std::cout << std::endl << "=>" << std::endl << "Conclusion: ";
	for (const Literal& l : this->conclusion) {
		std::vector<int> vars = l.getVars();
		std::vector<std::string> values = l.getValues();
		if (vars.size() == 1) {
			// ConstLiteral
			std::cout << vars.at(0) << "." << values.at(0) << "=" << values.at(1) << "; ";
		} else {
			// VarLiteral
			std::cout << vars.at(0) << "." << values.at(0) << "="
				<< vars.at(1) << "." << values.at(1) << "; ";
		}
	}
}
