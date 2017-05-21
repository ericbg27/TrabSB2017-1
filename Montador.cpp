#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stdlib.h>
#include <cctype>

using namespace std;

//***************************** DEFINICAO DE LISTAS ***************************************************

//**************************** LISTA EQU *******************************************************

class no {
    string rot; //Rotulo associado pela diretiva EQU
    string val_rotulo; //Valor associado ao rotulo
    no *prox_rot; //Posicao do proximo rotulo
public:
    no() {};
    void Def_Rotulo (string rotulo) {rot = rotulo;} //Define o rotulo de um no
    void Def_Valor (string valor) {val_rotulo = valor;} //Define o valor associado a um rotulo
    void Def_prox_rot (no *prox) {prox_rot = prox;} //Define proximo no
    string Return_rot() {return rot;}
    string Return_val() {return val_rotulo;}
    no* Return_prox_rot () {return prox_rot;}
};

class EQU_List { //Lista para as definicoes das diretivas EQU
    public:
        no *head;
        EQU_List() {
            head = NULL;
        }
        void insere_final (string,string); //Insere no no final da lista
        string busca_no (string,bool&); //Busca no na lista a partir do rotulo
        void limpa_lista();
};

void EQU_List::insere_final (string rotulo, string val) {
    no *novo_no = new no();
    novo_no->Def_Rotulo(rotulo);
    novo_no->Def_Valor(val);
    novo_no->Def_prox_rot(NULL);
    no *tmp = head;

    if(tmp != NULL) { //Se existem nos na lista, ir para o final
            while(tmp->Return_prox_rot() != NULL) {
                tmp = tmp->Return_prox_rot();
            }
        tmp->Def_prox_rot(novo_no);
    } else {
        head = novo_no;
    }
}

string EQU_List::busca_no (string label, bool& exist) { //Busca no na lista
    bool *aux = &exist;
    no *tmp = head;
    string tmpval;
    while(tmp != NULL) {
        if(tmp->Return_rot() == label) { //Se tiver rotulo == label, retornar valor associado e coloca flag exist em true
            tmpval = tmp->Return_val();
            *aux = true;
            return tmpval;
            break;
        }
        tmp = tmp->Return_prox_rot();
    }
    if(tmp == NULL) {
        *aux = false;
    }
}

void EQU_List::limpa_lista () {
    no *tmp = head;
    if (tmp == NULL)
        return;
    no *aux;
    do {
        aux = head->Return_prox_rot();
        head = aux;
        delete tmp;
        tmp = head;
    } while(tmp != NULL);
}

//*********************************************** FIM DA LISTA EQU *******************************************************

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
        bool eh_externo(string);
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

bool Simbolo_Tab::eh_externo(string tok) {
    Simbolo *sb = new Simbolo();
    sb = primeiro;
    while(sb != NULL) {
        if(sb->Retorna_rot() == tok) {
            if(sb->Retorna_ext() == true) {
                return true;
            } else {
                return false;
            }
            break;
        }
        sb = sb->Retorna_proximo_rot();
    }
    if(sb == NULL) {
        return false;
    }
}

//****************************************** FIM DA TABELA DE SIMBOLOS *********************************************************

//************************************************ LISTA DE ERROS ********************************************************

class erro {
    int flag_erro;
    int linha_num;
    erro *prox_erro;
public:
    erro() {};
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
   erro *p = new erro();
   p = erro1;
   erro *temp1 = new erro();
   erro *temp2 = new erro();
   novo_erro = new erro();
   novo_erro->Define_flag(flage);
   novo_erro->Define_linha(numline);
   novo_erro->Define_proxerro(NULL);
   int i = 0;
   if(p == NULL) {
        erro1 = novo_erro;
   } else {
   do {
        if(novo_erro->Return_linha() < p->Return_linha()) {
            if(i == 0) {
                temp2 = erro1;
                erro1 = novo_erro;
                erro1->Define_proxerro(temp2);
                break;
            }
            temp1 = p;
            temp2 = novo_erro;
            temp2->Define_proxerro(temp1);
            break;
        }
            temp1 = p;
            p = p->Return_proxerro();
            i++;
   } while(p != NULL);
   if(p == NULL) {
        temp1->Define_proxerro(novo_erro);
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
    Definicao() {};
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
        void imprime_def();
};

void Def_Tab::imprime_def() {
    Definicao *nov = def1;
    if(nov != NULL) {
    while(nov != NULL) {
    cout << nov->Retorna_def() << " = " << nov->Retorna_valdef() << endl;
    nov = nov->Retorna_prox_def();
    }
    }
}

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
    string conteudo;
    numerolinha *prox_lin;
public:
    Define_linum (int lin) {linum = lin;}
    Define_proxlin (numerolinha *proxli) {prox_lin = proxli;}
    Define_cont (string cont) {conteudo = cont;}
    int Return_linum() {return linum;}
    string Return_cont() {return conteudo;}
    numerolinha* Return_proxlin() {return prox_lin;}
};

class lista_linhas {
    public:
    numerolinha *primeiralinha;
    lista_linhas () {
        primeiralinha = NULL;
    }
    void insere_numerolin(int,string);
    void busca_listalinhas (int&,lista_linhas&,string,int);
    void limpa_listalin();
};

void lista_linhas::insere_numerolin(int linum1, string cont1) {
   numerolinha *nova_linha;
   numerolinha *p = new numerolinha();
   p = primeiralinha;
   numerolinha *temp1 = new numerolinha();
   numerolinha *temp2 = new numerolinha();
   nova_linha = new numerolinha();
   nova_linha->Define_linum(linum1);
   nova_linha->Define_cont(cont1);
   nova_linha->Define_proxlin(NULL);
   int i = 0;
   if(p == NULL) {
        primeiralinha = nova_linha;
   } else {
   do {
        if(nova_linha->Return_linum() < p->Return_linum()) {
            if(i == 0) {
                temp2 = primeiralinha;
                primeiralinha = nova_linha;
                primeiralinha->Define_proxlin(temp2);
            }
            temp1 = p;
            temp2 = nova_linha;
            temp2->Define_proxlin(temp1);
            break;
        }
            temp1 = p;
            p = p->Return_proxlin();
   } while(p != NULL);
   if(p == NULL){
        temp1->Define_proxlin(nova_linha);
   }
   }
}

void lista_linhas::busca_listalinhas (int &lcont, lista_linhas &ll, string cont2, int fgp) {
    numerolinha *new_linha = new numerolinha();
    new_linha = primeiralinha;
    numerolinha *tp = new numerolinha();
    numerolinha *auxlin = new numerolinha();
    int i = 1;
    if(fgp == 1) {
    while(new_linha != NULL) {
        if(new_linha->Return_linum() != i) {
            lcont = i;
            ll.insere_numerolin(lcont,cont2);
            break;
        }
        tp = new_linha;
        new_linha = new_linha->Return_proxlin();
        i++;
    }
    if(new_linha == NULL){
        lcont = i;
        auxlin->Define_linum(lcont);
        auxlin->Define_cont(cont2);
        auxlin->Define_proxlin(NULL);
        tp->Define_proxlin(auxlin);
    }
    } else if(fgp == 2) {
        while(new_linha != NULL) {
            if(new_linha->Return_cont() == cont2) {
                lcont = i;
                break;
            }
            new_linha = new_linha->Return_proxlin();
            i++;
        }
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
    Rotulo() {};
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
    Simb_TU() {};
    void Define_symbol(string s) {symbol = s;}
    void Define_value (string v) {value = v;}
    void Define_psymb (Simb_TU *psymb) {proxsymb = psymb;}
    string Return_symbol() {return symbol;}
    string Return_value() {return value;}
    Simb_TU* Return_psymb() {return proxsymb;}
};

class TU {
public:
    Simb_TU *symb1;
    TU () {
        symb1 = NULL;
    }
    void limpa_TU ();
    void imprime_TU ();
};

void TU::imprime_TU() {
    Simb_TU *nov = symb1;
    while(nov != NULL) {
    cout << nov->Return_symbol() << " = " << nov->Return_value() << endl;
    nov = nov->Return_psymb();
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

//**************************************** TABELA DE REALOCACAO **********************************************************

class elemento {
    int abs_ou_rel;
    elemento *proxel;
public:
    elemento () {};
    void Define_ar(int aor) {abs_ou_rel = aor;}
    void Define_proxel(elemento *pel) {proxel = pel;}
    int Return_ar() {return abs_ou_rel;}
    elemento* Return_proxel() {return proxel;}
};

class Rtab {
public:
    elemento *first;
    Rtab() {
        first = NULL;
    }
    void insere_el(int);
    void imprime_elem();
    void limpa_rt();
};

void Rtab::insere_el(int elm) {
    elemento *novo_elemento = new elemento();
    novo_elemento->Define_ar(elm);
    novo_elemento->Define_proxel(NULL);
    elemento *tmp = first;
    if(tmp != NULL) { //Se existem nos na lista, ir para o final
            while(tmp->Return_proxel()!= NULL) {
                tmp = tmp->Return_proxel();
            }
        tmp->Define_proxel(novo_elemento);
    } else {
        first = novo_elemento;
    }
}

void Rtab::imprime_elem() {
    elemento *nov = first;
    while(nov != NULL) {
    cout << nov->Return_ar();
    nov = nov->Return_proxel();
    }
}

void Rtab::limpa_rt() {
    elemento *tmpe = first;
    if (tmpe == NULL)
        return;
    elemento *auxe;
    do {
        auxe = first->Return_proxel();
        first = auxe;
        delete tmpe;
        tmpe = first;
    } while(tmpe != NULL);
}
//************************************ FIM DA TABELA DE REALOCACAO *******************************************************

//**************************************** FIM DA DEFINICAO DE LISTAS **********************************************

//************************************** PROTOTIPOS **************************************************************************
void Diretivas(string, Rtab&, TU&, Dados&, string, string, int&, int&, int&, Simbolo_Tab&, int, lista_erro&, Def_Tab&, int, string&, int&, bool&, int);
void cria_LI(Lista_Instrucoes&);
void cria_TS(Simbolo_Tab&);
void simb_to_def (Simbolo_Tab,Def_Tab&);
void insere_TU(Simbolo_Tab,TU&,int,string);
void Preprocessador(istream&,lista_erro&,lista_linhas&);
//***************************************************************************************************************************

int main () {
Simbolo_Tab simb;
TU TabUso;
Dados data;
Rtab TR;
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
int flagsec = 0, fbegin = 0, fend = 0, flagp = 1, flagel = 0, flages = 0, flaginst = 0, flagrot = 0, flagaux1 = 0, flagaux2 = 0, flagpos = 0, flagaux3 = 0, flagstop = 0;
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
flagstop - Flag para a diretiva STOP
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
    ifstream arquivo1 (nome.c_str());
    fstream saida ("Saida.o", ios::out);
    if(saida.is_open() && arquivo1.is_open()) {
    Preprocessador(arquivo1, errolist, linls);
    ifstream arquivo("Preproc.pre");
//**************************************************** PRIMEIRA PASSAGEM ****************************************************
         /*Aqui espera-se que a primeira linha seja a diretiva SECTION TEXT ou BEGIN. Se for BEGIN,
           procurar por SECTION TEXT. Em ambos os casos deve-se verificar se esta ultima existe.Se
           existir, gerar erros para todas as linhas anteriores.Caso contrario, gerar erro de Secao
            de texto faltante. Alem disso, faz-se as analises lexica, sintatica e semantica para cada
            linha */
        flagp = 1;
        while(getline(arquivo,line)) {
            lin_cont++; //Incrementando contador de linha
        if(linls.primeiralinha != NULL) {
            linls.busca_listalinhas(lin_cont,linls,line,flagp);
        }
            flagel = 0; //Zerando flags e contadores
            flages = 0;
            flagrot = 0;
            flagsec = 0;
            fbegin = 0;
            i = 0;
            t = 0;
            k = 0;
            j = 0;
            token1.clear();
            rotulo.clear();
            eh_diretiva == false;
            eh_simb = false;

            for(i=0;i<line.length();i++) {
                if(line.at(i) == ':' || line.at(i) == ' ' || i+1 == line.length()){
                                                                                     //Pegando token. Caso seja rotulo, verificar se nao esta repetido
                                                                                    //na linha e veifica se eh um token valido. Caso contrario, apenas
                                                                                    //verifica-se se eh um token valido
                    if(i+1 == line.length()) {
                        token1 += line.at(i);
                        opcode = inst.busca_instrucao(token1, pos_contaux, lin_cont, errolist);
                        if(opcode != "14" && opcode != "-1") {
                            errolist.insere_erro(3, lin_cont);
                        }
                        k = i;
                    }
                        k = i+1;
                        break;
                }
                token1 += line.at(i);
            }

            if(token1.length() > 50) {
                errolist.insere_erro(2,lin_cont);
                flagel = 1;
            }
            if(!(isalpha(token1.at(0)) != 0 || token1.at(0) == '_')) { //Vericando se eh um token valido
                errolist.insere_erro(2, lin_cont);
                flagel = 1;
            }
            for(t=1;t<token1.length();t++) {
                if(!(isalnum(token1.at(t)) != 0 || token1.at(t) == '_')){
                    errolist.insere_erro(2, lin_cont);
                    flagel = 1;
                }
            } //Fim da verificacao de validade do token

            if (flagel == 0) { //Se o primeiro token eh valido
                //Verificar se nao eh a diretiva SECTION TEXT
                if(token1 == "SECTION") {
                    Diretivas(rotulo, TR, TabUso, data, token1, line, pos_cont, fbegin, fend, simb, flagp, errolist, defin, lin_cont, outline, flagsec, eh_diretiva, flagaux2);
                }
                if(token1 == "END") {
                    errolist.insere_erro(4, lin_cont);
                }
                if(flagsec == 1) {
                    flagaux2 = flagsec;
                    break; //Se eh a diretiva SECTION TEXT sair do loop
                } else if(flagsec == 2) { //Se for a diretiva SECTION DATA, sair do loop
                    flagaux2 = flagsec;
                    break;
                } else if(flagsec == 3) {
                    flages = 1;
                    continue;
                }
                    if(line.at(i) == ':') { //Se eh rotulo, verificar se nao tem outro rotulo na mesma linha
                        flagrot = 1;
                        for(j=k;j<line.length();j++) {
                            if(line.at(j) != ' ' && line.at(j) != ':') { //Existe outro token
                                for(t=j;t<line.length();t++) {
                                    if(line.at(t) == ':') { //Se o token eh outro rotulo, gerar erro
                                        k = t;
                                        errolist.insere_erro(1, lin_cont);
                                        break;
                                    }
                                }
                            } else if (line.at(j) == ':'){ //Dois caracteres ':' depois do rotulo configuram um token invalido
                                k = j;
                                errolist.insere_erro(2, lin_cont);
                                flagel = 1;
                                break;
                            }
                        }
                    }
                        if(j == line.length() && flagel == 0) { //Se encontrou apenas 1 rotulo e o rotulo eh valido, armazenar na TS e ir para proximo token
                           simb.busca_simb(token1, eh_simb);
                           if(eh_simb == false) { //Se nao esta na TS
                                conversao << pos_cont; //Convertendo contador de int para string
                                for(t=i+2;t<line.length();t++) {
                                    if(line.at(t) == ' '){
                                        break;
                                    }
                                    straux2 += line.at(t);
                                }
                                if(straux2 == "EXTERN"){
                                    simb.inseresimb_final(token1, conversao.str(), true);
                                } else {
                                    simb.inseresimb_final(token1, conversao.str(), false);
                                }
                                straux2.clear();
                            } else { //Se esta na TS, erro
                                errolist.insere_erro(10, lin_cont);
                            }
                            rotulo = token1;
                            k++; //Proximo token
                            token1.clear();
                            for(t=k;t<line.length();t++) {
                                if(line.at(t) == ' ') {
                                    k = t;
                                    break;
                                }
                                token1 += line.at(t);
                                k = t;
                            }
                        }
                        if(token1.length() > 50) { //Vericando se eh um token valido
                            errolist.insere_erro(2,lin_cont);
                            flagel = 1;
                        }
                        if(!(isalpha(token1.at(0)) != 0 || token1.at(0) == '_')) {
                            errolist.insere_erro(2, lin_cont);
                            flagel = 1;
                        }
                        for(t=1;t<token1.length();t++) {
                            if(!(isalnum(token1.at(t)) != 0 || token1.at(t) == '_')){
                                errolist.insere_erro(2, lin_cont);
                                flagel = 1;
                            }
                        } //Fim da verificacao de validade do token
                        if(flagel == 0) {                                             //Verificar se eh instrucao ou diretiva, caso seja o token apos o rotulo
                            pos_contaux = pos_cont;                                   //ou o primeiro token nao seja rotulo e, alem disso, seja token valido
                            opcode = inst.busca_instrucao(token1, pos_contaux, lin_cont, errolist);
                            if(opcode != "-1") { //Se eh instrucao, verificar se o numero de operandos esta correto
                                flagpos = 1;
                                if(opcode == "14")
                                    flagstop = 1;
                                if(k != line.length()) { //STOP
                                if (line.at(k) == ' ')
                                    k++;
                                token1.clear();
                                for(i=k;i<line.length();i++) {
                                    if(line.at(i) == ' ' || line.at(i) == ',') {
                                        k = i+1;
                                        break;
                                    }
                                    if(line.at(i) != ',')
                                        token1 += line.at(i);
                                }
                                if(token1.length() > 50) { //Vericando se eh um token valido
                                    errolist.insere_erro(2,lin_cont);
                                    flagel = 1;
                                }
                                if(!(isalpha(token1.at(0)) != 0 || token1.at(0) == '_')) {
                                    errolist.insere_erro(2, lin_cont);
                                    flagel = 1;
                                }
                                for(t=1;t<token1.length();t++) {
                                    if(!(isalnum(token1.at(t)) != 0 || token1.at(t) == '_' || token1.at(t) == '+')){
                                        errolist.insere_erro(2, lin_cont);
                                        flagel = 1;
                                    }
                                } //Fim da verificacao de validade do token
                                if(i<line.length() && flagel == 0) { //Nesse caso existe outro token na linha, verificar
                                                                    //(Caso primeiro token seja valido)
                                    if(opcode != "09") { //Se nao for COPY nao deve ter 2 operandos
                                        errolist.insere_erro(3, lin_cont);
                                        flages = 1;
                                    }
                                    token1.clear();
                                    for(i=k;i<line.length();i++) { //Pegando o segundo operando
                                        if(line.at(i) == ' ') {
                                            errolist.insere_erro(3,lin_cont);
                                            flages = 1;
                                        }
                                        token1 += line.at(i);
                                    }
                                    if(token1.length() > 50) { //Vericando se eh um token valido
                                        errolist.insere_erro(2,lin_cont);
                                        flagel = 1;
                                    }
                                    if(!(isalpha(token1.at(0)) != 0 || token1.at(0) == '_')) {
                                        errolist.insere_erro(2, lin_cont);
                                        flagel = 1;
                                    }
                                    for(t=1;t<token1.length();t++) {
                                        if(!(isalnum(token1.at(t)) != 0 || token1.at(t) == '_' || token1.at(t) == '+')){
                                            errolist.insere_erro(2, lin_cont);
                                            flagel = 1;
                                        }
                                    } //Fim da verificacao de validade do token
                                }
                                }
                            } else {
                                Diretivas(rotulo, TR, TabUso, data, token1, line, pos_cont, fbegin, fend, simb, flagp, errolist, defin, lin_cont, outline, flagsec, eh_diretiva, flagaux2);
                                if(token1 == "SPACE" || token1 == "CONST") {
                                    flagpos = 1;
                                }
                                if(token1 == "END") {
                                    errolist.insere_erro(4, lin_cont);
                                }
                                if (fbegin == 1) {
                                    flagaux1 = fbegin;
                                }
                                if (fend == 1) {
                                    flagaux3 = fend;
                                }
                                if(eh_diretiva == false) {
                                    errolist.insere_erro(5, lin_cont);
                                }
                            }
                        }
                }
                if(flagsec == 0 && fbegin == 0) { //Se nao for a diretiva SECTION ou BEGIN, erro de diretiva ou instrucao na secao errada
                    errolist.insere_erro(4, lin_cont);
                }
                token1.clear();
            }
        if(flagaux2 == 0) {
            errolist.insere_erro(9, lin_cont);
        }
        while(getline(arquivo, line)) { //Se achou a diretiva SECTION
            lin_cont++; //Incrementando contador de linha
            if(linls.primeiralinha != NULL)
                linls.busca_listalinhas(lin_cont,linls,line,flagp);
            flagel = 0; //Zerando flags e contadores
            flages = 0;
            flagrot = 0;
            flagsec = 0;
            fbegin = 0;
            i = 0;
            t = 0;
            k = 0;
            j = 0;
            token1.clear();
            eh_diretiva = false;
            eh_simb = false;

            for(i=0;i<line.length();i++) {
                if(line.at(i) == ':' || line.at(i) == ' ' || i+1 == line.length()){
                                                                                     //Pegando token. Caso seja rotulo, verificar se nao esta repetido
                    if(line.at(i) == ' ' || i+1 == line.length()) {
                                                                                     //na linha e veifica se eh um token valido. Caso contrario, apenas
                        if(token1 != "SECTION" && token1 != "PUBLIC" && flagpos == 1) { //verifica-se se eh um token valido
                            pos_cont++;
                        }
                    }
                    if(i+1 == line.length()) {
                       token1 += line.at(i);
                       opcode = inst.busca_instrucao(token1, pos_contaux, lin_cont, errolist);
                        if(opcode != "14" && opcode != "-1") {
                            errolist.insere_erro(3, lin_cont);
                        }
                        k = i;
                        break;
                    }
                        k = i+1;
                        break;
                }
                token1 += line.at(i);
            }
            if(token1.length() > 50) {
                errolist.insere_erro(2,lin_cont);
                flagel = 1;
            }
            if(!(isalpha(token1.at(0)) != 0 || token1.at(0) == '_')) { //Vericando se eh um token valido
                errolist.insere_erro(2, lin_cont);
                flagel = 1;
            }
            for(t=1;t<token1.length();t++) {
                if(!(isalnum(token1.at(t)) != 0 || token1.at(t) == '_')){
                    errolist.insere_erro(2, lin_cont);
                    flagel = 1;
                }
            } //Fim da verificacao de validade do token
            if (flagel == 0) { //Se o primeiro token eh valido
                //Verificar se nao eh a diretiva SECTION TEXT
                if(token1 == "SECTION") {
                    Diretivas(rotulo, TR, TabUso, data, token1, line, pos_cont, fbegin, fend, simb, flagp, errolist, defin, lin_cont, outline, flagsec, eh_diretiva, flagaux2);
                }
                if(token1 == "BEGIN") {
                    errolist.insere_erro(4, lin_cont);
                }
                if(flagaux2 != 2 && token1 == "END") {
                    errolist.insere_erro(4, lin_cont);
                }
                if(k == line.length() && flagsec == 0) { //Se a linha acabou ou nao eh a diretiva SECTION
                    errolist.insere_erro(7, lin_cont); //Se a linha acabou, nao existe outro token. Logo, gerar erro
                    flages = 1;
                } else if(flagsec == 1) {
                    errolist.insere_erro(6, lin_cont);
                    flagaux2 = flagsec;
                    continue;
                } else if(flagsec == 2) {
                    flagaux2 = flagsec;
                    continue;
                } else if(flagsec == 3) {
                    flages = 1;
                    continue;
                }
                    if(line.at(i) == ':') { //Se eh rotulo, verificar se nao tem outro rotulo na mesma linha
                        flagrot = 1;
                        for(j=k;j<line.length();j++) {
                            if(line.at(j) != ' ' && line.at(j) != ':') { //Existe outro token
                                for(t=j;t<line.length();t++) {
                                    if(line.at(t) == ':') { //Se o token eh outro rotulo, gerar erro
                                        k = t;
                                        j = k;
                                        flagel = 1;
                                        errolist.insere_erro(1, lin_cont);
                                        break;
                                    }
                                }
                            } else if (line.at(j) == ':' && flagel == 0){ //Dois caracteres ':' depois do rotulo configuram um token invalido
                                k = j;
                                errolist.insere_erro(2, lin_cont);
                                flagel = 1;
                                break;
                            }
                        }
                    }
                        if(j == line.length() && flagel == 0) { //Se encontrou apenas 1 rotulo e o rotulo eh valido, armazenar na TS (caso ja nao esteja la) e ir para proximo token
                           simb.busca_simb(token1, eh_simb);
                           if(eh_simb == false) { //Se nao esta na TS
                                conversao.str("");
                                conversao.clear();
                                for(t=i+2;t<line.length();t++) {
                                    if(line.at(t) == ' '){
                                        break;
                                    }
                                    straux2 += line.at(t);
                                }
                                if(straux2 != "EXTERN" && straux2 != "PUBLIC" && straux2 != "BEGIN" && straux2 != "END"){
                                    pos_cont++;
                                }
                                straux2.clear();
                                conversao << pos_cont; //Convertendo contador de int para string
                                for(t=i+2;t<line.length();t++) {
                                    if(line.at(t) == ' '){
                                        break;
                                    }
                                    straux2 += line.at(t);
                                }
                                if(straux2 == "EXTERN"){
                                    simb.inseresimb_final(token1, conversao.str(), true);
                                } else {
                                    simb.inseresimb_final(token1, conversao.str(), false);
                                    pos_cont--;
                                }
                                straux2.clear();
                            } else { //Se esta na TS, erro
                                errolist.insere_erro(10, lin_cont);
                            }
                            rotulo = token1;
                            k++; //Proximo token
                            token1.clear();
                            for(t=k;t<line.length();t++) {
                                if(line.at(t) == ' ') {
                                    k = t;
                                    break;
                                }
                                token1 += line.at(t);
                                k = t;
                            }
                            if(token1 != "BEGIN" && token1 != "PUBLIC" && token1 != "EXTERN" && token1 != "END" && token1 != "CONST")
                                pos_cont++;
                        }

                        if(token1.length() > 50) { //Vericando se eh um token valido
                            errolist.insere_erro(2,lin_cont);
                            flagel = 1;
                        }
                        if(!(isalpha(token1.at(0)) != 0 || token1.at(0) == '_')) {
                            errolist.insere_erro(2, lin_cont);
                            flagel = 1;
                        }
                        for(t=1;t<token1.length();t++) {
                            if(!(isalnum(token1.at(t)) != 0 || token1.at(t) == '_')){
                                errolist.insere_erro(2, lin_cont);
                                flagel = 1;
                            }
                        } //Fim da verificacao de validade do token
                        if(flagel == 0) {
                                                                                      //Verificar se eh instrucao ou diretiva, caso seja o token apos o rotulo
                            pos_contaux = pos_cont;                                   //ou o primeiro token nao seja rotulo e, alem disso, seja token valido
                            opcode = inst.busca_instrucao(token1, pos_contaux, lin_cont, errolist);
                            if(opcode != "-1") { //Se eh instrucao, verificar se o numero de operandos esta correto
                                flagpos = 1;
                                if(opcode == "14")
                                    flagstop = 1;
                                if(flagaux2 == 2) {
                                    errolist.insere_erro(4,lin_cont);
                                }
                                if(opcode != "14") { //Se nao for a instrucao STOP
                                if (line.at(k) == ' ')
                                    k++;
                                token1.clear();
                                for(i=k;i<line.length();i++) { //Pegando primeiro token
                                    if(line.at(i) == ' ' || line.at(i) == ',') {
                                        k = i+1;
                                        break;
                                    }
                                    if(line.at(i) != ',')
                                        token1 += line.at(i);
                                }
                                pos_cont++;
                                if(token1.length() > 50) { //Vericando se eh um token valido
                                    errolist.insere_erro(2,lin_cont);
                                    flagel = 1;
                                }
                                if(!(isalpha(token1.at(0)) != 0 || token1.at(0) == '_')) {
                                    errolist.insere_erro(2, lin_cont);
                                    flagel = 1;
                                }
                                for(t=1;t<token1.length();t++) {
                                    if(!(isalnum(token1.at(t)) != 0 || token1.at(t) == '_' || token1.at(t) == '+')){
                                        errolist.insere_erro(2, lin_cont);
                                        flagel = 1;
                                    }
                                } //Fim da verificacao de validade do token
                                if(i<line.length() && flagel == 0) { //Nesse caso existe outro token na linha, verificar
                                    pos_cont++;                     //(Caso primeiro token seja valido)
                                    if(pos_cont != pos_contaux) {
                                        errolist.insere_erro(3, lin_cont);
                                        flages = 1;
                                    }

                                    token1.clear();
                                    for(j=k;j<line.length();j++) { //Pegando o segundo operando
                                        if(line.at(j) == ' ' && line.at(i) != ',') { //Caso nao seja a instrucao COPY
                                            errolist.insere_erro(3,lin_cont);
                                            flages = 1;
                                        } else if (line.at(j) == ' ' && line.at(i) == ',') {
                                            errolist.insere_erro(5,lin_cont);
                                            flages = 1;
                                        }
                                        if(line.at(j) != ' ')
                                            token1 += line.at(j);
                                    }
                                    if(token1.length() > 50) { //Vericando se eh um token valido
                                        errolist.insere_erro(2,lin_cont);
                                        flagel = 1;
                                    }
                                    if(!(isalpha(token1.at(0)) != 0 || token1.at(0) == '_')) {
                                        errolist.insere_erro(2, lin_cont);
                                        flagel = 1;
                                    }
                                    for(t=1;t<token1.length();t++) {
                                        if(!(isalnum(token1.at(t)) != 0 || token1.at(t) == '_' || token1.at(t) == '+')){
                                            errolist.insere_erro(2, lin_cont);
                                            flagel = 1;
                                        }
                                    } //Fim da verificacao de validade do token
                                }
                                }
                            } else {
                                Diretivas(rotulo, TR, TabUso, data, token1, line, pos_cont, fbegin, fend, simb, flagp, errolist, defin, lin_cont, outline, flagsec, eh_diretiva, flagaux2);
                                if(token1 == "SPACE" || token1 == "CONST") {
                                    flagpos = 1;
                                }
                                if(token1 == "BEGIN") {
                                    errolist.insere_erro(4, lin_cont);
                                }
                                if(flagaux2 != 2 && token1 == "END") {
                                    errolist.insere_erro(4, lin_cont);
                                }
                                if (fbegin == 1) {
                                    flagaux1 = fbegin;
                                }
                                if (fend == 1) {
                                    flagaux3 = fend;
                                }
                                if(eh_diretiva == false) {
                                    errolist.insere_erro(5, lin_cont);
                                }
                            }
                        }
                    }
                token1.clear();
            }
        if(flagaux1 == 1 && flagaux3 == 0 || flagaux1 == 0 && flagaux3 == 1) {
            errolist.insere_erro(12, lin_cont);
        }
        if(flagaux1 == 0 && flagaux3 == 0 && flagstop == 0) {
            errolist.insere_erro(13, lin_cont);
        }
simb_to_def(simb,defin);
cout << "TS" << endl;
simb.imprime_simb();
cout << "TD" << endl;
defin.imprime_def();
//*********************************************** FIM DA PRIMEIRA PASSAGEM **************************************************
arquivo.clear();
arquivo.seekg(0, ios::beg);
//**************************************************** SEGUNDA PASSAGEM *******************************************************
flagp = 2;
i = 0;
j = 0;
k = 0;
t = 0;
pos_cont = 0;
while(getline(arquivo,line)){
            //cout << line << endl;
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
                linls.busca_listalinhas(lin_cont,linls,line,flagp);
             for(i=0;i<line.length();i++) {     //Pegando tokens
                if(token1 == "SECTION" || token1 == "PUBLIC" || token1 == "EXTERN" || token1 == "BEGIN" || token1 == "END")
                    break;
                if(line.at(i) == ':' || line.at(i) == ' ' || i+1 == line.length() || line.at(i) == ',' || line.at(i) == '+'){
                    if(i+1 == line.length()) { //Se for o ultimo token da linha
                        token1 += line.at(i);
                        if(token1 == "SECTION" || token1 == "PUBLIC" || token1 == "EXTERN" || token1 == "BEGIN" || token1 == "END")
                            break;
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
                                    TR.insere_el(1);
                                    insere_TU(simb, TabUso, pos_cont, token1);
                                    pos_cont++;
                                }
                        } else if (opcode == "-1" && eh_diretiva == false) {
                            opcode = inst.busca_instrucao(token1, pos_contaux, lin_cont, errolist);
                            if(opcode == "14" ) { //Se for a instrucao STOP
                                TR.insere_el(0);
                                flaginst = 1;
                                outline += opcode;
                                outline += ' ';
                                pos_cont++;
                            }
                            if(token1 == "SPACE")
                                Diretivas(rotulo, TR, TabUso, data, token1, line, pos_cont, fbegin, fend, simb, flagp, errolist, defin, lin_cont, outline, flagsec, eh_diretiva, flagaux2);
                        }
                        break;
                    } else if(line.at(i) == ' ') {
                        opcode = inst.busca_instrucao(token1,pos_contaux, lin_cont, errolist);
                        if(opcode != "-1") {
                            TR.insere_el(0);
                            outline += opcode;
                            outline += ' ';
                            pos_cont++;
                            i++;
                        } else {
                            Diretivas(rotulo, TR, TabUso, data, token1, line, pos_cont, fbegin, fend, simb, flagp, errolist, defin, lin_cont, outline, flagsec, eh_diretiva, flagaux2);
                            i++;
                        }
                        token1.clear();
                      //  if(line.length() == i+1 && opcode != "-1") {//Se o simbolo nao for de um digito
                        //    i--;
                        //}
                       // cout << "token: " << token1 << endl;
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
                            insere_TU(simb, TabUso, pos_cont, token1);
                            TR.insere_el(1);
                            outline += straux3;
                            outline += ' ';
                        } else {
                            errolist.insere_erro(17, lin_cont);
                        }
                        straux3.clear();
                        token1.clear();
                        j = i+1;
                        pos_cont++;
                        for(i=j;i<line.length();i++) {
                            token1 += line.at(i);
                        }
                        straux3 = simb.busca_simb(token1,eh_simb);
                        if(eh_simb == true) {
                            TR.insere_el(1);
                            outline += straux3;
                            outline += ' ';
                            insere_TU(simb, TabUso, pos_cont, token1);
                        } else {
                            errolist.insere_erro(17, lin_cont);
                        }
                        straux3.clear();
                        pos_cont++;
                        break;
                    } else if(line.at(i) == '+') { //Se o token for uma posicao de um vetor
                        straux3 = simb.busca_simb(token1,eh_simb); //Se for um simbolo invalido, gerar erro
                        if(eh_simb == true) {
                            TR.insere_el(1);
                            espaco = data.space(token1);
                            insere_TU(simb, TabUso, pos_cont, token1);
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
                            if(atoi(token1.c_str()) >= espaco && simb.eh_externo(token1) == true) { //Se o espaco nao foi alocado para um operando nao externo
                                errolist.insere_erro(18, lin_cont); //Endereco de memoria nao reservado
                            } else {
                                conversao << straux3;
                                conversao >> aux;
                                aux += atoi(token1.c_str());
                                conversao.str("");
                                conversao.clear();
                                conversao << aux;
                                if(conversao.str().length() == 1)
                                    straux4 += '0';
                                straux4 += conversao.str();
                                outline += straux4;
                                outline += ' ';
                            }
                        }
                        pos_cont++;
                        continue;
                    }
                }
                    token1 += line.at(i);
                    if(i+1 == line.length()) {
                        i--;
                        token1.clear();
                    }
            }
            token1.clear();
        }
        //if(errolist.erro1 != NULL) {
          //  remove("Saida.o");
        //} else {
          cout << "CODE" << endl;
          outline.erase(outline.length()-1,1);
          cout << outline << endl;
          cout << "TU" << endl;
          TabUso.imprime_TU();
          cout << "TR" << endl;
          TR.imprime_elem();
          cout << endl;
          cout << "ERROS" << endl;
          errolist.imprime_erros();
        //}
    //}
//}
//*********************************************** FIM DA SEGUNDA PASSAGEM ***************************************************
}
}
errolist.limpa_listae(); //*
TabUso.limpa_TU(); //*
TR.limpa_rt(); // *
simb.limpa_tabelasimb(); //*
defin.limpa_tabeladef(); //*
return 0;
}

//****************************************************************************************** LISTA DE DIRETIVAS ******************************************************************************************************************************************************
void Diretivas(string rot, Rtab &TR1, TU &tabu, Dados &D, string nom, string line, int &cont_pos, int &flagbegin, int &flagend, Simbolo_Tab &tabs, int flagpas, lista_erro &lerr, Def_Tab &defs, int contlinha, string &lin_saida, int &flags, bool &diretiva_verif, int flaga) {
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
            if(flagpas == 2 && num > 0) {
                for(i=0;i<num;i++) {
                    TR1.insere_el(1);
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
            if(flaga == 1) {
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
                convert << auxl;
                convert >> num;
            }
            auxl.clear();
            auxl2.clear();
                cont_pos++;
            diretiva_verif = true;
            //cout << "CONST: " << num << endl;
            if(flagpas == 1)
                D.insere_dados(rot,true,num,1);
            if(flagpas == 2)
                TR1.insere_el(0);
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
            diretiva_verif = true;
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

//************************************************** FIM DA LISTA DE DIRETIVAS *************************************************

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

void simb_to_def (Simbolo_Tab s,Def_Tab &d) { //Passa simbolos da TS para a TD
    Simbolo *sb = new Simbolo();
    sb = s.primeiro;
    while(sb != NULL) {
        d.mod_def(sb->Retorna_rot(), sb->Retorna_val());
        sb = sb->Retorna_proximo_rot();
    }
}

//******************************************************** PRE-PROCESSADOR ****************************************************
void Preprocessador(istream &file, lista_erro &LE, lista_linhas &LL) {
EQU_List no; //Objeto da lista da diretiva EQU
string str, linha, strtemp;
string token, token1, token2, dir, linhaout, linhain, aux, aux2, aux3;
string equ, rotulo, valorstr; //strings para abrir arquivo, guardar linhas, verificacoes de linhas e diretivas
int tam1, tam2, tam3, i, j, k, t, cont, erro_count = 0, linhacont = 0; //Contadores e variaveis para tamanho de linha
int flagrotulo = 0, flagIF1 = 0, flagIF2 = 0, flagsection = 0, flagcopy = 0; //Flag para verificar erros, se existe rotulo, flags para diretiva IF, flag para verificar se o programa esta na ordem correta e flag para instrucao COPY
int *flag;
bool eh_rotulo = false; //Variavel para definir se pertence a lista da diretiva EQU
string valor; //Variavel para valor associado ao rotulo na lista da diretiva EQU
int posit = 0; //Inteiro para pegar posicao das diretivas IF, CONST e SPACE
size_t pos; //Necessario para funcao str.find()

ofstream out("Preproc.pre");
    while(getline(file,linha)) {
        pos = linha.find("\t");
        posit = pos;
        if(posit > -1) {
            while(posit > -1) {
                aux = linha.substr(0,pos);
                aux2 = linha.substr(pos+1,string::npos);
                linha.clear();
                linha += aux;
                linha += ' ';
                linha += aux2;
                aux.clear();
                aux2.clear();
                pos = linha.find("\t");
                posit = pos;
            }
        }
        linhacont++; //Incrementa contador de linha
        if(flagIF1 == 0 && flagIF2 == 1) { //Se achou a diretiva IF mas seu operando foi zero, ignorar linha
            flagIF2 = 0;
            LL.insere_numerolin(linhacont,linha); //Como a linha sera apagada no pre processamento, armazenar numero
            continue;
        }
        token.clear(); //Limpando strings
        equ.clear();
        valorstr.clear();
        rotulo.clear();
        dir.clear();
        token1.clear();
        token2.clear();
        aux.clear();
        valor.clear();
        linhain.clear();
        eh_rotulo = false; //Colocando variavel em false para o caso de nova verificacao

        if(linha.length() == 0) { //Se a linha estiver em branco, ir para a proxima linha
            LL.insere_numerolin(linhacont,linha); //Como a linha sera apagada no pre processamento, armazenar numero
            continue;
        }
        if (linha.at(0) == ';') {
            LL.insere_numerolin(linhacont,linha); //Como a linha sera apagada no pre processamento, armazenar numero
            continue;
        }
        tam2 = linha.length();
        transform(linha.begin(), linha.end(), linha.begin(), ptr_fun<int, int>(toupper)); //Colocando em maiusculo
        for(i=0;i<tam2;i++) { //Verifica espacos no inicio da linha
            if(linha.at(i) != ' ') {
                k = i;
                break;
            }
        }

//************************************** LEITURA DA LINHA DO ARQUIVO DE ENTRADA **************************************************

            while(i < linha.length()) {
                for(i=k;i<tam2;i++) { //Verifica espacos na linha
                    if(linha.at(i) != ' ') {
                        k = i;
                        break;
                    }
                }
                if(i == tam2 || linha.at(i) == ';') { //Se houver apenas comentarios no final da linha, ir para a proxima
                    break;
                }
                    for(i=k;i<tam2;i++) {//Pega token
                            if(linha.at(i) == ' ') {
                                break;
                            }
                            if(linha.at(i) == ',' && flagcopy == 1){ //COPY
                                linhain += token;
                                linhain += ",";
                                token.clear();
                                i++;
                                if(linha.at(i) == ' '){
                                    LE.insere_erro(5,linhacont);
                                }
                                flagcopy = 2;
                                break;
                            }
                            token += linha.at(i);
                    }
                        k = i;
                        if(flagcopy == 1) {
                            LE.insere_erro(5,linhacont);
                            for(i=k;i<tam2;i++) {
                                if(linha.at(i) == ',') {
                                    token += linha.at(i);
                                    k = i+1;
                                    break;
                                }
                            }
                        flagcopy = 2;
                        }
                        if(flagcopy == 2) {
                            k = i+1;
                            for(i=k;i<tam2;i++) {
                                if(linha.at(i) != ' ') {
                                    for(j=i;j<tam2;j++) {
                                        k = j+1;
                                        token += linha.at(j);
                                    }
                                break;
                                }
                            }
                        }
                        if(token == "COPY") { //Verificando se os operando da instrucao COPY estao da maneira correta
                            flagcopy = 1;
                        }
                        for(j=0;j<token.length();j++) {
                            if(token.at(j) == ':') {
                                if(no.head != NULL)
                                    aux2 = no.busca_no(aux, eh_rotulo);
                                if(eh_rotulo == true) {
                                    linhain += aux2;
                                    linhain += ':';
                                    linhain += ' ';
                                    token.clear();
                                    aux.clear();
                                    flagrotulo = 1;
                                }
                                break;
                            }
                           aux += token.at(j);
                        }
                        aux.clear();
                        aux2.clear();
                        aux = no.busca_no(token,eh_rotulo);
                        if(eh_rotulo == true) {
                            linhain += aux;
                            linhain += ' ';
                            token.clear();
                            aux.clear();
                        } else {
                        pos = token.find('+');
                        posit = pos;
                        if(posit > -1) {
                            aux2 = token.substr(0,pos);
                            aux3 = token.substr(pos+1,string::npos);
                            aux = no.busca_no(aux3,eh_rotulo);
                            if(eh_rotulo == true) {
                                token.clear();
                                token += aux2;
                                token += '+';
                                token += aux;
                            }
                            aux.clear();
                            aux2.clear();
                            aux3.clear();
                        }
                        linhain += token;
                        if(flagcopy == 0 || flagcopy == 1) {
                            linhain += ' ';
                        }
                        token.clear();
                        }
            }

//*******************************************************************************************************************************
        if(flagcopy != 2)
            linhain.erase(linhain.length()-1,1); //Apagando espaço restante no final da linha
        flagcopy = 0;
        pos = linhain.find("BEGIN");
        posit = pos;
        if(posit > -1) {
            out << linhain;
            out << endl;
            continue;
        }
        if(flagIF1 == 1) { //Se achou a diretiva IF e seu operando foi diferente de 0, imprimir linha no arquivo de saida
            out << linhain;
            out << endl;
            linhain.clear();
            flagIF1 = 0;
            flagIF2 = 0;
            continue;
        }
        tam3 = linhain.length();
        k = 0; //Zerando contadores
        i = 0;

//********************************************* ANALISE DA LINHA DE SAIDA ********************************************************

        while(i<linhain.length()) {
                token1.clear();
                token2.clear();
                dir.clear();

        //********************Verificacao da Diretiva SECTION*************************************
                for(i=k;i<tam3;i++) { //Verifica primeiro token (Verificacao da diretiva SECTION)
                    if(linhain.at(i) == ' ') {
                        for(j=k;j<i;j++)
                            token1 += linhain.at(j);
                        k = i+1;
                        break;
                    }
                }
                if(token1 == "SECTION") {  //Verifica segundo token (Verificacao de SECTION TEXT OU SECTION DATA)
                    for(j=i;j<tam3;j++) {
                        token2 += linhain.at(j);
                    }
                    dir = token1 + token2;
                        flagsection = 1; //Se ja se chegou na secao de texto, nao deve-se procurar pela diretiva EQU, apenas por IF.
                        out << dir;
                        out << endl;
                        break;
            //************************** Fim da verificacao da Diretiva SECTION ********************************

            //************************** Verificacao da Diretiva EQU ******************************************
                } else {
                    pos = linhain.find("EQU");
                    posit = pos;
                    if(posit > -1) {
                        k = 0;
                        //if(flagsection == 1)
                            //LE.insere_erro(4, linhacont);
                        for(i=k;i<tam3;i++) {
                            if(linhain.at(i) == ' ')
                                LE.insere_erro(2,linhacont);
                            if(linhain.at(i) == ':') { //Armazenando rotulo, como esperado para a diretiva EQU
                                for(j=0;j<i;j++)
                                    rotulo += linha.at(j);
                                k = i+2;
                                flagrotulo = 1; //Indica que existe rotulo
                                break;
                            }
                        }
                            if (flagrotulo == 0) { //Se nao houver rotulo, nao eh a diretiva EQU
                                LE.insere_erro(7, linhacont);
                            }
                        for(i=k;i<tam3;i++){ //Pegando proximo operando, que deve ser a diretiva EQU
                            if(linhain.at(i) == ' ') {
                                k = i+1;
                                break;
                            }
                            equ += linhain.at(i);
                        }
                        for(i=k;i<tam3;i++) { //Pega numero apos o EQU
                            if(linhain.at(i) == ' ') {
                                 LE.insere_erro(3, linhacont);
                            }
                            valorstr += linhain.at(i);
                        }
                        no.insere_final(rotulo, valorstr); //Criando no na lista de rotulos da diretiva EQU
                        LL.insere_numerolin(linhacont,linha); //Como a linha sera apagada no pre processamento, armazenar numero
                        break;
                    }
            //*********************** Fim da verificacao da diretiva EQU **********************************

                pos = linhain.find("IF"); //Procura diretiva IF, para verificacao
                posit = pos;
                if(posit > -1) {
                    //if(flagsection == 0)
                       // LE.insere_erro(4,linhacont);
                    for(j=pos+3;j<linhain.length();j++) {
                        if(linhain.at(j) == ' ') {
                            LE.insere_erro(3, linhacont);
                        }
                        aux += linhain.at(j);
                    }
                    if(atoi(aux.c_str()) != 0) {
                        flagIF1 = 1;
                    }
                    flagIF2 = 1; //Indica que entrou na diretiva IF, servindo para que nao se imprima a proxima linha
                    LL.insere_numerolin(linhacont,linha); //Como a linha sera apagada no pre processamento, armazenar numero
                    break;
                }
            }
                out << linhain;
                out << endl;
                linhain.clear();
            }
    }
//*******************************************************************************************************************************
no.limpa_lista();
}
//****************************************************** FIM DO PRE PROCESSADOR ***********************************************

//************************************************** INSERCAO NA TABELA DE USO *************************************************
void insere_TU (Simbolo_Tab TS, TU &usot, int post, string tk) {
    Simbolo *simbaux = new Simbolo();
    simbaux = TS.primeiro;
    Simb_TU *tu = new Simb_TU();
    Simb_TU *tuaux = new Simb_TU();
    stringstream conv;
    while(simbaux != NULL) {
        if(simbaux->Retorna_rot() == tk) {
            break;
        }
        simbaux = simbaux->Retorna_proximo_rot();
    }
    if(simbaux->Retorna_ext() == true) {
        conv.str("");
        conv.clear();
        if(usot.symb1 == NULL) {
            tu->Define_symbol(tk);
            conv << post;
            tu->Define_value(conv.str());
            tu->Define_psymb(NULL);
            usot.symb1 = tu;
        } else {
            tu = usot.symb1;
            while(tu->Return_psymb() != NULL) {
               tu = tu->Return_psymb();
            }
            tuaux->Define_symbol(tk);
            conv << post;
            tuaux->Define_value(conv.str());
            tuaux->Define_psymb(NULL);
            tu->Define_psymb(tuaux);
        }
    }
}

//*******************************************************************************************************************************
