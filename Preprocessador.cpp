#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;

int main () {
string str, linha, dir, token1, token2, equ, rotulo, valorstr; //strings para abrir arquivo, guardar linhas, verificacoes de linhas e diretivas
stringstream valor;
int tamanho, i, j, k, equrotulo;
int flag = 0, flagrotulo = 0; //Flag para verificar se o programa esta na ordem correta

cout << "Digite o nome do arquivo que deseja abrir: ";
getline (cin, str);

ifstream prog (str.c_str());
ofstream saida ("Preproc.txt");

if (prog.is_open() && saida.is_open()) {
    while(true) {
        getline(prog, linha);
        equ.clear();
        k = 0; //Inicializando contador auxiliar k com 0
        if(prog.eof() || flag == 1) { //Se chegou ao fim do arquivo, sair do loop
            if(flag == 1) {
               cout << "Programa nao esta na ordem correta." << endl;
               break;
            }
        break;
        }
        tamanho = linha.length(); //Pegando tamanho da linha
        transform(linha.begin(), linha.end(), linha.begin(), ptr_fun<int, int>(toupper)); //Colocando em maiusculo
/* Essa parte serve para verificar se teremos ou nao a diretiva EQU,
verificando primeiramente se o conteudo da linha eh igual a SECTION
TEXT, o que indicara que se trata de secao de texto.
    Alem disso, se nao se tratar nem da diretiva EQU nem da secao de
texto, o programa sera interrompido*/
        if(flag != 2) {
            for(i=0;i<tamanho;i++) { //Verifica espacos no inicio da linha
                if(linha.at(i) != ' ') {
                    k = i;
                    break;
                }
            }
            for(i=k;i<tamanho;i++) { //Verifica primeiro token (Verificacao da diretiva SECTION)
                if(linha.at(i) == ' ') {
                    for(j=k;j<i;j++)
                        token1 += linha.at(j);
                    k = i;
                    break;
                }
            }
            for(i=k;i<tamanho;i++) { //Verifica segindo token (Verificacao de SECTION TEXT OU SECTION DATA)
                if(linha.at(i) != ' ') {
                    for(j=i-1;j<tamanho;j++) {
                        if(linha.at(j) == ' ' && j>(i-1))
                            break;
                        token2 += linha.at(j);
                    }
                    break;
                }
            }
            dir = token1 + token2; //Armazenando diretiva na string dir
            if(dir == "SECTION TEXT") {
                flag = 2; //Se ja se chegou na secao de texto, nao deve-se procurar pela diretiva EQU, apenas por IF.
                break;
            } else if (dir == "SECTION DATA") {
                flag = 1;
                break;
            } else {
                k = 0;
                for(i=k;i<tamanho;i++) {
                    if(linha.at(i) == ':') { //Armazenando rotulo, como esperado para a diretiva EQU
                        for(j=0;j<i;j++)
                            rotulo += linha.at(j);
                        k = i+1;
                        flagrotulo = 1; //Indica que existe rotulo
                        break;
                    }  else if (flagrotulo == 0 && i == tamanho-1) { //Se nao houver rotulo, nao eh a diretiva EQU, o que configura um erro.
                        flag = 1;
                        break;
                    }
                }
                for(i=k;i<tamanho;i++){
                    if(linha.at(i) != ' ') { //Armazenando o proximo token, que deve ser a diretiva EQU
                        for(j=i;j<tamanho;j++) {
                            if(linha.at(j) == ' ') {
                                k = j;
                                break;
                            }
                            equ += linha.at(j);
                        }
                    break;
                    }
                }
                if (equ != "EQU") { //Se operando diferente de EQU, terminar execucao
                    flag = 1;
                    break;
                }
                for(i=k;i<tamanho;i++) {
                    if(linha.at(i) != ' ') { //Pega numero apos o equ e transforma em inteiro
                        for(j=i;j<tamanho;j++) {
                             valorstr += linha.at(j);
                        }
                        valor.str(valorstr);
                        break;
                    }
                }
                valor >> equrotulo;
                cout << "O rotulo " << rotulo << " eh igual a " << equrotulo;
            }
        }
    }
}
return 0;
}
