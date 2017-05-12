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
        if(tmp->Return_rot() == label) { //Se tiver rotulo == label, retornar valor associado e coloca flag exist em 1
            tmpval = tmp->Return_val();
            *aux = true;
            return tmpval;
            break;
        }
        tmp = tmp->Return_prox_rot();
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

//*********************************************** FIM DA DECLARACAO DE LISTAS **********************************************

int main () {
EQU_List no; //Objeto da lista da diretiva EQU
string str, linha, strtemp;
string token, token1, token2, dir, linhaout, linhain, aux;
string equ, rotulo, valorstr; //strings para abrir arquivo, guardar linhas, verificacoes de linhas e diretivas
int tam1, tam2, tam3, i, j, k, t, cont; //Contadores e variaveis para tamanho de linha
int flag_o = 0, flagrotulo = 0, flagIF1 = 0, flagIF2 = 0, flagsection = 0; //Flag para verificar erros, se existe rotulo, flags para diretiva IF e se o programa esta na ordem correta
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
fstream out ("Saida.txt", ios::out);
fstream in ("Saida.txt", ios::in);

if(out.is_open() && arq.is_open() && in.is_open()) {
    while(true) {
        getline(arq, linha); //Pegando uma linha do arquivo de entrada
        if(flagIF1 == 0 && flagIF2 == 1) { //Se achou a diretiva IF mas seu operando foi zero, ignorar linha
            flagIF2 = 0;
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

        if(arq.eof() || flag_o == 1) { //Se chegou ao fim do arquivo ou gerou um erro, sair do loop
            if(flag_o == 1) {
               cout << "Secao de dados vindo antes da secao de texto" << endl;
               break;
            }
            break;
        }
        if(linha.length() == 0) //Se a linha estiver em branco, ir para a proxima linha
            continue;
        if (linha.at(0) == ';')
            continue;
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
                if(i == tam2 || linha.at(i) == ';') { //Se houver apenas espacos no final da linha, ir para a proxima
                    break;
                }
                    for(i=k;i<tam2;i++) {//Pega token
                            if(linha.at(i) == ' ') {
                                break;
                            }
                            if(linha.at(i) == ','){ //COPY
                                linhain += token;
                                linhain += ",";
                                token.clear();
                                i++;
                            }
                            token += linha.at(i);
                    }
                        linhain += token;
                        linhain += ' ';
                        k = i;
                        token.clear();
            }

//*******************************************************************************************************************************

        linhain.erase(linhain.length()-1,1); //Apagando espaço restante no final da linha
        if(flagIF1 == 1) { //Se achou a diretiva IF mas seu operando foi diferente de 0, imprimir linha no arquivo de saida
            out << linhain;
            out << endl;
            linhain.clear();
            flagIF1 = 0;
            flagIF2 = 0;
            continue;
        }
          //out << linhain; //Gravando linha no arquivo de saida
          //out << endl;
          //linhain.clear();
        //getline(in, linhaout); //Como a linha esta ordenada a analise se torna mais facil
        tam3 = linhain.length();
        k = 0; //Zerando contadores
        i = 0;

//********************************************* ANALISE DA LINHA DE SAIDA ********************************************************

        while(i<linhain.length()) {
            if(flagsection != 1) { //Se ainda nao encontrou a diretiva SECTION TEXT, procurar pela diretiva EQU
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
                    if(dir == "SECTION TEXT") {
                        flagsection = 1; //Se ja se chegou na secao de texto, nao deve-se procurar pela diretiva EQU, apenas por IF.
                        out << dir;
                        out << endl;
                        break;
                    } else if (dir == "SECTION DATA") {
                        flag_o = 1;
                        break;
                    }
            //************************** Fim da verificacao da Diretiva SECTION ********************************

            //************************** Verificacao da Diretiva EQU ******************************************
                } else {
                    k = 0;
                    for(i=k;i<tam3;i++) {
                        if(linhain.at(i) == ':') { //Armazenando rotulo, como esperado para a diretiva EQU
                            for(j=0;j<i;j++)
                                rotulo += linha.at(j);
                            k = i+2;
                            flagrotulo = 1; //Indica que existe rotulo
                            break;
                        }
                    }
                        if (flagrotulo == 0) { //Se nao houver rotulo, nao eh a diretiva EQU, o que configura um erro.
                            flag_o = 1; //Alterar
                            break;
                        }
                    for(i=k;i<tam3;i++){ //Pegando proximo operando, que deve ser a diretiva EQU
                        if(linhain.at(i) == ' ') {
                            k = i+1;
                            break;
                        }
                        equ += linhain.at(i);
                    }
                    if (equ != "EQU") { //Se operando diferente de EQU, terminar execucao
                        flag_o = 4;
                        break;
                    }
                    for(i=k;i<tam3;i++) { //Pega numero apos o EQU
                        if(linhain.at(i) == ' ') {
                            flag_o = 3; //Erro de numero de operandos invalido
                            break;
                        }
                        valorstr += linhain.at(i);
                    }
                    no.insere_final(rotulo, valorstr); //Criando no na lista de rotulos da diretiva EQU
                }
            //*********************** Fim da verificacao da diretiva EQU **********************************

            } else { //Se ja encontrou a SECTION TEXT, procurar pelas diretivas IF, CONST e SPACE (na SECTION DATA tambem)
                pos = linhain.find("IF"); //Procura diretiva IF, para verificacao
                posit = pos;
                if(posit > -1) {
                    for(j=pos+3;j<linhain.length();j++) {
                        if(linhain.at(j) == ' ') { //Verificar se operando eh diferente de zero
                            flag_o = 3; //Indicando erro de numero de operandos invalido
                            break;
                        }
                        aux += linhain.at(j);
                    }
                    valor = no.busca_no(aux, eh_rotulo);
                    if(atoi(valor.c_str()) != 0) //Se IF levar numero, ajustar****
                        flagIF1 = 1;
                    flagIF2 = 1; //Indica que entrou na diretiva IF, servindo para que nao se imprima a proxima linha
                } else {
                    pos = linhain.find("CONST"); //Procura diretiva CONST, para alterar valor do rotulo caso este tenha sido associado a um valor pela diretiva EQU
                    posit = pos;
                    if(posit > -1) {
                        for(j=pos+6;j<linhain.length();j++) { //Pegando operando da diretiva CONST
                              aux += linhain.at(j);
                              if(linhain.at(j) == ' ') {
                                flag_o = 3; //Indicando erro de numero de operandos invalido
                                break;
                              }
                        }
                        valor = no.busca_no(aux,eh_rotulo); //Verificar se operando da diretiva CONST pertence a lista da diretiva EQU
                        if(eh_rotulo == true) {             //Caso pertenca, substitui-lo por seu valor
                            linhain.erase(pos+6,string::npos);
                            linhain += valor;
                        }
                    } else {
                        pos = linhain.find("SPACE"); // Procura diretiva SPACE
                        posit = pos;
                        if(posit > -1) {
                            for(j=pos+6;j<linhain.length();j++) { //Pegando operando da diretiva SPACE
                              aux += linhain.at(j);
                              if(linhain.at(j) == ' ') {
                                flag_o = 3; //Indicando erro de numero de operandos invalido
                                break;
                              }
                            }
                            valor = no.busca_no(aux,eh_rotulo); //Verificar se operando da diretiva SPACE pertence a lista da diretiva EQU
                            if(eh_rotulo == true) {             //Caso pertenca, substitui-lo por seu valor
                            linhain.erase(pos+6,string::npos);
                            linhain += valor;
                            }
                        }
                    }
                        out << linhain;
                        out << endl;
                        linhain.clear();
                    }
                    break;
                }
            }
        }

//*******************************************************************************************************************************
} else {
    cout << "Arquivo nao foi aberto corretamente" << endl;
}
} else {
    cout << "Arquivo nao esta no formato correto" << endl;
}
no.limpa_lista();
return 0;
}
