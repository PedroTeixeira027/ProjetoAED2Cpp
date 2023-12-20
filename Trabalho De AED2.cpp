// Trabalho de Algoritmos e Estrutura De Dados II, menu Associados, Dependentes e
// Visitantes.
// Alunos:
// João Pablo Soares Lino - Turma A
// Pedro Ângelo Tellaroli Vargas - Turma A
// Pedro Henrique Teixeira Da Silva - Turma B

// Declaraï¿½ï¿½o das bibliotecas ultilizadas para construï¿½ï¿½o do cï¿½digo
#include <iostream>
#include <locale.h>
#include <fstream>
#include <stdlib.h>
#include <windows.h>
#include <ctime>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>

// Declaraï¿½ï¿½o do STD para nï¿½o precisarmos ficar ultilizando ele toda hora
using namespace std;

// Struct para cadastrar pessoas

struct Tpessoas
{
    string cpf;
    string nome;
    string endereco;
    string email;
    string telefone;
    char sexo;
    string sexo_tipo;
    int dia_nasc;
    int mes_nasc;
    int ano_nasc;
    int cod_pessoa;
};

// Struct para abastecer dados de associados
struct Tassociados
{
    int cod_associado;
    int cod_pessoa;
    int dia_associacao;
    int mes_associacao;
    int ano_associacao;
    char tipo_socio;
    float mensalidade;
    int numDependentes;
};

// Struct para abastecer dados de dependentes
struct Tdependentes
{
    int cod_dependente;
    int cod_associado;
    int cod_pessoa;
    int cod_externo;
    int dia_associacao_de;
    int mes_associacao_de;
    int ano_associacao_de;
    string cpf_associado;
    string nome_associado;
};

// Struct para abastecer dados de visitantes
struct Tvisitantes
{
    int cod_visitante;
    int cod_associado;
    int cod_pessoa;
    int dia_visita_inicial;
    int mes_visita_inicial;
    int ano_visita_inicial;
    int dia_visita_final;
    int mes_visita_final;
    int ano_visita_final;
    int hora_inicial;
    int minuto_inicial;
    int hora_final;
    int minuto_final;
    int dia_visita_final2;
    int mes_visita_final2;
    int ano_visita_final2;
    int hora_final2;
    int minuto_final2;
};

// Protï¿½tipos das funï¿½ï¿½es
void MenuPrincipal();
void SubMenu1();
void SubMenu2();
void SubMenu3();
void SubMenu4();
void SubMenu5();
void editaPessoa();
void editaAssociado();
void editaDependente();
void editaVisita();
void cadastrarPessoas(Tpessoas &pessoa);
void cadastrarAssociados(Tassociados &associados, Tpessoas &pessoa);
void cadastrarDependentes(Tdependentes &dependentes, Tassociados &associados, Tpessoas &pessoa);
void cadastrarVisitantes(Tvisitantes &visitantes, Tpessoas &pessoa);
void registroVisita(Tpessoas &pessoa, Tvisitantes &visitantes, Tassociados &associados);
void lerContadorPessoa();
void lerContadorAssociados();
void lerContadorDependentes();
void lerContadorVisitantes();
void obterDataAtual(int &dia, int &mes, int &ano);
void obterHorarioAtual(int &horas, int &minutos);
void obterDataAtual2(int &dia2, int &mes2, int &ano2);
void obterHorarioAtual2(int &horas2, int &minutos2);
void excluirPessoa(const string &ExcluirPessoa);
void excluirAssociado(const string &ExcluirAssociado);
void excluirDependente(const string &ExcluirDependente);
void excluirVisita(const string &ExcluirVisita);

// lerContadorDependentes, lerContadorVisitantes e lerContadorPessoa.
static int contadorAssociados = 10000;
static int contadorDependentes = 10000;
static int contadorVisitantes = 10000;
static int contadorPessoa = 10000;

// Funï¿½ï¿½o principal
int main()
{
    setlocale(LC_ALL, "portuguese");
    lerContadorAssociados();
    lerContadorDependentes();
    lerContadorVisitantes();
    lerContadorPessoa();
    MenuPrincipal();
    return 0;
}

void MenuPrincipal()
{
    int opcao;
    do
    {
        system("cls");
        cout << "Menu Principal:\n\n";
        cout << "1 - Cadastro de Pessoas" << endl;
        cout << "2 - Relatorio de dependentes/associados" << endl;
        cout << "3 - Relatorio de visitas por associado" << endl;
        cout << "4 - Editar Cadastro" << endl;
        cout << "5 - Excluir Cadastro" << endl;
        cout << "0 - Sair\n\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        system("cls");
        switch (opcao)
        {
        case 1:
            SubMenu1();
            break;
        case 2:
            SubMenu2();
            break;
        case 3:
            SubMenu3();
            break;
        case 4:
            SubMenu4();
            break;
        case 5:
            SubMenu5();
            break;
        case 0:
            break;
        default:
            cout << "Opcao invalida...\n";
            Sleep(2000);
            system("cls");
            break;
        }
    } while (opcao != 0);
}

// Funï¿½ï¿½o do menu cadastro de pessoas
void SubMenu1()
{
    int subOpcao1;
    do
    {
        cout << "CADASTRO DE PESSOAS\n\n";
        cout << "1 - Cadastrar pessoas\n";
        cout << "2 - Registra visita\n";
        cout << "0 - Voltar ao menu principal\n\n";
        cout << "Escolha uma opcao: ";
        cin >> subOpcao1;
        system("cls");
        Tpessoas novaPessoa;
        Tvisitantes visitantes;
        Tassociados associados;
        switch (subOpcao1)
        {
        case 1:
            cadastrarPessoas(novaPessoa);
            break;
        case 2:
            registroVisita(novaPessoa, visitantes, associados);
            break;
        case 0:
            break;
        default:
            cout << "Opcao invalida!\n";
            break;
        }
    } while (subOpcao1 != 0);
}

// Funï¿½ï¿½o para gerar relatï¿½rio de dependentes/associados
void SubMenu2()
{
    int op;
    string tecla;
    fstream arquivoAssociados;
    fstream arquivoDependentes;
    fstream arquivoPessoas;
    arquivoAssociados.open("associados.txt", ios::in);
    arquivoDependentes.open("dependentes.txt", ios::in);
    arquivoPessoas.open("pessoas.txt", ios::in);

    cout << "Relatorio de Dependentes, Associados e Pessoas" << endl;
    cout << "1 - Associados" << endl;
    cout << "2 - Dependentes" << endl;
    cout << "3 - Pessoas" << endl;
    cout << "0 - Sair" << endl;

    do
    {
        cin >> op;
        switch (op)
        {
        case 1:

            // Exibir informaï¿½ï¿½es dos associados
            system("cls");
            cout << "Associados: \n";
            while (!arquivoAssociados.eof())
            {
                string line;
                getline(arquivoAssociados, line);
                cout << line << endl;
            }
            arquivoAssociados.close();
            cout << "\nFim do Relatorio\n";
            cout << "Aperte qualquer tecla para retornar ao Menu Principal";
            cin >> tecla;
            MenuPrincipal();
            break;

        case 2:

            // Exibir informaï¿½ï¿½es dos dependentes
            system("cls");
            cout << "\nDependentes: \n";
            while (!arquivoDependentes.eof())
            {
                string line;
                getline(arquivoDependentes, line);
                cout << line << endl;
            }

            arquivoDependentes.close();
            cout << "\nFim do Relatorio\n";
            cout << "Aperte qualquer tecla para retornar ao Menu Principal";
            cin >> tecla;
            MenuPrincipal();
            break;

        case 3:
            system("cls");
            cout << "\nPessoas: \n";
            while (!arquivoPessoas.eof())
            {
                string line;
                getline(arquivoPessoas, line);
                cout << line << endl;
            }
            arquivoPessoas.close();
            cout << "\nFim do Relatorio\n";
            cout << "Aperte qualquer tecla para retornar ao Menu Principal";
            cin >> tecla;
            MenuPrincipal();
            break;

        case 0:
            cout << "Aperte qualquer tecla pra retornar ao Menu Principal..." << endl;
            cin >> tecla;
            MenuPrincipal();
            break;
            system("cls");
        }
    } while (op != 0);
}

// Funï¿½ï¿½o para gerar relatï¿½rio de dependentes/associados
void SubMenu3()
{
    string tecla2;
    fstream arquivoRegistro("registrovisitasagendadas.txt", ios::in);
    fstream arquivoRegistro1("registrovisitas.txt", ios::in);
    if (!arquivoRegistro.is_open() || !arquivoRegistro1.is_open())
    {
        cout << "Erro ao abrir os arquivos. Certifique-se de que os arquivos registrovisitasagendadas.txt e registrosvisitas.txt existem.\n";
        Sleep(2000);
        system("cls");
        return;
    }

    // Exibir todos os registros de visitas
    cout << "Registro de visitas agendadas:\n\n";
    while (!arquivoRegistro.eof())
    {
        string line;
        getline(arquivoRegistro, line);
        cout << line << endl;
    }
    arquivoRegistro.close();

    // Exibir informaï¿½ï¿½es dos dependentes
    cout << "\nRegistro de visitas realizadas:\n\n";
    while (!arquivoRegistro1.eof())
    {
        string line;
        getline(arquivoRegistro1, line);
        cout << line << endl;
    }
    arquivoRegistro1.close();
    cout << "Fim do Relatorio\n";
    cout << "Aperte qualquer tecla pra retornar ao Menu Principal..." << endl;
    cin >> tecla2;
    system("cls");
}

void SubMenu4()
{
    int escolha;
    do
    {
        system("cls");
        cout << "\nEdicao de Cadastro!" << endl;
        cout << "\nOpcoes: " << endl;
        cout << "1 - Pessoas" << endl;
        cout << "2 - Associados" << endl;
        cout << "3 - Dependentes" << endl;
        cout << "4 - Visitas" << endl;
        cout << "0 - Sair" << endl;
        cin >> escolha;
        switch (escolha)
        {
        case 1:
            editaPessoa();
            break;
        case 2:
            editaAssociado();
            break;
        case 3:
            editaDependente();
            break;
        case 4:
            editaVisita();
            break;

        case 0:

            break;
        default:

            break;
        }
    } while (escolha != 0);
}

void SubMenu5()
{
    system("cls");
    int op;
    string ParaExcluirPessoa, ParaExcluirAssociado, ParaExcluirDependente, ParaExcluirVisitante;
    cout << "Exclusao de Registros!" << endl;
    cout << "1 - Pessoas" << endl;
    cout << "2 - Associados" << endl;
    cout << "3 - Dependentes" << endl;
    cout << "4 - Visitantes" << endl;
    cout << "0 - Sair" << endl;

    do
    {
        cin >> op;
        switch (op)
        {
        case 1:
            cout << "Digite o que deseja excluir em Pessoas: ";
            cin >> ParaExcluirPessoa;
            excluirPessoa(ParaExcluirPessoa);
            break;

        case 2:
            cout << "Digite o que deseja excluir em Associados: ";
            cin >> ParaExcluirAssociado;
            excluirAssociado(ParaExcluirAssociado);
            break;

        case 3:
            cout << "Digite o que deseja excluir em Dependentes: ";
            cin >> ParaExcluirDependente;
            excluirAssociado(ParaExcluirDependente);
            break;

        case 4:
            cout << "Digite o que deseja excluir em Visitantes: ";
            cin >> ParaExcluirVisitante;
            excluirVisita(ParaExcluirVisitante);
            break;

        case 0:
            break;
        }
    } while (op != 0);
}

void excluirPessoa(const string &excluirPessoa)
{

    ifstream arquivoPessoasIn("pessoas.txt");
    ofstream arquivoTempOut("temp.txt");

    if (!arquivoPessoasIn.is_open() || !arquivoTempOut.is_open())
    {
        cerr << "Erro ao abrir arquivos." << endl;
        return;
    }

    Tpessoas pessoa;
    string linha;

    // Leitura do arquivo, copiando para o arquivo temporÃ¡rio, exceto a pessoa a ser excluÃ­da
    while (getline(arquivoPessoasIn, linha))
    {
        if (linha != excluirPessoa) // Verifica se a linha Ã© igual Ã  string fornecida
        {

            if (linha.find("CPF: " + excluirPessoa) == string::npos &&
                linha.find("Codigo de Pessoa: " + excluirPessoa) == string::npos &&
                linha.find("Endereco: " + excluirPessoa) == string::npos &&
                linha.find("Email: " + excluirPessoa) == string::npos &&
                linha.find("Telefone: " + excluirPessoa) == string::npos &&
                linha.find("Sexo: " + excluirPessoa) == string::npos &&
                linha.find("Data de nascimento: " + excluirPessoa) == string::npos &&
                linha.find("Nome: " + excluirPessoa) == string::npos)
            {
                arquivoTempOut << linha << endl;
            }
        }
    }

    arquivoPessoasIn.close();
    arquivoTempOut.close();

    // Substituir o conteÃºdo original pelo conteÃºdo do arquivo temporÃ¡rio
    remove("pessoas.txt");
    rename("temp.txt", "pessoas.txt");
}

void excluirAssociado(const string &ExcluirAssociado)
{
    ifstream arquivoAssociadosIn("associados.txt");
    ofstream arquivoTempOut("temp.txt");

    if (!arquivoAssociadosIn.is_open() || !arquivoTempOut.is_open())
    {
        cerr << "Erro ao abrir arquivos." << endl;
        return;
    }

    Tpessoas pessoa;
    string linha;

    // Leitura do arquivo, copiando para o arquivo temporÃ¡rio, exceto a pessoa a ser excluÃ­da
    while (getline(arquivoAssociadosIn, linha))
    {
        if (linha != ExcluirAssociado) // Verifica se a linha Ã© igual Ã  string fornecida
        {

            if (linha.find("CPF: " + ExcluirAssociado) == string::npos &&
                linha.find("Codigo de Pessoa: " + ExcluirAssociado) == string::npos &&
                linha.find("Codigo de Associado: " + ExcluirAssociado) == string::npos &&
                linha.find("Data da Associacao: " + ExcluirAssociado) == string::npos &&
                linha.find("Mensalidade: " + ExcluirAssociado) == string::npos &&
                linha.find("Tipo de Socio: " + ExcluirAssociado) == string::npos &&
                linha.find("Nome: " + ExcluirAssociado) == string::npos)
            {
                arquivoTempOut << linha << endl;
            }
        }
    }

    arquivoAssociadosIn.close();
    arquivoTempOut.close();

    // Substituir o conteÃºdo original pelo conteÃºdo do arquivo temporÃ¡rio
    remove("associados.txt");
    rename("temp.txt", "associados.txt");
}

// Leitura do arquivo, copiando para o arquivo temporÃ¡rio, exceto a pessoa a ser excluÃ­da
void excluirDependente(const string &ExcluirDependente)
{
    ifstream arquivoDependentesIn("dependentes.txt");
    ofstream arquivoTempOut("temp.txt");

    if (!arquivoDependentesIn.is_open() || !arquivoTempOut.is_open())
    {
        cerr << "Erro ao abrir arquivos." << endl;
        return;
    }

    Tpessoas pessoa;
    string linha;

    // Leitura do arquivo, copiando para o arquivo temporÃ¡rio, exceto a pessoa a ser excluÃ­da
    while (getline(arquivoDependentesIn, linha))
    {
        if (linha != ExcluirDependente) // Verifica se a linha Ã© igual Ã  string fornecida
        {

            if (linha.find("Codigo de Pessoa: " + ExcluirDependente) == string::npos &&
                linha.find("Nome: " + ExcluirDependente) == string::npos &&
                linha.find("Data de nascimento: " + ExcluirDependente) == string::npos &&
                linha.find("Sexo: " + ExcluirDependente) == string::npos &&
                linha.find("Codigo de Dependente: " + ExcluirDependente) == string::npos &&
                linha.find("Data da Associacao: " + ExcluirDependente) == string::npos &&
                linha.find("Codigo Externo: " + ExcluirDependente) == string::npos &&
                linha.find("Codigo de Associado: " + ExcluirDependente) == string::npos &&
                linha.find("Nome Associado: " + ExcluirDependente) == string::npos &&
                linha.find("CPF do Associado: " + ExcluirDependente) == string::npos)
            {
                arquivoTempOut << linha << endl;
            }
        }
    }

    arquivoDependentesIn.close();
    arquivoTempOut.close();

    // Substituir o conteÃºdo original pelo conteÃºdo do arquivo temporÃ¡rio
    remove("dependentes.txt");
    rename("temp.txt", "dependentes.txt");
}

void excluirVisita(const string &ExcluirVisita)
{
    ifstream arquivoVisitasIn("visitantes.txt");
    ofstream arquivoTempOut("temp.txt");

    if (!arquivoVisitasIn.is_open() || !arquivoTempOut.is_open())
    {
        cerr << "Erro ao abrir arquivos." << endl;
        return;
    }

    Tpessoas pessoa;
    string linha;
    while (getline(arquivoVisitasIn, linha))
    {
        if (linha != ExcluirVisita)
        {
            if (linha.find("Codigo de Pessoa: " + ExcluirVisita) == string::npos &&
                linha.find("Nome: " + ExcluirVisita) == string::npos &&
                linha.find("CPF: " + ExcluirVisita) == string::npos &&
                linha.find("Data de nascimento: " + ExcluirVisita) == string::npos &&
                linha.find("Sexo: " + ExcluirVisita) == string::npos &&
                linha.find("Codigo de Visitante: " + ExcluirVisita) == string::npos &&
                linha.find("Codigo de Associado: " + ExcluirVisita) == string::npos)

            {
                arquivoTempOut << linha << endl;
            }
        }
    }

    arquivoVisitasIn.close();
    arquivoTempOut.close();

    // Substituir o conteÃºdo original pelo conteÃºdo do arquivo temporÃ¡rio
    remove("visitantes.txt");
    rename("temp.txt", "visitantes.txt");
}

void editaPessoa()
{

    system("cls");
    Tpessoas pessoa;

    cout << "!AVISO! O CODIGO DA PESSOA E UNICO E NAO PODE SER MUDADO" << endl;
    cout << "Digite seu codigo de Pessoa: ";
    cin >> pessoa.cod_pessoa;

    fstream arquivoPessoas("pessoas.txt", ios::in);

    if (!arquivoPessoas)
    {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    ofstream arquivoTemp("temp.txt", ios::out | ios::app);
    arquivoTemp << "!AVISO! Registro com correcao, favor considerar este." << endl;
    cout << "Insira seu CPF: ";
    cin.ignore(); // Ignora o caractere de nova linha deixado pelo cin anterior
    getline(cin, pessoa.cpf);
    arquivoTemp << "CPF: " << pessoa.cpf << endl;
    cout << "Digite seu nome: ";
    getline(cin, pessoa.nome);
    arquivoTemp << "Nome: " << pessoa.nome << endl;
    cout << "Digite seu endereco: ";
    getline(cin, pessoa.endereco);
    arquivoTemp << "Endereco: " << pessoa.endereco << endl;
    cout << "Digite seu email: ";
    getline(cin, pessoa.email);
    arquivoTemp << "Email: " << pessoa.email << endl;
    cout << "Digite seu numero de telefone: ";
    getline(cin, pessoa.telefone);
    arquivoTemp << "Telefone: " << pessoa.telefone << endl;
    cout << "Digite seu sexo: ";
    cin >> pessoa.sexo;
    while (!(pessoa.sexo == 'M' || pessoa.sexo == 'm' || pessoa.sexo == 'F' || pessoa.sexo == 'f'))
    {
        cout << "ERRO. Digite M ou F\n";
        cout << "Digite seu sexo: ";
        cin.clear(); // Limpa o estado de erro do cin
        cin.ignore();
        cin >> pessoa.sexo;
    }
    pessoa.sexo_tipo = "";
    if (pessoa.sexo == 'm' || pessoa.sexo == 'M')
        pessoa.sexo_tipo = "Masculino";
    else if (pessoa.sexo == 'f' || pessoa.sexo == 'F')
        pessoa.sexo_tipo = "Feminino";
    arquivoTemp << "Sexo: " << pessoa.sexo_tipo << endl;
    cout << "Digite a sua data de nascimento (dd mm aaaa): ";
    cin >> pessoa.dia_nasc >> pessoa.mes_nasc >> pessoa.ano_nasc;
    arquivoTemp << "Data de nascimento: " << pessoa.dia_nasc << "/" << pessoa.mes_nasc << "/" << pessoa.ano_nasc << endl;
    cout << "Seu codigo de pessoa permanece sendo:  " << pessoa.cod_pessoa << endl;
    arquivoTemp << "Codigo de Pessoa: " << pessoa.cod_pessoa << endl;
    arquivoTemp << "---------------------------------------" << endl;
    Sleep(2000);

    arquivoTemp << arquivoPessoas.rdbuf();

    arquivoPessoas.close();
    arquivoTemp.close();

    remove("pessoas.txt");
    rename("temp.txt", "pessoas.txt");
}

void editaAssociado()
{
    system("cls");

    float taxaFixa = 200.0;
    float taxaPorDependente = 30.0;

    Tpessoas pessoa;
    Tassociados associados;

    cout << "!AVISO! O CODIGO DA PESSOA E DO ASSOCIADO E UNICO E NAO PODE SER MUDADO" << endl;
    cout << "Digite seu codigo de Pessoa: ";
    cin >> pessoa.cod_pessoa;
    cout << "Digite seu codigo de Associado: ";
    cin >> associados.cod_associado;

    fstream arquivoAssociados("associados.txt", ios::in);
    ofstream arquivoTemp("temp.txt", ios::out | ios::app);

    if (!arquivoAssociados)
    {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return;
    }
    arquivoTemp << "!AVISO! Registro com correcao, favor considerar este." << endl;
    cout << "Digite a data de associacao (dd mm aaaa): ";
    cin >> associados.dia_associacao >> associados.mes_associacao >> associados.ano_associacao;
    arquivoTemp << "Data da Associacao: " << associados.dia_associacao << "/" << associados.mes_associacao << "/" << associados.ano_associacao << endl;
    cout << "Digite quantos dependentes voce tem (Caso nao tenha digite 0): ";
    cin >> associados.numDependentes;
    associados.mensalidade = taxaFixa + (associados.numDependentes * taxaPorDependente);
    cout << "Sua mensalidade sera de: " << associados.mensalidade << endl;
    arquivoTemp << "Mensalidade: R$ " << associados.mensalidade << endl;
    cout << "Digite seu tipo de Associacao (Digite 'P' para Proprietario ou 'C' para Contribuinte): ";
    cin >> associados.tipo_socio;
    while (!(associados.tipo_socio == 'P' || associados.tipo_socio == 'p' || associados.tipo_socio == 'C' || associados.tipo_socio == 'c'))
    {
        cout << "ERRO. Digite P ou C: \n";
        cout << "Digite seu tipo de Associacao: ";
        cin.clear(); // Limpa o estado de erro do cin
        cin.ignore();
        cin >> associados.tipo_socio;
    }
    string contribuinte = "";
    if (associados.tipo_socio == 'P' || associados.tipo_socio == 'p')
        contribuinte = "Proprietario";
    else if (associados.tipo_socio == 'C' || associados.tipo_socio == 'c')
        contribuinte = "Contribuinte";

    arquivoTemp << "Tipo de Socio: " << contribuinte << endl;
    cout << "Seu codigo de pessoa permanece sendo: " << pessoa.cod_pessoa << endl;
    cout << "Seu codigo de associado permanece sendo: " << associados.cod_associado << endl;
    arquivoTemp << "Codigo de Pessoa: " << pessoa.cod_pessoa << endl;
    arquivoTemp << "Codigo de Associado: " << associados.cod_associado << endl;
    arquivoTemp << "---------------------------------------" << endl;
    cout << "Alteracao realizada com sucesso!";

    Sleep(2000);

    arquivoTemp << arquivoAssociados.rdbuf();

    arquivoAssociados.close();
    arquivoTemp.close();

    remove("associados.txt");
    rename("temp.txt", "associados.txt");
}

void editaDependente()
{
    system("cls");

    Tpessoas pessoa;
    Tdependentes dependentes;

    cout << "!AVISO! O CODIGO DA PESSOA E DO DEPENDENTE E UNICO E NAO PODE SER MUDADO" << endl;
    cout << "Digite seu codigo de Pessoa: ";
    cin >> pessoa.cod_pessoa;
    cout << "Digite seu codigo de Dependente: ";
    cin >> dependentes.cod_dependente;

    fstream arquivoDependentes("dependentes.txt", ios::in);
    ofstream arquivoTemp("temp.txt", ios::out | ios::app);

    if (!arquivoDependentes)
    {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return;
    }
    arquivoTemp << "!AVISO! Registro com correcao, favor considerar este." << endl;
    cout << "Digite a data de associacao (dd mm aaaa): ";
    cin >> dependentes.dia_associacao_de >> dependentes.mes_associacao_de >> dependentes.ano_associacao_de;
    arquivoTemp << "Data da Associacao: " << dependentes.dia_associacao_de << "/" << dependentes.mes_associacao_de << "/" << dependentes.ano_associacao_de << endl;
    dependentes.cod_externo = dependentes.ano_associacao_de + dependentes.cod_dependente;
    cout << "Codigo externo: " << dependentes.cod_externo << endl;
    arquivoTemp << "Codigo Externo: " << dependentes.cod_externo << endl;

    // Aqui precisa criar uma condicional para verificar se o cï¿½digo de associado existe
    cout << "Digite o codigo do Associado que voce esta vinculado: " << endl;
    cin >> dependentes.cod_associado;
    arquivoTemp << "Codigo de Associado: " << dependentes.cod_associado << endl;
    cout << "Digite o nome do Associado que voce esta vinculado: ";
    cin >> dependentes.nome_associado;
    arquivoTemp << "Nome Associado: " << dependentes.nome_associado << endl;
    cout << "Digite o CPF do Associado que voce esta vinculado: ";
    cin >> dependentes.cpf_associado;
    arquivoTemp << "CPF do Associado: " << dependentes.cpf_associado << endl;

    cout << "Seu codigo de pessoa permanece sendo: " << pessoa.cod_pessoa << endl;
    cout << "Seu codigo de dependente permanece sendo: " << dependentes.cod_dependente << endl;

    arquivoTemp << "Codigo de Pessoa: " << pessoa.cod_pessoa << endl;
    arquivoTemp << "Codigo de Dependente: " << dependentes.cod_dependente << endl;
    arquivoTemp << "---------------------------------------" << endl;
    cout << "Alteracao realizada com sucesso!";

    Sleep(2000);

    arquivoTemp << arquivoDependentes.rdbuf();

    arquivoDependentes.close();
    arquivoTemp.close();

    remove("dependentes.txt");
    rename("temp.txt", "dependentes.txt");
}

void editaVisita()
{
    system("cls");
    Tpessoas pessoa;
    Tvisitantes visitantes;
    Tassociados associados;

    cout << "!AVISO! O CODIGO DA PESSOA E DO VISITANTE E UNICO E NAO PODE SER MUDADO" << endl;
    cout << "Digite seu codigo de Pessoa: ";
    cin >> pessoa.cod_pessoa;
    cout << "Digite seu codigo de Visitante: ";
    cin >> visitantes.cod_visitante;

    char agenda;
    cout << "A visita foi agendada? (Sim ou Nao): ";
    cin >> agenda;
    while (agenda != 'S' && agenda != 's' && agenda != 'N' && agenda != 'n')
    {
        cout << "A visita foi agendada? (Sim ou Nao): ";
        cin >> agenda;
    }
    if (agenda == 'S' || agenda == 's')
    {
        fstream arquivoRegistro;
        arquivoRegistro.open("registrovisitasagendadas.txt", ios::in);
        ofstream arquivoTemp("temp.txt", ios::out | ios::app);
        system("cls");
        arquivoTemp << "!AVISO! Registro com correcao, favor considerar este." << endl;
        cout << "Digite seu codigo de Visitante: ";
        cin >> visitantes.cod_visitante;
        cout << "Digite o codigo do seu Associado: ";
        cin >> associados.cod_associado;
        cout << "Digite a data inicial da visita (dd mm aaaa): ";
        cin >> visitantes.dia_visita_inicial >> visitantes.mes_visita_inicial >> visitantes.ano_visita_inicial;
        cout << "Digite o horario de inicio da visita (hh mm): ";
        cin >> visitantes.hora_inicial >> visitantes.minuto_inicial;
        arquivoTemp << "Codigo de Visitante: " << visitantes.cod_visitante << endl;
        arquivoTemp << "Codigo do Associado: " << associados.cod_associado << endl;
        arquivoTemp << "Data do inicio da visita: " << visitantes.dia_visita_inicial << "/" << visitantes.mes_visita_inicial << "/" << visitantes.ano_visita_inicial << endl;
        arquivoTemp << "Horario do inicio da visita: " << visitantes.hora_inicial << ":" << visitantes.minuto_inicial << endl;
        cout << "Digite a data de termino da visita (dd mm aaaa): ";
        cin >> visitantes.dia_visita_final >> visitantes.mes_visita_final >> visitantes.ano_visita_final;
        cout << "Digite o horario de termino da visita (hh mm): ";
        cin >> visitantes.hora_final >> visitantes.minuto_final;
        arquivoTemp << "Data do termino da visita: " << visitantes.dia_visita_final << "/" << visitantes.mes_visita_final << "/" << visitantes.ano_visita_final << endl;
        arquivoTemp << "Horario do termino da visita: " << visitantes.hora_final << ":" << visitantes.minuto_final << endl;
        arquivoTemp << "---------------------------------------" << endl;
        cout << "\nAlteracao realizada com sucesso!";
        Sleep(2000);
        system("cls");

        arquivoTemp << arquivoRegistro.rdbuf();

        arquivoRegistro.close();
        arquivoTemp.close();

        remove("registrovisitasagendadas.txt");
        rename("temp.txt", "registrovisitasagendadas.txt");
    }

    if (agenda == 'N' || agenda == 'n')
    {
        fstream arquivoRegistro1;
        Tvisitantes visitantes;
        visitantes.cod_visitante = contadorVisitantes++;
        int diaAtual, mesAtual, anoAtual;
        int horas, minutos;
        obterDataAtual(diaAtual, mesAtual, anoAtual);
        obterHorarioAtual(horas, minutos);
        visitantes.dia_visita_inicial = diaAtual;
        visitantes.mes_visita_inicial = mesAtual;
        visitantes.ano_visita_inicial = anoAtual;
        arquivoRegistro1.open("registrovisitas.txt", ios::in); // Abre o arquivo no modo de adiï¿½ï¿½o
        ofstream arquivoTemp("temp.txt", ios::out | ios::app);
        system("cls");
        arquivoTemp << "!AVISO! Registro com correcao, favor considerar este." << endl;
        cout << "Digite o codigo do visitante: ";
        cin >> visitantes.cod_visitante;
        arquivoTemp << "Codigo de Visitante: " << visitantes.cod_visitante << endl;
        cout << "Digite o codigo do Associado: ";
        cin >> associados.cod_associado;
        arquivoTemp << "Codigo do Associado: " << associados.cod_associado << endl;
        cout << "Digite a data de termino da visita (dd mm aaaa): ";
        cin >> visitantes.dia_visita_final2 >> visitantes.mes_visita_final2 >> visitantes.ano_visita_final2;
        cout << "Digite o horario do termino da visita (hh mm): ";
        cin >> visitantes.hora_final2 >> visitantes.minuto_final2;
        cout << "Data de inicio da Visita: " << visitantes.dia_visita_inicial << "/" << visitantes.mes_visita_inicial << "/" << visitantes.ano_visita_inicial << endl;
        arquivoTemp << "Data de inicio da Visita: " << visitantes.dia_visita_inicial << "/" << visitantes.mes_visita_inicial << "/" << visitantes.ano_visita_inicial << endl;
        cout << "Horario de inicio da Visita: " << horas << ":" << minutos << endl;
        cout << "Aproveite sua visita! " << endl;
        arquivoTemp << "Horario de inicio da visita: " << horas << ":" << minutos << endl;
        arquivoTemp << "Data do termino da visita: " << visitantes.dia_visita_final2 << "/" << visitantes.mes_visita_final2 << "/" << visitantes.ano_visita_final2 << endl;
        arquivoTemp << "Horario do termino da visita: " << visitantes.hora_final2 << ":" << visitantes.minuto_final2 << endl;
        arquivoTemp << "---------------------------------------" << endl;
        Sleep(2000);
        system("cls");

        arquivoTemp << arquivoRegistro1.rdbuf();

        arquivoRegistro1.close();
        arquivoTemp.close();

        remove("registrovisitas.txt");
        rename("temp.txt", "registrovisitas.txt");
    }
}

// Funï¿½ï¿½o para cadastrar novas pessoas
void cadastrarPessoas(Tpessoas &pessoa)
{
    pessoa.cod_pessoa = contadorPessoa++;
    fstream arquivopessoas;                                       // Para salvar os dados das pessoas
    arquivopessoas.open("pessoas.txt", ios::out | std::ios::app); // Abre o arquivo no modo de adiï¿½ï¿½o

    // Salvar dados da pessoa no arquivo
    cout << "Insira seu CPF: ";
    cin.ignore(); // Ignora o caractere de nova linha deixado pelo cin anterior
    getline(cin, pessoa.cpf);
    arquivopessoas << "CPF: " << pessoa.cpf << endl;
    cout << "Digite seu nome: ";
    getline(cin, pessoa.nome);
    arquivopessoas << "Nome: " << pessoa.nome << endl;
    cout << "Digite seu endereï¿½o: ";
    getline(cin, pessoa.endereco);
    arquivopessoas << "Endereco: " << pessoa.endereco << endl;
    cout << "Digite seu email: ";
    getline(cin, pessoa.email);
    arquivopessoas << "Email: " << pessoa.email << endl;
    cout << "Digite seu numero de telefone: ";
    getline(cin, pessoa.telefone);
    arquivopessoas << "Telefone: " << pessoa.telefone << endl;
    cout << "Digite seu sexo: ";
    cin >> pessoa.sexo;
    while (!(pessoa.sexo == 'M' || pessoa.sexo == 'm' || pessoa.sexo == 'F' || pessoa.sexo == 'f'))
    {
        cout << "ERRO. Digite M ou F\n";
        cout << "Digite seu sexo: ";
        cin.clear(); // Limpa o estado de erro do cin
        cin.ignore();
        cin >> pessoa.sexo;
    }
    pessoa.sexo_tipo = "";
    if (pessoa.sexo == 'm' || pessoa.sexo == 'M')
        pessoa.sexo_tipo = "Masculino";
    else if (pessoa.sexo == 'f' || pessoa.sexo == 'F')
        pessoa.sexo_tipo = "Feminino";
    arquivopessoas << "Sexo: " << pessoa.sexo_tipo << endl;
    cout << "Digite a sua data de nascimento (dd mm aaaa): ";
    cin >> pessoa.dia_nasc >> pessoa.mes_nasc >> pessoa.ano_nasc;
    arquivopessoas << "Data de nascimento: " << pessoa.dia_nasc << "/" << pessoa.mes_nasc << "/" << pessoa.ano_nasc << endl;
    cout << "Seu codigo de Pessoa serï¿½: " << pessoa.cod_pessoa << endl;
    arquivopessoas << "Codigo de Pessoa: " << pessoa.cod_pessoa << endl;
    arquivopessoas << "---------------------------------------" << endl;
    Sleep(2000);
    arquivopessoas.close(); // Fecha o arquivo
    system("cls");
    int opcao;
    do
    {
        cout << "Escolha uma opcao:\n\n";
        cout << "1 - ASSOCIADO\n";
        cout << "2 - DEPENDENTE\n";
        cout << "3 - VISITANTE\n\n";
        cout << "Opcao: ";
        cin >> opcao;
        system("cls");
        Tassociados associados;
        Tdependentes dependentes;
        Tvisitantes visitantes;
        switch (opcao)
        {
        case 1:
            cadastrarAssociados(associados, pessoa);
            break;
        case 2:
            cadastrarDependentes(dependentes, associados, pessoa);
            break;
        case 3:
            cadastrarVisitantes(visitantes, pessoa);
            break;
        default:
            cout << "Opcao invalida! Por favor, escolha 1, 2 ou 3...";
            Sleep(1500);
            system("cls");
            break;
        }
    } while (opcao < 1 || opcao > 3);
}

// Funï¿½ï¿½o para cadastrar dados especï¿½ficos de associados
void cadastrarAssociados(Tassociados &associados, Tpessoas &pessoa) // Aqui precisar criar uma funï¿½ï¿½o separada para calcular a mensalidade
{
    float taxaFixa = 200.0;
    float taxaPorDependente = 30.0;
    fstream arquivoAssociados;
    associados.cod_associado = contadorAssociados++;

    // Usa o cï¿½digo da pessoa cadastrada
    arquivoAssociados.open("associados.txt", ios::out | std::ios::app); // Abre o arquivo no modo de adiï¿½ï¿½o

    // Salvar dados do associado no arquivo
    cout << "Nome: " << pessoa.nome << endl;
    arquivoAssociados << "Nome: " << pessoa.nome << endl;
    cout << "CPF: " << pessoa.cpf << endl;
    arquivoAssociados << "CPF: " << pessoa.cpf << endl;
    cout << "Codigo de Pessoa: " << pessoa.cod_pessoa << endl;
    arquivoAssociados << "Codigo de Pessoa: " << pessoa.cod_pessoa << endl;
    cout << "Codigo de Associado: " << associados.cod_associado << endl;
    arquivoAssociados << "Codigo de Associado: " << associados.cod_associado << endl;
    cout << "Digite a data de associacao (dd mm aaaa): ";
    cin >> associados.dia_associacao >> associados.mes_associacao >> associados.ano_associacao;
    arquivoAssociados << "Data da Associacao: " << associados.dia_associacao << "/" << associados.mes_associacao << "/" << associados.ano_associacao << endl;
    cout << "Digite quantos dependentes voce tem (Caso nao tenha digite 0): ";
    cin >> associados.numDependentes;
    associados.mensalidade = taxaFixa + (associados.numDependentes * taxaPorDependente);
    cout << "Sua mensalidade sera de: " << associados.mensalidade << endl;
    arquivoAssociados << "Mensalidade: R$ " << associados.mensalidade << endl;
    cout << "Digite seu tipo de Associacao (Digite 'P' para Proprietario ou 'C' para Contribuinte): ";
    cin >> associados.tipo_socio;
    while (!(associados.tipo_socio == 'P' || associados.tipo_socio == 'p' || associados.tipo_socio == 'C' || associados.tipo_socio == 'c'))
    {
        cout << "ERRO. Digite P ou C: \n";
        cout << "Digite seu tipo de Associacao: ";
        cin.clear(); // Limpa o estado de erro do cin
        cin.ignore();
        cin >> associados.tipo_socio;
    }
    string contribuinte = "";
    if (associados.tipo_socio == 'P' || associados.tipo_socio == 'p')
        contribuinte = "Proprietario";
    else if (associados.tipo_socio == 'C' || associados.tipo_socio == 'c')
        contribuinte = "Contribuinte";
    arquivoAssociados << "Tipo de Socio: " << contribuinte << endl;
    arquivoAssociados << "---------------------------------------" << endl;
    cout << "Cadastro realizado com sucesso!";
    Sleep(2000);
    system("cls");
    arquivoAssociados.close(); // Fecha o arquivo
}

// Funï¿½ï¿½o para cadastrar dados especï¿½ficos de dependentes
void cadastrarDependentes(Tdependentes &dependentes, Tassociados &associados, Tpessoas &pessoa)
{
    fstream arquivoDependentes;
    dependentes.cod_dependente = contadorDependentes++;
    // Usa o cï¿½digo da pessoa cadastrada

    // Verificar a maioridade do dependente
    int anoAtual;
    time_t agora = time(0);
    tm *dataAtual = localtime(&agora);
    anoAtual = dataAtual->tm_year + 1900;

    if ((anoAtual - pessoa.ano_nasc) >= 18)
    {
        cout << "Dependente de maior idade. Sera cadastrado como visitante." << endl;
        Tvisitantes visitantes;
        system("cls");
        Sleep(2000);
        cadastrarVisitantes(visitantes, pessoa);
    }
    else
    {
        // Atualiza o nï¿½mero de dependentes do associado
        associados.numDependentes++;
        arquivoDependentes.open("dependentes.txt", ios::out | std::ios::app); // Abre o arquivo no modo de adiï¿½ï¿½o

        // Salvar dados do dependente no arquivo
        cout << "Codigo de Pessoa: " << pessoa.cod_pessoa << endl;
        arquivoDependentes << "Codigo de Pessoa: " << pessoa.cod_pessoa << endl;
        cout << "Nome: " << pessoa.nome << endl;
        arquivoDependentes << "Nome: " << pessoa.nome << endl;
        cout << "Data de nascimento: " << pessoa.dia_nasc << "/" << pessoa.mes_nasc << "/" << pessoa.ano_nasc << endl;
        arquivoDependentes << "Data de nascimento: " << pessoa.dia_nasc << "/" << pessoa.mes_nasc << "/" << pessoa.ano_nasc << endl;
        cout << "Sexo: " << pessoa.sexo_tipo << endl;
        arquivoDependentes << "Sexo: " << pessoa.sexo_tipo << endl;
        cout << "Codigo de Dependente: " << dependentes.cod_dependente << endl;
        arquivoDependentes << "Codigo de Dependente: " << dependentes.cod_dependente << endl;
        cout << "Digite a data de associacao (dd mm aaaa): ";
        cin >> dependentes.dia_associacao_de >> dependentes.mes_associacao_de >> dependentes.ano_associacao_de;
        arquivoDependentes << "Data da Associacao: " << dependentes.dia_associacao_de << "/" << dependentes.mes_associacao_de << "/" << dependentes.ano_associacao_de << endl;
        dependentes.cod_externo = dependentes.ano_associacao_de + dependentes.cod_dependente;
        cout << "Codigo externo: " << dependentes.cod_externo << endl;
        arquivoDependentes << "Codigo Externo: " << dependentes.cod_externo << endl;

        // Aqui precisa criar uma condicional para verificar se o cï¿½digo de associado existe
        cout << "Digite o codigo do Associado que voce esta vinculado: ";
        cin >> dependentes.cod_associado;
        arquivoDependentes << "Codigo de Associado: " << dependentes.cod_associado << endl;
        cout << "Digite o nome do Associado que voce esta vinculado: ";
        cin >> dependentes.nome_associado;
        arquivoDependentes << "Nome Associado: " << dependentes.nome_associado << endl;
        cout << "Digite o CPF do Associado que voce esta vinculado: ";
        cin >> dependentes.cpf_associado;
        arquivoDependentes << "CPF do Associado: " << dependentes.cpf_associado << endl;
        arquivoDependentes << "---------------------------------------" << endl;
        cout << "Cadastro realizado com sucesso!";
        Sleep(2000);
        system("cls");
        arquivoDependentes.close(); // Fecha o arquivo
    }
}

// Funï¿½ï¿½o para cadastrar dados especï¿½ficos de visitantes e registrar visitas
void cadastrarVisitantes(Tvisitantes &visitantes, Tpessoas &pessoa) // Aqui tem coisas para arrumar
{
    fstream arquivoVisitantes;
    visitantes.cod_visitante = contadorVisitantes++;

    // Usa o cï¿½digo da pessoa cadastrada
    arquivoVisitantes.open("visitantes.txt", ios::out | std::ios::app); // Abre o arquivo no modo de adiï¿½ï¿½o

    // Salvar dados do visitante no arquivo
    cout << "Codigo de Pessoa: " << pessoa.cod_pessoa << endl;
    arquivoVisitantes << "Codigo de Pessoa: " << pessoa.cod_pessoa << endl;
    cout << "Nome: " << pessoa.nome << endl;
    arquivoVisitantes << "Nome: " << pessoa.nome << endl;
    cout << "CPF: " << pessoa.cpf << endl;
    arquivoVisitantes << "CPF: " << pessoa.cpf << endl;
    cout << "Data de nascimento: " << pessoa.dia_nasc << "/" << pessoa.mes_nasc << "/" << pessoa.ano_nasc << endl;
    arquivoVisitantes << "Data de nascimento: " << pessoa.dia_nasc << "/" << pessoa.mes_nasc << "/" << pessoa.ano_nasc << endl;
    cout << "Sexo: " << pessoa.sexo_tipo << endl;
    arquivoVisitantes << "Sexo: " << pessoa.sexo_tipo << endl;
    cout << "Codigo de visitante: " << visitantes.cod_visitante << endl;
    arquivoVisitantes << "Codigo de Visitante: " << visitantes.cod_visitante << endl;

    // Aqui precisa criar uma condicional para verficar se o cï¿½digo existe
    cout << "Digite o codigo do Associado: ";
    cin >> visitantes.cod_associado;
    arquivoVisitantes << "Codigo de Associado: " << visitantes.cod_associado << endl;
    cout << "Cadastro realizado com sucesso!";
    Sleep(2000);
    system("cls");
    arquivoVisitantes.close(); // Fecha o arquivo
}

// Funï¿½ï¿½o para fazer o registro de visitas
void registroVisita(Tpessoas &pessoa, Tvisitantes &visitantes, Tassociados &associados)
{
    cout << "Registro de visita\n\n";
    char agenda;
    cout << "Deseja agendar a visita? Se nao, faze-la agora mesmo? (Sim ou Nï¿½o): ";
    cin >> agenda;
    while (agenda != 'S' && agenda != 's' && agenda != 'N' && agenda != 'n')
    {
        cout << "Deseja agendar a visita? Se nao, faze-la agora mesmo? (Sim ou Nï¿½o): ";
        cin >> agenda;
    }
    if (agenda == 'S' || agenda == 's')
    {
        fstream arquivoRegistro;
        arquivoRegistro.open("registrovisitasagendadas.txt", ios::out | ios::app);
        system("cls");
        cout << "Digite seu codigo de Visitante: ";
        cin >> visitantes.cod_visitante;
        cout << "Digite o codigo do seu Associado: ";
        cin >> associados.cod_associado;
        cout << "Digite a data inicial da visita (dd mm aaaa): ";
        cin >> visitantes.dia_visita_inicial >> visitantes.mes_visita_inicial >> visitantes.ano_visita_inicial;
        cout << "Digite o horario de inicio da visita (hh mm): ";
        cin >> visitantes.hora_inicial >> visitantes.minuto_inicial;
        arquivoRegistro << "Codigo de Visitante: " << visitantes.cod_visitante << endl;
        arquivoRegistro << "Codigo do Associado: " << associados.cod_associado << endl;
        arquivoRegistro << "Data do inicio da visita: " << visitantes.dia_visita_inicial << "/" << visitantes.mes_visita_inicial << "/" << visitantes.ano_visita_inicial << endl;
        arquivoRegistro << "Horario do inicio da visita: " << visitantes.hora_inicial << ":" << visitantes.minuto_inicial << endl;
        cout << "Digite a data de termino da visita (dd mm aaaa): ";
        cin >> visitantes.dia_visita_final >> visitantes.mes_visita_final >> visitantes.ano_visita_final;
        cout << "Digite o horario de termino da visita (hh mm): ";
        cin >> visitantes.hora_final >> visitantes.minuto_final;
        arquivoRegistro << "Data do termino da visita: " << visitantes.dia_visita_final << "/" << visitantes.mes_visita_final << "/" << visitantes.ano_visita_final << endl;
        arquivoRegistro << "Horario do termino da visita: " << visitantes.hora_final << ":" << visitantes.minuto_final << endl;
        arquivoRegistro << "---------------------------------------" << endl;
        cout << "\nAgendamento realizado com sucesso!";
        Sleep(2000);
        system("cls");
        arquivoRegistro.close();
    }
    if (agenda == 'N' || agenda == 'n')
    {
        fstream arquivoRegistro1;
        Tvisitantes visitantes;
        visitantes.cod_visitante = contadorVisitantes++;
        int diaAtual, mesAtual, anoAtual;
        int horas, minutos;
        obterDataAtual(diaAtual, mesAtual, anoAtual);
        obterHorarioAtual(horas, minutos);
        visitantes.dia_visita_inicial = diaAtual;
        visitantes.mes_visita_inicial = mesAtual;
        visitantes.ano_visita_inicial = anoAtual;
        arquivoRegistro1.open("registrovisitas.txt", ios::out | ios::app); // Abre o arquivo no modo de adiï¿½ï¿½o
        system("cls");
        cout << "Digite o codigo do visitante: ";
        cin >> visitantes.cod_visitante;
        arquivoRegistro1 << "Codigo de Visitante: " << visitantes.cod_visitante << endl;
        cout << "Digite o codigo do Associado: ";
        cin >> associados.cod_associado;
        arquivoRegistro1 << "Codigo do Associado: " << associados.cod_associado << endl;
        cout << "Digite a data de termino da visita (dd mm aaaa): ";
        cin >> visitantes.dia_visita_final2 >> visitantes.mes_visita_final2 >> visitantes.ano_visita_final2;
        cout << "Digite o horario do termino da visita (hh mm): ";
        cin >> visitantes.hora_final2 >> visitantes.minuto_final2;
        cout << "Data de inicio da Visita: " << visitantes.dia_visita_inicial << "/" << visitantes.mes_visita_inicial << "/" << visitantes.ano_visita_inicial << endl;
        arquivoRegistro1 << "Data de inicio da Visita: " << visitantes.dia_visita_inicial << "/" << visitantes.mes_visita_inicial << "/" << visitantes.ano_visita_inicial << endl;
        cout << "Horario de inicio da Visita: " << horas << ":" << minutos << endl;
        cout << "Aproveite sua visita! " << endl;
        arquivoRegistro1 << "Horario de inicio da visita: " << horas << ":" << minutos << endl;
        arquivoRegistro1 << "Data do termino da visita: " << visitantes.dia_visita_final2 << "/" << visitantes.mes_visita_final2 << "/" << visitantes.ano_visita_final2 << endl;
        arquivoRegistro1 << "Horario do termino da visita: " << visitantes.hora_final2 << ":" << visitantes.minuto_final2 << endl;
        arquivoRegistro1 << "---------------------------------------" << endl;
        Sleep(2000);
        system("cls");
        arquivoRegistro1.close();
    }
}

// Funï¿½ï¿½o para ler o valor mais alto do arquivo de pessoas
void lerContadorPessoa()
{
    ifstream arquivoPessoas("pessoas.txt");
    if (arquivoPessoas.is_open())
    {
        int maxCodPessoa = 10000;
        string line;
        while (getline(arquivoPessoas, line))
        {
            if (line.find("Codigo de Pessoa: ") != string::npos)
            {
                int codPessoa;
                sscanf(line.c_str(), "Codigo de Pessoa: %d", &codPessoa);
                if (codPessoa > maxCodPessoa)
                {
                    maxCodPessoa = codPessoa;
                }
            }
        }
        arquivoPessoas.close();
        contadorPessoa = maxCodPessoa + 1;
    }
}

// Funï¿½ï¿½o para ler o valor mais alto do arquivo de associados
void lerContadorAssociados()
{
    ifstream arquivoAssociados("associados.txt");
    if (arquivoAssociados.is_open())
    {
        int maxCodAssociado = 10000;
        string line;
        while (getline(arquivoAssociados, line))
        {
            if (line.find("Codigo de Associado:") != string::npos)
            {
                int codAssociado;
                sscanf(line.c_str(), "Codigo de Associado: %d", &codAssociado);
                if (codAssociado > maxCodAssociado)
                {
                    maxCodAssociado = codAssociado;
                }
            }
        }
        arquivoAssociados.close();
        // Incrementa o contador antes de atribuir ao contadorAssociados
        contadorAssociados = maxCodAssociado + 1;
    }
}

// Funï¿½ï¿½o para ler o valor mais alto do arquivo de dependentes
void lerContadorDependentes()
{
    ifstream arquivoDependentes("dependentes.txt");
    if (arquivoDependentes.is_open())
    {
        int maxCodDependente = 10000;
        string line;
        while (getline(arquivoDependentes, line))
        {
            if (line.find("Codigo de Dependente:") != string::npos)
            {
                int codDependente;
                sscanf(line.c_str(), "Codigo de Dependente: %d", &codDependente);
                if (codDependente > maxCodDependente)
                {
                    maxCodDependente = codDependente;
                }
            }
        }
        arquivoDependentes.close();
        contadorDependentes = maxCodDependente + 1;
    }
}

// Funï¿½ï¿½o para ler o valor mais alto do arquivo de visitantes
void lerContadorVisitantes()
{
    ifstream arquivoVisitantes("visitantes.txt");
    if (arquivoVisitantes.is_open())
    {
        int maxCodVisitante = 10000;
        string line;
        while (getline(arquivoVisitantes, line))
        {
            if (line.find("Codigo de Visitante:") != string::npos)
            {
                int codVisitante;
                sscanf(line.c_str(), "Codigo de Visitante: %d", &codVisitante);
                if (codVisitante > maxCodVisitante)
                {
                    maxCodVisitante = codVisitante;
                }
            }
        }
        arquivoVisitantes.close();
        contadorVisitantes = maxCodVisitante + 1;
    }
}

// Funï¿½ï¿½o para obter data atual
void obterDataAtual(int &dia, int &mes, int &ano)
{
    time_t t = time(0);
    tm *now = localtime(&t);
    dia = now->tm_mday;
    mes = now->tm_mon + 1;     // O mï¿½s ï¿½ base 0
    ano = now->tm_year + 1900; // Contagem de anos desde 1900
}

// Funï¿½ï¿½o para obter horï¿½rio atual
void obterHorarioAtual(int &horas, int &minutos)
{
    time_t t = time(0);
    tm *now = localtime(&t);
    horas = now->tm_hour;
    minutos = now->tm_min;
}

void obterDataAtual2(int &dia2, int &mes2, int &ano2)
{
    time_t agora = time(0);
    tm *dataAtual2 = localtime(&agora);
    dia2 = dataAtual2->tm_mday;
    mes2 = dataAtual2->tm_mon + 1;     // O mï¿½s ï¿½ base 0, entï¿½o adicionamos 1
    ano2 = dataAtual2->tm_year + 1900; // Contagem de anos desde 1900
}

void obterHorarioAtual2(int &horas2, int &minutos2)
{
    time_t agora = time(0);
    tm *horarioAtual2 = localtime(&agora);
    horas2 = horarioAtual2->tm_hour;
    minutos2 = horarioAtual2->tm_min;
}
