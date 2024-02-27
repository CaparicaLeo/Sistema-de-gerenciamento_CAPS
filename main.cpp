//Seguinte: ANALISE TODOS OS CASOS POSSIVEIS, DEIXE O CODIGO MAIS BONITO VISUALMENTE//
#include <iostream>
#include <unistd.h>
#include <string>

using namespace std;

// Definição da struct Carro
struct Carro {
    string marca;
    string modelo;
    string ano;
    double precoCompra,precoVende,kmMetragem;
    bool sinistro, leilao;
};

// Definição da struct Data
struct Data {
    int dia, mes, anoNascimento;
};

// Definição da struct Endereco
struct Endereco {
    string bairro, cidade, rua, CEP;
    int numero;
};

// Definição da struct Cliente
struct Cliente {
    string nome, nomeMae, contato,CPF;
    Endereco moradia;
    Data nascimento;
};

const int  MAX_CARROS=32; // Limite de carros na loja
const int MAX_CLIENTES=INT16_MAX; // Pode-se ter infinitos clientes cadastrados

void cadCarro(Carro *&estoque, int &totalCarros,double &gasto);//Cadastra Carros
void cadCliente(Cliente *&clientela, int &totalClientes);//Cadastra Clientes
void listCarro(const Carro *estoque, int totalCarros);//Lista os carros
void listCliente(const Cliente *clientela, int totalClientes);// Lista os Clientes
void editCarro(Carro *&estoque, int &totalCarros);
void editCliente(Cliente *&clientela, int&totalClientes);
void excluirCliente(Cliente *&clientela, int &totalClientes);// Excluir Cadastro de clientes
void venda(Carro *estoque, Cliente *clientela, int totalCarros, int totalClientes, double &bruto); //Vende carros
double receitaTotal(double gasto, double bruto);//Calcula o lucro
bool validaCPF(const string &cpf);//Valida CPF

int main(){
    Carro *estoque = new Carro[MAX_CARROS];// Vetor para o estoque
    Cliente *clientela = new Cliente[MAX_CLIENTES]; //Vetor para a clientela
    
    int totalCarros = 0; // Total de carros no estoque
    int totalClientes = 0; // Total de clientes cadastrados
    double gasto=0.0, bruto=0.0; // Dados para o lucro
    int opcao, opcaoFinal=1; // Opções 
    do{
        //MENU
        cout << "SISTEMA DE GERENCIAMENTO DE CARROS CAPS" << endl;
        cout << "Escolha uma opcao:" << endl;
        cout << "[1]. Cadastrar novo carro" << endl<< endl;
        cout << "[2]. Listar carros disponiveis" << endl<< endl;
        cout << "[3]. Editar cadastro do Carro" << endl<< endl;
        cout << "[4]. Cadastrar cliente" << endl<< endl;
        cout << "[5]. Veja os clientes cadastrados" << endl<< endl;
        cout << "[6]. Editar Cadastro do Cliente" << endl<< endl;
        cout << "[7]. Excluir Cadastro do Cliente" << endl<< endl;
        cout << "[8]. Vender carro" << endl<< endl;
        cout << "[9]. Ver receita total atual" << endl<< endl;
        cout << "[0]. Sair" << endl<< endl;
        cout << "Opcao: ";
        cin >> opcao;

        switch(opcao){
            case 1:
                cadCarro(estoque, totalCarros,gasto);
                break;
            case 2:
                listCarro(estoque,totalCarros);
                break;
            case 3:
                editCarro(estoque,totalCarros);
                break;
            case 4:
                cadCliente(clientela,totalClientes);
                break;
            case 5:
                listCliente(clientela,totalClientes);
                break;
            case 6:
                editCliente(clientela,totalClientes);
                break;
            case 7:
                excluirCliente(clientela,totalClientes);
                break;
            case 8:
                venda(estoque, clientela, totalCarros, totalClientes, bruto);
                --totalCarros;
                cout << endl << "RECEITA ATUAL: " << receitaTotal(gasto, bruto) << endl;
                break;
            case 9:
                if (gasto == 0.0 && bruto == 0.0) {
                    cout << endl << "NAO HOUVE VENDAS OU COMPRAS" << endl << endl;
                }
                else {
                    cout << "RECEITA ATUAL: " << endl << endl << "GASTOS: " << gasto << endl 
                         << "BRUTO: " << bruto << endl << "LUCRO: " << receitaTotal(gasto, bruto) 
                         << endl << endl;
                }
                break;
            case 0: 
                cout << "CARREGANDO..." << endl << endl;
                sleep(5);
                break;
            default: 
                cout << "INVALIDO" << endl << endl;
                break; 
        }
    }while(opcao!=0);
    do{
        if(opcaoFinal!=1){
            cout << "SELEÇÃO INVALIDA!!" << endl << endl;
        }
        cout << "RELATORIO DIARIO" << endl;
        cout << "GASTOS: " << gasto << endl;
        cout << "RENDIMENTO BRUTO: " << bruto << endl;
        cout << "LUCRO TOTAL DIARIO: " << receitaTotal(gasto,bruto)<< endl;
        cout << "APERTE 1 PARA SAIR: ";
        cin >> opcaoFinal;
    }while(opcaoFinal!=1);
    cout << "FECHANDO PROGRAMA EM 3...";
    sleep(1);
    cout << "2...";
    sleep(1);
    cout << "1...";
    sleep(3);

    delete[] estoque;
    delete[] clientela;

    return 0;
}
void cadCarro(Carro *&estoque, int &totalCarros, double &gasto){
    system("cls");
    int opSin, opLei;
    if(totalCarros<MAX_CARROS){
        Carro novoCarro;
        cout << "Marca: ";
        cin >> novoCarro.marca;
        cout << "Modelo: ";
        cin.ignore();
        getline(cin, novoCarro.modelo);
        cout << "Ano: ";
        cin >> novoCarro.ano;
        cout << "Kilometragem: ";
        cin >> novoCarro.kmMetragem;
        do{
            cout << endl << "O CARRO TEM SINISTRO ?" << endl << "Digite 1 para sim, 0 para nao" << endl
                 << "SELECIONE: ";
            cin >> opSin;
            switch(opSin){
                case 1: 
                    novoCarro.sinistro = true;
                    break;
                case 0:
                    novoCarro.sinistro = false;
                    break;
                default:
                    cout << "INVALIDO!!" << endl;
                    break;
            }
        }while(opSin != 1 && opSin!=0);
        do{
            cout << endl << "O CARRO TEM LEILAO ?" << endl << "Digite 1 para sim, 0 para nao" << endl
                 << "SELECIONE: ";
            cin >> opLei;
            switch(opLei){
                case 1: 
                    novoCarro.leilao = true;
                    break;
                case 0:
                    novoCarro.leilao = false;
                    break;
                default:
                    cout << "INVALIDO!!" << endl;
                    break;
            }
        }while(opSin != 1 && opSin!=0);
        cout << endl;
        cout << "Por quanto voce comprou: ";
        cin >> novoCarro.precoCompra;
        cout << "Por quanto voce pretende vender: ";
        cin >> novoCarro.precoVende;
        gasto=novoCarro.precoCompra;
        estoque[totalCarros]=novoCarro;
        totalCarros++;
    }
    else{
        cout << endl << "LIMITE DE CARROS ATINGIDO !!! " << endl << endl;
        sleep(5);
    }
};
void cadCliente(Cliente *&clientela, int &totalClientes){
    system("cls");
    if (totalClientes < MAX_CLIENTES){
        Cliente novoCliente;
        cout << "Digite o nome do cliente: ";
        cin.ignore();
        getline(cin, novoCliente.nome);
        cout << "Digite o CPF do cliente: ";
        do{
            getline(cin, novoCliente.CPF);
            if (validaCPF(novoCliente.CPF)==false) {
            cout << "CPF INVALIDO !" << endl;
            }
        }while(validaCPF(novoCliente.CPF)!= true);

        cout << "Digite o nome da mae do cliente: ";
        
        getline(cin, novoCliente.nomeMae);

        cout << "Digite o contato do cliente: ";
        
        getline(cin, novoCliente.contato);

        cout << "Digite o bairro do cliente: ";
        
        getline(cin, novoCliente.moradia.bairro);

        cout << "Digite a cidade do cliente: ";
        
        getline(cin, novoCliente.moradia.cidade);

        cout << "Digite a rua do cliente: ";
        
        getline(cin, novoCliente.moradia.rua);

        cout << "Digite o CEP do cliente: "; 
       
        getline(cin, novoCliente.moradia.CEP);

        cout << "Digite o número da residência do cliente: ";
        
        cin >> novoCliente.moradia.numero;

        cout << "Digite a data de nascimento do cliente (DD MM AAAA): ";
        cin >> novoCliente.nascimento.dia >> novoCliente.nascimento.mes >> novoCliente.nascimento.anoNascimento;

        clientela[totalClientes] = novoCliente;
        totalClientes++;
        cout << "Cliente cadastrado com sucesso!" << endl;
    } 
    else{
        cout << "Limite máximo de clientes atingido!" << endl;
    }
    sleep(5);
    system("cls");
};
void listCarro(const Carro *estoque, int totalCarros){
    system("cls");
    if(totalCarros>0){
        cout << "Lista de carros disponiveis:" << endl;
        for (int i = 0; i < totalCarros; ++i) {
            cout << "Carro " << i + 1 << ":" << endl;
            cout << "Marca: " << estoque[i].marca << endl;
            cout << "Modelo: " << estoque[i].modelo << endl;
            cout << "Ano: " << estoque[i].ano << endl;
            cout << "Kilometragem: " << estoque[i].kmMetragem << endl;
            cout << "Sinistro: ";
            if(estoque[i].sinistro==true){
                cout << "SIM" << endl;
            }
            else{
                cout << "NAO" << endl;
            }
                cout << "Leilao: ";
            if(estoque[i].leilao==true){
                cout << "SIM" << endl;
            }
            else{
            cout << "NAO" << endl;
            }
            cout << "Preco: R$" << estoque[i].precoVende << endl;
            cout << endl;
        }
        cout << endl << endl;
    }
    else{
        cout << "NÃO HA CARROS PARA SE LISTAR !" << endl << endl;
    }
}
void editCarro(Carro *&estoque, int &totalCarros){
    cout << "Teste 1" << endl;
}
void editCliente(Cliente *&clientela, int&totalClientes){
    cout << "Teste 2" << endl;
}
void excluirCliente(Cliente *&clientela, int &totalClientes){
    cout << "Teste 3" << endl;
}
void listCliente(const Cliente *clientela, int totalClientes){
    system("cls");
    if(totalClientes==0){
        cout << "NÃO HÁ CLIENTES CADASTRADOS !!!" << endl << endl;
    }
    cout << "Lista de clientes disponíveis:" << endl;
    for (int i = 0; i < totalClientes; i++) {
        cout << "CLIENTE " << i + 1 << ": " << endl
             << "NOME: "<< clientela[i].nome << endl;
        cout << "CPF: " << clientela[i].CPF << endl;
        cout << "CONTATO: " << clientela[i].contato << endl;
        cout << "IDADE: " << 2024-clientela[i].nascimento.anoNascimento << endl;
        cout << endl;
    }
    cout << endl << endl;
};
void venda(Carro *estoque, Cliente *clientela, int totalCarros, int totalClientes,double &bruto){
    system("cls");
    if (totalCarros == 0) {
        cout << "Não há carros disponíveis para venda." << endl;
        return;
    }

    cout << "Escolha o número do carro que deseja vender:" << endl;
    listCarro(estoque, totalCarros);

    int indiceCarro;
    cout << "Digite o número do carro que deseja vender: ";
    cin >> indiceCarro;

    if (indiceCarro < 1 || indiceCarro > totalCarros) {
        cout << "Carro inválido!" << endl;
        return;
    }
    int opCad;
    cout << "O cliente é cadastrado?" << endl << "1 para sim"<< endl
         << "0 para não" << endl <<"Selecione: ";
    cin >> opCad;
    switch(opCad){
        case 1:
            listCliente(clientela, totalClientes);
            break;
        case 0:
            cadCliente(clientela, totalClientes);
            listCliente(clientela, totalClientes);
            break;
    }
    
    int indiceCliente;
    cout << "Digite o número do cliente que está comprando o carro: ";
    cin >> indiceCliente;
    if(indiceCliente < 1 || indiceCliente> totalClientes){
        cout << "Cliente Inválido!!" << endl;
        return;
    }

    system("cls");
    int certeza=0;
    int opPreco;
    cout << "Você esta vendendo o Carro: " << endl;
    cout << "Numero no estoque: " << indiceCarro << endl;
    cout << "Marca: " << estoque[indiceCarro-1].marca << endl;
    cout << "Modelo: " << estoque[indiceCarro-1].modelo << endl;
    cout << "Ano: " << estoque[indiceCarro-1].ano << endl;
    cout << "Preço: " << estoque[indiceCarro-1].precoVende << endl;
    cout << "Deseja mudar esse preço? " << endl << "Digite 1 para sim" << endl << "Digite 0 para não" << endl
         << "Selecione: ";
    cin >> opPreco;
    do{
        switch(opPreco){
        case 1: 
            cout << endl << "DIGITE O PREÇO: ";
            cin >> estoque[indiceCarro-1].precoVende;
            break;
        case 0:
            break;
        default:
            cout << endl << "DIGITE UM VALOR VALIDO!" << endl;
            break;
        }
    }while(opPreco!=0 && opPreco!=1);

    cout << endl << "Para o cliente: " << endl;
    cout << "Numero da Clientela: " << indiceCliente << endl;
    cout << "Nome: " << clientela[indiceCliente-1].nome << endl;
    cout << "Nome da Mae: " << clientela[indiceCliente-1].nomeMae << endl;
    cout << "Nascido em: " << clientela[indiceCliente-1].nascimento.dia << "/" 
         << clientela[indiceCliente-1].nascimento.mes 
         << "/" << clientela[indiceCliente-1].nascimento.anoNascimento << endl;
    cout << "Contato: " << clientela[indiceCliente-1].contato << endl;
    cout << "Mora na rua: " << clientela[indiceCliente-1].moradia.rua << endl;
    cout << "Numero: " << clientela[indiceCliente-1].moradia.numero << endl;
    cout << "Bairro: " << clientela[indiceCliente-1].moradia.bairro << endl;
    cout << "CEP: " << clientela[indiceCliente-1].moradia.CEP << endl;
    cout << "Na cidade de: " << clientela[indiceCliente-1].moradia.cidade << endl;
    cout << endl << "Venda Absoluta ?" << endl << "Aperte 1 para SIM" << endl << "Aperte 0 para NAO" << endl
         << "Selecione: ";
    cin >> certeza;
    if (indiceCliente < 1 || indiceCliente > totalClientes) {
        cout << "Cliente inválido!" << endl;
        return;
    }
    if(certeza==0){
        return;
    }
    else{
        bruto += estoque[indiceCarro-1].precoVende;
        cout << "Carro vendido para " << clientela[indiceCliente - 1].nome << " com sucesso!" << endl;
        for (int i = indiceCarro - 1; i < totalCarros - 1; ++i) {
        estoque[i] = estoque[i + 1];
        }
        totalCarros--;
    }
    cout << "CARREGANDO..."<< endl;
    sleep(5);
};
double receitaTotal(double gasto, double bruto){
    system("cls");
    double receita;
    receita = bruto-gasto;
    return receita;
};
bool validaCPF(const string &cpf) {
    if (cpf.length() != 11)
        return false;

    for (char c : cpf) {
        if (!isdigit(c))
            return false;
    }

    int soma = 0;
    for (int i = 0; i < 9; i++) {
        soma += (cpf[i] - '0') * (10 - i);
    }
    int digito1 = 11 - (soma % 11);
    if (digito1 >= 10)
        digito1 = 0;

    if (digito1 != (cpf[9] - '0'))
        return false;

    soma = 0;
    for (int i = 0; i < 10; i++) {
        soma += (cpf[i] - '0') * (11 - i);
    }
    int digito2 = 11 - (soma % 11);
    if (digito2 >= 10)
        digito2 = 0;

    if (digito2 != (cpf[10] - '0'))
        return false;

    return true;
}
