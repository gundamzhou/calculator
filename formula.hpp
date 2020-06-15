#ifndef FORMULA_HPP
#define FORMULA_HPP

#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>

class Formula{
/*
  this class store an function equation in function of x and compute it's value to a given value of x.
  author : zhou Killian
  contact : killian.zhou@efrei.net

  if you want to use this class for your programs plz don't forget to quote me, I even prefer if you ask me first
  */
public:


    Formula(std::string nFormula);

    Formula();

    double getOrdinate(double absicia);

    void setFormula(std::string nFormula);

    std::string getFormula();

private:
    std::string formula;

    double compute(double a, double b, char op);

    double fromString(std::string formula, double absicia);

};
#endif
