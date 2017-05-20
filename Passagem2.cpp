#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stdlib.h>
#include <cctype>

using namespace std;

//**************************************** TABELA DE SIMBOLOS ****************************************************************

class Simbolo {
    string rotulo; //Rotulo da tabela de simbolos
    string valor_rotulo; //Valor associado ao rotulo
    bool ext;
    Simbolo *prox_rotulo; //Posicao do proximo rotulo
public:
    Simbolo() {};
    void Define_Rotulo1 (string rot1) {rotulo = rot1;} //Define o rotulo de um no
    void Define_Valorrot (string valor_rot1) {valor_rotulo = valor_rot1;} //Define o valor associado a um rotulo
    void Define_proximo_rot (Simbolo *proximo) {prox_rotulo = proximo;} //Define proximo no
    void Define_ext (bool eh_ext) {ext = eh_ext;}
    string Retorna_rot() {return rotulo;}
    string Retorna_val() {return valor_rotulo;}
    Simbolo* Retorna_proximo_rot () {return prox_rotulo;}
    bool Retorna_ext () {return ext;}
};

class Simbolo_Tab { //Lista para as definicoes das diretivas EQU
    public:
        Simbolo *primeiro;
        Simbolo_Tab() {
            primeiro = NULL;
        }
        void inseresimb_final (string,string,bool); //Insere no no final da tabela
        void imprime_simb();
        string busca_simb (string,bool&); //Busca no na lista a partir do rotulo
        void limpa_tabelasimb();
};

void Simbolo_Tab::imprime_simb() {
     Simbolo *nov = primeiro;
    while(nov != NULL) {
    cout << nov->Retorna_rot() << " = " << nov->Retorna_val() << endl;
    nov = nov->Retorna_proximo_rot();
    }
}

void Simbolo_Tab::inseresimb_final (string rotulo1, string valor1, bool ext1) {
    string aux;
    Simbolo *novo_simb = new Simbolo();
    novo_simb->Define_Rotulo1(rotulo1);
    novo_simb->Define_ext(ext1);
    if(valor1.length() == 1) {
        aux += '0';
        aux += valor1;
        novo_simb->Define_Valorrot(aux);
    } else {
    novo_simb->Define_Valorrot(valor1);
    }
    novo_simb->Define_proximo_rot(NULL);
    Simbolo *tmp = primeiro;

    if(tmp != NULL) { //Se existem nos na lista, ir para o final
            while(tmp->Retorna_proximo_rot() != NULL) {
                tmp = tmp->Retorna_proximo_rot();
            }
        tmp->Define_proximo_rot(novo_simb);
    } else {
        primeiro = novo_simb;
    }
}

string Simbolo_Tab::busca_simb (string rot2, bool& existe) { //Busca no na lista
    bool *aux = &existe;
    Simbolo *tmp = primeiro;
    string tmpval;
    while(tmp != NULL) {
        if(tmp->Retorna_rot() == rot2) { //Se tiver rotulo == rot2, retornar valor associado e coloca flag exist em true
            tmpval = tmp->Retorna_val();
            *aux = true;
            return tmpval;
            break;
        }
        tmp = tmp->Retorna_proximo_rot();
    }
}

void Simbolo_Tab::limpa_tabelasimb () {
    Simbolo *tmp = primeiro;
    if (tmp == NULL)
        return;
    Simbolo *aux;
    do {
        aux = primeiro->Retorna_proximo_rot();
        primeiro = aux;
        delete tmp;
        tmp = primeiro;
    } while(tmp != NULL);
}

//****************************************** FIM DA TABELA DE SIMBOLOS *********************************************************

//************************************************ LISTA DE ERROS ********************************************************

class erro {
    int flag_erro;
    int linha_num;
    erro *prox_erro;
public:
    Define_flag (int flag) {flag_erro = flag;}
    Define_linha (int numl) {linha_num = numl;}
    Define_proxerro (erro *proxe) {prox_erro = proxe;}
    int Return_flag() {return flag_erro;}
    int Return_linha() {return linha_num;}
    erro* Return_proxerro() {return prox_erro;}
};

class lista_erro {
    public:
    erro *erro1;
    lista_erro () {
        erro1 = NULL;
    }
    void insere_erro (int,int);
    void imprime_erros();
    void limpa_listae();
};

void lista_erro::insere_erro(int flage, int numline) {
   erro *novo_erro;
   erro *p = erro1, *temp;
   novo_erro = new erro();
   novo_erro->Define_flag(flage);
   novo_erro->Define_linha(numline);
   novo_erro->Define_proxerro(NULL);
   if(p == NULL) {
        erro1 = novo_erro;
   } else {
   do {
        if(novo_erro->Return_linha() < p->Return_linha()) {
            temp = p;
            p = novo_erro;
            p->Define_proxerro(temp);
        }
            temp = p;
            p = p->Return_proxerro();
   } while(p != NULL);
   if(p == NULL) {
        temp->Define_proxerro(novo_erro);
   }
   }
}

void lista_erro::imprime_erros() {
    erro *tmpe1 = erro1;
    if(tmpe1 != NULL) {
    while(tmpe1 != NULL) {
        if(tmpe1->Return_flag() == 1) {
            cout << "Linha " << tmpe1->Return_linha() << ": " << "Dois rotulos na mesma linha" << endl;
        }
        if(tmpe1->Return_flag() == 2) {
            cout << "Linha " << tmpe1->Return_linha() << ": " << "Token invalido" << endl;
        }
        if(tmpe1->Return_flag() == 3) {
            cout << "Linha " << tmpe1->Return_linha() << ": " << "Numero de operandos invalido" << endl;
        }
        if(tmpe1->Return_flag() == 4) {
            cout << "Linha " << tmpe1->Return_linha() << ": " << "Diretiva/Instrucao na secao errada" <<  endl;
        }
        if(tmpe1->Return_flag() == 5) {
            cout << "Linha " << tmpe1->Return_linha() << ": " << "Instrucao/diretiva invalida" << endl;
        }
        if(tmpe1->Return_flag() == 6) {
            cout << "Secao de dados vindo antes da secao de texto" << endl;
        }
        if(tmpe1->Return_flag() == 7) {
            cout << "Linha " << tmpe1->Return_linha() << ": " << "Declaracao ausente" << endl;
        }
        if(tmpe1->Return_flag() == 8) {
            cout << "Linha " << tmpe1->Return_linha() << ": " << "Secao invalida" << endl;
        }
        if(tmpe1->Return_flag() == 9) {
            cout << "Secao TEXTO faltante" << endl;
        }
        if(tmpe1->Return_flag() == 10) {
            cout << "Linha " << tmpe1->Return_linha() << ": " << "Rotulo repetido" << endl;
        }
        if(tmpe1->Return_flag() == 11) {
            cout << "Linha " << tmpe1->Return_linha() << ": " << "Modificacao de valor constante" << endl;
        }
        if(tmpe1->Return_flag() == 12) {
            cout << "Falta de diretiva END ou BEGIN" << endl;
        }
        if(tmpe1->Return_flag() == 13) {
            cout << "Programa nao eh modulo e nao possui instrucao STOP" << endl;
        }
        if(tmpe1->Return_flag() == 14) {
            cout << "Linha " << tmpe1->Return_linha() << ": " << "Divisao por zero" << endl;
        }
        if(tmpe1->Return_flag() == 15) {
            cout << "Linha " << tmpe1->Return_linha() << ": " << "Pulo para rotulo invalido" << endl;
        }
        if(tmpe1->Return_flag() == 16) {
            cout << "Linha " << tmpe1->Return_linha() << ": " << "Diretiva SPACE nao pode receber 0 como argumento" << endl;
        }
        if(tmpe1->Return_flag() == 17) {
            cout << "Linha " << tmpe1->Return_linha() << ": " << "Operando invalido" << endl;
        }
        if(tmpe1->Return_flag() == 18) {
            cout << "Linha " << tmpe1->Return_linha() << ": " << "Endereco de memoria nao reservado" << endl;
        }
        if(tmpe1->Return_flag() == 19) {
            cout << "Linha " << tmpe1->Return_linha() << ": " << "Diretiva SPACE nao pode receber numeros negativos como argumento" << endl;
        }
            tmpe1=tmpe1->Return_proxerro();
    }
    }
}

void lista_erro::limpa_listae() {
    erro *tmpe = erro1;
    if (tmpe == NULL)
        return;
    erro *auxe;
    do {
        auxe = erro1->Return_proxerro();
        erro1 = auxe;
        delete tmpe;
        tmpe = erro1;
    } while(tmpe != NULL);
}


//*********************************************** FIM DA LISTA DE ERROS ***************************************************

//**************************************** TABELA DE DEFINICOES **************************************************************

class Definicao {
    string rotulo_def; //Rotulo da tabela de simbolos
    string valor_def; //Valor associado ao rotulo
    Definicao *prox_def; //Posicao do proximo rotulo
public:
    no() {};
    void Define_Rotulodef (string rotd) {rotulo_def = rotd;} //Define o rotulo de um no
    void Define_Valordef (string valor_def1) {valor_def = valor_def1;} //Define o valor associado a um rotulo
    void Define_prox_def (Definicao *proximod) {prox_def = proximod;} //Define proximo no
    string Retorna_def() {return rotulo_def;}
    string Retorna_valdef() {return valor_def;}
    Definicao* Retorna_prox_def () {return prox_def;}
};

class Def_Tab { //Lista para as definicoes das diretivas EQU
    Definicao *def1;
    public:
        Def_Tab() {
            def1 = NULL;
        }
        void inseredef_final (string,string); //Insere no no final da tabela
        void mod_def (string,string); //Modifica valor da definicao
        void limpa_tabeladef();
};

void Def_Tab::inseredef_final (string def, string valord) {
    Definicao *nova_def = new Definicao();
    nova_def->Define_Rotulodef(def);
    nova_def->Define_Valordef(valord);
    nova_def->Define_prox_def(NULL);
    Definicao *tmp = def1;

    if(tmp != NULL) { //Se existem nos na lista, ir para o final
            while(tmp->Retorna_prox_def() != NULL) {
                tmp = tmp->Retorna_prox_def();
            }
        tmp->Define_prox_def(nova_def);
    } else {
        def1 = nova_def;
    }
}

void Def_Tab::mod_def (string def2, string novo_valor) { //Busca no na lista
    Definicao *tmp = def1;
    while(tmp != NULL) {
        if(tmp->Retorna_def() == def2) { //Se tiver definicao == def2, alterar valor
            tmp->Define_Valordef(novo_valor);
            break;
        }
        tmp = tmp->Retorna_prox_def();
    }
}

void Def_Tab::limpa_tabeladef () {
    Definicao *tmp = def1;
    if (tmp == NULL)
        return;
    Definicao *aux;
    do {
        aux = def1->Retorna_prox_def();
        def1 = aux;
        delete tmp;
        tmp = def1;
    } while(tmp != NULL);
}

//*********************************** FIM DA TABELA DE DEFINICOES ************************************************************

//*********************************************** LISTA DE INSTRUCOES ****************************************************

class Instrucao {
    string nome_inst;
    string opcode;
    int num_operandos;
    Instrucao *prox;
public:
    Instrucao() {};
    void Def_nome_inst(string); //Definicoes da instrucao
    void Def_opcode(string);
    void Def_num_operandos(int);
    void Def_prox(Instrucao*);
    string Return_nome_inst();
    string Return_opcode();
    int Return_num_operandos();
    Instrucao* Return_prox();
};

class Lista_Instrucoes {
     Instrucao *Instrucao1;
     public:
        Lista_Instrucoes() {
            Instrucao1 = NULL;
        }
        void inserefinal_instrucao (string,string,int); //Insere instrucao na lista
        string busca_instrucao (string,int&,int,lista_erro&); //Busca instrucao na lista
        void limpa_lista_inst ();
};

void Instrucao::Def_nome_inst(string name) {
    nome_inst = name;
}
void Instrucao::Def_opcode(string op) {
    opcode = op;
}
void Instrucao::Def_num_operandos(int num) {
    num_operandos = num;
}
void Instrucao::Def_prox(Instrucao *nxt) {
    prox = nxt;
}
string Instrucao::Return_nome_inst() {
    return nome_inst;
}
string Instrucao::Return_opcode() {
    return opcode;
}
int Instrucao::Return_num_operandos() {
    return num_operandos;
}
Instrucao* Instrucao::Return_prox() {
    return prox;
}

void Lista_Instrucoes::inserefinal_instrucao(string name, string op, int operand) {
    Instrucao *nova_instrucao = new Instrucao();
    nova_instrucao->Instrucao::Def_nome_inst(name);
    nova_instrucao->Instrucao::Def_opcode(op);
    nova_instrucao->Instrucao::Def_num_operandos(operand);
    nova_instrucao->Instrucao::Def_prox(NULL);
    Instrucao *tmp = Instrucao1;

    if(tmp != NULL) { //Se existem nos na lista, ir para o final
            while(tmp->Instrucao::Return_prox() != NULL) {
                tmp = tmp->Instrucao::Return_prox();
            }
        tmp->Instrucao::Def_prox(nova_instrucao);
    } else {
        Instrucao1 = nova_instrucao;
    }
}

string Lista_Instrucoes::busca_instrucao(string name, int &contador_pos, int contador_lin, lista_erro &lerro) {
    Instrucao *tmp = Instrucao1;
    int tmpval;
    int flag_inst = 0;
    while(tmp != NULL) {
        if(tmp->Instrucao::Return_nome_inst() == name) {
            tmpval = tmp->Instrucao::Return_num_operandos();
            flag_inst = 1;
            break;
        }
        tmp = tmp->Instrucao::Return_prox();
    }
    if(flag_inst == 1) {//Se existir a instrucao procurada, retornar numero de operandos, caso contrario retornar -1.
        contador_pos += tmpval;
        return tmp->Return_opcode();
    } else {
        return "-1";
        lerro.insere_erro(5, contador_lin);
    }
}

void Lista_Instrucoes::limpa_lista_inst() {
    Instrucao *tmp = Instrucao1;
    Instrucao *aux;
    do {
        aux = Instrucao1->Instrucao::Return_prox();
        Instrucao1 = aux;
        delete tmp;
        tmp = Instrucao1;
    } while(tmp != NULL);
}

//************************************** FIM DA LISTA DE INSTRUCOES *******************************************************

//*********************************************** LISTA DE LINHAS APAGADAS ************************************************
//Serve para que se possa printar o valor da linha certo caso haja um erro

class numerolinha {
    int linum;
    numerolinha *prox_lin;
public:
    Define_linum (int lin) {linum = lin;}
    Define_proxlin (numerolinha *proxli) {prox_lin = proxli;}
    int Return_linum() {return linum;}
    numerolinha* Return_proxlin() {return prox_lin;}
};

class lista_linhas {
    public:
    numerolinha *primeiralinha;
    lista_linhas () {
        primeiralinha = NULL;
    }
    void insere_numerolin(int);
    void busca_listalinhas (int&,lista_linhas&);
    void limpa_listalin();
};

void lista_linhas::insere_numerolin(int linum1) {
   numerolinha *nova_linha;
   numerolinha *p = primeiralinha, *temp;
   nova_linha = new numerolinha();
   nova_linha->Define_linum(linum1);
   nova_linha->Define_proxlin(NULL);
   if(p == NULL) {
        primeiralinha = nova_linha;
   } else {
   do {
        if(nova_linha->Return_linum() < p->Return_linum()) {
            temp = p;
            p = nova_linha;
            p->Define_proxlin(temp);
        }
            temp = p;
            p = p->Return_proxlin();
   } while(p != NULL);
   if(p == NULL){
        temp->Define_proxlin(nova_linha);
   }
   }
}

void lista_linhas::busca_listalinhas (int &lcont, lista_linhas &ll) {
    numerolinha *new_linha = primeiralinha;
    numerolinha *tp;
    int i = 1;
    while(new_linha != NULL) {
        if(new_linha->Return_linum() != i) {
            lcont = i;
            ll.insere_numerolin(lcont);
            break;
        }
        tp = new_linha;
        new_linha = new_linha->Return_proxlin();
        i++;
    }
    if(new_linha == NULL){
        new_linha->Define_linum(lcont);
        new_linha->Define_proxlin(NULL);
        tp->Define_proxlin(new_linha);
    }
}

void lista_linhas::limpa_listalin() {
    numerolinha *tmpe = primeiralinha;
    if (tmpe == NULL)
        return;
    numerolinha *auxe;
    do {
        auxe = primeiralinha->Return_proxlin();
        primeiralinha = auxe;
        delete tmpe;
        tmpe = primeiralinha;
    } while(tmpe != NULL);
}

//*********************************************** FIM DA LISTA DE LINHAS **************************************************

//*********************************************** LISTA DE DADOS **********************************************************
//Armazena informacoes sobre rotulo que eh constante ou que teve espaco reservado (vetor)

class Rotulo {
    string rname;
    bool eh_const;
    int valor_const;
    int espaco_reserv;
    Rotulo *prox_rname;
public:
    void Define_rname (string rn) {rname = rn;}
    void Define_const (bool ehc) {eh_const = ehc;}
    void Define_valconst (int valc) {valor_const = valc;}
    void Define_espaco (int space) {espaco_reserv = space;}
    void Define_proxr (Rotulo* prn) {prox_rname = prn;}
    string Return_rname() {return rname;}
    bool Return_const() {return eh_const;}
    int Return_valconst() {return valor_const;}
    int Return_space() {return espaco_reserv;}
    Rotulo* Return_proxrn() {return prox_rname;}
};
class Dados {
    Rotulo *rn1;
public:
    Dados() {
        rn1 = NULL;
    }
    void insere_dados(string,bool,int,int);
    bool ehconst(string,int&,bool&);
    int space(string);
    void limpa_dados();
    void imprime_dados();
};
void Dados::imprime_dados() {
    Rotulo *nov = rn1;
    while(nov != NULL) {
    cout << nov->Return_rname() << endl;
    cout << nov->Return_valconst() << endl;
    cout << nov->Return_space() << endl;
    cout << nov->Return_const() << endl;
    nov = nov->Return_proxrn();
    }
}

void Dados::insere_dados(string rnm, bool ec, int vc, int sp) {
    Rotulo *novo_rn = new Rotulo();
    novo_rn->Rotulo::Define_rname(rnm);
    novo_rn->Rotulo::Define_const(ec);
    novo_rn->Rotulo::Define_valconst(vc);
    novo_rn->Rotulo::Define_espaco(sp);
    novo_rn->Rotulo::Define_proxr(NULL);
    Rotulo *tmp = rn1;
    if(tmp != NULL) { //Se existem nos na lista, ir para o final
            while(tmp->Rotulo::Return_proxrn() != NULL) {
                tmp = tmp->Rotulo::Return_proxrn();
            }
        tmp->Rotulo::Define_proxr(novo_rn);
    } else {
        rn1 = novo_rn;
    }
}
bool Dados::ehconst(string rnm1, int &vc1, bool &ehc) {
    Rotulo *new_rn = rn1;
    Rotulo *tp;
    while(new_rn != NULL) {
        if(new_rn->Return_rname() == rnm1) {
            vc1 = new_rn->Return_valconst();
            ehc = new_rn->Return_const();
            return new_rn->Return_const();
            break;
        }
        new_rn = new_rn->Return_proxrn();
    }
    if(new_rn == NULL) {
        ehc = false;
    }
}
int Dados::space(string rnm2) {
    Rotulo *new_rn1 = rn1;
    Rotulo *tp;
    while(new_rn1 != NULL) {
        if(new_rn1->Return_rname() == rnm2) {
            return new_rn1->Return_space();
            break;
        }
        new_rn1 = new_rn1->Return_proxrn();
    }
    if(new_rn1 == NULL) {
        return 1;
    }
}

void Dados::limpa_dados() {
    Rotulo *tmpe = rn1;
    if (tmpe == NULL)
        return;
    Rotulo *auxe;
    do {
        auxe = rn1->Return_proxrn();
        rn1 = auxe;
        delete tmpe;
        tmpe = rn1;
    } while(tmpe != NULL);
}

//****************************************** FIM DA LISTA DE DADOS *****************************************************

//*********************************************** TABELA DE USO ********************************************************

class Simb_TU {
    string symbol;
    string value;
    Simb_TU *proxsymb;
public:
    void Define_symbol(string s) {symbol = s;}
    void Define_value (string v) {value = v;}
    void Define_psymb (Simb_TU *psymb) {proxsymb = psymb;}
    string Return_symbol() {return symbol;}
    string Return_value() {return value;}
    Simb_TU* Return_psymb() {return proxsymb;}
};

class TU {
    Simb_TU* symb1;
public:
    TU () {
        symb1 = NULL;
    }
    void insere_symb (string,string);
    void limpa_TU ();
};

void TU::insere_symb(string sb, string vl) {
    Simb_TU *novo_symb = new Simb_TU();
    novo_symb->Simb_TU::Define_symbol(sb);
    novo_symb->Simb_TU::Define_value(vl);
    novo_symb->Simb_TU::Define_psymb(NULL);
    Simb_TU *tmp = symb1;

    if(tmp != NULL) { //Se existem nos na lista, ir para o final
            while(tmp->Simb_TU::Return_psymb() != NULL) {
                tmp = tmp->Simb_TU::Return_psymb();
            }
        tmp->Simb_TU::Define_psymb(novo_symb);
    } else {
        symb1 = novo_symb;
    }
}

void TU::limpa_TU() {
    Simb_TU *tmpe = symb1;
    if (tmpe == NULL)
        return;
    Simb_TU *auxe;
    do {
        auxe = symb1->Return_psymb();
        symb1 = auxe;
        delete tmpe;
        tmpe = symb1;
    } while(tmpe != NULL);
}
//******************************************* FIM DA TABELA DE USO *******************************************************

//******************************************* LISTA CODIGO ***************************************************************
//Lista que armazena o codigo para grava-lo posteriormente no arquivo de saida

/*class code_op {
    string operat;
    code_op *nop;
public:
    Define_operat (string opr) {operat = opr;}
    Define_nop (code_op *nop1) {nop = nop1;}
    string Return_operat() {return operat;}
    code_op* Return_nop() {return nop;}
};

class code {
public:
    code_op *start;
    code {
        start = NULL;
    }
    void insere_codefinal(string);
    void limpa_code();
};

void code::insere_codefinal(string codn) {
    code_op *opc = new code_op();
    opc->Define_operat(codn);
    nova_instrucao->Define_nop(NULL);
    code_op *tmp = start;

    if(tmp != NULL) { //Se existem nos na lista, ir para o final
            while(tmp->Return_nop() != NULL) {
                tmp = tmp->Return_nop();
            }
        tmp->Define_nop(opc);
    } else {
        start = opc;
    }
}

void code::limpa_code() {
    code_op *tmpe = start;
    if (tmpe == NULL)
        return;
    code_op *auxe;
    do {
        auxe = start->Return_nop();
        start = auxe;
        delete tmpe;
        tmpe = start;
    } while(tmpe != NULL);
}*/
//*************************************** FIM DA LISTA CODIGO *************************************************************

//************************************** Prototipo **************************************************************************
void Diretivas(string, TU&, Dados&, string, string, int&, int&, int&, Simbolo_Tab&, int, lista_erro&, Def_Tab&, int, string&, int&, bool&, int);
void cria_LI(Lista_Instrucoes&);
void cria_TS(Simbolo_Tab&);
//***************************************************************************************************************************

int main () {
Simbolo_Tab simb;
TU TabUso;
Dados data;
lista_erro errolist;
Def_Tab defin;
Lista_Instrucoes inst;
cria_LI(inst);
lista_linhas linls;
string nome, nometemp, rotulo; //strings usadas para abrir o arquivo e verifica extensao
string line, outline; //strings utilizadas para as linhas
string straux1, straux2, straux3, straux4, opcode = "-1", token1;
stringstream conversao;
int t = 0, j = 0, i = 0, k = 0, tam1, aux, espaco;
int pos_cont = 0, pos_contaux = 0, lin_cont = 0; //Contadores de posicao (Para verificacoes de instrucoes e contador de linha)
int flagsec = 0, fbegin = 0, fend = 0, flagp = 1, flagel = 0, flages = 0, flaginst = 0, flagrot = 0, flagaux1 = 0, flagaux2 = 0, flagpos = 0, flagaux3 = 0;
/*
flagsec - flag para verificacao da diretiva SECTION
fbegin - flag para verificacao da diretiva BEGIN
fend - flag para verificacao da diretiva END
flagp - flag para verificacao da passagem (primeira ou segunda)
flagel - flag para erro lexico
flages - flag para erro sintatico
flaginst - flag para indicar que eh instrucao
flagrot - flag que indica a existencia de um rotulo
flagaux1 e flagaux2 - flags auxiliares
*/
bool eh_diretiva, eh_simb, constante; //Variavel para verificar se eh diretiva
int valor_const; //Variavel para verificar o valor de um operando constante
size_t pos1;

cout << "Digite o nome do arquivo que deseja abrir: ";
getline (cin, nome);
tam1 = nome.length();
for(t=tam1-4;t<tam1;t++) {
     nometemp += nome.at(t);
}
if(nometemp.compare(".pre") == 0 || nometemp.compare(".asm") == 0) { // Verificando se o arquivo esta no formato correto
    ifstream arquivo (nome.c_str());
    fstream saida ("Saida.o", ios::out);

    if(saida.is_open() && arquivo.is_open()) {
        flagp = 2;
        simb.inseresimb_final("Y", "23", false);
        simb.inseresimb_final("T1", "27", false);
        simb.inseresimb_final("N1", "28", false);
        simb.inseresimb_final("N3", "29", false);
        data.insere_dados("Y",false,0,4);
        data.insere_dados("T1",true,0,1);
        while(getline(arquivo,line)){
            eh_diretiva = false;
            constante = false;
            eh_simb = false;
            opcode.clear();
            token1.clear();
            straux3.clear();
            straux4.clear();
            conversao.str("");
            conversao.clear();
            lin_cont++;
            opcode = "-1";
            if(linls.primeiralinha != NULL)
                linls.busca_listalinhas(lin_cont,linls);
             for(i=0;i<line.length();i++) {     //Pegando tokens
                if(line.at(i) == ':' || line.at(i) == ' ' || i+1 == line.length() || line.at(i) == ',' || line.at(i) == '+'){
                    if(i+1 == line.length()) { //Se for o ultimo token da linha
                        token1 += line.at(i);
                        if(opcode != "-1" && eh_diretiva == false) { //Se ultimo token tiver sido uma instrucao
                            straux3 = simb.busca_simb(token1, eh_simb);
                            if((opcode == "05" || opcode == "06" || opcode == "07" || opcode == "08") && eh_simb == false) { //Se for pulo e o rotulo for invalido, erro
                                errolist.insere_erro(15, lin_cont);
                            }
                            if(eh_simb == true) {
                                data.ehconst(token1, valor_const, constante);
                                if(constante == true) {
                                    if(opcode == "04" && valor_const == 0) { //Se a instrucao for DIV e o operando for zero, erro
                                        errolist.insere_erro(14, lin_cont);
                                    } else if (opcode == "11" || opcode == "12" || opcode == "09") { //Se for INPUT, STORE ou COPY, erro de modificacao de valor const.
                                        errolist.insere_erro(11, lin_cont);
                                    }
                                }
                                    outline += straux3;
                                    outline += ' ';
                                }
                        } else if (opcode == "-1" && eh_diretiva == false) {
                            opcode = inst.busca_instrucao(token1, pos_cont, lin_cont, errolist);
                            if(opcode == "14" ) { //Se for a instrucao STOP
                                flaginst = 1;
                                outline += opcode;
                                outline += ' ';
                            }
                        }
                        break;
                    } else if(line.at(i) == ' ') {
                        opcode = inst.busca_instrucao(token1,pos_cont, lin_cont, errolist);
                        if(opcode != "-1") {
                            outline += opcode;
                            outline += ' ';
                        }
                        Diretivas(rotulo, TabUso, data, token1, line, pos_cont, fbegin, fend, simb, flagp, errolist, defin, lin_cont, outline, flagsec, eh_diretiva, flagaux2);
                        token1.clear();
                        i++;
                    } else if(line.at(i) == ':') { //Se encontrou rotulo, ignorar
                        j = i+1;
                        for(i=j;i<line.length();i++) { //Indo para o proximo token
                            if(line.at(i) != ' ') {
                                break;
                            }
                        }
                        opcode.clear();
                        token1.clear();
                        opcode = "-1";
                    } else if(line.at(i) == ',') {
                        straux3 = simb.busca_simb(token1,eh_simb);
                        if(eh_simb == true) {
                            outline += straux3;
                            outline += ' ';
                        } else {
                            errolist.insere_erro(17, lin_cont);
                        }
                        straux3.clear();
                        token1.clear();
                        j = i+1;
                        for(i=j;i<line.length();i++) {
                            token1 += line.at(i);
                        }
                        straux3 = simb.busca_simb(token1,eh_simb);
                        if(eh_simb == true) {
                            outline += straux3;
                            outline += ' ';
                        } else {
                            errolist.insere_erro(17, lin_cont);
                        }
                        straux3.clear();
                        break;
                    } else if(line.at(i) == '+') { //Se o token for uma posicao de um vetor
                        straux3 = simb.busca_simb(token1,eh_simb); //Se for um simbolo invalido, gerar erro
                        if(eh_simb == true) {
                            espaco = data.space(token1);
                        } else {
                            errolist.insere_erro(17, lin_cont); //Operando invalido
                        }
                        token1.clear();
                        j = i+1;
                        for(i=j;i<line.length();i++) {
                            token1 += line.at(i);
                        }
                        pos1 = token1.find_first_not_of("0123456789",0);
                        if(pos1 == string::npos) {
                            if(atoi(token1.c_str()) >= espaco) { //Se o espaco nao foi alocado
                                errolist.insere_erro(18, lin_cont); //Endereco de memoria nao reservado
                            } else {
                                conversao << straux3;
                                conversao >> aux;
                                aux += atoi(token1.c_str());
                                conversao.str("");
                                conversao.clear();
                                conversao << aux;
                                straux4 = conversao.str();
                                outline += straux4;
                                outline += ' ';
                            }
                        }
                        break;
                    }
                }
                token1 += line.at(i);
            }
            token1.clear();
        }
        if(errolist.erro1 != NULL) {
            remove("Saida.o");
        } else {
            cout << outline << endl;
        }
    }
}
errolist.imprime_erros();
return 0;
}

void Diretivas(string rot, TU &tabu, Dados &D, string nom, string line, int &cont_pos, int &flagbegin, int &flagend, Simbolo_Tab &tabs, int flagpas, lista_erro &lerr, Def_Tab &defs, int contlinha, string &lin_saida, int &flags, bool &diretiva_verif, int flaga) {
    /*
    Argumentos:
    rot - Rotulo (se houver)
    tabu - Tabela de uso
    D - Tabela de dados
    nom - Nome da diretiva
    line - Linha sendo lida
    cont_pos - contador de posicao
    flagbegin - flag setada caso estejamos tratando da diretiva BEGIN
    flagend - flag setada caso estejamos tratando da diretiva END
    tabs - Tabela de Simbolos
    flagpas - flag que define a passagem que se esta realizando
    lerr - Lista de erros
    contlinha - Contador de linha
    flags - flag da diretiva SECTION
    flaga - flagauxiliar
    */
    int i, i1; //contador
    string stringaux, auxl, auxl2;
    size_t posic; //Utilizada na instrucao find
    int num, pos;
    stringstream hexadec, convert; //Usadas para converter hexadecimal para decimal e int para char
    hexadec.str("");
    hexadec.clear();
    convert.str("");
    convert.clear();

        if (nom == "SECTION") {
            posic = line.find("SECTION");
            posic += 8;
            for(i=posic;i<line.length();i++) {
                if(line.at(i) == ' ') {
                    lerr.insere_erro(3,contlinha);
                    break;
                }
                auxl += line.at(i);
            }
            if(i == line.length()) { //Se a linha terminou
            if(auxl == "TEXT") {
                flags = 1;
            } else if(auxl == "DATA") {
                flags = 2;
            } else {
                lerr.insere_erro(8,contlinha);
                flags = 3;
            }
            } else {
                lerr.insere_erro(8,contlinha);
                flags = 3;
            }
            diretiva_verif = true;
        } else if(nom == "SPACE") {
            if(flaga == 1 && diretiva_verif == true) {
                lerr.insere_erro(4, contlinha);
            }
            posic = line.find("SPACE");
            posic += 6;
            for(i=posic;i<line.length();i++) {
                if(line.at(i) == ' ') {
                    i1 = i;
                    break;
                }
                auxl += line.at(i);
            }
            /*hexadec << hex << auxl;
            hexadec >> num;
            if((atoi(auxl.c_str()) != 0 || num != 0)) {
            for(i=i1;i<line.length();i++){
                if(line.at(i) != ' ') {
                    break;
                }
            }*/
            if(i >= line.length()-1) { //SPACE tem um operando ou nenhum operando
            if(auxl.length() > 0) {
                posic = auxl.find("X");
                pos = posic;
                if(pos > -1) {
                    if(auxl.at(0) == '0') {
                    for(i=2;i<4;i++) {
                        auxl2 += auxl.at(i);
                    }
                    posic = auxl2.find_first_not_of("0123456789ABCDEF",0);
                    if(posic == string::npos) {
                        hexadec << hex << auxl2;
                        hexadec >> num;
                    } else {
                        lerr.insere_erro(17,contlinha);
                    }
                } else if(auxl.at(0) == '-') {
                    lerr.insere_erro(19,contlinha);
                }
                } else {
                    posic = auxl.find_first_not_of("0123456789",0);
                    if(posic == string::npos) {
                        num = atoi(auxl.c_str());
                    } else {
                        lerr.insere_erro(17,contlinha);
                    }
                    if(num < 0) {
                        lerr.insere_erro(19,contlinha);
                    }
                }
            } else {
                num = 1;
            }
            if(flagpas == 1 && num > 0) { //Se estamos na primeira passagem
                cont_pos += num;
            } else if(flagpas == 2 && num > 0) { //Se estamos na primeira passagem
                for(i=0;i<num;i++) {
                    lin_saida += "00";
                    lin_saida += " ";
                }
            }
            } else {
                lerr.insere_erro(3, contlinha);
            }
            diretiva_verif = true;
            D.insere_dados(rot,false,0,num);
            if(num == 0) {
                lerr.insere_erro(16,contlinha);
                diretiva_verif = true;
            }
        } else if(nom == "CONST") {
            if(flaga == 1 && diretiva_verif == true) {
                lerr.insere_erro(4, contlinha);
            }
            posic = line.find("CONST");
            posic += 6;
            for(i=posic;i<line.length();i++) {
                if(line.at(i) ==  ' ') {
                    lerr.insere_erro(3, contlinha);
                }
                auxl += line.at(i);
            }

            if(auxl.length() > 1) {
            if(auxl.find("X") > -1) { //Se o numero for hexadecimal, converter para decimal e gravar na saida
                if(auxl.at(0) == '0') {
                    for(i=2;i<4;i++) {
                        auxl2 += auxl.at(i);
                    }
                    posic = auxl2.find_first_not_of("0123456789ABCDEF",0);
                    if(posic == string::npos) {
                        hexadec << hex << auxl2;
                        hexadec >> num;
                    } else {
                        lerr.insere_erro(17,contlinha);
                    }
                } else if(auxl.at(0) == '-') {
                    auxl2 += '-';
                    for(i=3;i<5;i++) {
                        auxl2 += auxl.at(i);
                    }
                     posic = auxl2.find_first_not_of("0123456789ABCDEF-",0);
                     if(posic == string::npos) {
                        hexadec << hex << auxl2;
                        hexadec >> num;
                    } else {
                        lerr.insere_erro(17,contlinha);
                    }
                } else {
                    posic = auxl.find_first_not_of("0123456789-",0);
                    if(posic == string::npos) {
                        num = atoi(auxl.c_str());
                    } else {
                        lerr.insere_erro(17,contlinha);
                    }
                }
                if(flagpas == 2) { //Se estamos na segunda passagem
                    convert << num;
                    auxl = convert.str();
                    lin_saida += auxl;
                    lin_saida += ' ';
                }
                auxl2.clear();
            } else { //Se o numero for decimal e tiver mais de 1 digito, gravar na saida
                if(flagpas == 2) { //Se estamos na segunda passagem
                    lin_saida += auxl;
                    lin_saida += ' ';
                }
            }
            } else if (auxl.length() == 1){ //Se o numero so possuir um digito, adicionar um 0 na frente e gravar
                if(flagpas == 2) { //Se estamos na segunda passagem
                    auxl2 += '0';
                    auxl2 += auxl;
                    lin_saida += auxl2;
                    lin_saida += ' ';
                }
            }
            auxl.clear();
            auxl2.clear();
            if (flagpas == 1) { //Se estamos na primeira passagem
                cont_pos += 1;
            }
            diretiva_verif = true;
            D.insere_dados(rot,true,num,1);
        } else if (nom == "PUBLIC") {
            if(flagpas == 1) {
            posic = line.find("PUBLIC");
            posic += 7;
            for(i=posic;i<line.length();i++) {
                if(line.at(i) ==  ' ') {
                    lerr.insere_erro(3, contlinha);
                }
                stringaux += line.at(i);
            }
            }
            diretiva_verif = true;
            defs.inseredef_final(stringaux, "0");
        } else if (nom == "EXTERN") {
            if(flagpas == 2) {
                posic = line.find("EXTERN");
                posic += 7;
                for(i=posic;i<line.length();i++) {
                    if(line.at(i) ==  ' ') {
                        lerr.insere_erro(3, contlinha);
                    }
                    auxl += line.at(i);
                }
                convert << cont_pos;
                tabu.insere_symb(auxl,convert.str());
            }
            diretiva_verif = true;
        //So na segunda passagem
         }else if (nom == "BEGIN"){
            flagbegin = 1;
            diretiva_verif = true;
         } else if (nom == "END") {
            flagend = 1;
            diretiva_verif = true;
         } else {
            diretiva_verif = false;
         }
    hexadec.str("");
    hexadec.clear();
    convert.str("");
    convert.clear();
    auxl.clear();
}

void cria_LI(Lista_Instrucoes &LI) { //Funcao que cria a lista de instrucoes
LI.inserefinal_instrucao("ADD","01", 1);
LI.inserefinal_instrucao("SUB","02", 1);
LI.inserefinal_instrucao("MULT","03", 1);
LI.inserefinal_instrucao("DIV","04", 1);
LI.inserefinal_instrucao("JMP","05", 1);
LI.inserefinal_instrucao("JMPN","06", 1);
LI.inserefinal_instrucao("JMPP","07", 1);
LI.inserefinal_instrucao("JMPZ","08", 1);
LI.inserefinal_instrucao("COPY","09", 2);
LI.inserefinal_instrucao("LOAD","10", 1);
LI.inserefinal_instrucao("STORE","11",1);
LI.inserefinal_instrucao("INPUT","12",1);
LI.inserefinal_instrucao("OUTPUT","13",1);
LI.inserefinal_instrucao("STOP","14",0);
}

void cria_TS(Simbolo_Tab &TS) {
TS.inseresimb_final("L1", "0");
TS.inseresimb_final("L2", "4");
TS.inseresimb_final("L3", "7");
TS.inseresimb_final("L4", "11");
}
