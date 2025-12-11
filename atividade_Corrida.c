#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// corrida maluca
void classificacao(int *id, int *distancia, char *carro, size_t tam_vetor);
void trilhas(int *id, int *distancia, char *carro, size_t tam_vetor);
void vencedor(int *id, int *distancia, char *carro, size_t tam_vetor);

int main()
{
    size_t tam_vetor = 10;
    int *id = (int *)malloc(sizeof(int) * tam_vetor);
    int *distancia = (int *)malloc(sizeof(int) * tam_vetor);
    char *carro = (char *)malloc(sizeof(char) * tam_vetor);

    if (id == NULL || distancia == NULL || carro == NULL)
    {
        printf("Erro na alocação de memória\n");
        return 1;
    }

    char simbolos[10] = {'!', '@', '#', '$', '%', '&', '*', '?', '+', '^'};
    for (size_t i = 0; i < tam_vetor; i++) // inicializando tudo
    {
        *(carro + i) = simbolos[i];
        *(id + i) = i;
        *(distancia + i) = 0;
    }

    srand(time(NULL));

    int fim = 0;

    while (1)
    {
        system("cls"); // limpa a tela ANTES de mostrar a nova rodada

        for (size_t i = 0; i < tam_vetor; i++)
        {
            *(distancia + i) += 4 + rand() % 7;
        }

        // imprime todas as trilhas só depois de atualizar tudo
        trilhas(id, distancia, carro, tam_vetor);
        Sleep(200);

        // verifica se alguém ganhou
        for (size_t i = 0; i < tam_vetor; i++)
        {
            if (*(distancia + i) >= 100)
            {
                fim = 1;
                break;
            }
        }

        if (fim)
            break;
    }

    // chama as funções
    // classificacao(id,distancia,carro,tam_vetor);
    vencedor(id, distancia, carro, tam_vetor);
    free(id);
    free(carro);
    free(distancia);
}

void classificacao(int *id, int *distancia, char *carro, size_t tam_vetor) // ele teria q ordenar a cada mudança na trilha
{
    size_t i, prox_maior_pos, maior;
    int aux;

    for (i = 0; i < (tam_vetor - 1); i++)
    {
        maior = i;

        for (prox_maior_pos = (i + 1); prox_maior_pos < tam_vetor; prox_maior_pos)
        {
            if (*(distancia + prox_maior_pos) > *(distancia + maior))

            {
                maior = prox_maior_pos;
            }
        }
        if (i != maior)
        {
            // seleção do maior de cada coisa, distancia,id, e o simb do carro
            int aux_dist = *(distancia + i);
            *(distancia + i) = *(distancia + maior);
            *(distancia + maior) = aux_dist;

            int aux_id = *(id + i);
            *(id + i) = *(id + maior);
            *(id + maior) = aux_id;

            char aux_carro = *(carro + i);
            *(carro + i) = *(carro + maior);
            *(carro + maior) = aux_carro;
        }
    }
}

void trilhas(int *id, int *distancia, char *carro, size_t tam_vetor)
{ // nesse faz a trilha do carro

    for (size_t i = 0; i < tam_vetor; i++)
    {
        printf("%d. %c: ", *(id + i), *(carro + i));
        for (int j = 0; j < *(distancia + i) && j < 100; j++)
        {
            printf("=");
        }
        printf("\n");
    }

    printf("------------------------------------------------------------------------\n");
}

void vencedor(int *id, int *distancia, char *carro, size_t tam_vetor)
{
    int maior_dist = *distancia;
    int pos = 0;

    for (size_t i = 1; i < tam_vetor; i++)
    {
        if (*(distancia + i) > maior_dist)
        {
            maior_dist = *(distancia + i);
            pos = i;
        }
    }

    printf("\n O vencedor eh o carro %c (ID %d) com distancia %d!\n",
           *(carro + pos), *(id + pos), *(distancia + pos));
}
