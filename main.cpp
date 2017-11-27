#include <conio.h>
#include <windows.h>
#include <cstdio>
#include <iostream>
#include <math.h>

using namespace std;

enum Cores {
    PRETO,
    AZUL_ESCURO,
    VERDE_ESCURO,
    TURQUESA_ESCURO,
    VERMELHO_ESCURO,
    VIOLETA_ESCURO,
    MARROM,
    CINZA,
    CINZA_ESCURO,
    AZUL,
    VERDE,
    TURQUESA,
    VERMELHO,
    VIOLETA,
    AMARELO,
    BRANCO
};

static int __BACKGROUND = PRETO;
static int __FOREGROUND = BRANCO;

void CorTexto(int Cor)
{
      __FOREGROUND = Cor;
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Cor + (__BACKGROUND << 4));
}

void FundoTexto(int Cor)
{
     __BACKGROUND = Cor;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), __FOREGROUND + (Cor << 4));
}

void Escreve(Cores cor, Cores fundo, char* texto)
{
    CorTexto(cor);
    FundoTexto(fundo);
    printf("%s\n", texto);
    CorTexto(BRANCO);
    FundoTexto(PRETO);
}

void Menu(int extra = 2)
{
    Escreve(BRANCO, PRETO,              "0-PRETO    (0%)");
    Escreve(PRETO, MARROM,              "1-MARROM   (1%)");
    Escreve(PRETO, VERMELHO,            "2-VERMELHO (2%)");
    if (extra <= 2) {
        Escreve(PRETO, VERMELHO_ESCURO, "3-LARANJA      ");
        Escreve(PRETO, AMARELO,         "4-AMARELO      ");
    }
    Escreve(PRETO, VERDE,               "5-VERDE  (0.5%)");
    Escreve(PRETO, AZUL,                "6-AZUL  (0.25%)");
    Escreve(PRETO, VIOLETA,             "7-VIOLETA(0.1%)");
    Escreve(PRETO, CINZA,               "8-CINZA (0.05%)");
    if (extra <= 2) {
        Escreve(PRETO, BRANCO,          "9-BRANCO       ");
    }
    if (extra >= 2) {
        Escreve(PRETO, AMARELO,         "10-OURO    (5%)");
        Escreve(PRETO, CINZA_ESCURO,    "11-PRATA  (10%)");
    }
    if (extra >= 3) {
        Escreve(BRANCO, PRETO,          "12-SEM COR(20%)");
    }
}

char* Unidade(int uni)
{
    switch(uni) {
        case 0:
            return "";
            break;
        case 1:
            return "K";
            break;
        case 2:
            return "M";
            break;
        default:
            break;
    }
}

int ConverteCores(int cor)
{
    switch(cor) {
        case 0: return 0; break;
        case 1: return 6; break;
        case 2: return 12; break;
        case 3: return 4; break;
        case 4: return 14; break;
        case 5: return 10; break;
        case 6: return 9; break;
        case 7: return 13; break;
        case 8: return 7; break;
        case 9: return 15; break;
    }
}

int main()
{
    int v;
    double r;
    int mode;
    int uni = 0;

    CorTexto(BRANCO);

    cout << "\x20\x20\xdb\xdb\xdb\xdb\x20\x20\n";
    cout << "\x20\xdb\x20\x20\x20\x20\xdb\x20\n";
    cout << "\xdb\x20\x20\x20\x20\x20\x20\xdb\n";
    cout << "\xdb\x20\x20\x20\x20\x20\x20\xdb\n";
    cout << "\x20\xdb\x20\x20\x20\x20\xdb\x20\n";
    cout << "\x20\x20\xdb\x20\x20\xdb\x20\x20\n";
    cout << "\xdb\xdb\xdb\x20\x20\xdb\xdb\xdb\n\n";

    printf("1-Cores -> Valor\n");
    printf("2-Valor -> Cores\n");
    scanf("%i", &v);
    system("CLS");

    if (v == 1) {
        printf("1-Resistor de 4 faixas\n");
        printf("2-Resistor de 5 faixas\n");
        scanf("%i", &mode);
        system("CLS");

        printf("Digite o valor equivalente a cor da primeira faixa do resistor:\n");
        Menu(1);
        scanf("%i", &v);

        r = v*10;
        system("CLS");

        printf("Digite o valor equivalente a cor da segunda faixa do resistor:\n");
        Menu(1);
        scanf("%i", &v);

        r += v;
        system("CLS");

        if (mode == 2) {
            printf("Digite o valor equivalente a cor da terceira faixa do resistor:\n");
            Menu(1);
            scanf("%i", &v);

            r *= 10;
            r += v;
            system("CLS");
        }

        printf("Digite o valor equivalente a cor da faixa de multiplicacao do resistor:\n");
        Menu(2);
        scanf("%i", &v);

        if (v >= 10) {
            v -= 9;
            v *= -1;
        }

        r *= pow(10, v);
        system("CLS");

        printf("Digite o valor equivalente a cor da faixa de tolerancia do resistor:\n");
        Menu(3);
        scanf("%i", &v);

        float p;

        switch(v) {
            case 0:
                p = 0;
                break;
            case 1:
                p = 1;
                break;
            case 2:
                p = 2;
                break;
            case 5:
                p = 0.5;
                break;
            case 6:
                p = 0.25;
                break;
            case 7:
                p = 0.1;
                break;
            case 8:
                p = 0.05;
                break;
            case 10:
                p = 5;
                break;
            case 11:
                p = 10;
                break;
            case 12:
                p = 20;
                break;
            default:
                break;
        }
        system("CLS");

        while(fmod(r, 1000) == 0) {
            r /= 1000;
            uni++;
        }

        printf("Valor Nominal:%.2lf %sohms\n", r, Unidade(uni));
        printf("Valor Minimo:%.2lf %sohms\n", r-r*(p/100), Unidade(uni));
        printf("Valor Maximo:%.2lf %sohms\n", r+r*(p/100), Unidade(uni));
    } else if (v == 2) {
        printf("Digite o valor do resistor em ohms:\n");
        scanf("%lf", &r);

        while(fmod(r, 10) == 0) {
            r /= 10;
            uni++;
        }

        if (r >= 100) {
            cout << 5 << endl;
            Escreve(PRETO, (Cores)ConverteCores((int)((r - fmod(r, 100)) / 100)), "           ");
            Escreve(PRETO, (Cores)ConverteCores((int)((fmod(r, 100) - fmod(r, 10)) / 10)), "           ");
            Escreve(PRETO, (Cores)ConverteCores(fmod(r, 10)), "           ");
            Escreve(PRETO, (Cores)ConverteCores(uni), "           ");
        } else {
            Escreve(PRETO, (Cores)ConverteCores(((r - fmod(r, 10)) / 10)), "           ");
            Escreve(PRETO, (Cores)ConverteCores(fmod(r, 10)), "           ");
            Escreve(PRETO, (Cores)ConverteCores(uni), "           ");
        }
    }

    system("PAUSE");
    return 0;
}
