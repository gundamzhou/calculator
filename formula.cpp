#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include "formula.hpp"

std::string Formula::getFormula(){
    //formula getter
    return this->formula;
}

void Formula::setFormula(std::string nFormula){
    //formula setter
    this->formula = nFormula;
}

double Formula::getOrdinate(double absicia){
    //to get the ordinate
    return this->fromString(this->formula, absicia);
}

Formula::Formula(){
    //classic call
    this->formula = "x";
}

Formula::Formula(std::string nFormula){
    //overload with given formula
    this->formula = nFormula;
}

double Formula::compute(double a, double b, char op){
    //simple operation function
    switch(op){
        case '+':
            return a + b;
            break;
        case '-':
            return a - b;
            break;
        case '*':
            return a * b;
            break;
        case '/':
            return a / b;
            break;
        case '^':
            return pow(a, b);
            break;
    }
}

double Formula::fromString(std::string formula, double absicia){
    /*
    function which take a string which contain a formula and compute it swaping x by a given value
    warning : 4*x^3 = (4*x)^3
    warning : 10/100*10 = (10/100)*10
    I keep this since it's still logic and it easier to code :3
    author: zhou Killian
    contact : killian.zhou@efrei.net

    if you want to use this function for your programs plz don't forget to quote me, I even prefer if you ask me first

    */
    double buffer = 0, buffer2 = 0, resutlt = 0, base = 0;
    char operation = ' ', operation2 = ' ';
    int parenthesis_counter = 0;
    std::string str_buffer = "", command_buffer = "";
    bool decimal = false, parenthesis = false, constant = false;
    try{
        for(int i = 0; i < formula.size(); i++){
            //std::cout << "resutlt = " << resutlt << std::endl << "character = " << formula[i] << std::endl << std::endl;
            if(formula[i] != ' '){
                if(parenthesis){
                    if(formula[i]==','){
                        if(str_buffer != ""){
                            base = fromString(str_buffer, absicia);
                        }else{
                            throw 30;
                        }
                        str_buffer = "";
                    }else if(formula[i] == '('){
                        parenthesis_counter++;
                        str_buffer += formula[i];
                    }else if(formula[i] == ')'){
                        parenthesis_counter--;
                        if(parenthesis_counter == 0){
                            parenthesis = false;
                            if(str_buffer != ""){
                                buffer = fromString(str_buffer, absicia);
                            }
                            if(command_buffer.compare("cos") == 0){
                                buffer = cos(buffer);
                            }else if(command_buffer.compare("arccos") == 0){
                                buffer = acos(buffer);
                            }else if(command_buffer.compare("arcsin") == 0){
                                buffer = asin(buffer);
                            }else if(command_buffer.compare("sin") == 0){
                                buffer = sin(buffer);
                            }else if(command_buffer.compare("sqrt") == 0){
                                buffer = (buffer >= 0)?sqrt(buffer):0;
                            }else if(command_buffer.compare("exp") == 0){
                                buffer = exp(buffer);
                            }else if(command_buffer.compare("ln")==0){
                                buffer = log (buffer);
                            }else if(command_buffer.compare("log")==0){
                                buffer = (log (base) / log (buffer));
                            }else if(command_buffer.compare("abs")==0){
                                buffer = std::abs(buffer);
                            }else if(command_buffer.compare("")!=0){
                                throw 3;
                            }
                            base = 0;
                            str_buffer = "";
                            command_buffer = "";
                        }else{
                            str_buffer += formula[i];
                        }
                    }else{
                        str_buffer += formula[i];
                    }
                }
                else{
                    if(formula[i] == 'x' && formula[i-1]!='e' && formula[i+1]!='p'){
                      if(buffer == 0){
                          buffer = absicia;
                      }else{
                          throw 83; //put a star little red shit
                      }
                    }else if(int(formula[i]) >= int('0') && int(formula[i]) <= int('9')){
                      if(constant == false){
                        if(buffer != 0 && !decimal){
                          buffer *= 10;
                        }
                        buffer += int(formula[i]) - int('0');
                        if(decimal && (int(formula[i]) - int('0'))!=0){
                            buffer *= 0.1;
                        }
                      }else{
                        throw 20;
                      }
                    }else if(formula[i] == '.'){
                        decimal = true;
                    }else if(formula[i] == '('){
                        parenthesis = true;
                        parenthesis_counter++;
                    }else if(formula[i] == '-' || formula[i] == '+'){
                        constant = false;
                        if(operation != ' '){
                            if (operation == '*' || operation == '/' || operation == '^')
                            {
                                if(buffer == 0 &&  operation == '/'){throw 60;}// ahah 8/0
                                buffer = compute(buffer2, buffer, operation);
                                operation = (operation2 == ' ')?'+':operation2;
                                operation2 = ' ';
                            }
                            resutlt = compute(resutlt, buffer, operation);
                        }else{
                            resutlt = buffer;
                        }
                        buffer = 0;
                        decimal = false;
                        operation = formula[i];
                    }else if(formula[i] == '*' || formula[i] == '/' || formula[i] == '^'){
                        constant = false;
                        if (operation == '*' || operation == '/' || operation == '^')
                        {
                            if(buffer == 0 &&  operation == '/'){throw 60;}// ahah 8/0
                            buffer = compute(buffer2, buffer, operation);
                            operation = operation2;
                        }
                        operation2 = operation;
                        buffer2 = buffer;
                        buffer = 0;
                        decimal = false;
                        operation = formula[i];
                    }else{
                        command_buffer += formula[i];
                        if(command_buffer.compare("pi")==0){
                          if(buffer == 0){
                            buffer = 3.14159265358979323846;
                            constant = true;
                          }else{
                            throw 20;
                          }
                        }
                    }
                }
                //end parenthesis condition
            }
            //end space char condition
        }
        //end for loop
        if (buffer != '0')
        {
            if(operation != ' '){
                if (operation == '*' || operation == '/' || operation == '^')
                {
                    if(buffer == 0 &&  operation == '/'){throw 60;}// ahah 8/0
                    buffer = compute(buffer2, buffer, operation);
                    operation = (operation2 == ' ')?'+':operation2;
                    operation2 = ' ';
                }
                resutlt = compute(resutlt, buffer, operation);
            }else{
                resutlt = buffer;
            }
        }
        //std::cout << "resutlt = " << resutlt << std::endl << std::endl;
        return resutlt;
    }catch(int e){
        std::cout << "computation stop with the key error number " << e << std::endl;
        return 0;
    }
}
