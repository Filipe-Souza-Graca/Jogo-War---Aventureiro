#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define Limite 5
#define max_string 100

typedef struct
{
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

typedef struct
{
    char nomeUsuario[max_string];
    int ataque;
} atacante;

typedef struct
{
    char nomeUsuario[max_string];
    int defesa;

} Defensor;

void liberarMemoria(Territorio *mapa)
{
    if (mapa != NULL)
    {
        free(mapa);
    }
}

int main()
{

    

   Territorio *mapa = (Territorio *)calloc(Limite, sizeof(Territorio));
    int jogador = 0;
    int opcao;

    Territorio *atacante;
    Territorio *defensor;
    atacante = (Territorio *)calloc(Limite, sizeof(Territorio));
    defensor = (Territorio *)calloc(Limite, sizeof(Territorio));
    
    if (mapa == NULL)
    {
        printf("Não foi possovel alocar memoria para o mapa");
        return 1;
    };
    
    
    srand(time(NULL));


    printf("=====================\n");
    printf("Coloque o seu Territorio\n");
    printf("\nSelecione a as seguintes opções seguinte:\n");
    printf("================================\n");
    printf("\nDigite 1 para cadastrar\n");
    printf("================================\n");
    printf("\nDigite 2 para ver as lista cadastrada\n");
    printf("================================\n");
    printf("\nDigite 3 para jogar\n");
    printf("================================\n");
    printf("\nDigite 0 para sair do cadastro\n");

    

    do
    {

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            if (jogador < Limite)
            {
                printf("\n===========Coloque o nome do país===========\n");
                printf("Nome!\n");

                scanf("%s", mapa[jogador].nome, "\n");

                printf("\n===========Coloque a cor das peças===========\n");
                printf("\ncoloque a cor, ex. Vermelo, azul, rosa, etc.\n");

                scanf("%s", mapa[jogador].cor, "\n");

                printf("\nAgora coloque a quantidade de peça do dabuleiro o Jogador possui\n");
                scanf("%d", &mapa[jogador].tropas);

                jogador++;
            }
            else
            {
                printf("\nVoce atingiu o limite de cadastro!\n");
            }
            break;

        case 2:

            printf("\nAqui esta a lista de mapa\n");
            for (int i = 0; i < jogador; i++)
            {

                printf("%d. pais: %s cor: %s tropas: %d\n",
                       i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
            }

            break;

        case 3:
            if (jogador < 1)
            {
                printf("Não possui mapa o suficiente");
            }
            else
            {
                int idA, idB;
                printf("selecione o atacante e o defensor");
                printf("O atacante tem é: ");
                scanf("%d", &idA);

                if (idA == 0)
                {
                    printf("\nVoce esta saindo da partida");
                    break;
                }
                printf("O atacante tem é: ");
                scanf("%d", &idB);

                if (idA > 0 && idA <= jogador && idB > 0 && idB <= jogador && idA != idB)
                {

                    *atacante = mapa[idA - 1];
                    *defensor = mapa[idB - 1];

                    printf("\nATACANTE: %s (Cor: %s) , Tropas: %d",
                           (*atacante).nome, (*atacante).cor, (*atacante).tropas);

                    printf("\nDEFENSOR: %s (Cor: %s) , Tropas: %d\n",
                           (*defensor).nome, (*defensor).cor, (*defensor).tropas);

                    printf("Vamos lançar os dados");

                    int dadoAtacante = (rand() % 6) + 1;
                    int dadoDefensor = (rand() % 6) + 1;
                    printf("\nVamos lançar primeiro o do Atacante que é de: [%d]", dadoAtacante);
                    printf("O valor do dado defensor é: [%d]", dadoDefensor);

                    if (dadoAtacante > dadoDefensor)
                    {
                        printf("\nO Defensor perdeu a rodada");
                        strcpy(mapa[idB - 1].cor, (*atacante).cor);
                        strcpy((*defensor).cor, (*atacante).cor);

                        int metade = (*atacante).tropas / 2;

                        mapa[idB - 1].tropas = metade;
                        (*defensor).tropas = metade;

                        mapa[idA - 1].tropas -= metade;
                        (*atacante).tropas -= metade;

                        printf("\nTerritorio dominado! %d tropas transferidas.", metade);
                    }
                    else
                    {
                        printf("\nO Atacante perdeu a rodada!");
                        (*atacante).tropas -= 1;
                        mapa[idA - 1].tropas -= 1;
                    }
                    printf("\nO estado atual das é de: %s (%d tropas) vs %s (%d tropas)\n",
                    (*atacante).nome, (*atacante).tropas,
                    (*defensor).nome, (*defensor).tropas);
                }
                else
                {
                    printf("mapa invalidos");
                }
            }
            break;

        case 0:
            printf("\n...Saindo do cadastro....!\n");
            break;
        }

    } while (opcao != 0);

    liberarMemoria(mapa);
    free(atacante);
    free(defensor);

    return 0;
};
