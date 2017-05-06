#include <string>
#include <iostream>

using namespace std;

struct Instrucoes {
string nome;
string opcode;
int num_operandos;
struct Intrucoes *prox;
};

typedef struct Intrucoes Instrucao;

Instrucao ADD, SUB, MULT, DIV, JMP, JMPN, JMPP, JMPZ, COPY, LOAD, ATORE, INPUT, OUTPUT, STOP;

ADD.nome = "ADD";
ADD.opcode = "01";
ADD.num_operandos = 1;
ADD.prox = &SUB;

SUB.nome = "SUB";
SUB.opcode = "02";
SUB.num_operandos = 1;
SUB.prox = &MULT;

MULT.nome = "MULT";
MULT.opcode = "03";
MULT.num_operandos = 1;
MULT.prox = &DIV;
