//Esse codigo le linhas, descartando comentarios e espaços, separando rotulos, instrucoes e operandos.
//Isso so eh feito se o arquivo tiver a extensao .asm ou .pre

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main () {
string str, linha, strtemp;
char *rotulo, *token;
int tam1, tam2, i, j, k, t;

cout << "Digite o nome do arquivo que deseja abrir: ";
getline (cin, str);
tam1 = str.length();

for(i=tam1-4,j=0;i<tam1;i++,j++) {
     strtemp += str.at(i);
}
cout << strtemp << endl;
if(strtemp.compare(".asm") == 0 || strtemp.compare(".pre") == 0) { // Verifica se o arquivo esta no formato correto
ifstream arq (str.c_str());
ofstream out ("Saida.txt");

if(out.is_open() && arq.is_open()) {
    while(true) {
        getline(arq, linha); //Pegando uma linha do arquivo de entrada
        if(arq.eof())
            break;
        if (linha.at(0) == ';')
            continue;
        tam2 = linha.length();
        transform(linha.begin(), linha.end(), linha.begin(), ptr_fun<int, int>(toupper)); //Colocando em maiusculo
        for(i=0;i<tam2;i++) { //Verifica espacos no inicio da linha
            if(linha.at(i) != ' ') {
                k = i;
                break;
            } else {
                continue;
            }
        }
        if(linha.at(k) != '0' && linha.at(k) != '1' && linha.at(k) != '2' && linha.at(k) != '3' && linha.at(k) != '4' && linha.at(k) != '5' && linha.at(k) != '6' && linha.at(k) != '7' && linha.at(k) != '8' && linha.at(k) != '9') {
        //Verificando se o token nao comeca com numero
            rotulo = new char [(i+1)-k];
            for(i=k;i<tam2;i++) { //Pegando rotulo, se houver, e gravando no arquivo de saida
                if(linha.at(i) == ':') { // Se chegou ao caracter :, imprime rotulo no arquivo de saida
                    for(j=k,t=0;j<i;j++,t++)
                        rotulo[t] = linha.at(j);
                    rotulo[i] = '\0';
                    out << rotulo;
                    out << ' ';
                    k = i+1;
                    break;
                }
                if(i == (linha.length() - 1)) { //Se nao existe rotulo
                    i = k; //Contador volta para o inicio do token
                    break;
                }
            }
        }
        while(i < (linha.length()-1)) { //Enquanto nao esta no fim da linha, deve-se pegar tokens
            for(i=k;i<tam2;i++) { //Verifica espacos
                if(linha.at(i) != ' ') {
                    k = i;
                    break;
                }
            }
                if(linha.at(i) == ';')
                    break;
            if(linha.at(k) != '0' && linha.at(k) != '1' && linha.at(k) != '2' && linha.at(k) != '3' && linha.at(k) != '4' && linha.at(k) != '5' && linha.at(k) != '6' && linha.at(k) != '7' && linha.at(k) != '8' && linha.at(k) != '9') {
            //Verificando se o token nao comeca com numero
                for(i=k;i<tam2;i++) { //Pegando token e gravando no arquivo de saida
                    if(linha.at(i) == ' ' || i == (tam2 - 1)) { //Se chegar a um espaço ou ao fim da linha, imprime token no arquivo de saida
                        token = new char [(i+1)-k];
                        if (i == (tam2 - 1)) { //Se eh o ultimo token da linha, linha.at(i) == caracter
                            for(j=k,t=0;j<=i;j++,t++)
                                token[t] = linha.at(j);
                        } else { //Se nao eh o ultimo token da linha, linha.at(i) == ' ' (Exceto pelo copy)
                            for(j=k,t=0;j<i;j++,t++) {
                                token[t] = linha.at(j);
                            }
                            token[i] = '\0';
                        }
                        out << token;
                        out << ' ';
                        k = i;
                        break;
                    }
                }
            }
        }
    }
    delete[] rotulo;
    delete[] token;
} else {
    cout << "Arquivo nao foi aberto corretamente" << endl;
}
} else {
    cout << "Arquivo nao esta no formato correto" << endl;
}
return 0;
}
