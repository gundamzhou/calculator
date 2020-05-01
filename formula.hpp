#ifndef FORMULA_H
#define FORMULA_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

class Formula {
private:
    std::vector<std::vector<std::string>> f_decomposed;
    int f_iteration;
public:

    std::string str_given;

    Formula();

    Formula(std::string formulas);

    void appendFromString(std::string formula);

    bool isOperation(char know);

    float operate(char operation, float a, float b);

    float getY(float x);

    void readFormula(std::string input);
};
#endif // FORMULA_H
