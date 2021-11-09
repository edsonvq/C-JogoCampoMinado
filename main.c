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
            printf("\n Qtd de Linhas inválida! Tente novamente...");
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
            printf("\n Qtd de Colunas inválida! Tente novamente...");
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

// Solução 2
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
        printf("\nNíveis do Jogo: ");
        printf("\n1 - Fácil ");
        printf("\n2 - Médio ");
        printf("\n3 - Difícil ");

        printf("\nEscolha o nível que deseja jogar: ");
        scanf("%d", &nivel);

        // Solução 1
        if(nivel<1 || nivel>3)
        {
            printf("\nNível inválido. Tente novamente...");
        }

        // Solução 2
        //if (!estaDentroIntervalo(nivel, 1, 3)){
        //    printf("\nNível inválido. Tente novamente...");
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

    printf("\nSeu jogo terá %.f bombas.", *qtdBombas);
}

void lancarBombas(float qtdBombas, char campo[TAM][TAM], int dimL, int dimC)
{
    int i, lAlet, cAlet;

    srand((unsigned)time(NULL) ); // Geração da semente para gerar números randômicos diferentes

    for(i=1; i<=qtdBombas; i++)
    {
        lAlet = rand()%dimL;     // Número aleatório para a linha
        cAlet = rand()%dimC;     // Número aleatório para a coluna

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

            // Fazer o "relógio" (senão for bomba)
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

    // O jogador deve escolher uma posição válida
    do
    {
        printf("\nEscolha a posição de linha e coluna que deseja marcar: ");
        scanf("%d %d", &lj, &cj);

        if(lj<=0 || lj>dimL || cj<=0 || cj>dimC)
            printf("\nPosição inválida! Tente novamente...");

    }
    while(lj<=0 || lj>dimL || cj<=0 || cj>dimC);

    lj--;
    cj--;

    // Verificar se a posição já não foi jogada
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
        printf("\nEsta posição já foi marcada. Tente novamente...");
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

    // Configura o software para português (permitindo utilizar acentuações)
    setlocale(LC_CTYPE, "portuguese");

    // 1º Passo - Usuário escolhe as dimensões
    definirDimensoes(&dimL, &dimC);
    printf("\nCampo com dimensoes %d X %d\n", dimL, dimC);

    // 2º Passo - Calcular a qtd de bombas
    calcularQtdBombas(dimL, dimC, &qtdBombas);

    // 3º Passo - Limpar campo colocando ?
    limparCampo(campo);
    //mostrarCampo(campo, dimL, dimC);

    // 4º Passo - Lançar bombas
    lancarBombas(qtdBombas, campo, dimL, dimC);
    //mostrarCampo(campo, dimL, dimC);

    // 5º Passo - Lancar Numeros
    lancarNumeros(campo, dimL, dimC);
    mostrarCampo(campo, dimL, dimC);

    // 6º Passo - Limpar a matriz tela
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
        printf("\nParabéns!!! Você ganhou!!! :-)");
    }

    return 0;
}
