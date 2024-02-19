#ifndef NOTATIONCONVERTER_H
#define NOTATIONCONVERTER_H

#include "Deque.hpp"
#include "NotationConverterInterface.hpp"
#include <iostream>
#include <string>

//Exception Hanlding for invalid characters and miss-matched operators
class invalidInput : public std::runtime_error {
    public:
        invalidInput(const std::string& err) : std::runtime_error(err) {};
};

//Initialzations
class NotationConverter : public NotationConverterInterface {
    public:
        //Constructor
        NotationConverter() {};

        //Methods to be defined as part of the assignment
        std::string postfixToInfix(std::string inStr);
        std::string postfixToPrefix(std::string inStr);

        std::string infixToPostfix(std::string inStr);
        std::string infixToPrefix(std::string inStr);

        std::string prefixToInfix(std::string inStr);
        std::string prefixToPostfix(std::string inStr);

    private:

        //Implementation of Deque to assist with operations
        Deque<std::string> deque;

        //some useful varibales for logic
        int operandCount = 0;
        int operatorCount = 0;
        int parenthCount = 0;

        //String used to concatenate operands & operators inside parentheses
        std::string catString;

        //Boolean used to identify characters in input string
        bool isOperand(std::string s) {char c = s.at(0); return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));}
        bool isOperator(std::string s) {char c = s.at(0); return c == '*' || c == '/' || c == '+' || c == '-';}
        bool isLPar(std::string s) {char c = s.at(0); return c == '(';}
        bool isRPar(std::string s) {char c = s.at(0); return c == ')';}


        //Exception Handling
        void checkValidOps(std::string inStr);
        void checkValidPostPre(std::string inStr);
        void checkValidInfix(std::string inStr);
};


//Function Definitions

//Functions for Exception Hanlding
void NotationConverter::checkValidOps(std::string inStr) {
    int slen = inStr.length();
    int operands = 0;
    int operators = 0;
    for (int i = 0; i < slen; i++) {
        std::string s(1, inStr.at(i)); 
        if (isOperand(s)) {
            operands++;
        } else if (isOperator(s)) {
            operators++;
        }
    }
    if (operands != operators + 1) {
        throw invalidInput("Operators don't match up with operands");
    }
}
void NotationConverter::checkValidPostPre(std::string inStr) {
    int slen = inStr.length(); 
    for (int i = 0; i < slen; i++) {
        std::string s(1, inStr.at(i)); 
        if (s != " " && !isOperand(s) && !isOperator(s)) {
            throw invalidInput("Invalid Character Entered");
        }
    } 
    checkValidOps(inStr);
    }
void NotationConverter::checkValidInfix(std::string inStr) {
    int slen = inStr.length(); 
    for (int i = 0; i < slen; i++) {
        std::string s(1, inStr.at(i)); 
        if (s != " " && !isOperand(s) && !isOperator(s) && !isLPar(s) && !isRPar(s)) {
            throw invalidInput("Invalid Character Entered");
        }
    } 
    checkValidOps(inStr);
    }

//Assignment 2 Functions


//Most of these functions have a similar structure, just different logic
std::string NotationConverter::postfixToInfix(std::string inStr) {

    //Exception Handling
    checkValidPostPre(inStr);

    //Iterate through input string, coverting notation
    int slen = inStr.length();
    for(int i = 0; i < slen; i++) {
        std::string s(1, inStr.at(i));

        //Check if operand and add to front of deque if true
        if(isOperand(s)) {
            deque.insertFront(s);
            operandCount++;

        //Check if operator and concatenate operands if true 
        //(safe to assume post fix should always have two operands before an operator
        //e.g. A B + (A and B are Operands followed by +), and also A B - C D + - (where A B - and C D + are operand followed by -)
        } else if(isOperator(s)) {
            catString = deque.front() + ')';
            deque.removeFront();
            catString.insert(0, ' ' + s + ' ');
            catString.insert(0, '(' + deque.front());
            deque.removeFront();
            deque.insertFront(catString);
            operandCount -= 2;
        } 
    }
    return deque.front();
}

//Similar structure to previous, just concatenated differently
std::string NotationConverter::postfixToPrefix(std::string inStr) {
    checkValidPostPre(inStr);
    int slen = inStr.length();
    for(int i = 0; i < slen; i++) {
        std::string s(1, inStr.at(i));
        if(isOperand(s)) {
            deque.insertFront(s);
            operandCount++;
        } else if(isOperator(s)) {
            catString = deque.front();
            deque.removeFront();
            catString.insert(0, ' ' + deque.front() + ' ');
            deque.removeFront();
            catString.insert(0, s);
            deque.insertFront(catString);
            operandCount -= 2;
        } 
    }

    return deque.front();

}


//Slightly most complicated due to reading parentheses
std::string NotationConverter::infixToPostfix(std::string inStr) {

    //Exeption Handling
    checkValidInfix(inStr);
    int slen = inStr.length();

    //Iterate through String
    for(int i = 0; i < slen; i++) {
        std::string s(1, inStr.at(i));

        //Recursion is used when an LPar, '(' is read
        if(isLPar(s)) {

            //Create a new string, consisting of all values of the input string,
            //starting after the LPar that was read
            //e.g. inStr = A * (B + C)
            //newInStr = B + C)
            std::string newInStr = inStr;
            newInStr.erase(0, i+1);

            //If an operator has been added to the Deque, a situation similar to the following has occured
            // (A + B) - (C * D)
            // Where     ^ this is the LPar that was read
            //This means (A + B) has been concatedated to A B +and is in the Deque
            //(C * D) need to be concatenated to C D *
            //Then A B + and C D * need to be contenated to A B + C D * -
            if (operatorCount == 1) {
                operatorCount = 0;

                //Function calls insted with newInStr
                //in our example, newInStr is C * D)
                //The function call converts C * D to C D * and adds it to the Deque
                infixToPostfix(newInStr);

                //Takes (in our example) C D *, -, and A B + and concatenates them
                catString = deque.front();
                deque.removeFront();
                catString.insert(catString.length(), ' ' + deque.front());
                deque.removeFront();
                catString.insert(0, deque.front() + ' ');
                deque.removeFront();

                //Adds new operand, e.g. A B + C D * -, to the Deque
                deque.insertFront(catString);

                //Parse through the string to the next RPar, effectively catching up on
                //operations performed in the recursion
                for(int j = i; j < slen; j++) {
                    std::string t(1, inStr.at(j));
                    if (isRPar(t)) {
                        i = j;
                        break;
                    }
                }

            //If no operators are in the Deque, calls itself and 
            //adds the concatenated operands and operator inside the parenthesis to the Deque as a new operand
            } else {infixToPostfix(newInStr); 

                    //Skips to next corresponding RPar, catching up with operations made in recursion
                    for(int j = i + 1; j < slen; j++) {
                        std::string t(1, inStr.at(j));
                        if (isLPar(t)) {
                            parenthCount++;
                        }
                        if (isRPar(t) && parenthCount == 0) {
                            i = j;
                            break;
                        } else if (isRPar(t) && parenthCount > 0) {
                            parenthCount--;
                        }
                    }}

        //Checks if charater is operand
        } else if (isOperand(s)) {
            //If there is an operator in the deque, then
            //concatenate the current operand with the operator and the next deque element and add to the Deque
            //(which should be the other operand the operator is acting on)
            if (operatorCount == 1) {
                catString = deque.front();
                deque.removeFront();
                operatorCount--;
                catString.insert(0, ' ' + s + ' ');
                catString.insert(0, deque.front());
                deque.removeFront();
                operandCount--;
                deque.insertFront(catString);
            
            //If there are no operators in the Deque, add the operand to the Deque
            } else {
                deque.insertFront(s);
                operandCount++;
            }
        
        //Check if character is an Operator
        } else if (isOperator(s)) {
            //Add Operator to the deque
            deque.insertFront(s);
            operatorCount++;

        //Check if the character is an RPar, ')'
        } else if (isRPar(s)) {

            //If true, then the current intance of the function is a recursion,
            //Return the front of the deque and return to previous call of the function
            return(deque.front());
        }
    }
    return deque.front();


}

//Similar structure to previous, just concatenated differently
std::string NotationConverter::infixToPrefix(std::string inStr) {
    checkValidInfix(inStr);
    int slen = inStr.length();
    for(int i = 0; i < slen; i++) {
        std::string s(1, inStr.at(i));
        if(isLPar(s)) {
            std::string newInStr = inStr;
            newInStr.erase(0, i+1);
            if (operatorCount == 1) {
                operatorCount = 0;
                infixToPrefix(newInStr);
                catString = deque.front();
                deque.removeFront();
                catString.insert(0, deque.front() + ' ');
                deque.removeFront();
                catString.insert(2, deque.front() + ' ');
                deque.removeFront();
                deque.insertFront(catString);
                for(int j = i; j < slen; j++) {
                    std::string t(1, inStr.at(j));
                    if (isRPar(t)) {
                        i = j;
                        break;
                    }
                }
                
            } else {infixToPrefix(newInStr); 
                    for(int j = i + 1; j < slen; j++) {
                        std::string t(1, inStr.at(j));
                        if (isLPar(t)) {
                            parenthCount++;
                        }
                        if (isRPar(t) && parenthCount == 0) {
                            i = j;
                            break;
                        } else if (isRPar(t) && parenthCount > 0) {
                            parenthCount--;
                        }
                    }}

        } else if (isOperand(s)) {
            if (operatorCount == 1) {
                catString = deque.front();
                deque.removeFront();
                operatorCount--;
                catString.insert(catString.length(), ' ' + deque.front() + ' ');
                deque.removeFront();
                operandCount--;
                catString.insert(catString.length(), s);
                deque.insertFront(catString);
            } else {
                deque.insertFront(s);
                operandCount++;
            }
        } else if (isOperator(s)) {
            deque.insertFront(s);
            operatorCount++;
        } else if (isRPar(s)) {
            return(deque.front());
        }
    }
    return deque.front();


}


//Similar Structure to postfixToInfix functions, but iterate from end of
//inStr to beginning (backwards)
std::string NotationConverter::prefixToInfix(std::string inStr) {
    checkValidPostPre(inStr);
    int slen = inStr.length();
    for(int i = slen - 1; i >= 0; i--) {
        std::string s(1, inStr.at(i));
        if(isOperand(s)) {
            deque.insertFront(s);
            operandCount++;
        } else if(isOperator(s)) {
            catString = '(' + deque.front();
            deque.removeFront();
            catString.insert(catString.length(), ' ' + s + ' ');
            catString.insert(catString.length(), deque.front() + ')');
            deque.removeFront();
            deque.insertFront(catString);
            operandCount -= 2;
        } 
    }

    return deque.front();

}

//Similar Structure to postfixToPrefix functions, but iterate from end of
//inStr to beginning (backwards) and concatenation is reversed
std::string NotationConverter::prefixToPostfix(std::string inStr) {
    checkValidPostPre(inStr);
    int slen = inStr.length();
    for(int i = slen - 1; i >= 0; i--) {
        std::string s(1, inStr.at(i));
        if(isOperand(s)) {
            deque.insertFront(s);
            operandCount++;
        } else if(isOperator(s)) {
            catString = deque.front();
            deque.removeFront();
            catString.insert(catString.length(), ' ' + deque.front() + ' ');
            catString.insert(catString.length(), s);
            deque.removeFront();
            deque.insertFront(catString);
            operandCount -= 2;
        } 
    }

    return deque.front();

}


#endif
