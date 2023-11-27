//Trabalho de Algoritmos e Estrutura De Dados II, menu Associados, Dependentes e
//Visitantes.
//Alunos:
//João Pablo Soares Lino - Turma A
//Pedro Ângelo Tellaroli Vargas - Turma A
//Pedro Henrique Teixeira Da Silva - Turma B

//Declaração das bibliotecas ultilizadas para construção do código
#include <iostream>
#include <locale.h>
#include <fstream>
#include <stdlib.h>
#include <windows.h>
#include <ctime>
#include <string>
#include <math.h>

//Declaração do STD para não precisarmos ficar ultilizando ele toda hora
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

// Protótipos das funções
void MenuPrincipal();
void SubMenu1();
void SubMenu2();
void SubMenu3();
void SubMenu4();
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

//lerContadorDependentes, lerContadorVisitantes e lerContadorPessoa.
static int contadorAssociados = 10000;
static int contadorDependentes = 10000;
static int contadorVisitantes = 10000;
static int contadorPessoa = 10000;

//Função principal
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
		cout << "Menu Principal:\n\n";
		cout << "1 - Cadastro de Pessoas" << endl;
		cout << "2 - Relatório de dependentes/associados" << endl;
		cout << "3 - Relatório de visitas por associado" << endl;
        cout << "4 - Editar Cadastro" << endl;
		cout << "0 - Sair\n\n";
		cout << "Escolha uma opção: ";
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
		case 0:
			break;
		default:
			cout << "Opção Inválida...\n";
			Sleep(2000);
			system("cls");
			break;
		}
	}
	while(opcao != 0);
}

//Função do menu cadastro de pessoas
void SubMenu1()
{
	int subOpcao1;
	do
	{
		cout << "CADASTRO DE PESSOAS\n\n";
		cout << "1 - Cadastrar pessoas\n";
		cout << "2 - Registra visita\n";
		cout << "0 - Voltar ao menu principal\n\n";
		cout << "Escolha uma opção: ";
		cin >> subOpcao1;
		system("cls");
		Tpessoas novaPessoa;
		Tvisitantes visitantes;
		Tassociados associados;
		switch(subOpcao1)
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
			cout << "Opção inválida!\n";
			break;
		}
	}
	while(subOpcao1 != 0);
}

//Função para gerar relatório de dependentes/associados
void SubMenu2()
{
	string tecla;
	fstream arquivoAssociados("associados.txt", ios::in);
	fstream arquivoDependentes("dependentes.txt", ios::in);
	if (!arquivoAssociados.is_open() || !arquivoDependentes.is_open())
	{
		cout << "Erro ao abrir os arquivos. Certifique-se de que os arquivos associados.txt e dependentes.txt existem.\n";
		Sleep(2000);
		system("cls");
		return;
	}
	cout << "Relatório de Dependentes/Associados\n\n";

	// Exibir informações dos associados
	cout << "Associados: \n";
	while (!arquivoAssociados.eof())
	{
		string line;
		getline(arquivoAssociados, line);
		cout << line << endl;
	}
	arquivoAssociados.close();

	// Exibir informações dos dependentes
	cout << "\nDependentes: \n";
	while (!arquivoDependentes.eof())
	{
		string line;
		getline(arquivoDependentes, line);
		cout << line << endl;
	}
	arquivoDependentes.close();
	cout << "\nFim do Relatório\n";
	cout << "Aperte qualquer tecla pra retornar ao Menu Principal..." << endl;
	cin >> tecla;
	system("cls");
}

//Função para gerar relatório de dependentes/associados
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

	// Exibir informações dos dependentes
	cout << "\nRegistro de visitas realizadas:\n\n";
	while (!arquivoRegistro1.eof())
	{
		string line;
		getline(arquivoRegistro1, line);
		cout << line << endl;
	}
	arquivoRegistro1.close();
	cout << "Fim do Relatório\n";
	cout << "Aperte qualquer tecla pra retornar ao Menu Principal..." << endl;
	cin >> tecla2;
	system("cls");
}

void SubMenu4() {
    int escolha;
    do{
    system("cls");
    cout << "\nEdicao de Cadastro!" << endl;
    cout << "\nOpcoes: " << endl;
    cout << "1 - Pessoas" << endl;
    cout << "2 - Associados" << endl;
    cout << "3 - Dependentes" << endl;
    cout << "4 - Visitantes" << endl;
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
    }while(escolha != 0);
}

void editaPessoa() {
    system("cls");
    int EscPessoa;
    Tpessoas pessoa;
    fstream arquivoEditaPessoa;
    arquivoEditaPessoa.open("EditadoPessoa.txt", ios::out | ios::app);
    cout << "!AVISO! O CODIGO DA PESSOA É UNICO E NAO PODE SER MUDADO" << endl;
    cout << "Digite seu codigo de Pessoa: ";
    cin >> pessoa.cod_pessoa;
    arquivoEditaPessoa << "Codigo da Pessoa: " << pessoa.cod_pessoa << endl;
    cout << "Opcoes: " << endl;
    cout << "1 - CPF " << endl;
    cout << "2 - Nome " << endl;
    cout << "3 - Endereço " << endl;
    cout << "4 - Email " << endl;
    cout << "5 - Telefone " << endl;
    cout << "6 - Sexo " << endl;
    cout << "7 - Data de Nascimento " << endl;
    cout << "0 - Sair " << endl;
    cout << "_________________________________________" << endl;
    cin >> EscPessoa;
    do {
     switch(EscPessoa)
     {
        case 1:
        cout << "CPF: ";
        cin >> pessoa.cpf;
        arquivoEditaPessoa << "CPF: " << pessoa.cpf << endl;
        arquivoEditaPessoa << "_________________________________________" << endl;
        return;
        break ;
        case 2:
        cout << "Nome: ";
        cin >> pessoa.nome;
        arquivoEditaPessoa << "Nome: " << pessoa.nome << endl;
        arquivoEditaPessoa << "_________________________________________" << endl; 
        return;
        break;
        case 3:
        cout << "Endereco: ";
        cin >> pessoa.endereco;
        arquivoEditaPessoa << "Endereco: " << pessoa.endereco << endl;
        arquivoEditaPessoa << "_________________________________________" << endl;
         return;
        break;
        case 4:
        cout << "Email: ";
        cin >> pessoa.email;
        arquivoEditaPessoa << "Email: " << pessoa.email << endl;
        arquivoEditaPessoa << "_________________________________________" << endl;
         return;
        break;
        case 5:
        cout << "Telefone: ";
        cin >> pessoa.telefone;
        arquivoEditaPessoa << "Telefone: " << pessoa.telefone << endl;
        arquivoEditaPessoa << "_________________________________________" << endl;
         return;
        break;
        case 6:
        cout << "Sexo(M/F): ";
        cin >> pessoa.sexo;
        while (!(pessoa.sexo == 'M' || pessoa.sexo == 'm' || pessoa.sexo == 'F' || pessoa.sexo == 'f'))
	{
		cout << "ERRO. Digite M ou F\n";
		cout << "Sexo(M/F): ";
		cin.clear();  // Limpa o estado de erro do cin
		cin.ignore();
		cin >> pessoa.sexo;
	}
	pessoa.sexo_tipo = "";
	if(pessoa.sexo == 'm' || pessoa.sexo == 'M')
		pessoa.sexo_tipo = "Masculino";
	else if(pessoa.sexo == 'f' || pessoa.sexo == 'F')
		pessoa.sexo_tipo = "Feminino";
        arquivoEditaPessoa << "Sexo: " << pessoa.sexo_tipo << endl;
        arquivoEditaPessoa << "_________________________________________" << endl;
        return;
        break;
        case 7:
        cout << "Data de Nascimento (dd mm aaaa): ";
        cin >> pessoa.dia_nasc >> pessoa.mes_nasc >> pessoa.ano_nasc;
        arquivoEditaPessoa << "Data de Nascimento " << pessoa.dia_nasc << "/" << pessoa.mes_nasc << "/" << pessoa.ano_nasc << endl;
        arquivoEditaPessoa << "_________________________________________" << endl;
         return;
        break;
        case 0:
        break;
        default:
        break;
     }
    }while(EscPessoa != 0);
   arquivoEditaPessoa.close();
}

void editaAssociado() {
    system("cls");
    int soma;
    int EscAssociado;
    Tpessoas pessoa;
    Tassociados associado;
    fstream arquivoEditaAssociado;
    arquivoEditaAssociado.open("EditadoAssociado.txt", ios::out | ios::app);
    cout << "!AVISO! O CODIGO DA PESSOA E DO ASSOCIADO É UNICO E NAO PODE SER MUDADO" << endl;
    cout << "Digite seu codigo de Pessoa: ";
    cin >> pessoa.cod_pessoa;
    cout << "Digite seu codigo de Associado: ";
    cin >> associado.cod_associado;
    arquivoEditaAssociado << "Codigo da Pessoa: " << pessoa.cod_pessoa << endl;
    arquivoEditaAssociado << "Codigo do Associado: " << associado.cod_associado << endl;
    cout << "Opcoes: " << endl;
    cout << "1 - Tipo de Socio(P/C): " << endl;
    cout << "2 - Numero de Dependentes (Caso tenha algum falecimento): " << endl;
    cout << "3 - Data da Associação (dd mm aaaa): " << endl;
    cout << "0 - Sair " << endl;
    cout << "_________________________________________" << endl;
    cin >> EscAssociado;
    do {
     switch(EscAssociado)
     {
        case 1:
        cout << "Tipo de Socio(P/C): ";
        cin >> associado.tipo_socio;
        arquivoEditaAssociado << "Tipo de Sócio: " << associado.tipo_socio << endl;
        arquivoEditaAssociado << "_________________________________________" << endl;
        return;
        break ;
        case 2:
        cout << "Numero de dependentes: ";
        cin >> associado.numDependentes;
        soma = 200 + (associado.numDependentes*30);
        cout << "Sua nova mensalidade será de R$" << soma << endl;
        Sleep(3000);
        arquivoEditaAssociado << "Numero de dependentes: " << associado.numDependentes << endl;
        arquivoEditaAssociado << "Nova mensalidade: " << soma << endl;
        arquivoEditaAssociado << "_________________________________________" << endl; 
        return;
        break;
        case 3:
        cout << "Data da AssociaÇão(dd mm aaaa): ";
        cin >> associado.dia_associacao >> associado.mes_associacao >> associado.ano_associacao;
        arquivoEditaAssociado << "Data da Associação: " << associado.dia_associacao << "/" << associado.mes_associacao << "/" << associado.ano_associacao << endl;
        arquivoEditaAssociado << "_________________________________________" << endl;
        return;
        break;
        case 0:
        break;
        default:
        break;
     }
    }while(EscAssociado != 0);
   arquivoEditaAssociado.close();
}

void editaDependente() {
    system("cls");
    int soma;
    int EscDependente;
    Tpessoas pessoa;
    Tdependentes dependente;
    fstream arquivoEditaDependente;
    arquivoEditaDependente.open("EditadoDependente.txt", ios::out | ios::app);
    cout << "!AVISO! O CODIGO DA PESSOA E DO DEPENDENTE É UNICO E NAO PODE SER MUDADO" << endl;
    cout << "Digite seu codigo de Pessoa: ";
    cin >> pessoa.cod_pessoa;
    cout << "Digite seu codigo de Dependente ";
    cin >> dependente.cod_dependente;
    arquivoEditaDependente << "Codigo da Pessoa: " << pessoa.cod_pessoa << endl;
    arquivoEditaDependente << "Codigo do Dependente " << dependente.cod_dependente << endl;
    cout << "Opcoes: " << endl;
    cout << "1 - CPF do Associado: " << endl;
    cout << "2 - Data de Associação(dd mm aaaa): " << endl;
    cout << "0 - Sair " << endl;
    cout << "_________________________________________" << endl;
    cin >> EscDependente;
    do {
     switch(EscDependente)
     {
        case 1:
        cout << "CPF do Associado: ";
        cin >> pessoa.cpf;
        arquivoEditaDependente << "CPF do Associado: " << pessoa.cpf << endl;
        arquivoEditaDependente << "_________________________________________" << endl;
        return;
        break ;
        case 2:
        cout << "Data da Associação: ";
        cin >> dependente.dia_associacao_de >> dependente.mes_associacao_de >> dependente.ano_associacao_de;
        soma = dependente.cod_dependente + dependente.ano_associacao_de;
        cout << "Seu novo codigo Externo será:  "<< soma << endl;
        Sleep(3000);
        arquivoEditaDependente << "Data da Associação: " << dependente.dia_associacao_de << "/" << dependente.mes_associacao_de << "/" << dependente.ano_associacao_de << endl;
        arquivoEditaDependente << "Novo Codigo Externo:  " << soma << endl;
        arquivoEditaDependente << "_________________________________________" << endl; 
        return;
        break;
        case 0:
        break;
        default:
        break;
     }
    }while(EscDependente != 0);
   arquivoEditaDependente.close();
}

void editaVisita() {
    system("cls");
    int EscVisita;
    Tpessoas pessoa;
    Tvisitantes visitantes;
    fstream arquivoEditaVisita;
    arquivoEditaVisita.open("EditadoVisita.txt", ios::out | ios::app);
    cout << "!AVISO! O CODIGO DA PESSOA E DO VISITANTE É UNICO E NAO PODE SER MUDADO" << endl;
    cout << "Digite seu codigo de Pessoa: ";
    cin >> pessoa.cod_pessoa;
    cout << "Digite seu codigo de Visitante: ";
    cin >> visitantes.cod_visitante;
    arquivoEditaVisita << "Codigo da Pessoa: " << pessoa.cod_pessoa << endl;
    arquivoEditaVisita << "Codigo do Visitante: " << visitantes.cod_visitante << endl;
    cout << "Opcoes: " << endl;
    cout << "1 - Data do inicio da Visita(dd mm aaaa): " << endl;
    cout << "2 - Data do termino da Visita(dd mm aaaa): " << endl;
    cout << "3 - Horario Inicial da Visita(hh mm): " << endl;
    cout << "4 _ Horario Final da Visita(hh mm):  " << endl;
    cout << "0 - Sair " << endl;
    cout << "_________________________________________" << endl;
    cin >> EscVisita;
    do {
     switch(EscVisita)
     {
        case 1:
    
        cout << "Data do inicio da Visita(dd mm aaaa): ";
        cin >> visitantes.dia_visita_inicial >> visitantes.mes_visita_inicial >> visitantes.ano_visita_inicial; 
        arquivoEditaVisita << "Data Visita Inicial: " << visitantes.dia_visita_inicial << "/" << visitantes.mes_visita_inicial << "/" << visitantes.ano_visita_inicial << endl; 
        arquivoEditaVisita << "_________________________________________" << endl;
        return;
        break ;
        case 2:
        cout << "Data do término da Visita(dd mm aaaa): ";
        cin >> visitantes.dia_visita_final >> visitantes.mes_visita_final >> visitantes.ano_visita_final;
        arquivoEditaVisita << "Data do término da Visita:  " << visitantes.dia_visita_final << "/" << visitantes.mes_visita_final << "/" << visitantes.ano_visita_final << endl; 
        arquivoEditaVisita << "_________________________________________" << endl; 
        return;
        break; 
        case 3:
        cout << "Horario do inicio da visita(hh mm): ";
        cin >> visitantes.hora_inicial >> visitantes.minuto_inicial;
        arquivoEditaVisita << "Horario Inicial: " << visitantes.hora_inicial << ":" << visitantes.minuto_inicial << endl;
        arquivoEditaVisita << "_________________________________________" << endl; 
        return;
        break;
        case 4:
        cout << "Horario do termino da visita(hh mm): ";
        cin >> visitantes.hora_final>> visitantes.minuto_final;
        arquivoEditaVisita << "Horario Final: " << visitantes.hora_final << ":" << visitantes.minuto_final << endl;
        arquivoEditaVisita << "_________________________________________" << endl; 
        return;
        break;
        case 0:
        break;
        default:
        break;
     }
    }while(EscVisita != 0);
   arquivoEditaVisita.close();
}

// Função para cadastrar novas pessoas
void cadastrarPessoas(Tpessoas &pessoa)
{
	pessoa.cod_pessoa = contadorPessoa++;
	fstream arquivopessoas; // Para salvar os dados das pessoas
	arquivopessoas.open("pessoas.txt", ios::out | std::ios::app); // Abre o arquivo no modo de adição
	
	// Salvar dados da pessoa no arquivo
	cout << "Insira seu CPF: ";
	cin.ignore();  // Ignora o caractere de nova linha deixado pelo cin anterior
	getline(cin, pessoa.cpf);
	arquivopessoas << "CPF: " << pessoa.cpf << endl;
	cout << "Digite seu nome: ";
	getline(cin, pessoa.nome);
	arquivopessoas << "Nome: " << pessoa.nome << endl;
	cout << "Digite seu endereço: ";
	getline(cin, pessoa.endereco);
	arquivopessoas << "Endereço: " << pessoa.endereco << endl;
	cout << "Digite seu email: ";
	getline(cin, pessoa.email);
	arquivopessoas << "Email: " << pessoa.email << endl;
	cout << "Digite seu número de telefone: ";
	getline(cin, pessoa.telefone);
	arquivopessoas << "Telefone: " << pessoa.telefone << endl;
	cout << "Digite seu sexo: ";
	cin >> pessoa.sexo;
	while (!(pessoa.sexo == 'M' || pessoa.sexo == 'm' || pessoa.sexo == 'F' || pessoa.sexo == 'f'))
	{
		cout << "ERRO. Digite M ou F\n";
		cout << "Digite seu sexo: ";
		cin.clear();  // Limpa o estado de erro do cin
		cin.ignore();
		cin >> pessoa.sexo;
	}
	pessoa.sexo_tipo = "";
	if(pessoa.sexo == 'm' || pessoa.sexo == 'M')
		pessoa.sexo_tipo = "Masculino";
	else if(pessoa.sexo == 'f' || pessoa.sexo == 'F')
		pessoa.sexo_tipo = "Feminino";
	arquivopessoas << "Sexo: " << pessoa.sexo_tipo << endl;
	cout << "Digite a sua data de nascimento (dd mm aaaa): ";
	cin >> pessoa.dia_nasc >> pessoa.mes_nasc >> pessoa.ano_nasc;
	arquivopessoas << "Data de nascimento: " << pessoa.dia_nasc << "/" << pessoa.mes_nasc << "/" << pessoa.ano_nasc << endl;
	cout << "Seu código de Pessoa será: " << pessoa.cod_pessoa << endl;
	arquivopessoas << "Código de Pessoa: " << pessoa.cod_pessoa << endl;
	arquivopessoas << "---------------------------------------" << endl;
	Sleep(2000);
	arquivopessoas.close(); // Fecha o arquivo
	system("cls");
	int opcao;
	do
	{
		cout << "Escolha uma opção:\n\n";
		cout << "1 - ASSOCIADO\n";
		cout << "2 - DEPENDENTE\n";
		cout << "3 - VISITANTE\n\n";
		cout << "Opção: ";
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
			cout << "Opção inválida! Por favor, escolha 1, 2 ou 3...";
			Sleep(1500);
			system("cls");
			break;
		}
	}
	while (opcao < 1 || opcao > 3);
}



// Função para cadastrar dados específicos de associados
void cadastrarAssociados(Tassociados &associados, Tpessoas &pessoa)   // Aqui precisar criar uma função separada para calcular a mensalidade
{
	float taxaFixa = 200.0;
    float taxaPorDependente = 30.0;
	fstream arquivoAssociados;
	associados.cod_associado = contadorAssociados++;
	
	// Usa o código da pessoa cadastrada
	arquivoAssociados.open("associados.txt", ios::out | std::ios::app); // Abre o arquivo no modo de adição

	// Salvar dados do associado no arquivo
	cout << "Nome: " << pessoa.nome << endl;
	arquivoAssociados << "Nome: " << pessoa.nome << endl;
	cout << "CPF: " << pessoa.cpf << endl;
	arquivoAssociados << "CPF: " << pessoa.cpf << endl;
	cout << "Código de Pessoa: " << pessoa.cod_pessoa << endl;
	arquivoAssociados << "Código de Pessoa: " << pessoa.cod_pessoa << endl;
	cout << "Código de Associado: " << associados.cod_associado << endl;
	arquivoAssociados << "Código de Associado: " << associados.cod_associado << endl;
	cout << "Digite a data de associação (dd mm aaaa): ";
	cin >> associados.dia_associacao >> associados.mes_associacao >> associados.ano_associacao;
	arquivoAssociados << "Data da Associação: " << associados.dia_associacao << "/" << associados.mes_associacao << "/" << associados.ano_associacao << endl;
	cout << "Digite quantos dependentes voce tem (Caso nao tenha digite 0): ";
    cin >> associados.numDependentes;
	associados.mensalidade = taxaFixa + (associados.numDependentes * taxaPorDependente);
	cout << "Sua mensalidade sera de: " << associados.mensalidade << endl;
    arquivoAssociados << "Mensalidade: R$ " << associados.mensalidade << endl;
	cout << "Digite seu tipo de Associação (Digite 'P' para Proprietário ou 'C' para Contribuinte): ";
	cin >> associados.tipo_socio;
	while (!(associados.tipo_socio == 'P' || associados.tipo_socio == 'p' || associados.tipo_socio == 'C' || associados.tipo_socio == 'c'))
	{
		cout << "ERRO. Digite P ou C: \n";
		cout << "Digite seu tipo de Associação: ";
		cin.clear();  // Limpa o estado de erro do cin
		cin.ignore();
		cin >> associados.tipo_socio;
	}
	string contribuinte = "";
	if(associados.tipo_socio == 'P' || associados.tipo_socio == 'p')
		contribuinte = "Proprietário";
	else if(associados.tipo_socio == 'C' || associados.tipo_socio == 'c')
		contribuinte = "Contribuinte";
	arquivoAssociados << "Tipo de Sócio: " << contribuinte << endl;
	arquivoAssociados << "---------------------------------------" << endl;
	cout << "Cadastro realizado com sucesso!";
	Sleep(2000);
	system("cls");
	arquivoAssociados.close(); // Fecha o arquivo
}

// Função para cadastrar dados específicos de dependentes
void cadastrarDependentes(Tdependentes &dependentes, Tassociados &associados, Tpessoas &pessoa)
{
	fstream arquivoDependentes;
	dependentes.cod_dependente = contadorDependentes++;
	// Usa o código da pessoa cadastrada

	//Verificar a maioridade do dependente
	int anoAtual;
	time_t agora = time(0);
	tm *dataAtual = localtime(&agora);
	anoAtual = dataAtual->tm_year + 1900;

	if((anoAtual - pessoa.ano_nasc) >= 18)
	{
		cout << "Dependente de maior idade. Será cadastrado como visitante." << endl;
		Tvisitantes visitantes;
		system("cls");
		Sleep(2000);
		cadastrarVisitantes(visitantes, pessoa);
	}
	else
	{
		//Atualiza o número de dependentes do associado
		associados.numDependentes++;
		arquivoDependentes.open("dependentes.txt", ios::out | std::ios::app); // Abre o arquivo no modo de adição

		// Salvar dados do dependente no arquivo
		cout << "Código de Pessoa: " << pessoa.cod_pessoa << endl;
		arquivoDependentes << "Código de Pessoa: " << pessoa.cod_pessoa << endl;
		cout << "Nome: " << pessoa.nome << endl;
		arquivoDependentes << "Nome: " << pessoa.nome << endl;
		cout << "Data de nascimento: " << pessoa.dia_nasc << "/" << pessoa.mes_nasc << "/" << pessoa.ano_nasc << endl;
		arquivoDependentes << "Data de nascimento: " << pessoa.dia_nasc << "/" << pessoa.mes_nasc << "/" << pessoa.ano_nasc << endl;
		cout << "Sexo: " << pessoa.sexo_tipo << endl;
		arquivoDependentes << "Sexo: " << pessoa.sexo_tipo << endl;
		cout << "Código de Dependente: " << dependentes.cod_dependente << endl;
		arquivoDependentes << "Código de Dependente: " << dependentes.cod_dependente << endl;
		cout << "Digite a data de associação (dd mm aaaa): ";
		cin >> dependentes.dia_associacao_de >> dependentes.mes_associacao_de >> dependentes.ano_associacao_de;
		arquivoDependentes << "Data da Associação: " << dependentes.dia_associacao_de << "/" << dependentes.mes_associacao_de << "/" << dependentes.ano_associacao_de << endl;
		dependentes.cod_externo = dependentes.ano_associacao_de + dependentes.cod_dependente;
		cout << "Código externo: " << dependentes.cod_externo << endl;
		arquivoDependentes << "Código Externo: " << dependentes. cod_externo << endl;

		// Aqui precisa criar uma condicional para verificar se o código de associado existe
		cout << "Digite o código do Associado que você está vinculado: " << endl;
		cin >> dependentes.cod_associado;
		arquivoDependentes << "Código de Associado: " << dependentes.cod_associado << endl;
		cout << "Cadastro realizado com sucesso!";
		Sleep(2000);
		system("cls");
		arquivoDependentes.close(); // Fecha o arquivo
	}
}

// Função para cadastrar dados específicos de visitantes e registrar visitas
void cadastrarVisitantes(Tvisitantes &visitantes, Tpessoas &pessoa)   // Aqui tem coisas para arrumar
{
	fstream arquivoVisitantes;
	visitantes.cod_visitante = contadorVisitantes++;
	
	// Usa o código da pessoa cadastrada
	arquivoVisitantes.open("visitantes.txt", ios::out | std::ios::app); // Abre o arquivo no modo de adição

	// Salvar dados do visitante no arquivo
	cout << "Código de Pessoa: " << pessoa.cod_pessoa << endl;
	arquivoVisitantes << "Código de Pessoa: " << pessoa.cod_pessoa << endl;
	cout << "Nome: " << pessoa.nome << endl;
	arquivoVisitantes << "Nome: " << pessoa.nome << endl;
	cout << "CPF: " << pessoa.cpf << endl;
	arquivoVisitantes << "CPF: " << pessoa.cpf << endl;
	cout << "Data de nascimento: " << pessoa.dia_nasc << "/" << pessoa.mes_nasc << "/" << pessoa.ano_nasc << endl;
	arquivoVisitantes << "Data de nascimento: " << pessoa.dia_nasc << "/" << pessoa.mes_nasc << "/" << pessoa.ano_nasc << endl;
	cout << "Sexo: " << pessoa.sexo_tipo << endl;
	arquivoVisitantes << "Sexo: " << pessoa.sexo_tipo << endl;
	cout << "Código de visitante: " << visitantes.cod_visitante << endl;
	arquivoVisitantes << "Código de Visitante: " << visitantes.cod_visitante << endl;

	// Aqui precisa criar uma condicional para verficar se o código existe
	cout << "Digite o código do Associado: ";
	cin >> visitantes.cod_associado;
	arquivoVisitantes << "Código de Associado: " << visitantes.cod_associado << endl;
	cout << "Cadastro realizado com sucesso!";
	Sleep(2000);
	system("cls");
	arquivoVisitantes.close(); // Fecha o arquivo
}

// Função para fazer o registro de visitas
void registroVisita(Tpessoas &pessoa, Tvisitantes &visitantes, Tassociados &associados)
{
	cout << "Registro de visita\n\n";
	char agenda;
	cout << "Deseja agendar a visita? Se não, fazê-la agora mesmo? (Sim ou Não): ";
	cin >> agenda;
	while(agenda!='S'&&agenda!='s'&&agenda!='N'&&agenda!='n')
	{
		cout << "Deseja agendar a visita? Se não, fazê-la agora mesmo? (Sim ou Não): ";
		cin >> agenda;
	}
	if(agenda == 'S' || agenda == 's')
	{
		fstream arquivoRegistro;
		arquivoRegistro.open("registrovisitasagendadas.txt", ios::out | ios::app);
		system("cls");
		cout << "Digite seu código de Visitante: ";
		cin >> visitantes.cod_visitante;
		cout << "Digite o código do seu Associado: ";
		cin >> associados.cod_associado;
		cout << "Digite a data inicial da visita (dd mm aaaa): ";
		cin >> visitantes.dia_visita_inicial >> visitantes.mes_visita_inicial >> visitantes.ano_visita_inicial;
		cout << "Digite o horário de início da visita (hh mm): ";
		cin >> visitantes.hora_inicial >> visitantes.minuto_inicial;
		arquivoRegistro << "Código de Visitante: " << visitantes.cod_visitante << endl;
		arquivoRegistro << "Código do Associado: " << associados.cod_associado << endl;
		arquivoRegistro << "Data do início da visita: " << visitantes.dia_visita_inicial << "/" << visitantes.mes_visita_inicial << "/" << visitantes.ano_visita_inicial << endl;
		arquivoRegistro << "Horário do início da visita: " << visitantes.hora_inicial << ":" << visitantes.minuto_inicial << endl;
		cout << "Digite a data de término da visita (dd mm aaaa): ";
		cin >> visitantes.dia_visita_final >> visitantes.mes_visita_final >> visitantes.ano_visita_final;
		cout << "Digite o horário de término da visita (hh mm): ";
		cin >> visitantes.hora_final >> visitantes.minuto_final;
		arquivoRegistro << "Data do término da visita: " << visitantes.dia_visita_final << "/" << visitantes.mes_visita_final << "/" << visitantes.ano_visita_final << endl;
		arquivoRegistro << "Horário do término da visita: " << visitantes.hora_final << ":" << visitantes.minuto_final << endl;
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
		arquivoRegistro1.open("registrovisitas.txt", ios::out | ios::app); // Abre o arquivo no modo de adição
		system("cls");
		cout << "Digite o código do visitante: ";
		cin >> visitantes.cod_visitante;
		arquivoRegistro1 << "Código de Visitante: " << visitantes.cod_visitante << endl;
		cout << "Digite o código do Associado: ";
		cin >> associados.cod_associado;
		arquivoRegistro1 << "Código do Associado: " << associados.cod_associado << endl;
		cout << "Digite a data de término da visita (dd mm aaaa): ";
		cin >> visitantes.dia_visita_final2 >> visitantes.mes_visita_final2 >> visitantes.ano_visita_final2;
		cout << "Digite o horário do término da visita (hh mm): ";
		cin >> visitantes.hora_final2 >> visitantes.minuto_final2;
		cout << "Data de início da Visita: " << visitantes.dia_visita_inicial << "/" << visitantes.mes_visita_inicial << "/" << visitantes.ano_visita_inicial << endl;
		arquivoRegistro1 << "Data de início da Visita: " << visitantes.dia_visita_inicial << "/" << visitantes.mes_visita_inicial << "/" << visitantes.ano_visita_inicial << endl;
		cout << "Horário de início da Visita: " << horas << ":" << minutos << endl;
		cout << "Aproveite sua visita! " << endl;
		arquivoRegistro1 << "Horário de início da visita: " << horas << ":" << minutos << endl;
		arquivoRegistro1 << "Data do término da visita: " << visitantes.dia_visita_final2 << "/" << visitantes.mes_visita_final2 << "/" << visitantes.ano_visita_final2 << endl;
		arquivoRegistro1 << "Horário do término da visita: " << visitantes.hora_final2 << ":" << visitantes.minuto_final2 << endl;
		arquivoRegistro1 << "---------------------------------------" << endl;
		Sleep(2000);
		system("cls");
		arquivoRegistro1.close();
	}
}

// Função para ler o valor mais alto do arquivo de pessoas
void lerContadorPessoa()
{
	ifstream arquivoPessoas("pessoas.txt");
	if (arquivoPessoas.is_open())
	{
		int maxCodPessoa = 10000;
		string line;
		while (getline(arquivoPessoas, line))
		{
			if (line.find("Código de Pessoa: ") != string::npos)
			{
				int codPessoa;
				sscanf(line.c_str(), "Código de Pessoa: %d", &codPessoa);
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

// Função para ler o valor mais alto do arquivo de associados
void lerContadorAssociados()
{
	ifstream arquivoAssociados("associados.txt");
	if (arquivoAssociados.is_open())
	{
		int maxCodAssociado = 10000;
		string line;
		while (getline(arquivoAssociados, line))
		{
			if (line.find("Código de Associado:") != string::npos)
			{
				int codAssociado;
				sscanf(line.c_str(), "Código de Associado: %d", &codAssociado);
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

// Função para ler o valor mais alto do arquivo de dependentes
void lerContadorDependentes()
{
	ifstream arquivoDependentes("dependentes.txt");
	if (arquivoDependentes.is_open())
	{
		int maxCodDependente = 10000;
		string line;
		while (getline(arquivoDependentes, line))
		{
			if (line.find("Código de Dependente:") != string::npos)
			{
				int codDependente;
				sscanf(line.c_str(), "Código de Dependente: %d", &codDependente);
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

// Função para ler o valor mais alto do arquivo de visitantes
void lerContadorVisitantes()
{
	ifstream arquivoVisitantes("visitantes.txt");
	if (arquivoVisitantes.is_open())
	{
		int maxCodVisitante = 10000;
		string line;
		while (getline(arquivoVisitantes, line))
		{
			if (line.find("Código de Visitante:") != string::npos)
			{
				int codVisitante;
				sscanf(line.c_str(), "Código de Visitante: %d", &codVisitante);
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

// Função para obter data atual
void obterDataAtual(int &dia, int &mes, int &ano)
{
	time_t t = time(0);
	tm* now = localtime(&t);
	dia = now->tm_mday;
	mes = now->tm_mon + 1;  // O mês é base 0
	ano = now->tm_year + 1900;  // Contagem de anos desde 1900
}

// Função para obter horário atual
void obterHorarioAtual(int &horas, int &minutos)
{
	time_t t = time(0);
	tm* now = localtime(&t);
	horas = now->tm_hour;
	minutos = now->tm_min;
}

void obterDataAtual2(int &dia2, int &mes2, int &ano2)
{
	time_t agora = time(0);
	tm *dataAtual2 = localtime(&agora);
	dia2 = dataAtual2->tm_mday;
	mes2 = dataAtual2->tm_mon + 1;  // O mês é base 0, então adicionamos 1
	ano2 = dataAtual2->tm_year + 1900;  // Contagem de anos desde 1900
}

void obterHorarioAtual2(int &horas2, int &minutos2)
{
	time_t agora = time(0);
	tm *horarioAtual2 = localtime(&agora);
	horas2 = horarioAtual2->tm_hour;
	minutos2 = horarioAtual2->tm_min;
}
