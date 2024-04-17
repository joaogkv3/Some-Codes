
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

int main() {
    int passa_valor, numero = 0;    // Variável numero é para armazenar o número lido
    int linha = 1;  
    int direcao = 1;// 0=cima 1=direita 2=baixo 3=esquerda (direção que ele está indo)
    int y_max, x_max = 0; //x e y que são dados para nos no começo 
    int x, y, op = 0; // op = numero de operacoes

    char symbol; // Variável para armazenar o caractere lido

    bool startProcessing = false; 

    stringstream salva_valor; // quarda um valor pra acumilar até encontrar um simbolo

    // Nome do arquivo a ser lido
    string filename = "symbols.txt";

    // Abrindo o arquivo para leitura
    ifstream file(filename);

    // Verificando se o arquivo foi aberto com sucesso
    if (!file.is_open()) {
        cout << "Erro ao abrir o arquivo " << filename << endl;
        return 1;
    }
    
    // Definindo as dimensões da matriz
    string line;
    if (getline(file, line)) {
        stringstream ss(line);
        ss >> y_max >> x_max;
    } else {  // se não tem nada pra ler
        cout << "Erro: Arquivo vazio ou sem linhas." << endl;
        return 1;
    }
    
    // Matriz para armazenar os símbolos
    vector<vector<char>> matrix(y_max, vector<char>(x_max, ' ')); // Inicializa todos os lugares com ' '

    // Lendo e preenchendo a matriz
    while (getline(file, line)) {
        x = 0;
        if (line.find_first_not_of(" \t\r\n") != string::npos) { // Checa se há caracteres além de espaços
            for (char &symbol : line) {                          //para todos os caracteres na linha
                if (x < x_max) {                                 //enquanto ele é menos que o max
                    matrix[y][x++] = symbol;             //bota o caractere no espaço dele e aumenta x em 1
                }
            }
            y++;
        }
    }

    // Fechando o arquivo
    file.close();
    
    x = 0;
    y = 0;

    //procurando o inicio (o simbolo "-" no inicio de uma linha)
    while(1){
        symbol = matrix[y][x];
      if (symbol == '-'){      //se achar "-", e quebra o while
          break;
        }
      y++;
    }
    
    while (1) {
        op++;   //almenta o numero de operacoes

        symbol = matrix[y][x];

        if (symbol >= '0' && symbol <= '9') {
            // Se o caractere for um dígito, acumular como parte de um número
            salva_valor << symbol;
        } else {
            // Se não for um dígito, extrair o número acumulado
            if (!(salva_valor.str().empty())) {
                salva_valor >> passa_valor; 
                numero = numero + passa_valor; // passa o valor, mais o valor anterior

                salva_valor.str("");
                salva_valor.clear(); // Limpar o stringstream
            }
        }
        
        //troca de direção se for "\"
        if(symbol == '\\'){
        switch(direcao){
                case 0:     
                direcao = 3;
                break;
                case 1:
                direcao = 2;
                break;
                case 2:
                direcao = 1;
                break;
                case 3:
                direcao = 0;
                break;
                default:
                break;
            }
        }
        //troca de direção de for "/"
        if(symbol == '/'){
        switch(direcao){
                case 0:
                direcao = 1;
                break;
                case 1:
                direcao = 0;
                break;
                case 2:
                direcao = 3;
                break;
                case 3:
                direcao = 2;
                break;
                default:
                break;
            }
        }
        //se chegar no "#", termina o while
        if (symbol == '#') {
            break;
        }
        
        //vai pra cima, baixo, direita ou esquerda dependendo da direção
        switch(direcao){
            case 0:
            --y;
            break;
            case 1:
            ++x;
            break;
            case 2:
            ++y;
            break;
            case 3:
            --x;
            break;
            default:
            break;
        }
    }
    
    //imprime o resultado final
    cout << "total de dinheiro recolhido: "<< numero << endl;
    cout << "numero de operacoes: " << op << endl; 

    return 0;
}
