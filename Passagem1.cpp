#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stdlib.h>
using namespace std;

//**************************************** TABELA DE SIMBOLOS ****************************************************************

class Simbolo {
    string rotulo; //Rotulo da tabela de simbolos
    string valor_rotulo; //Valor associado ao rotulo
    Simbolo *prox_rotulo; //Posicao do proximo rotulo
public:
    no() {};
    void Define_Rotulo1 (string rot1) {rotulo = rot1;} //Define o rotulo de um no
    void Define_Valorrot (string valor_rot1) {valor_rotulo = valor_rot1;} //Define o valor associado a um rotulo
    void Define_proximo_rot (Simbolo *proximo) {prox_rotulo = proximo;} //Define proximo no
    string Retorna_rot() {return rotulo;}
    string Retorna_val() {return valor_rotulo;}
    Simbolo* Retorna_proximo_rot () {return prox_rotulo;}
};

class Simbolo_Tab { //Lista para as definicoes das diretivas EQU
    Simbolo *primeiro;
    public:
        Simbolo_Tab() {
            primeiro = NULL;
        }
        void inseresimb_final (string,string); //Insere no no final da tabela
        string busca_simb (string,bool&); //Busca no na lista a partir do rotulo
        void limpa_tabelasimb();
};

void Simbolo_Tab::inseresimb_final (string rotulo1, string valor1) {
    Simbolo *novo_simb = new Simbolo();
    novo_simb->Define_Rotulo1(rotulo1);
    novo_simb->Define_Valorrot(valor1);
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
            erro1->Define_proxerro(temp->Return_proxerro());
        }
        if(p->Return_proxerro() != NULL) {
            p = p->Return_proxerro();
        } else {
            p->Define_proxerro(novo_erro);
        }
   } while(p->Return_proxerro() != NULL);
   }
}

void lista_erro::imprime_erros() {
    erro *tmpe1 = erro1;
    if(tmpe1 != NULL) {
    do {
        if(tmpe1->Return_flag() == 2) {
            cout << "Linha " << tmpe1->Return_linha() << ": " << "Rotulo invalido" << endl;
        }
        if(tmpe1->Return_flag() == 3) {
            cout << "Linha " << tmpe1->Return_linha() << ": " << "Numero de operandos invalido" << endl;
        }
        if(tmpe1->Return_flag() == 4) {
            cout << "Linha " << tmpe1->Return_linha() << ": " << "Diretiva/Instrucao na secao errada" <<  endl;
        }
        if(tmpe1->Return_flag() == 5) {
            cout << "Linha " << tmpe1->Return_linha() << ": " << "Instrucao invalida" << endl;
        }
        if(tmpe1->Return_flag() == 6) {
            cout << "Linha " << tmpe1->Return_linha() << ": " << "Diretiva invalida" << endl;
        }
            tmpe1=tmpe1->Return_proxerro();
    }while(tmpe1 != NULL);
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
        string busca_instrucao (string,int*); //Busca instrucao na lista
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

string Lista_Instrucoes::busca_instrucao(string name, int *contador_pos, int contador_lin, lista_erro *lerro) {
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
        *contador_pos += tmpval;
        return tmp->Return_opcode();
    } else {
        lerro->insere_erro(5, contador_lin);
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

int main () {
Simbolo_Tab simb;
string nome, nometemp; //strings usadas para abrir o arquivo e verifica extensao
string line;
int t = 0, j = 0, i = 0, k = 0, tam1;
int
int flag1 = 0;

cout << "Digite o nome do arquivo que deseja abrir: ";
getline (cin, nome);
tam1 = nome.length();

for(t=tam1-4,j=0;t<tam1;t++,j++) {
     nometemp += nometemp.at(t);
}
if(nometemp.compare(".pre") == 0 || nometemp.compare(".asm")) { // Verifica se o arquivo esta no formato correto
    ifstream arquivo (nome.c_str());
    fstream saida ("Saida.o", ios::out);

    if(saida.is_open() && arquivo.is_open()) {
        getline(arquivo, line); //Pegando uma linha do arquivo de entrada
        while(true) {
            getline(arquivo, line); //Pegando uma linha do arquivo de entrada
            if(arquivo.eof() || flag1 == 1) {
                if(flag1 == 1) {
                    cout << "Diretiva ou instrucao na secao errada" << endl;
                    break;
                }
                break;
            }
        }
    }
}
}

void Diretivas(string nom, string line, int *cont_pos, int *flagbegin, int *flagend, Simbolo_Tab *tabs, int flagpas, lista_erro *lerr, Def_Tab *defs, int contlinha, string *lin_saida, int *flags) {
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
    */
    int i; //contador
    string auxl;
    size_t posic; //Utilizada na instrucao find
    int num;
    stringstream hexadec, convert; //Usadas para converter hexadecimal para decimal e int para char

        if (nom == "SECTION") {
            posic = line.find("SECTION");

            *flags = 1;
        } else if(nom == "SPACE") {
            posic = line.find("SPACE");
            posic += 6;
            for(i=posic;i<line.length();i++) {
                if(line.at(i) ==  ' ') {
                    lerr->insere_erro(3, contlinha);
                }
                auxl += line.at(i);
            }
            if(auxl.at(0) == '0' && auxl.at(1) == 'X') {
                hexadec << hex << auxl;
                hexadec >> num;
            } else {
                num = atoi(auxl.c_str());
            }
            if(flagpas == 1) { //Se estamos na primeira passagem
                *cont_pos += num;
            } else if(flagpas == 2) { //Se estamos na primeira passagem
                for(i=0;i<num;i++) {
                    *lin_saida += "00";
                    *lin_saida += " ";
                }
            }
        } else if(nom == "CONST") {
            posic = line.find("CONST");
            posic += 6;
            for(i=posic;i<line.length();i++) {
                if(line.at(i) ==  ' ') {
                    lerr->insere_erro(3, contlinha);
                }
                auxl += line.at(i);
            }
            if(auxl.at(0) == '0' && auxl.at(1) == 'X') {
                hexadec << hex << auxl;
                hexadec >> num;
            } else {
                num = atoi(auxl.c_str());
            }
            auxl.clear();
            if (flagpas == 1) { //Se estamos na primeira passagem
                *cont_pos += 1;
            } else if (flagpas == 2) { //Se estamos na segunda passagem
                convert << num;
                auxl = convert.str();
                *lin_saida += auxl;
                *lin_saida += " ";
            }
        } else if (nom == "PUBLIC") {
            if(flagpas == 1) {
            posic = line.find("PUBLIC");
            posic += 7;
            for(i=posic;i<line.length();i++) {
                if(line.at(i) ==  ' ') {
                    lerr->insere_erro(3, contlinha);
                }
                auxl += line.at(i);
            }
            defs->inseredef_final(auxl, 0);
            }
       /* } else if (nom == "EXTERN") {
            if(flagpas == 2) {
                posic = line.find("EXTERN");
                posic += 7;
                for(i=posic;i<line.length();i++) {
                    if(line.at(i) ==  ' ') {
                        lerr->insere_erro(3, contlinha);
                    }
                    auxl += line.at(i);
                }
                insere_TU(auxl,*cont_pos)
            }
        }*/
        //So na segunda passagem
         else if (nom == BEGIN){
            *flagbegin = 1;
         } else if (nom == END) {
            *flagend = 1;
         } else {
            lerr.insere_erro(6,contlinha);
         }
    hexadec.str("");
    convert.str("");
    auxl.clear();
}

