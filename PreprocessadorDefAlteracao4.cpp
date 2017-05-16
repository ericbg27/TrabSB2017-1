#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stdlib.h>

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
    no *head;
    public:
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
    do {
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
            cout << "Linha " << tmpe1->Return_linha() << ": " << "Instrucao invalida" << endl;
        }
        if(tmpe1->Return_flag() == 6) {
            cout << "Linha " << tmpe1->Return_linha() << ": " << "Diretiva invalida" << endl;
        }
        if(tmpe1->Return_flag() == 7) {
            cout << "Linha " << tmpe1->Return_linha() << ": " << "Declaracao ausente" << endl;
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

//*********************************************** LISTA DE LINHAS APAGADAS ************************************************
//Serve para que se possa printar o valor da linha certo caso haja um erro
//Usar a da passagem1.cpp
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
    numerolinha *primeiralinha;
    public:
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
    while(new_linha != NULL) {
        if(lcont < new_linha->Return_linum()) {
            ll.insere_numerolin(lcont);
            break;
        }
        tp = new_linha;
        new_linha = new_linha->Return_proxlin();
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

//*********************************************** FIM DA DECLARACAO DE LISTAS **********************************************

int main () {
EQU_List no; //Objeto da lista da diretiva EQU
lista_erro err;
lista_linhas linelist;
string str, linha, strtemp;
string token, token1, token2, dir, linhaout, linhain, aux;
string equ, rotulo, valorstr; //strings para abrir arquivo, guardar linhas, verificacoes de linhas e diretivas
int tam1, tam2, tam3, i, j, k, t, cont, erro_count = 0, linhacont = 0; //Contadores e variaveis para tamanho de linha
int flagrotulo = 0, flagIF1 = 0, flagIF2 = 0, flagsection = 0, flagcopy = 0; //Flag para verificar erros, se existe rotulo, flags para diretiva IF, flag para verificar se o programa esta na ordem correta e flag para instrucao COPY
int *flag;
bool eh_rotulo = false; //Variavel para definir se pertence a lista da diretiva EQU
string valor; //Variavel para valor associado ao rotulo na lista da diretiva EQU
int posit = 0; //Inteiro para pegar posicao das diretivas IF, CONST e SPACE
size_t pos; //Necessario para funcao str.find()

cout << "Digite o nome do arquivo que deseja abrir: ";
getline (cin, str);
tam1 = str.length();

for(t=tam1-4,j=0;t<tam1;t++,j++) {
     strtemp += str.at(t);
}
if(strtemp.compare(".asm") == 0 || strtemp.compare(".pre") == 0) { // Verifica se o arquivo esta no formato correto
ifstream arq (str.c_str());
fstream out ("Preproc.pre", ios::out);

if(out.is_open() && arq.is_open()) {
    while(getline(arq,linha)) {
        linhacont++; //Incrementa contador de linha
        if(flagIF1 == 0 && flagIF2 == 1) { //Se achou a diretiva IF mas seu operando foi zero, ignorar linha
            flagIF2 = 0;
            linelist.insere_numerolin(linhacont); //Como a linha sera apagada no pre processamento, armazenar numero
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
            linelist.insere_numerolin(linhacont); //Como a linha sera apagada no pre processamento, armazenar numero
            continue;
        }
        if (linha.at(0) == ';') {
            linelist.insere_numerolin(linhacont); //Como a linha sera apagada no pre processamento, armazenar numero
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
                                flagcopy = 2;
                            }
                            token += linha.at(i);
                    }
                        k = i;
                        if(flagcopy == 1) {
                            err.insere_erro(5,linhacont);
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
                        aux = no.busca_no(token,eh_rotulo);
                        if(eh_rotulo == true) {
                            linhain += aux;
                            linhain += ' ';
                            token.clear();
                            aux.clear();
                        } else {
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
            cout << linhain << endl;
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
                cout << linhain << endl;
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
                            //err.insere_erro(4, linhacont);
                        for(i=k;i<tam3;i++) {
                            if(linhain.at(i) == ' ')
                                err.insere_erro(2,linhacont);
                            if(linhain.at(i) == ':') { //Armazenando rotulo, como esperado para a diretiva EQU
                                for(j=0;j<i;j++)
                                    rotulo += linha.at(j);
                                k = i+2;
                                flagrotulo = 1; //Indica que existe rotulo
                                break;
                            }
                        }
                            if (flagrotulo == 0) { //Se nao houver rotulo, nao eh a diretiva EQU
                                err.insere_erro(7, linhacont);
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
                                 err.insere_erro(3, linhacont);
                            }
                            valorstr += linhain.at(i);
                        }
                        no.insere_final(rotulo, valorstr); //Criando no na lista de rotulos da diretiva EQU
                        linelist.insere_numerolin(linhacont); //Como a linha sera apagada no pre processamento, armazenar numero
                        break;
                    }
            //*********************** Fim da verificacao da diretiva EQU **********************************

                pos = linhain.find("IF"); //Procura diretiva IF, para verificacao
                posit = pos;
                if(posit > -1) {
                    //if(flagsection == 0)
                       // err.insere_erro(4,linhacont);
                    for(j=pos+3;j<linhain.length();j++) {
                        if(linhain.at(j) == ' ') {
                            err.insere_erro(3, linhacont);
                        }
                        aux += linhain.at(j);
                    }
                    if(atoi(aux.c_str()) != 0) {
                        flagIF1 = 1;
                    }
                    flagIF2 = 1; //Indica que entrou na diretiva IF, servindo para que nao se imprima a proxima linha
                    linelist.insere_numerolin(linhacont); //Como a linha sera apagada no pre processamento, armazenar numero
                    break;
                }
            }
                out << linhain;
                out << endl;
                linhain.clear();
            }
    }
//*******************************************************************************************************************************
} else {
    cout << "Arquivo nao foi aberto corretamente" << endl;
}
} else {
    cout << "Arquivo nao esta no formato correto" << endl;
}
err.imprime_erros();
no.limpa_lista();
err.limpa_listae();
linelist.limpa_listalin();
return 0;
}
