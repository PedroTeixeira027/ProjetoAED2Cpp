//Declaração das Bibliotecas
#include <iostream>
#include <locale.h>
#include <fstream>
#include <stdlib.h>
#include <windows.h>
#include <ctime>
#include <string>
#include <math.h>
#include <algorithm>
#include <cctype> 

//Declaração do STD
using namespace std;

// Struct para cadastrar pessoas
struct Tpessoas {
    string cpf;
    string nome;
    string endereco;
    string email;
    string telefone;
    string sexo;
    int dia_nasc;
    int mes_nasc;
    int ano_nasc;
    int cod_pessoa;
};

// Struct para abastecer dados de associados
struct Tassociados {
    int cod_associado;
    int cod_pessoa;
    int dia_associacao;
    int mes_associacao;
    int ano_associacao;
    string tipo_socio;
    float mensalidade;
    int numDependentes;
};

// Struct para abastecer dados de dependentes
struct Tdependentes {
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
struct Tvisitantes {
    int cod_visitante;
    int cod_associado;
    int cod_pessoa;
    int dia_visita_inicial;
    int mes_visita_inicial;
    int ano_visita_inicial;  
    int dia_visita_final;
    int mes_visita_final;
    int ano_visita_final;
};

//lerContadorDependentes, lerContadorVisitantes e lerContadorPessoa.
static int contadorAssociados;
static int contadorDependentes;
static int contadorVisitantes;
static int contadorPessoa;

// Protótipos das funções
void MenuPrincipal();
void SubMenu1();
void SubMenu2();
void SubMenu3();
void cadastrarPessoas(Tpessoas &pessoa);
void lerContadorPessoa();
void editarCadastro(Tpessoas &pessoa);
void cadastrarAssociados(Tassociados &associados, Tpessoas &pessoa);
void lerContadorAssociados();
void cadastrarDependentes(Tdependentes &dependentes, Tassociados &associados, Tpessoas &pessoa);
void lerContadorDependentes();
void cadastrarVisitantes(Tvisitantes &visitantes, Tpessoas &pessoa);
void lerContadorVisitantes();
void registrarVisita(int codAssociado, Tpessoas &pessoa);
void obterDataAtual(int &dia, int &mes, int &ano);
void obterHorarioAtual(int &horas, int &minutos);
void obterDataAtual2(int &dia2, int &mes2, int &ano2);
void obterHorarioAtual2(int &horas2, int &minutos2);

//Função principal
int main() {
	setlocale(LC_ALL,"portuguese");

    lerContadorAssociados();
     lerContadorDependentes();
    lerContadorVisitantes();
    lerContadorPessoa();

	MenuPrincipal();
    return 0;
} 

//Função do menu principal do cadastro de pessoas
void MenuPrincipal(){
 int opcao;
    do {
        cout << "Menu Principal:\n\n";
		cout << "1 - Cadastro de Pessoas" << endl;
	   	cout << "2 - Relatório de dependentes/associados" << endl;
		cout << "3 - Relatório de visitas por associado" <<endl;
        cout << "0 - Sair\n\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;
		system("cls");
        switch (opcao) {
            case 1:
                SubMenu1();
                break;
            case 2:
            	SubMenu2();
            	break;
            case 3:
            	SubMenu3();
            	break;
            case 0:
                break;
            default:
            	cout<<"Opção Inválida...\n";
            	Sleep(2000);
            	system("cls");
                break;
        }
    } while(opcao!=0);
}

//Função do submenu1 cadastro de pessoas
void SubMenu1() {
    int subOpcao1;
    do {
        cout << "CADASTRO DE PESSOAS\n\n";
        cout << "1 - Cadastrar pessoas\n";
        cout << "2 - Atualizar dados de pessoas\n";
        cout << "3 - Cadastrar visita\n";
        cout << "0 - Voltar ao menu principal\n\n";
        cout << "Escolha uma opção: ";
        cin >> subOpcao1;
        system("cls");
        Tpessoas novaPessoa;
        switch(subOpcao1) {
            case 1:
            	cadastrarPessoas(novaPessoa);
                break;
            case 2:
            	editarCadastro(novaPessoa);
                break;
            case 3:
            	cout << "Cadastrar Visita:\n";
                cout << "Digite o código do associado: ";
                int codAssociado;
                cin >> codAssociado;
                registrarVisita(codAssociado, novaPessoa);
            	break;
            case 0:
                break;
            default:
                cout << "Opção inválida!\n";
                break;
        }
    } while(subOpcao1!=0);
}

//Função para gerar relatório de dependentes/associados
void SubMenu2() {
    string tecla;
    fstream arquivoAssociados("associados.txt", ios::in);
    fstream arquivoDependentes("dependentes.txt", ios::in);
    if (!arquivoAssociados.is_open() || !arquivoDependentes.is_open()) {
        cout << "Erro ao abrir os arquivos. Certifique-se de que os arquivos associados.txt e dependentes.txt existem.\n";
        Sleep(2000);
		system("cls");
        return;
    }
    cout << "Relatório de Dependentes/Associados\n\n";
    
    // Exibir informações dos associados
    cout << "Associados:\n";
    while (!arquivoAssociados.eof()) {
        string line;
        getline(arquivoAssociados, line);
        cout << line << endl;
    }
    arquivoAssociados.close();
    
    // Exibir informações dos dependentes
    cout << "\nDependentes:\n";
    while (!arquivoDependentes.eof()) {
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

// Função para gerar relatório de visitas por associado
void SubMenu3() {  
    string tecla2;
    fstream arquivoVisitantes("visitantes.txt", ios::in);
    if (!arquivoVisitantes.is_open()) {
        cout << "Erro ao abrir o arquivo visitantes.txt. Certifique-se de que o arquivo existe.\n";
        Sleep(2000);
        system("cls");
        return;
    }
    int codAssociado;
    cout << "Digite o código do associado para gerar o relatório de visitas: ";
    cin >> codAssociado;
    cout << "\nRelatório de Visitas por Associado\n\n";
    
    // Exibir informações das visitas do associado
    while (!arquivoVisitantes.eof()) {
        int codVisitante, codAssociadoArquivo, codPessoa, diaVisita, mesVisita, anoVisita;
        string line;
        getline(arquivoVisitantes, line);
        if (line.find("Código de Visitante:") != string::npos) {
        	
            // Extrair informações da linha
            
            sscanf(line.c_str(), "Código de Visitante: %d", &codVisitante);
            // Extrair as próximas linhas
            
            getline(arquivoVisitantes, line);
            sscanf(line.c_str(), "Código de Associado: %d", &codAssociadoArquivo);
            getline(arquivoVisitantes, line);
            sscanf(line.c_str(), "Código de Pessoa: %d", &codPessoa);
            getline(arquivoVisitantes, line);
            sscanf(line.c_str(), "Data de Visita: %d/%d/%d", &diaVisita, &mesVisita, &anoVisita);
            
            // Verificar se o associado corresponde ao código informado
            if (codAssociado == codAssociadoArquivo) {
                cout << "Código de Visitante: " << codVisitante << endl;
                cout << "Código de Associado: " << codAssociadoArquivo << endl;
                cout << "Código de Pessoa: " << codPessoa << endl;
                cout << "Data de Visita: " << diaVisita << "/" << mesVisita << "/" << anoVisita << endl;
            }
        }
    }
	arquivoVisitantes.close();
	cout << "\nFim do Relatório\n";
	cout << "Aperte qualquer tecla pra retornar ao Menu Principal..." << endl;
	cin >> tecla2; 
	system("cls");
}

// Função para cadastrar novas pessoas
void cadastrarPessoas(Tpessoas &pessoa) {
    pessoa.cod_pessoa = contadorPessoa++;
    fstream arquivopessoas; // Para salvar os dados das pessoas
    arquivopessoas.open("pessoas.txt", ios::out | std::ios::app); // Abre o arquivo no modo de adição

    // Salvar dados da pessoa no arquivo
    cout << "Insira seu CPF:";
    cin >> pessoa.cpf;
    arquivopessoas << "CPF: " << pessoa.cpf << endl;
    cout << "Digite seu nome:";
    cin >> pessoa.nome;
    arquivopessoas << "Nome: " << pessoa.nome << endl;
    cout << "Digite seu endereco:";
    cin >> pessoa.endereco;
    arquivopessoas << "Endereço: " << pessoa.endereco << endl;
    cout << "Digite seu email: ";
    cin >> pessoa.email;
    arquivopessoas << "Email: " << pessoa.email << endl;
    cout << "Digite seu numero de telefone: ";
    cin >> pessoa.telefone;
    arquivopessoas << "Telefone: " << pessoa.telefone << endl;
    cout << "Digite seu sexo: ";
    cin >> pessoa.sexo;
 
    // Converter a entrada para minúsculas
    transform(pessoa.sexo.begin(), pessoa.sexo.end(), pessoa.sexo.begin(), ::tolower);
    
    // Verificar se a entrada é válida
    while (pessoa.sexo != "masculino" && pessoa.sexo != "feminino") {
        cout << "ERRO. Digite Masculino ou Feminino\n";
        cout << "Digite seu sexo: ";
        cin >> pessoa.sexo;
        transform(pessoa.sexo.begin(), pessoa.sexo.end(), pessoa.sexo.begin(), ::tolower);
    }
    arquivopessoas << "Sexo: " << pessoa.sexo << endl;
    cout << "Digite o dia do seu nascimento: ";
    cin >> pessoa.dia_nasc;
    cout << "Digite i mes do seu nascimento: ";
    cin >> pessoa.mes_nasc;
    cout << "Digite o ano do seu nascimento: ";
    cin >> pessoa.ano_nasc;
    arquivopessoas << "Data de nascimento: " << pessoa.dia_nasc << "/" << pessoa.mes_nasc << "/" << pessoa.ano_nasc << endl;
    cout<< "Seu código de Pessoa sera: " << pessoa.cod_pessoa << endl;
    arquivopessoas << "Codigo de Pessoa: " << pessoa.cod_pessoa << endl;
    arquivopessoas << "---------------------------------------" << endl;
    Sleep(2000);
    arquivopessoas.close(); // Fecha o arquivo
    system("cls");
    int opcao;
    do {
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
        switch (opcao) {
            case 1:
                cadastrarAssociados(associados, pessoa);
                break;
            
                // Passa a pessoa como argumento
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
    } while (opcao < 1 || opcao > 3);
}

// Função para editar informações de uma pessoa
void editarCadastro(Tpessoas &pessoa) {
    int opcao;
    do {
        cout << "Escolha a informação que deseja editar:\n";
        cout << "1 - CPF: " << pessoa.cpf << endl;
        cout << "2 - Nome: " << pessoa.nome << endl;
        cout << "3 - Endereço: " << pessoa.endereco << endl;
        cout << "4 - Email: " << pessoa.email << endl;
        cout << "5 - Telefone: " << pessoa.telefone << endl;
        cout << "6 - Sexo: " << pessoa.sexo << endl;
        cout << "7 - Data de Nascimento: " << pessoa.dia_nasc << "/" << pessoa.mes_nasc << "/" << pessoa.ano_nasc << endl;
        cout << "0 - Voltar\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;
        switch (opcao) {
            case 1:
                cout << "Novo CPF: ";
                cin >> pessoa.cpf;
                break;
            case 2:
                cout << "Novo Nome: ";
                cin.ignore();
                getline(cin, pessoa.nome);
                break;
            case 3:
                cout << "Novo Endereço: ";
                cin.ignore();
                getline(cin, pessoa.endereco);
                break;
            case 4:
                cout << "Novo Email: ";
                cin.ignore();
                getline(cin, pessoa.email);
                break;
            case 5:
                cout << "Novo Telefone: ";
                cin.ignore();
                getline(cin, pessoa.telefone);
                break;
            case 6:
                cout << "Novo Sexo: ";
                cin >> pessoa.sexo;
                break;
            case 7:
                cout << "Nova Data de Nascimento (dd mm aaaa): ";
                cin >> pessoa.dia_nasc >> pessoa.mes_nasc >> pessoa.ano_nasc;
                break;
            case 0:
                break;
            default:
                cout << "Opção inválida! Por favor, escolha de 0 a 7...\n";
                break;
        }

        // Atualizar o arquivo após cada edição
        fstream arquivopessoas("pessoas.txt", ios::out);
        arquivopessoas << "CPF: " << pessoa.cpf << endl;
        arquivopessoas << "Nome: " << pessoa.nome << endl;
        arquivopessoas << "Endereço: " << pessoa.endereco << endl;
        arquivopessoas << "Email: " << pessoa.email << endl;
        arquivopessoas << "Telefone: " << pessoa.telefone << endl;
        arquivopessoas << "Sexo: " << pessoa.sexo << endl;
        arquivopessoas << "Data de nascimento: " << pessoa.dia_nasc << "/" << pessoa.mes_nasc << "/" << pessoa.ano_nasc << endl;
        arquivopessoas.close();
    } while (opcao != 0);
}

// Função para cadastrar dados específicos de associados
void cadastrarAssociados(Tassociados &associados, Tpessoas &pessoa) {
    fstream arquivoAssociados;
    associados.cod_associado = contadorAssociados++;
     // Usa o código da pessoa cadastrada
    
    // Cálculo da mensalidade
    float taxaFixa = 200.0;
    float taxaPorDependente = 30.0;
    associados.mensalidade = taxaFixa + (taxaPorDependente * associados.numDependentes);
    arquivoAssociados.open("associados.txt", ios::out | std::ios::app); // Abre o arquivo no modo de adição

    // Salvar dados do associado no arquivo
    cout << "Seu nome e: " << pessoa.nome << endl;
    arquivoAssociados << "Nome: " << pessoa.nome << endl;
    cout << "Seu CPF e: " << pessoa.cpf << endl;
    arquivoAssociados << "CPF: " << pessoa.cpf << endl;
    cout << "Seu codigo de Pessoa e: " << pessoa.cod_pessoa << endl;
    arquivoAssociados << "Código de Pessoa: " << pessoa.cod_pessoa << endl;
    cout << "Seu codigo de Associado será" << associados.cod_associado << endl;
    arquivoAssociados << "Código de Associado: " << associados.cod_associado << endl;
    cout << "Sua mensalidade sera de: " << associados.mensalidade << endl;
    arquivoAssociados << "Mensalidade: R$ " << associados.mensalidade << endl;
    cout << "Digite o dia da sua associação: ";
    cin >> associados.dia_associacao;
    cout << "Digite o mes da sua associação: ";
    cin >> associados.mes_associacao;
    cout << "Digite o ano da sua associação: ";
    cin >> associados.ano_associacao;
    arquivoAssociados << "Data da Associação: " << associados.dia_associacao << "/" << associados.mes_associacao << "/" << associados.ano_associacao << endl;
    cout << "Que tipo de Socio voce e? (Proprietario ou Contribuinte)";
    cin >> associados.tipo_socio;
   
     // Converter a entrada para minúsculas
    transform(associados.tipo_socio.begin(), associados.tipo_socio.end(), associados.tipo_socio.begin(), ::tolower);
    
    // Verificar se a entrada é válida
    while (associados.tipo_socio != "proprietario" && associados.tipo_socio != "contribuinte") {
        cout << "ERRO. Digite Proprietario ou Contribuinte\n";
        cout << "Que tipo de Socio voce e? (Proprietario ou Contribuinte) ";
        cin >> associados.tipo_socio;
        transform(associados.tipo_socio.begin(), associados.tipo_socio.end(), associados.tipo_socio.begin(), ::tolower);
    }
    arquivoAssociados << "Tipo de Socio: " << associados.tipo_socio << endl;
    arquivoAssociados << "---------------------------------------" << endl;
    cout << "Cadastro realizado com sucesso!";
    Sleep(2000);
    system("cls");
    arquivoAssociados.close(); // Fecha o arquivo
}

// Função para cadastrar dados específicos de  dependentes
void cadastrarDependentes(Tdependentes &dependentes, Tassociados &associados, Tpessoas &pessoa) {
    fstream arquivoDependentes;
    dependentes.cod_dependente = contadorDependentes++;
	// Usa o código da pessoa cadastrada
    
    //Verificar a maioridade do dependente
    int anoAtual;
    time_t agora = time(0);
    tm *dataAtual = localtime(&agora);
    anoAtual = dataAtual->tm_year + 1900;
    if((anoAtual - pessoa.ano_nasc)>=18){
		cout << "Dependente de maior idade. Será cadastrado como visitante." << endl;
		Tvisitantes visitantes;
		system("cls");
        Sleep(2000);
        cadastrarVisitantes(visitantes, pessoa);
	} else {
		
		//Atualiza o número de dependentes do associado
		associados.numDependentes++;
		arquivoDependentes.open("dependentes.txt", ios::out | std::ios::app); // Abre o arquivo no modo de adição

    	// Salvar dados do dependente no arquivo
        cout << "Seu codigo de Pessoa e: " << pessoa.cod_pessoa << endl;
    	arquivoDependentes << "Código de Pessoa: " << pessoa.cod_pessoa << endl;
        cout << "Seu nome e:" << pessoa.nome << endl;
        arquivoDependentes << "Nome: " << pessoa.nome << endl;
        cout << "Sua data de nascimento e: " << pessoa.dia_nasc << "/" << pessoa.mes_nasc << "/" << pessoa.ano_nasc << endl;
        arquivoDependentes << "Data de nascimento: " << pessoa.dia_nasc << "/" << pessoa.mes_nasc << "/" << pessoa.ano_nasc << endl;
        cout << "Seu sexo e: " << pessoa.sexo << endl;
        arquivoDependentes << "Sexo: " << pessoa.sexo << endl;
        cout << "Seu codigo de Dependente sera: " << dependentes.cod_dependente << endl;
    	arquivoDependentes << "Código de Dependente: " << dependentes.cod_dependente << endl;
        cout << "Digite o dia da sua associação: ";
        cin >> dependentes.dia_associacao_de;
        cout << "Digite o mes da sua associação: ";
        cin >> dependentes.mes_associacao_de;
        cout << "Digite o ano da sua associação: ";
        cin >> dependentes.ano_associacao_de;
        arquivoDependentes << "Data da Associação: " << dependentes.dia_associacao_de << "/" << dependentes.mes_associacao_de << "/" << dependentes.ano_associacao_de << endl;
        dependentes.cod_externo = dependentes.ano_associacao_de + dependentes.cod_dependente;
        cout << "Seu codigo Externo sera: " << dependentes.cod_externo << endl;
        arquivoDependentes << "Codigo Externo: " << dependentes. cod_externo << endl;
        cout << "Digite o codigo do Associado que voce esta vinculado: " << dependentes.cod_associado << endl;
        cin >> dependentes.cod_associado;
    	arquivoDependentes << "Código de Associado: " << dependentes.cod_associado << endl;
        cout << "Digite o CPF do Associado: ";
        cin >> dependentes.cpf_associado;
        arquivoDependentes << "O CPF do Associado e: " << dependentes.cpf_associado << endl;
        arquivoDependentes << "---------------------------------------" << endl;
        cout << "Cadastro realizado com sucesso!";
        Sleep(2000);
        system("cls"); 
    	arquivoDependentes.close(); // Fecha o arquivo
	}
}

// Função para cadastrar dados específicos de visitantes e registrar visitas
void cadastrarVisitantes(Tvisitantes &visitantes, Tpessoas &pessoa) {
    fstream arquivoVisitantes;
    visitantes.cod_visitante = contadorVisitantes++;
    
	// Usa o código da pessoa cadastrada
    arquivoVisitantes.open("visitantes.txt", ios::out | std::ios::app); // Abre o arquivo no modo de adição

    // Salvar dados do visitante no arquivo
    cout << "Seu codigo de Pessoa e: " << pessoa.cod_pessoa << endl;
    arquivoVisitantes << "Código de Pessoa: " << pessoa.cod_pessoa << endl;
    cout << "Seu nome e: " << pessoa.nome << endl;
    arquivoVisitantes << "Nome: " << pessoa.nome << endl;
    cout << "Seu CPF e: " << pessoa.cpf << endl;
    arquivoVisitantes << "CPF: " << pessoa.cpf << endl;
    cout << "Sua data de nascimento e: " << pessoa.dia_nasc << "/" << pessoa.mes_nasc << "/" << pessoa.ano_nasc << endl;
    arquivoVisitantes << "Data de nascimento: " << pessoa.dia_nasc << "/" << pessoa.mes_nasc << "/" << pessoa.ano_nasc << endl;
    cout << "Seu sexo e: " << pessoa.sexo << endl;
    arquivoVisitantes << "Sexo: " << pessoa.sexo << endl;
    cout << "Seu codigo de visitante sera: " << visitantes.cod_visitante << endl;
    arquivoVisitantes << "Código de Visitante: " << visitantes.cod_visitante << endl;
    cout << "Digite o codigo do Associado: ";
    cin >> visitantes.cod_associado;
    arquivoVisitantes << "Código de Associado: " << visitantes.cod_associado << endl;
    cout << "Digite o dia que começa sua visita: ";
    cin >> visitantes.dia_visita_inicial;
    cout << "Digite o mes que começa sua visita: ";
    cin >> visitantes.mes_visita_inicial;
    cout << "Digite o ano que começa sua visita: ";
    cin >> visitantes.ano_visita_inicial;
    arquivoVisitantes << "Data do inicio da visita: " << visitantes.dia_visita_inicial << "/" << visitantes.mes_visita_inicial << "/" << visitantes.ano_visita_inicial << endl;
    cout << "Digite o dia que termina sua visita: ";
    cin >> visitantes.dia_visita_final;
    cout << "Digite o mes que termina sua visita: ";
    cin >> visitantes.mes_visita_final;
    cout << "Digite o ano que termina sua visita: ";
    cin >> visitantes.ano_visita_final;
    arquivoVisitantes << "Data do termino da visita: " << visitantes.dia_visita_final << "/" << visitantes.mes_visita_final << "/" << visitantes.ano_visita_final << endl;
    arquivoVisitantes << "---------------------------------------" << endl;
    cout << "Cadastro realizado com sucesso!";
    Sleep(2000);
    system("cls"); 
    arquivoVisitantes.close(); // Fecha o arquivo
}

// Função para ler o valor mais alto do arquivo de pessoas
void lerContadorPessoa() {
    ifstream arquivoPessoas("pessoas.txt");
    if (arquivoPessoas.is_open()) {
        int maxCodPessoa = 10000;
        string line;
        while (getline(arquivoPessoas, line)) {
            if (line.find("Codigo de Pessoa:") != string::npos) {  // Corrigido aqui
                int codPessoa;
                sscanf(line.c_str(), "Codigo de Pessoa: %d", &codPessoa);  // Corrigido aqui
                if (codPessoa > maxCodPessoa) {
                    maxCodPessoa = codPessoa;
                }
            }
        }
        arquivoPessoas.close();
        contadorPessoa = maxCodPessoa + 1;
    }
}

// Função para ler o valor mais alto do arquivo de associados
void lerContadorAssociados() {
    ifstream arquivoAssociados("associados.txt");
    if (arquivoAssociados.is_open()) {
        int maxCodAssociado = 10000;
        string line;
        while (getline(arquivoAssociados, line)) {
            if (line.find("Código de Associado:") != string::npos) {
                int codAssociado;
                sscanf(line.c_str(), "Código de Associado: %d", &codAssociado);
                if (codAssociado > maxCodAssociado) {
                    maxCodAssociado = codAssociado;
                }
            }
        }
        arquivoAssociados.close();
        contadorAssociados = maxCodAssociado + 1;
    }
}

// Função para ler o valor mais alto do arquivo de dependentes
void lerContadorDependentes() {
    ifstream arquivoDependentes("dependentes.txt");
    if (arquivoDependentes.is_open()) {
        int maxCodDependente = 10000;
        string line;
        while (getline(arquivoDependentes, line)) {
            if (line.find("Código de Dependente:") != string::npos) {
                int codDependente;
                sscanf(line.c_str(), "Código de Dependente: %d", &codDependente);
                if (codDependente > maxCodDependente) {
                    maxCodDependente = codDependente;
                }
            }
        }
        arquivoDependentes.close();
        contadorDependentes = maxCodDependente + 1;
    }
}

// Função para ler o valor mais alto do arquivo de visitantes
void lerContadorVisitantes() {
    ifstream arquivoVisitantes("visitantes.txt");
    if (arquivoVisitantes.is_open()) {
        int maxCodVisitante = 10000;
        string line;
        while (getline(arquivoVisitantes, line)) {
            if (line.find("Código de Visitante:") != string::npos) {
                int codVisitante;
                sscanf(line.c_str(), "Código de Visitante: %d", &codVisitante);
                if (codVisitante > maxCodVisitante) {
                    maxCodVisitante = codVisitante;
                }
            }
        }
        arquivoVisitantes.close();
        contadorVisitantes = maxCodVisitante + 1;
    }
}

// Função para registrar visitas
void registrarVisita(int codAssociado, Tpessoas &pessoa) {
    fstream arquivoVisitantes;
    Tvisitantes visitantes;
    visitantes.cod_visitante = contadorVisitantes++;
    visitantes.cod_associado = codAssociado;
    
	// Usa o código da pessoa cadastrada
    int diaAtual, mesAtual, anoAtual;
    int diaAtual2, mesAtual2, anoAtual2;
    int horas, minutos;
    int horas2, minutos2;
    obterDataAtual(diaAtual, mesAtual, anoAtual);
    obterHorarioAtual(horas, minutos);
    obterDataAtual2(diaAtual2, mesAtual2, anoAtual2);
    obterHorarioAtual2(horas2, minutos2);
    visitantes.dia_visita_inicial = diaAtual;
    visitantes.mes_visita_inicial = mesAtual;
    visitantes.ano_visita_inicial = anoAtual;
    visitantes.dia_visita_final = diaAtual2;
    visitantes.mes_visita_final = mesAtual2;
    visitantes.ano_visita_final = anoAtual2;
    arquivoVisitantes.open("visitantes.txt", ios::app); // Abre o arquivo no modo de adição
    
    // Salvar dados do visitante no arquivo
    arquivoVisitantes << "Código de Visitante: " << visitantes.cod_visitante << endl;
    arquivoVisitantes << "Código de Associado: " << visitantes.cod_associado << endl;
    arquivoVisitantes << "Código de Pessoa: " << pessoa.cod_pessoa << endl;
    arquivoVisitantes << "Data de inicio da Visita: " << visitantes.dia_visita_inicial << "/" << visitantes.mes_visita_inicial << "/" << visitantes.ano_visita_inicial << endl;
    arquivoVisitantes << "Horário de inicio da Visita: " << horas << ":" << minutos << endl;
    arquivoVisitantes << "Data do termino da Visita: " << visitantes.dia_visita_final << "/" << visitantes.mes_visita_final << "/" << visitantes.ano_visita_final << endl;
    arquivoVisitantes << "Horário do termino da Visita: " << horas2 << ":" << minutos2 << endl;
    arquivoVisitantes.close(); // Fecha o arquivo
}

// Função para obter a data atual
void obterDataAtual(int &dia, int &mes, int &ano) {
    time_t agora = time(0);
    tm *dataAtual = localtime(&agora);
    dia = dataAtual->tm_mday;
    mes = dataAtual->tm_mon + 1;  // O mês é base 0, então adicionamos 1
    ano = dataAtual->tm_year + 1900;  // Contagem de anos desde 1900
}

// Função para obter o horário atual
void obterHorarioAtual(int &horas, int &minutos) {
    time_t agora = time(0);
    tm *horarioAtual = localtime(&agora);

    horas = horarioAtual->tm_hour;
    minutos = horarioAtual->tm_min;
}

//Função para obter data atual 12
void obterDataAtual2(int &dia2, int &mes2, int &ano2) {
    time_t agora = time(0);
    tm *dataAtual2 = localtime(&agora);

    dia2 = dataAtual2->tm_mday;
    mes2 = dataAtual2->tm_mon + 1;  // O mês é base 0, então adicionamos 1
    ano2 = dataAtual2->tm_year + 1900;  // Contagem de anos desde 1900
}

//Função para obter horario atual 12
void obterHorarioAtual2(int &horas2, int &minutos2) {
    time_t agora = time(0);
    tm *horarioAtual2 = localtime(&agora);

    horas2 = horarioAtual2->tm_hour;
    minutos2 = horarioAtual2->tm_min;
}
