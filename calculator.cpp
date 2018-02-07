#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cctype>
#include <string>
#include <fstream>
using namespace std;
/*registers
    registers maps register names (string) to a vector of operations and values (strings) which will either be numbers or registers.
    For example, a register could consist of [+,5,-,2,+,A,*,B]. Before each value is an operation associated with that value.
*/
unordered_map<string, vector<string>*> registers; 
/*isAlphaNumeric
   s is alphanumeric if all of its characters are alphanumeric (except for the first character which is allowed to be "-" to allow negative numbers)
*/
bool isAlphaNumeric(const string & s){
    if (s.size()==0){return false;}
    if (!isalnum(s[0]) && s[0]!='-'){return false;} //Handling negative numbers
    bool alnum = true;
    for_each(s.begin()+1, s.end(), [s, &alnum](char c){
        if (!isalnum(c)){
            alnum = false;
        }
    });
    return alnum;
}
/*isNumber
    Very similar to isAlphaNumeric, but checks if s is a number
*/
bool isNumber(const string & s){
    if (s.size()==0){return false;}
    if (!isdigit(s[0]) && s[0]!='-'){return false;} //Handling negative numbers
    bool num = true;
    for_each(s.begin()+1, s.end(), [s, &num](char c){
        if (!isdigit(c)){
            num = false;
        }
    });
    return num;
}
/*make_lower_casee
    Takes a string s and makes it lower case.
*/
void make_lower_case(string & s){
    for_each(s.begin(), s.end(),[&s](char & c){
        c = tolower(c);
    });
}
/*evaluate
    Parameter reg is a name of a register. Save the vector of register reg in vals. Then loop through the vector and perform oerations on values and the result.
    If a value is a register, recursively call evaluate on that register.
*/
int evaluate(string & reg){
    int res{0};
    vector<string> vals = *registers[reg]; //Vector of register reg
    for(int i=0;i<registers[reg]->size();i+=2){ //i will be an operation and i+1 a value or register
        int delta{0};
        
        if (registers.find(vals.at(i+1))!=registers.end()){ //Value is a register.
            if (vals.at(i+1)==reg){//Value is the same register that is printed, avoids loop
                delta = res;
            }
            else{
                delta = evaluate(vals.at(i+1)); //Recursive call
            }
        }
        else if(isNumber(vals.at(i+1))){ //Value is a number
            delta = stoi(vals.at(i+1));
        }
        else{ //Value is a register that does not exist, create it and it assumes value 0.
            registers[vals.at(i+1)]= new vector<string>;
        }
        if (vals.at(i)=="+"){ //Perform the correct operation on the result;
            res += delta;
        }
        if (vals.at(i)=="-"){
            res -= delta;
        }
        if (vals.at(i)=="*"){
            res *= delta;
        }
    }
    return res;
}
/*main
    Reads the first word/register of every input row and makes it lower case. If it is "quit", exit the program. If it is "print", print the next input which is a register.
    If it is neither "quit" or "print" it is assumed to be a register that should be manipulated with some operation.
*/
int main(int argc, char* argv[]){
    ifstream ins("in.txt");
    streambuf *cinbuf = cin.rdbuf();
    if (argc > 1){ //If a filename has been given as argument, redirect cin from standard input to file 
        cin.rdbuf(ins.rdbuf()); 
    }
    string in; // Either "quit", "print" or a register
    while (cin>>in){ //Run as long as there is input
        make_lower_case(in);
        if (in == "quit"){ //Quits
            break;
        }
        else if(in == "print"){ //Prints
            string reg; //Register to be printed
            cin >> reg;
            make_lower_case(reg);
            if (!isAlphaNumeric(reg)){//Register is not alphanumeric
                cout << "Register is not alphanumeric."<<endl;
            }
            else if (registers.find(reg)==registers.end()){ //If the register that should be printed does not exist, create it and it will assume value 0.
                registers[reg]= new vector<string>;
            }
            cout << evaluate(reg)<< endl;
        }
        else if(isAlphaNumeric(in)) { //Input is some register
            string op; //Operation to be performed
            cin>>op;
            make_lower_case(op);
            string val; //Value to apply to register in
            cin>>val;
            make_lower_case(val);

            if (registers.find(in)==registers.end()){ //If register in does not exist, initialize with an empty vector.
                registers[in]= new vector<string>;
            }
            if (!isAlphaNumeric(val)){//The value is neither a number or an alphanumeric register
                cout << "Value is not alphanumeric."<<endl;
            }
            else if (op == "add"){ //Checks which operation to use, append the corresponding symbol to the vector.
                registers[in]->push_back("+");
                registers[in]->push_back(val);//Append the value. A check of whether it is a number or a register will be performed when printed
            }
            else if (op=="subtract"){
                registers[in]->push_back("-");
                registers[in]->push_back(val);
            }
            else if (op=="multiply"){
                registers[in]->push_back("*");
                registers[in]->push_back(val);
            }
            else{//Not a correct operation
                cout << "Operation is not allowed."<<endl;
            }
        }
        else{//Faulty input. Register is not alphanumeric.
            string dummy;
            cin>>dummy>>dummy;//Assumes the user wrote faulty register, eats the operation and value inputs;
            cout << "Register is not alphanumeric."<<endl;
        }
        
    }
    cin.rdbuf(cinbuf);//Resets standard input
    return 0;
}