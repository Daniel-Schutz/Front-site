#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kdtree.h"

typedef struct _restaurantes
{
    int linha;
    char address[100];
    char categories[100];
    char city[100];
    char country[100];
    float latitude;
    float longitude;
    char name[100];
    int postalCode;
    char province[3];
    char websites[800];
} restaurante;

int compara_restaurantes(const void *a, const void *b, int altura)
{
    restaurante *restaurante_a = (restaurante *)a;
    restaurante *restaurante_b = (restaurante *)b;

    if (altura % 2 == 0)
    {
        if (restaurante_a->latitude < restaurante_b->latitude)
            return -1;
        else if (restaurante_a->latitude > restaurante_b->latitude)
            return 1;
        else
            return 0;
    }
    else
    {
        if (restaurante_a->longitude < restaurante_b->longitude)
            return -1;
        else if (restaurante_a->longitude > restaurante_b->longitude)
            return 1;
        else
            return 0;
    }
}

void imprimir_arvore_restaurante(tno *no)
{
    if (no != NULL)
    {
        restaurante *restaurante_atual = (restaurante *)no->item;
        printf("\n");
        printf("restaurante: %s\n", restaurante_atual->name);

        printf("\n");

        imprimir_arvore_restaurante(no->esq);
        imprimir_arvore_restaurante(no->dir);
    }
}

void imprimir_nos(tno **nos, int quantidade)
{
    printf("\nRestaurante mais proximo:");
    for (int i = 0; i < quantidade; i++)
    {
        if (nos[i] != NULL)
        {
            restaurante *restaurante_atual = (restaurante *)nos[i]->item;
            printf("\n");
            printf("restaurante: %s\n\n", restaurante_atual->name);
        }
        else
        {
            printf("restaurantes mais proximos ja encontradas\n");
        }
    }
}

int main()
{
    tarv *arvore = criar_arvore(compara_restaurantes);
    FILE *arquivo = fopen("Fast_Food_Restaurantscerto.txt", "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char linha[900];
    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        restaurante *r = malloc(sizeof(restaurante));

        sscanf(linha, "%d,%[^,],%[^,],%[^,],%[^,],%f,%f,%[^,],%d,%[^,],%[^\n]",
               &r->linha, r->address, r->categories, r->city, r->country, &r->latitude, &r->longitude, r->name, &r->postalCode, r->province, r->websites);

        inserir_no(arvore, r);

        /*printf("ID: %d\n", r.linha);
        printf("Endereço: %s\n", r.address);
        printf("Tipo: %s\n", r.categories);
        printf("restaurante: %s\n", r.city);
        printf("País: %s\n", r.country);
        printf("Latitude: %f\n", r.latitude);
        printf("Longitude: %f\n", r.longitude);
        printf("Nome: %s\n", r.name);
        printf("CEP: %d\n", r.postalCode);
        printf("Estado: %s\n", r.province);
        printf("URLs: %s\n", r.websites);
        printf("--------------------------\n");*/
    }

    // imprimir_arvore_restaurante(arvore->raiz);

    fclose(arquivo);

    restaurante restaurante_busca;
    int quantidade_proximos = 1;
    int opcao;
    do
    {
        printf("1 - Buscar restaurante\n");
        printf("2 - Encerrar Programa\n");
        scanf("%d", &opcao);
        if (opcao < 1 || opcao > 2)
        {
            printf("\nEscreva um numero valido!\n");
        }
        if (opcao == 1)
        {
            printf("\nDigite a latitude que voce deseja pesquisar:");
            scanf("%f", &restaurante_busca.latitude);
            printf("\nDigite a longitude que voce deseja pesquisar:");
            scanf("%f", &restaurante_busca.longitude);
            tno **nos_proximos = encontrar_proximo(arvore, &restaurante_busca, quantidade_proximos, compara_restaurantes);
            imprimir_nos(nos_proximos, quantidade_proximos);
        }

    } while (opcao != 2);
    deletar_arvore(arvore);
    // 36.11447,-115.0665

    return 0;
}
