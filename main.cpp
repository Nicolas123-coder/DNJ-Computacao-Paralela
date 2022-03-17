//Domingos Soares do Carmo Neto - 32032889
//Joao Pedro de Paula Oliveira do Amaral - 32049390 - jppoamaral@hotmail.com 
//Nicolas de Barros - 32070837
#include<iostream>
#include <string>
#include <cstdlib>
#pragma warning(disable : 4996)
using namespace std;

#define MAX_SIZE 50

typedef struct
{
    char name[MAX_SIZE];
    int age;
    float height;
} Pessoa;

void leNomeArquivoEntrada(char S1[])
{
    cout << "Digite o nome do arquivo: ";
    cin >> S1;
}

int abreArquivoAEntrada(FILE** file, char* name)
{
    if ((*file = fopen(name, "r")) != NULL)
        return 1;
    else
        return 0;
}

int leDadosUmaPessoa(Pessoa* destino, FILE* file)
{
    char auxLine[MAX_SIZE];
    for (int i = 0; i < 3; i++)
    {
        if (fgets(auxLine, MAX_SIZE, file))
        {
            cout << auxLine << "\n";
            switch (i)
            {
            case 0:
                strcpy(destino->name, strtok(auxLine, "\n"));
                break;
            case 1:
                destino->age = atoi(auxLine);
                break;
            default:
                destino->height = atof(auxLine);
                break;
            }
        }
        else return 0;
    }
    return 1;
}

void fechaArquivo(FILE* file) { fclose(file); }

int comparaAltura(const void* pessoaA, const void* pessoaB)
{
    Pessoa auxA = *(Pessoa*)pessoaA;
    Pessoa auxB = *(Pessoa*)pessoaB;

    if (auxA.height > auxB.height)
        return 1;
    else if (auxA.height == auxB.height)
        return 0;
    else
        return -1;
}

void ordenaVetor(Pessoa* lst, int size) { qsort(lst, size, sizeof(Pessoa), comparaAltura); }

void imprimeVetor(Pessoa* lst, int size)
{
    FILE* file = fopen("output.txt", "w");
    char br[] = { '\n' };

    for (int i = 0; i < size; i++)
    {
        fprintf(file, lst[i].name);
        char temp[MAX_SIZE];

        fprintf(file, br);

        itoa(lst[i].age, temp, 10);
        fprintf(file, temp);

        fprintf(file, br);

        gcvt(lst[i].height, 2, temp);
        fprintf(file, temp);

        fprintf(file, br);
    }
    fclose(file);
}

int main()
{
    setlocale(LC_ALL, "pt-BR.UTF-8");

    char S1[MAX_SIZE];
    Pessoa Povo[10], P;
    FILE* f;
    int i = 1;

    leNomeArquivoEntrada(S1);
    if (abreArquivoAEntrada(&f, S1) == 1)
    {
        do {
           if (leDadosUmaPessoa(&P, f) == 1)
           {
               Povo[i] = P;
               i++;
           }
           else break;
        } while (1);
        fechaArquivo(f);
        ordenaVetor(Povo, i);
        imprimeVetor(Povo, i);
    } else cout << ("Erro na abertura do arquivo");
}