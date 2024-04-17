#include <iostream> //inclui aqui diversas bibliotecas pois ao longo do codigo faço uso de várias funções da biblioteca de c++
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <random>
#include <limits>
#include <map>
#include <iomanip>


using namespace std; //espaço de nomes 

class Sorteio { // crio uma classe chamada sorteio para ter as informações do sorteio em si

    private:

       static const int MAX_NUMERO = 50; // declaro uma variavel constante que diz que meu numero maximo sera 50, quando se trata de sorteios
   
    public:

        vector<vector<int>> sorteiosRealizados; //crio um vetor de vetor de inteiros para armazenar os sorteios que ja foram realizados

        static const int NUMEROS_POR_SORTEIO = 5; // declaro uma variavel constante que diz que serão sorteados 5 numeros por sorteio

        const vector<vector<int>>& getSorteiosRealizados() const { //método que retorna os sorteios realizados
        
          return sorteiosRealizados;
        
        }

        Sorteio() { sorteiosRealizados.reserve(MAX_NUMERO); } //construtor da classe sorteio que reserva espaço para os sorteios realizados


        bool realizarSorteio() { //método que realiza o sorteio

         if (sorteiosRealizados.size() >= MAX_NUMERO) { // Verifica se o limite de sorteios foi atingido
            return false; // Não realiza mais sorteios se atingir o limite

          }

         vector<int> numerosSorteados; //vetor que abriga os numeros sorteados
         vector<int> possiveisNumeros(50); //vetor que abriga os possiveis numeros que podem ser sorteados
         iota(begin(possiveisNumeros), end(possiveisNumeros), 1); // Preenche o vetor com os números de 1 a 50, isso nos numeros que podem ser sorteados
        
         unsigned seed = chrono::system_clock::now().time_since_epoch().count(); // "Semente" para gerar números aleatórios, é uma função para randomização da linguagem c++
         shuffle(begin(possiveisNumeros), end(possiveisNumeros), default_random_engine(seed)); // Embaralha os números possíveis, para assegurar que o sorteado sera um numero aleatorio

    
         copy_n(possiveisNumeros.begin(), NUMEROS_POR_SORTEIO, back_inserter(numerosSorteados)); // Copia os primeiros 5 números sorteados para o vetor de números sorteados, novamente uso uma função de c++, chamada copy_n, que copia os primeiros 5 numeros sorteados para o vetor de numeros sorteados
        
        
         sorteiosRealizados.push_back(numerosSorteados); // Adiciona os números sorteados ao vetor de sorteios realizados, assim posso ir mantendo controle dos sorteios que ja froam realizados

         return true;

        }

    
    
        vector<int> getNumerosSorteados() const { //método que retorna os numeros sorteados
         if (!sorteiosRealizados.empty()) { // Verifica se há sorteios realizados
            return sorteiosRealizados.back(); // Retorna o último sorteio realizado
         }
         return vector<int>(); // Retorna um vetor vazio se nenhum sorteio foi realizado ainda
        }

};

class Aposta{ //crio uma classe chamada aposta para ter as informações do ato da aposta em si

    private:
    
       static int proximoId; // declaro essa variavel para poder futuramente estipular a regra que diz que o proximo id sera o id atual + 1, começando em 1000
       int id; // declaro o id da aposta, digo, a variavel que ira armazenar o id da aposta
       vector<int> numerosEscolhidos;//crio um vetor que abriga os numeros escolhidos pelo usuario
       bool surpresinha; // declaro um booleano que diz se a aposta foi feita de forma aleatoria ou manual

    public:
       static const int NUMEROS_POR_SORTEIO = 5; // 
       static const int MAX_NUMERO = 50; // Fix: Change the access specifier of MAX_NUMERO from private to public
        

       Aposta(const vector<int>& numeros, bool surpresinha = false) :  id(proximoId++), numerosEscolhidos(numeros), surpresinha(surpresinha){}//construtor da classe que recebe um vetor de numeros e o atribui ao vetor numerosEscolhidos//atribui o id da aposta

       const vector<int>& getNumerosEscolhidos() const{ //método que retorna os numeros escolhidos pelo meu usuario

         return numerosEscolhidos;

       }   

       bool isSurpresinha() const { //método que retorna se a aposta foi feita de forma aleatoria ou manual

        return surpresinha;

       }

        
       int getId() const{ //método que retorna o id da aposta

            return id;

        }

        static bool validarNumeros(const vector<int>& numeros) {

            if (numeros.size() != NUMEROS_POR_SORTEIO) return false; // Verifica se a quantidade de números é a esperada
            
            // Verifica se todos os números estão dentro do intervalo permitido
            for (int numero : numeros) {
                if (numero < 1 || numero > MAX_NUMERO) return false; 
            }
            return true;
        }


};

      int Aposta::proximoId = 1000; //inicializa o id da aposta como 1000

class Apostador{ //pensei em criar uma classe que abriga a pessoa que irá apostar, com seus atributos e métodos, para que fique algo organizado.

    private:
    
       string cpf; // atributo que ira armazenar o cpf do apostador
  
    public: 

       string nome; // nome do apostador, tive por no public para que pudessse ser acessada mais tarde
       vector <Aposta> apostasRealizadas; //vetor que abriga as apostas realizadas pelo apostador

 

      Apostador(std::string n, std::vector<Aposta> a) : nome(n), apostasRealizadas(a) {} //construtor da classe apostador que recebe o nome e as apostas realizadas

      void apostaManual (const vector<int>& numeros){ //método que realiza a aposta manual caso essa seja a escolha do apostador.
  
        apostasRealizadas.push_back(Aposta(numeros)); //adiciona a aposta realizada no vetor de apostas realizadas

     } 

      void apostaSurpresinha(){ //crio um metodo que faz a aposta aleatoria se o usuario decidir assim

        vector<int> numeros; //um vetor que abriga os numeros escolhidos

        for (int i=0; i<5; i++){ //laço de repetição simples que gera 5 numeros aleatorios
       
            int numero = rand() % 50 + 1; //gera um numero aleatorio entre 1 e 50
            numeros.push_back(numero);// adiciona o numero gerado no vetor

        }

    apostasRealizadas.push_back(Aposta(numeros)); // adiciona a aposta realizada no meu vector de apostas realizadas

}

    const vector<Aposta>& getApostasRealizadas() const{ //método que retorna as apostas realizadas até o momento
    return apostasRealizadas;
}

string getNome() const { //método que retorna o nome do apostador
    return nome;
}

};

class GerenciadorDeApostas { //crio uma classe que ira gerenciar as apostas, com seus atributos e métodos, para que fique algo organizado... essa classe, dee ceerto modo, é a mais importante do meu programa, pois é ela que ira gerenciar as apostas, os sorteios e os apostadores.

    private: 

    vector<Apostador> apostadores; // Armazena os apostadores
    Sorteio sorteio; // Objeto sorteio para gerenciar sorteios
    bool faseDeSorteio = false; // Controla se a fase de sorteio está ativa, pois se ela estiver, nao se pode apostar

    public:

     void iniciarFaseDeSorteio() { //método que inicia a fase de sorteio

    faseDeSorteio = true;

    for (int i = 0; i < 25 && faseDeSorteio; ++i) { // Realiza até 25 sorteios ou até que haja um vencedor

        if (!sorteio.realizarSorteio()) { // Realiza um sorteio
            cout << "Não foi possível realizar o sorteio." << endl; // Exibe uma mensagem de erro caso necessário
            break;
        }

        const auto& numerosSorteados = sorteio.getSorteiosRealizados().back(); // Obtém os números sorteados
       
        cout << "Números sorteados: "; // Exibe os números sorteados até entao

        for (int num : numerosSorteados) { // Exibe os números sorteados

            cout << num << " ";

        }
        cout << endl;

        vector<string> vencedores; // Vetor para armazenar os nomes dos vencedores e seus dados, caso hajam vencedores


        for (auto& apostador : apostadores) { // Verifica se algum apostador acertou todos os números sorteados

            for (auto& aposta : apostador.getApostasRealizadas()) { // Verifica cada aposta do apostador

                int acertos = contarAcertos(aposta.getNumerosEscolhidos(), numerosSorteados); // Conta os acertos da aposta

                if (acertos == Aposta::NUMEROS_POR_SORTEIO) { // Se acertou todos os números
                    vencedores.push_back(apostador.getNome() + (aposta.isSurpresinha() ? " (Surpresinha)" : "")); // Adiciona o nome do vencedor ao vetor de vencedores
                    
                    faseDeSorteio = false; // Encerra a fase de sorteio se houver algum vencedor
                }
            }
        }

        if (!vencedores.empty()) { //  verifica Se houve vencedores
            cout << "Apostas vencedoras:\n"; // Exibe as apostas vencedoras
            for (auto& vencedor : vencedores) { // Exibe os nomes dos vencedores
                cout << vencedor << "\n"; // Exibe o nome do vencedor
            }
        } else if (i == 24) { // Se chegou ao limite de sorteios sem vencedores
            cout << "Não houve vencedores após 25 sorteios." << endl; // Exibe uma mensagem informando que não houve vencedores
        }
    }
}

        int contarAcertos(const vector<int>& numerosEscolhidos, const vector<int>& numerosSorteados) const { //método que conta os acertos de um apostador
    int acertos = 0; 
    for (int numero : numerosEscolhidos) { // Verifica se cada número escolhido está entre os números sorteados
        if (find(numerosSorteados.begin(), numerosSorteados.end(), numero) != numerosSorteados.end()) { // Se o número foi sorteado
            ++acertos; // Incrementa o contador de acertos, para que seja comparado para ver se o apostador realmente acertou tudo
        }
    }
    return acertos; 
}

      void mostrarApostasPorApostador() const {    //método que exibe as apostas realizadas por cada apostador  
    
    for (const Apostador& apostador : apostadores) {  //laço de repetição que percorre o vetor de apostadores, para poder dizer depois que o apostador x fez tais apostas... 
        cout << apostador.getNome() << " fez essas apostas:" << endl; //exibe o nome do apostador e diz que ele fez tais apostas
        for (const Aposta& aposta : apostador.getApostasRealizadas()) { //laço de repetição que percorre o vetor de apostas realizadas pelo apostador
            cout << "ID: " << aposta.getId() << " - Numeros: "; //exibe o id da aposta e os numeros escolhidos
            for (int numero : aposta.getNumerosEscolhidos()) { //laço de repetição que percorre os numeros escolhidos
                cout << numero << " "; 
            }
            cout << endl;
        }
        cout << endl;
    }

    
    int rodadasRealizadas = sorteio.getSorteiosRealizados().size(); // Conta o número de rodadas de sorteio realizadas, variavel 
    int apostasVencedoras = 0; // Conta o número de apostas vencedoras realizadas, variavel

    
    map<int, int> numerosApostados; // Mapa para armazenar a quantidade de vezes que cada número foi apostado, decidi usar essa função pois ela me permite armazenar a quantidade de vezes que cada numero foi apostado, e assim, posso exibir isso para o usuario
    for (const Apostador& apostador : apostadores) {
        for (const Aposta& aposta : apostador.getApostasRealizadas()) { // Conta quantas vezes cada número foi apostado
            for (int numero : aposta.getNumerosEscolhidos()) { // Conta quantas vezes cada número foi apostado 
                numerosApostados[numero]++;
            }
        }
    }

   
    cout << "Numero apostado  e Qtd de apostas" << endl; // Exibe os números apostados e a quantidade de vezes que foram apostados
    for (const auto& par : numerosApostados) { //laço de repetição que percorre o mapa de numeros apostados
        cout << setw(2) << par.first << "          " << setw(2) << par.second << endl; // Exibe o número e a quantidade de vezes que foi apostado, faço uso da função setw para formatar a saída e deixar mais organizado
    }
    cout << endl;

    // Mostra informações sobre as rodadas de sorteio
    cout << "Rodadas de Sorteio realizadas: " << rodadasRealizadas << endl; // Exibe o número de rodadas de sorteio realizadas

    // Verifica se houve apostas vencedoras
    vector<string> vencedores; // Vetor para armazenar os nomes dos vencedores
    vector<int> numerosSorteados = {1, 2, 3, 4, 5};  //  faz   um vetor com os numeros sorteados
    for (const Apostador& apostador : apostadores) { // Verifica se algum apostador acertou todos os números sorteados
        for (const Aposta& aposta : apostador.getApostasRealizadas()) { // Verifica cada aposta do apostador
            int acertos = contarAcertos(aposta.getNumerosEscolhidos(), numerosSorteados); // Conta os acertos da aposta
            if (acertos == Aposta::NUMEROS_POR_SORTEIO) {
                vencedores.push_back(apostador.getNome() + (aposta.isSurpresinha() ? " (Surpresinha)" : "")); // Adiciona o nome do vencedor ao vetor de vencedores e diz se a aposta foi feita de forma aleatoria ou manual
                apostasVencedoras++;
            }
        }
    }

    
    if (!vencedores.empty()) { // Verifica se houve vencedores
        sort(vencedores.begin(), vencedores.end()); // Ordena os nomes dos vencedores em ordem alfabética
        cout << "Apostas vencedoras:\n"; // Exibe as apostas vencedoras
        for (const string& vencedor : vencedores) {     // Exibe os nomes dos vencedores
            cout << vencedor << "\n";
        }
    } else { // Se não houve vencedores 
        cout << "Não houve vencedores.\n";
    }
}


    void mostrarNumerosSorteados() const {  //método que exibe os numeros sorteados
    
    const auto& sorteios = sorteio.getSorteiosRealizados(); // Obtém os sorteios realizados
    cout << "Números sorteados nas rodadas:" << endl;
    for (const auto& sorteio : sorteios) { // Exibe os números sorteados em cada rodada
        for (int numero : sorteio) {
            cout << numero << " ";
        }
        cout << endl;
    }
}

      Apostador* encontrarApostador(const string& nome) { //método que encontra um apostador pelo nome
        for (Apostador& apostador : apostadores) { // Percorre o vetor de apostadores
            if (apostador.getNome() == nome) {  // Verifica se o nome do apostador é igual ao nome passado como parâmetro 
                return &apostador;
            }
        }
        return nullptr;
    }

   
         bool estaNaFaseDeSorteio() const { //método que verifica se estamos na fase de sorteio
        return faseDeSorteio;
  } 
        
        void registrarAposta(const string& cpf, const string& nome, const vector<int>& numeros, bool isManual = true) { //método que registra a aposta do apostador
            Apostador* apostador = encontrarApostador(nome);    // Encontra o apostador pelo nome
            if (!apostador) { // Se o apostador não foi encontrado
                apostadores.push_back(Apostador(nome, std::vector<Aposta>{})); // Adiciona um novo apostador ao vetor de apostadores

                apostador = &apostadores.back();// Registra a aposta
            }
            if (isManual) { // Se a aposta foi manual, realiza a aposta manual
                apostador->apostaManual(numeros); // Realiza a aposta manual
            } else { // Se a aposta foi feita de forma aleatoria, realiza a aposta de forma aleatoria
                apostador->apostaSurpresinha();
            }
        }
        
       
           

  };  
   

      


                                   
    
    

int main() { //função principal do meu programa, onde tudo acontece

    string nome, cpf; // Variáveis para armazenar o nome e o CPF do apostador
    GerenciadorDeApostas gerenciador; // Crio um objeto da classe GerenciadorDeApostas para gerenciar as apostas
    srand(static_cast<unsigned>(time(nullptr))); // Inicializa a semente de números aleatórios (expliquei la encima) 
    
    bool rodando = true; // variavel que controla se o programa esta rodando ou nao, no caso o meu while que controla o menu
    bool primeiraExecucao = true; // variavel que controla se é a primeira execução do programa, para exibir a mensagem de boas vindas apenas uma vez
    
    while (rodando) { //laço de repetição que controla o menu do programa

        if(primeiraExecucao){ // Exibe uma mensagem de boas-vindas na primeira execução
            cout <<"Seja bem-vindo caro(a) apostador(a)!\n" <<endl;     
            cout <<"A premiacao para o apostador que acertar os 5 numeros sorteados, e uma vaga na Dell!!"<<endl;
            primeiraExecucao = false;
        }

        
         

     

        cout << "\nMenu:\n" // Exibe o menu de opções para que o usuario digite o numero que corresponde ao que ele quer fazer no momento 
             << " 1. Fazer Aposta\n"
             << " 2. Realizar Apuracao\n"
             << " 3. Ver Apostas Realizadas\n"
             << " 4. Sair\n"
             << "Escolha uma opcao: ";

        int opcao;
         if (!(cin >> opcao)) { // Verifica se a entrada é válida
            cin.clear(); // Limpa flags de erro... tive alguns problemas com o buffer de entrada enquanto fazia testes, por isso meu programa tem varios limpadores de buffers, para evitar qualquer coisa que possa dar errado
            continue;
        }

switch(opcao) { //laço de repetição que controla as opções do menu, e o que acontece quando o usuario escolhe uma opção, o switch case 
case 1: {   // Fazer Aposta
              
            
            
         
               if (gerenciador.estaNaFaseDeSorteio()) { // Verifica se estamos na fase de sorteio
        cout << "Nao e possivel fazer apostas durante a fase de sorteio.\n"; 
        break;
    }

    
    cout << "Digite seu nome: "; // Pede o nome do apostador 
    cin >> nome;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer de entrada, expliquei antes o porque disso... e a sintaxe é apenas a sintaxe da função que já é da linguagem  
    cout << "Digite seu CPF: ";
    cin >> cpf;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer de entrada

    int tipoAposta; // Variável para armazenar o tipo de aposta 
    cout << "Escolha o tipo de aposta:\n 1. Manual\n 2. Surpresinha\n"; // Pede ao usuário que escolha o tipo de aposta
    cin >> tipoAposta;

    if (tipoAposta == 1) { // Aposta manual
        vector<int> numeros;
       
cin.clear();
cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

cout <<"Digite os 5 números da sua aposta (entre 1 e 50), sem repeticoes: "<<endl;// Limpa o buffer de entrada e pede ao usuario que digite os numeros da aposta

        for (int i = 0; i < 5; i++) { //laço de repetição que pede ao usuario que digite os numeros da aposta
            int numero;
            cin >> numero;
            numeros.push_back(numero); // Adiciona o número ao vetor de números
            
            
            
        }

        cout << "Voce digitou os seguintes numeros: "; // Exibe os números digitados
for (auto n : numeros) { //laço de repetição que exibe os numeros digitados 
    cout << n << " ";
}
cout << endl;

           
      
        gerenciador.registrarAposta(cpf, nome, numeros, true); // Registra a aposta manual
    }else if (tipoAposta == 2) { // Surpresinha 
    gerenciador.registrarAposta(cpf, nome, {}, false); // Registra a aposta de forma aleatória
    }else{ //caso o usuario digite uma opção invalida
        cout <<"Opcao invalida \n";

    }
    break;
          }
    
    
  

case 2: { // Realizar Apuração 
    char confirmacao; // Variável para armazenar a confirmação do usuário
    cout << "Voce deseja realmente realizar a apuracao? (s/n): ";
    cin >> confirmacao;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer de entrada

    if (tolower(confirmacao) == 's') { // Verifica se o usuário confirmou a apuração, faço uso de tolower que tambem é uma função de c++, para que não importe se meu usuario digite em maiusculo ou minusculo 
        cout << "Iniciando a fase de apuracao...\n";

        if (gerenciador.estaNaFaseDeSorteio()) { // Verifica se a fase de apuração já está em andamento
            cout << "A fase de apuracao ja esta em andamento.\n";   
            
        }else{ // Se a fase de apuração não estiver em andamento, inicia a fase de apuração

            gerenciador.iniciarFaseDeSorteio();
        }
    }else{ //caso o usuario digite algo diferente de s
        cout << "retornando ao menu...\n";

    }
    break;
}
    


    
case 3: { // Ver Apostas Realizadas
    gerenciador.mostrarApostasPorApostador(); // Exibe as apostas realizadas por cada apostador
    cout << "Pressione qualquer tecla para voltar ao menu..."; // Pede ao usuário que pressione qualquer tecla para voltar ao menu
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer
    cin.get(); // Aguarda o usuário pressionar uma tecla
    break; } 

case 4: { // Sair
    cout << "Saindo do programa...\n\n";

    
    cout << "Resumo das apostas realizadas:\n";     // Exibe um resumo das apostas realizadas
    gerenciador.mostrarApostasPorApostador(); // Exibe as apostas realizadas por cada apostador

    
    cout << "\nResumo dos números sorteados:\n"; // Exibe um resumo dos números sorteados
    gerenciador.mostrarNumerosSorteados(); // Exibe os números sorteados

    rodando = false; // Encerra o programa
    break;

    
}


        
    
    
    
default: { //caso o usuario digite uma opção invalida
        cout << "Opcao invalida, tente novamente.\n"; // Exibe uma mensagem de erro
        break;
    }
}
    }
return 0; //retorna 0 para o sistema operacional, indicando que o programa foi executado com sucesso
}
    

    
    





  
      
    
    