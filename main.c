#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <time.h>

#define TAM 25

void definirDimensoes(int *pdimL, int *pdimC)
{
    do
    {
        printf("\n Entre com a qtd de linhas do seu campo (>=2 e <=%i): ", TAM);
        scanf("%d", pdimL);

        if(*pdimL < 2 || *pdimL > TAM)
        {
            printf("\n Qtd de Linhas inv�lida! Tente novamente...");
            fflush(stdin);
            getchar();
        }
        system("cls");
    }
    while(*pdimL < 2 || *pdimL > TAM);

    do
    {
        printf("\n Entre com a qtd de colunas do seu campo (>=2 e <=%i): ", TAM);
        scanf("%d", pdimC);

        if(*pdimC < 2 || *pdimC > TAM)
        {
            printf("\n Qtd de Colunas inv�lida! Tente novamente...");
            fflush(stdin);
            getchar();
        }
        system("cls");
    }
    while(*pdimC < 2 || *pdimC > TAM);

}

void mostrarCampo(char campo[TAM][TAM], int dimL, int dimC)
{
    int l, c;

    printf("\n");

    // Imprimir legenda da coluna
    printf("   ");
    for (c=1; c<dimC+1; c++)
    {
        printf("%2i ", c);
    }
    printf("\n");

    // Imprimir celulas da matriz
    for (l=0; l<dimL; l++)
    {
        printf("%2i ", l+1);

        for (c=0; c<dimC; c++)
        {
            printf(" %c ", campo[l][c]);
        }
        printf("\n");
    }
}

void limparCampo(char campo[TAM][TAM])
{
    int l, c;

    for (l=0; l<TAM; l++)
    {
        for (c=0; c<TAM; c++)
        {
            campo[l][c]='?';
        }
    }
}

// Solu��o 2
/*int estaDentroIntervalo(int num, int min, int max){
    if (num>=min && num<=max){
        return 1;
    }else{
        return 0;
    }
}*/

int definirNivel()
{
    int nivel=0;

    while(nivel<1 || nivel>3)
    {
        printf("\nN�veis do Jogo: ");
        printf("\n1 - F�cil ");
        printf("\n2 - M�dio ");
        printf("\n3 - Dif�cil ");

        printf("\nEscolha o n�vel que deseja jogar: ");
        scanf("%d", &nivel);

        // Solu��o 1
        if(nivel<1 || nivel>3)
        {
            printf("\nN�vel inv�lido. Tente novamente...");
        }

        // Solu��o 2
        //if (!estaDentroIntervalo(nivel, 1, 3)){
        //    printf("\nN�vel inv�lido. Tente novamente...");
        //}
    }
    return nivel;
}

void calcularQtdBombas(int dimL, int dimC, float *qtdBombas)
{
    float percBombas;

    switch (definirNivel())
    {
    case 1:
        percBombas = 0.25;
        break;
    case 2:
        percBombas = 0.50;
        break;
    case 3:
        percBombas = 0.75;
        break;
    }

    *qtdBombas = roundf((dimL * dimC) * percBombas);

    printf("\nSeu jogo ter� %.f bombas.", *qtdBombas);
}

void lancarBombas(float qtdBombas, char campo[TAM][TAM], int dimL, int dimC)
{
    int i, lAlet, cAlet;

    srand((unsigned)time(NULL) ); // Gera��o da semente para gerar n�meros rand�micos diferentes

    for(i=1; i<=qtdBombas; i++)
    {
        lAlet = rand()%dimL;     // N�mero aleat�rio para a linha
        cAlet = rand()%dimC;     // N�mero aleat�rio para a coluna

        if (campo[lAlet][cAlet] == '?')
        {
            campo[lAlet][cAlet] = '*';
        }
        else
        {
            i--;
        }
    }
}

void lancarNumeros(char campo[TAM][TAM], int dimL, int dimC)
{
    int l, c, contaBombas=0;

    for(l=0; l<dimL; l++)
    {
        for(c=0; c<dimC; c++)
        {
            contaBombas = 0;

            // Fazer o "rel�gio" (sen�o for bomba)
            if(campo[l][c]=='?')
            {
                if((campo[l-1][c]=='*')&&(l-1>=0))
                    contaBombas++;
                if((campo[l-1][c+1]=='*')&&(l-1>=0)&&(c+1<dimC))
                    contaBombas++;
                if((campo[l][c+1]=='*')&&(c+1<dimC))
                    contaBombas++;
                if((campo[l+1][c+1]=='*')&&(l+1<dimL)&&(c+1<dimC))
                    contaBombas++;
                if((campo[l+1][c]=='*')&&(l+1<dimL))
                    contaBombas++;
                if((campo[l+1][c-1]=='*')&&(l+1<dimL)&&(c-1>=0))
                    contaBombas++;
                if((campo[l][c-1]=='*')&&(c-1>=0))
                    contaBombas++;
                if((campo[l-1][c-1]=='*')&&(l-1>=0)&&(c-1>=0))
                    contaBombas++;

                // Preencher o numero
                campo[l][c] = contaBombas+48; // Conversao de int para char usando Tabela ASCII
            }
        }
    }
}

int jogar(int dimL, int dimC, char tela[TAM][TAM], char campo[TAM][TAM])
{
    int lj, cj;

    // O jogador deve escolher uma posi��o v�lida
    do
    {
        printf("\nEscolha a posi��o de linha e coluna que deseja marcar: ");
        scanf("%d %d", &lj, &cj);

        if(lj<=0 || lj>dimL || cj<=0 || cj>dimC)
            printf("\nPosi��o inv�lida! Tente novamente...");

    }
    while(lj<=0 || lj>dimL || cj<=0 || cj>dimC);

    lj--;
    cj--;

    // Verificar se a posi��o j� n�o foi jogada
    if(tela[lj][cj] == '?')
    {
        tela[lj][cj] = campo[lj][cj];
        if (tela[lj][cj] == '*')
        {
            printf("\nGAME OVER :-P");
            return 0;
        }
    }
    else
    {
        printf("\nEsta posi��o j� foi marcada. Tente novamente...");
        return -1;
    }
    return 1;
}

int main()
{
    char campo[TAM][TAM];
    char tela[TAM][TAM];
    int dimL = 0, dimC = 0;
    float qtdBombas = 0;
    float qtdJogadas = 0;
    int res;

    // Configura o software para portugu�s (permitindo utilizar acentua��es)
    setlocale(LC_CTYPE, "portuguese");

    // 1� Passo - Usu�rio escolhe as dimens�es
    definirDimensoes(&dimL, &dimC);
    printf("\nCampo com dimensoes %d X %d\n", dimL, dimC);

    // 2� Passo - Calcular a qtd de bombas
    calcularQtdBombas(dimL, dimC, &qtdBombas);

    // 3� Passo - Limpar campo colocando ?
    limparCampo(campo);
    //mostrarCampo(campo, dimL, dimC);

    // 4� Passo - Lan�ar bombas
    lancarBombas(qtdBombas, campo, dimL, dimC);
    //mostrarCampo(campo, dimL, dimC);

    // 5� Passo - Lancar Numeros
    lancarNumeros(campo, dimL, dimC);
    mostrarCampo(campo, dimL, dimC);

    // 6� Passo - Limpar a matriz tela
    limparCampo(tela);

    qtdJogadas = (dimL * dimC) - qtdBombas;
    do
    {
        mostrarCampo(tela, dimL, dimC);

        res = jogar(dimL, dimC, tela, campo);
        if(res == 1)
        {
            qtdJogadas--;
        }

    }
    while(res != 0 && qtdJogadas!=0);

    mostrarCampo(tela, dimL, dimC);

    if(res = 1)
    {
        printf("\nParab�ns!!! Voc� ganhou!!! :-)");
    }

    return 0;
}
