#IFNDEF _Lista_de_Instrucoes
#define _Lista_de_Instrucoes

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

DIV.nome = "DIV";
DIV.opcode = "04";
DIV.num_operandos = 1;
DIV.prox = &JMP;

JMP.nome = "JMP";
JMP.opcode = "05";
JMP.num_operandos = 1;
JMP.prox = &JMPN;

JMPN.nome = "JMPN";
JMPN.opcode = "06";
JMPN.num_operandos = 1;
JMPN.prox = &JMPP;

JMPP.nome = "JMPP";
JMPP.opcode = "07";
JMPP.num_operandos = 1;
JMPP.prox = &JMPZ;

JMPZ.nome = "JMPZ";
JMPZ.opcode = "08";
JMPZ.num_operandos = 1;
JMPZ.prox = &COPY;

COPY.nome = "COPY";
COPY.opcode = "09";
COPY.num_operandos = 2;
COPY.prox = &LOAD;

LOAD.nome = "LOAD";
LOAD.opcode = "10";
LOAD.num_operandos = 1;
LOAD.prox = &STORE;

STORE.nome = "STORE";
STORE.opcode = "11";
STORE.num_operandos = 1;
STORE.prox = &INPUT;

INPUT.nome = "INPUT";
INPUT.opcode = "12";
INPUT.num_operandos = 1;
INPUT.prox = &OUTPUT;

OUTPUT.nome = "OUTPUT";
OUTPUT.opcode = "13";
OUTPUT.num_operandos = 1;
OUTPUT.prox = &STOP;

STOP.nome = "STOP";
STOP.opcode = "14";
STOP.num_operandos = 0;
STOP.prox = NULL;

void busca_instrucao();

#endif
