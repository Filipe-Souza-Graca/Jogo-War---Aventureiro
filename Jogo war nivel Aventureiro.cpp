#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define Limite 5
#define max_string 100

typedef struct {
    char pais[30];
    char cor[10];
    int tropas;
} Territorio;

typedef struct {
    char nomeUsuario[max_string];
    int ataque;
} Atacante;

typedef struct {
    char nomeUsuario[max_string];
    int defesa;
} Defensor;

int main() {
    // Inicializa a semente do número aleatório
    srand(time(NULL));

    Atacante *atq = (Atacante*)calloc(Limite, sizeof(Atacante));
    Defensor *def = (Defensor*)calloc(Limite, sizeof(Defensor));
    Territorio *mapa = (Territorio*)malloc(Limite * sizeof(Territorio));

    if (atq == NULL || def == NULL || mapa == NULL) {
        printf("Erro de alocação de memória!\n");
        return 1;
    }

    int opcao;
    int nacao = 0;
    int jogador = 0;

    printf("Bora comecar!\n");

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("================================\n");
        printf("1. Cadastrar Pais, Cor e Tropas\n");
        printf("================================\n");
        printf("2. Cadastrar Jogadores\n");
        printf("================================\n");
        printf("3. Ver Lista de Paises\n");
        printf("================================\n");
        printf("4. Ver Lista de Jogadores\n");
        printf("================================\n");
        printf("5. Comecar Batalha\n");
        printf("================================\n");
        printf("0. Sair do sistema\n");
        printf("================================\n");
        printf("Escolha: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida!\n");
            while(getchar() != '\n'); // Limpa buffer se digitar letra
            continue;
        }
        getchar(); // Limpa o \n

        switch(opcao) {
            case 1:
                if (nacao < Limite) {
                    printf("Insira o Nome do pais (ou '0' para cancelar): "); //Interrompe se for colocado 0
                    scanf("%s", mapa[nacao].pais);
                    if (strcmp(mapa[nacao].pais, "0") == 0) break;

                    printf("Cor do pais: ");
                    scanf("%s", mapa[nacao].cor);
                    if(strcmp(mapa[nacao].cor, 0) == 0) break;
                    
                    printf("Quantidade de tropas: ");
                    scanf("%d", &mapa[nacao].tropas);                
                    if (mapa[nacao].tropas <= 0) break; {
                        printf("Quantidade invalida. Cadastro cancelado.\n");
                    } else {
                        nacao++;
                        printf("Pais cadastrado com sucesso!\n"); 
                    }
                } else {
                    printf("\nLimite de paises atingido!\n");
                }
                break;

            case 2:
                if (jogador < Limite) {
                    printf("\nNome do Jogador %d (ou '0' para cancelar): ", jogador + 1);
                    scanf("%s", atq[jogador].nomeUsuario); // adicionando jogador
                    if (strcmp(atq[jogador].nomeUsuario, "0") == 0) break; // interrompe o cadastro se se colocar 0

                    strcpy(def[jogador].nomeUsuario, atq[jogador].nomeUsuario); // o mesmo jogador de ataque pode ser de defesa, copia de um e usa para outro função do strcpy()
                    atq[jogador].ataque = 0;
                    def[jogador].defesa = 0;
                    jogador++;
                } else {
                    printf("\nLimite de jogadores atingido!\n");
                }
                break;

            case 3:
                printf("\n--- LISTA DE PAISES ---\n");
                if (nacao == 0) printf("Nenhum pais cadastrado.\n");
                else {
                    for (int i = 0; i < nacao; i++) {
                        printf("[%d] Pais: %s | Cor: %s | Tropas: %d\n", 
                            i + 1, 
                            mapa[i].pais, 
                            mapa[i].cor, 
                            mapa[i].tropas);
                    }
                }
                break;

            case 4:
                printf("\n--- LISTA DE JOGADORES ---\n");
                if (jogador == 0) printf("Nenhum jogador cadastrado.\n");
                else {
                    for (int i = 0; i < jogador; i++) {
                        printf("[%d] Jogador: %s\n", i + 1, atq[i].nomeUsuario); // Lista de jogador já cadastrado tem como utilização do strcpy(), então basta cadastrar um unica vez
                    }
                }
                break;

            case 5:
                if (jogador < 2 || nacao < 1) {
                    printf("\nErro: Necessario pelo menos 2 jogadores e 1 pais!\n");
                } else {
                    int idAtq, idDef, idPais; // acrescentando variaveis para identificar id do atacante, id do defensor, e id pais(utilizando *mapa) 

                    printf("\nID do Atacante: "); 
                    scanf("%d", &idAtq);
                    printf("ID do Defensor: ");  
                    scanf("%d", &idDef);
                    printf("ID do Pais: ");      
                    scanf("%d", &idPais);
                    idAtq--; idDef--; idPais--; 

                    if (idAtq < 0 || idAtq >= jogador || idDef < 0 || idDef >= jogador || idPais < 0 || idPais >= nacao) {
                        printf("\nErro: IDs invalidos!\n");
                        break;
                    }
                    if (idAtq == idDef) {
                        printf("\nErro: Um jogador nao pode atacar a si mesmo!\n"); // condição para evitar auto-exterminio
                        break;
                    }
                    // Aqui como o dado não começa com 0, deve ser incrementado com + 1, caso contraio seria de 0 a 5
                    int dadoAtq = (rand() % 6) + 1;
                    int dadoDef = (rand() % 6) + 1;

                    printf("\n--- BATALHA EM %s ---\n", mapa[idPais].pais);
                    printf("%s tirou: %d\n", atq[idAtq].nomeUsuario, dadoAtq);
                    printf("%s tirou: %d\n", def[idDef].nomeUsuario, dadoDef);

                    if (dadoAtq > dadoDef) {
                        int perda = dadoAtq - dadoDef;
                        mapa[idPais].tropas -= perda;
                        printf("\nVITORIA DO ATACANTE! O pais perdeu %d tropas.\n", perda);

                        if (mapa[idPais].tropas <= 0) {
                            printf("--- TERRITORIO CONQUISTADO POR %s! ---\n", atq[idAtq].nomeUsuario);
                            printf("O defensor %s foi eliminado!\n", def[idDef].nomeUsuario);

                            // Ocupação
                            mapa[idPais].tropas = (dadoAtq / 2) + 1;
                            printf("Nova cor do territorio: ");
                            scanf("%s", mapa[idPais].cor);

                            // Remoção do jogador
                            // j pode indicar o indicie como o i++ (controlador do laço for())
                            for (int j = idDef; j < jogador - 1; j++)  {
                                atq[j] = atq[j + 1];
                                def[j] = def[j + 1];
                            }
                            jogador--;
                        }
                    } else {
                        int perdaAtq = (dadoAtq / 2);
                        mapa[idPais].tropas += 1; // Defesa reforçada
                        printf("\nA DEFESA VENCEU! O ataque perdeu forca.\n");
                        // Aqui você pode subtrair algo do atacante se tiver uma variável de "tropas do jogador"
                    }
                    printf("Situacao atual de %s: %d tropas.\n", mapa[idPais].pais, mapa[idPais].tropas);
                }
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    free(atq);
    free(def);
    free(mapa);

    return 0;
}
