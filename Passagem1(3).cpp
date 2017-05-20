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
    erro *erro1;
    public:
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
            cout << "Linha "<< tmpe1->Return_linha() << ": " << "Diretiva SPACE nao pode ter operando 0" << endl;
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
    public:
        Definicao *def1;
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
    while(nov != NULL) {
    cout << nov->Retorna_def() << " = " << nov->Retorna_valdef() << endl;
    nov = nov->Retorna_prox_def();
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
    bool ehconst(string,int&);
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
bool Dados::ehconst(string rnm1, int &vc1) {
    Rotulo *new_rn = rn1;
    Rotulo *tp;
    while(new_rn != NULL) {
        if(new_rn->Return_rname() == rnm1) {
            vc1 = new_rn->Return_valconst();
            return new_rn->Return_const();
        }
        new_rn = new_rn->Return_proxrn();
    }
}
int Dados::space(string rnm2) {
    Rotulo *new_rn1 = rn1;
    Rotulo *tp;
    while(new_rn1 != NULL) {
        if(new_rn1->Return_rname() == rnm2) {
            return new_rn1->Return_space();
        }
        new_rn1 = new_rn1->Return_proxrn();
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
//************************************** Prototipo **************************************************************
void Diretivas(string, Dados&, string, string, int&, int&, int&, Simbolo_Tab&, int, lista_erro&, Def_Tab&, int, string&, int&, bool&, int);
void cria_LI(Lista_Instrucoes&);
void simb_to_def (Simbolo_Tab,Def_Tab&);
//***************************************************************************************************************
int main () {
Simbolo_Tab simb;
lista_erro errolist;
Def_Tab defin;
Lista_Instrucoes inst;
cria_LI(inst);
lista_linhas linls;
Dados data;
string nome, nometemp; //strings usadas para abrir o arquivo e verifica extensao
string line, outline; //strings utilizadas para as linhas
string straux1, straux2, opcode, token1, rotulo;
stringstream conversao;
int t = 0, j = 0, i = 0, k = 0, tam1, aux;
int pos_cont = 0, pos_contaux = 0, lin_cont = 0; //Contadores de posicao (Para verificacoes de instrucoes e contador de linha)
int flagsec = 0, fbegin = 0, fend = 0, flagp = 1, flagel = 0, flages = 0, flaginst = 0, flagrot = 0, flagaux1 = 0, flagaux2 = 0, flagaux3 = 0, flagpos = 0, flagstop = 0;
/*
flagsec - flag para verificacao da diretiva SECTION
fbegin - flag para verificacao da diretiva BEGIN
fend - flag para verificacao da diretiva END
flagp - flag para verificacao da passagem (primeira ou segunda)
flagel - flag para erro lexico
flages - flag para erro sintatico
flageinst - flag para indicar que eh instrucao
flagrot - flag que indica a existencia de um rotulo
flagaux1,flagaux2 e flagaux3 - flags auxiliares
flagpos - flag para o contador de posicao
flagstop - flag para a diretiva STOP
*/
bool eh_diretiva, eh_simb, constante, pbc; //Variavel para verificar se eh diretiva, variavel para verificar se eh simbolo e variavel para verificar se eh constante
int valor_const; //Variavel para verificar o valor de um operando constante

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
         /*Aqui espera-se que a primeira linha seja a diretiva SECTION TEXT ou BEGIN. Se for BEGIN,
           procurar por SECTION TEXT. Em ambos os casos deve-se verificar se esta ultima existe.Se
           existir, gerar erros para todas as linhas anteriores.Caso contrario, gerar erro de Secao
            de texto faltante. Alem disso, faz-se as analises lexica, sintatica e semantica para cada
            linha */
        while(getline(arquivo,line)) {
            lin_cont++; //Incrementando contador de linha
            if(linls.primeiralinha != NULL)
                linls.busca_listalinhas(lin_cont,linls);
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
                if(token1 != "PUBLIC" && token1 != "SPACE") {
                Diretivas(rotulo, data, token1, line, pos_cont, fbegin, fend, simb, flagp, errolist, defin, lin_cont, outline, flagsec, eh_diretiva, flagaux2);

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
                                for(t=i+1;t<line.length();t++) {
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
                                Diretivas(rotulo, data, token1, line, pos_cont, fbegin, fend, simb, flagp, errolist, defin, lin_cont, outline, flagsec, eh_diretiva, flagaux2);
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
                linls.busca_listalinhas(lin_cont,linls);
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
                        if(token1 != "SECTION" && flagpos == 1)                      //verifica-se se eh um token valido
                            pos_cont++;
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

            flagpos = 1;
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
                if(token1 != "PUBLIC" && token1 != "SPACE") {
                    Diretivas(rotulo, data, token1, line, pos_cont, fbegin, fend, simb, flagp, errolist, defin, lin_cont, outline, flagsec, eh_diretiva, flagaux2);

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
                                pos_cont++;
                                conversao << pos_cont; //Convertendo contador de int para string
                                for(t=i+1;t<line.length();t++) {
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
                                pos_cont--;
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
                            if(token1 != "BEGIN" && token1 != "PUBLIC" && token1 != "EXTERN" && token1 != "END")
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
                                Diretivas(rotulo, data, token1, line, pos_cont, fbegin, fend, simb, flagp, errolist, defin, lin_cont, outline, flagsec, eh_diretiva, flagaux2);
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
simb.imprime_simb(); //*
cout << endl; //*
defin.imprime_def(); //*
errolist.imprime_erros();//*
errolist.limpa_listae(); //So para testes*
simb.limpa_tabelasimb(); //*
defin.limpa_tabeladef(); //*
inst.limpa_lista_inst();//*
data.limpa_dados();//*
return 0;
       }
    }
}

void Diretivas(string rot, Dados &D, string nom, string line, int &cont_pos, int &flagbegin, int &flagend, Simbolo_Tab &tabs, int flagpas, lista_erro &lerr, Def_Tab &defs, int contlinha, string &lin_saida, int &flags, bool &diretiva_verif, int flaga) {
    /*
    Argumentos:
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
    int num;
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
            hexadec << hex << auxl;
            hexadec >> num;
            if(atoi(auxl.c_str()) != 0 || num != 0) {
            for(i=i1;i<line.length();i++){
                if(line.at(i) != ' ') {
                    break;
                }
            }
            if(i >= line.length()-1) { //SPACE tem um operando ou nenhum operando
            if(auxl.length() > 0) {
                if(auxl.find("X") > -1) {
                    hexadec << hex << auxl;
                    hexadec >> num;
                } else {
                    num = atoi(auxl.c_str());
                }
            } else {
                num = 1;
            }
            if(flagpas == 1) { //Se estamos na primeira passagem
                cont_pos += num;
            } else if(flagpas == 2) { //Se estamos na primeira passagem
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
            } else {
                lerr.insere_erro(14,contlinha);
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
            if(auxl.find("X") > -1) {
                if(auxl.at(0) == '0') {
                    for(i=2;i<4;i++) {
                        auxl2 += auxl.at(i);
                    }
                    hexadec << hex << auxl2;
                    hexadec >> num;

                } else if(auxl.at(0) == '-') {
                    auxl2 += '-';
                    for(i=3;i<5;i++) {
                        auxl2 += auxl.at(i);
                    }
                    hexadec << hex << auxl2;
                    hexadec >> num;
                }
            }
            }
            num = atoi(auxl.c_str());
            auxl.clear();
            auxl2.clear();
            if (flagpas == 1) { //Se estamos na primeira passagem
                cont_pos += 1;
            } else if (flagpas == 2) { //Se estamos na segunda passagem
                convert << num;
                auxl = convert.str();
                lin_saida += auxl;
                lin_saida += " ";
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
            //tabs.altera_simb(stringaux);
       /* } else if (nom == "EXTERN") {
            if(flagpas == 2) {
                posic = line.find("EXTERN");
                posic += 7;
                for(i=posic;i<line.length();i++) {
                    if(line.at(i) ==  ' ') {
                        lerr.insere_erro(3, contlinha);
                    }
                    auxl += line.at(i);
                }
                insere_TU(auxl,cont_pos)
            }
            diretiva_verif = true;
        }*/
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

void simb_to_def (Simbolo_Tab s,Def_Tab &d) { //Passa simbolos da TS para a TD
    Simbolo *sb = new Simbolo();
    sb = s.primeiro;
    while(sb != NULL) {
        d.mod_def(sb->Retorna_rot(), sb->Retorna_val());
        sb = sb->Retorna_proximo_rot();
    }
}
