#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

void busca(string str, string *opcode, int *contador){
    instrucao *p = &ADD;
    while(flag == 1){
        if(str == p -> nome){
            flag = 1;
            *opcode = p -> opcode;
            contador += p -> num_operandos;
        }
        else {
            p = p -> prox;
        }
        if(p == NULL){
            cout << "Erro! Instrucao nao reconhecida!";
        }
    }
}
