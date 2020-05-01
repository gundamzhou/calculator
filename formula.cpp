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
#include "formula.hpp"

bool Formula::isOperation(char know) {
    const int lengthListe = 5;
    char liste[lengthListe] = { '^', '/', '+', '-', '*' };
    for (int i = 0; i < lengthListe; i++) {
        if (know == liste[i]) {
            return true;
        }
    }
    return false;
}

Formula::Formula() {
    f_iteration = 0;
    str_given = "x^2-1";
    this->appendFromString("x^2-1");
}

Formula::Formula(std::string formulas){
    f_iteration = 0;
    str_given = formulas;
    this->appendFromString(formulas);
}

void Formula::appendFromString(std::string formula) {
    std::vector<std::string> buffer;
    f_iteration = 0;
    buffer.push_back("");
    buffer.push_back("");
    for (int i = 0; i < formula.length(); i++)
    {
        if (formula[i] == 'x') {
            buffer[0] = formula[i];
            buffer[1] = "unknown";
        }
        else if (formula[i] >= 48 && formula[i] < 58 || formula[i] == (char)46) {
            buffer[0] = formula[i];
            buffer[1] = "integer";
        }
        else if (isOperation(formula[i])) {
            buffer[0] = formula[i];
            buffer[1] = "operation";
        }

        //free the buffer
        if (f_iteration) {
            if (buffer[1] == this->f_decomposed[f_iteration - 1][1]) {
                this->f_decomposed[f_iteration - 1][0] += buffer[0];
            }
            else {
                f_decomposed.push_back(buffer);
                f_iteration++;
            }
            buffer[0] = "";
            buffer[1] = "";
        }
        else {
            this->f_decomposed.push_back(buffer);
            buffer[0] = "";
            buffer[1] = "";
            f_iteration++;
        }
    }
}

float Formula::operate(char operation, float a, float b) {
    float result = 0;
    switch (operation) {
    case '^':
        result = pow(a, b);
        break;
    case '/':
        if (b) result = a / b;
        break;
    case '+':
        result = a + b;
        break;
    case '-':
        result = a - b;
        break;
    case '*':
        result = a * b;
        break;
    default:
        break;
    }
    return result;
}

float Formula::getY(float x) {
    float value;
    for (int i = 0; i < f_iteration; i++) {
        if (f_decomposed[i][1] == "unknown") {
            f_decomposed[i][0] = std::to_string(x);
        }
    }

    if (f_decomposed[0][1] != "integer" && f_decomposed[0][1] != "unknown") {
        return 0;
    }
    else {
        std::string::size_type sz;
        value = std::stof( f_decomposed[0][0], &sz);
    }
    for (int i = 1; i < f_iteration; i++) {
        if (isOperation(f_decomposed[i][0][0])) {
            std::string::size_type sz;
            value = operate(f_decomposed[i][0][0], value, std::stof(f_decomposed[i + 1][0], &sz));
            //std::cout << x << ":" << value << std::endl;
            //std::cout << "value = " << value << "; f_decomposed [i][0][0]" << std::endl;
            i++;
        }
    }
    //std::cout << value << ";" << f_decomposed[0][0] << std::endl;
    return value;
}

void Formula::readFormula(std::string input) {

}
