#include <iostream>
#include <locale.h>
#include <fstream>

using namespace std;

struct Tpessoas {

};

struct Tassociados {
    
};

struct Tdependentes {
    
};

struct Tvisitantes {
    
};

void MenuPrincipal();
void SubMenu1();
void SubMenu2();
void SubMenu3();
void SubMenu4();
void SubMenu5();
void SubMenu6();

int main() {
	setlocale(LC_ALL,"portuguese");
    MenuPrincipal();
    return 0;
}

void MenuPrincipal() {
    int opcao;
    do {
        cout << "Menu Principal:\n";
		cout << "Escolha uma opção" << endl;
		cout << "1- Associados." << endl;
	   	cout << "2- Dependentes." << endl;
	   	cout << "3- Visitantes." <<endl;
	   	cout << "4- Registro de visita." <<endl;
	   	cout << "5- Relatório de dependentes/associados." << endl;
		cout << "6- Relatório de visitas por associado." <<endl;
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

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
            case 4:
            	break;
            case 5:
            	break;
            case 6:
            	break;
            case 0:
                break;
            default:
                cout << "Opção inválida! Tente novamente.\n";
                break;
        }

    } while (opcao != 0);
}

void SubMenu1() {
    int subOpcao1;
    do {
        cout << "Associados\n";
        cout << "1- Cadastro de associados";
        cout << "2- Manutenção de dados associados\n";
        cout << "0. Voltar ao menu principal\n";
        cout << "Escolha uma opção: ";
        cin >> subOpcao1;

        switch (subOpcao1) {
            case 1:
                break;
            case 2:
                break;
            case 0:
                break;
            default:
                cout << "Opção inválida!\n";
                break;
        }
    } while (subOpcao1 != 0);
}

void SubMenu2() {
    int subOpcao2;
    do {
        cout << "Dependentes:\n";
        cout << "1- Cadastro de dependentes";
        cout << "2- Manutenção de dados dependentes\n";
        cout << "0. Voltar ao menu principal\n";
        cout << "Escolha uma opção: ";
        cin >> subOpcao2;

        switch (subOpcao2) {
            case 1:
            	
                break;
            case 2:
                break;
            case 0:
                break;
            default:
                cout << "Opção inválida!\n";
                break;
        }
    } while (subOpcao2 != 0);
}

void SubMenu3() {
    int subOpcao3;
    do {
        cout << "Visitantes:\n";
        cout << "1- Cadastro de visitantes";
        cout << "2- Manutenção de dados visitantes\n";
        cout << "0. Voltar ao menu principal\n";
        cout << "Escolha uma opção: ";
        cin >> subOpcao3;

        switch (subOpcao3) {
            case 1:
                break;
            case 2:
                break;
            case 0:
                break;
            default:
                cout << "Opção inválida!\n";
                break;
        }
    } while (subOpcao3 != 0);
}