#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char FILENAME[] = "dados.txt";
char FILENAME_AUX[] = "auxiliar.txt";

typedef struct dado {
    int id;
    char titulo[50];
    char tipo[10];
    int ano;
    char genero[50];
    int classificacao;
    int duracao;
    int like;
    int dislike;
} Filme;

void titulo(){
    system("cls");
    printf(" _   _   _____   _    _   _____    _____   _       _   _     _     \n");
    printf("| | | | | ____| |  \\ | | |  __ \\  |  ___| | |     | | \\ \\  / / \n");
    printf("| | | | | |__   |   \\| | | |__| | | |__   | |     | |  \\ \\/ /   \n");
    printf("| | | | |  __|  | |\\ | | |  ___/  |  __|  | |     | |   \\ \\/    \n");
    printf("| |_| | | |___  | | \\  | | |      | |     | |___  | |   / / \\    \n");
    printf("\\_____/ |_____| |_|  \\_| |_|      |_|     |_____| |_|  /_/ \\_\\  \n");
    printf("\n");
}

int verifica_id(){
    int id=0;
    Filme aux;
    FILE * arquivo = fopen(FILENAME, "rb");

    if(arquivo == NULL){
        printf("ERRO AO ABRIR O ARQUIVO!\n");
        exit(1);
    }
    while(fread(&aux, sizeof(Filme), 1, arquivo)){
        id = aux.id;
    }

    fclose(arquivo);
    return id;
}

void troca_dados(){
    Filme aux;

    fclose(fopen(FILENAME, "wb"));
    FILE * arquivo = fopen(FILENAME, "ab");
    FILE * arquivo2 = fopen(FILENAME_AUX, "rb");

    if (arquivo == NULL || arquivo2 == NULL){
        printf("ERRO AO ABRIR O ARQUIVO!\n");
        exit(1);
    }
    while(fread(&aux, sizeof(Filme), 1, arquivo2)){
        fwrite(&aux, sizeof(Filme), 1, arquivo);
    }

    fclose(arquivo2);
    fclose(arquivo);
}
int cadastrar(int id){
    titulo();
    int result;
    Filme aux;
    FILE * arquivo = fopen(FILENAME, "ab");

    if (arquivo == NULL){
        printf("ERRO AO ABRIR O ARQUIVO!\n");
        exit(1);
    }

    aux.id = id;
    printf("Titulo: ");
    fgets(aux.titulo, 50, stdin);
    aux.titulo[strlen(aux.titulo) - 1] = '\0';
    printf("Tipo: ");
    fgets(aux.tipo, 10, stdin);
    aux.tipo[strlen(aux.tipo) - 1] = '\0';
    printf("Ano de lancamento: ");
    scanf("%d", &aux.ano);
    getchar();
    printf("Genero: ");
    fgets(aux.genero, 50, stdin);
    aux.genero[strlen(aux.genero) - 1] = '\0';
    printf("Classificacao indicativa: ");
    scanf("%d", &aux.classificacao);
    printf("Duracao (minutos): ");
    scanf("%d", &aux.duracao);
    printf("Likes: ");
    scanf("%d", &aux.like);
    printf("Dislikes: ");
    scanf("%d", &aux.dislike);
    result = fwrite(&aux, sizeof(Filme), 1, arquivo);
    fclose(arquivo);

    return result;
}
void listar(){
    titulo();
    Filme aux;
    FILE * arquivo = fopen(FILENAME, "rb");

    if (arquivo == NULL){
        printf("ERRO AO ABRIR O ARQUIVO!\n");
        exit(1);
    }
    while(fread(&aux, sizeof(Filme), 1, arquivo)){
        printf("Id: %d\n", aux.id);
        printf("Titulo: %s\n", aux.titulo);
        printf("Tipo: %s\n", aux.tipo);
        printf("Ano: %d\n", aux.ano);
        printf("Genero: %s\n", aux.genero);
        printf("Classificacao indicativa: %d anos\n", aux.classificacao);
        printf("Duracao: %d minutos\n", aux.duracao);
        printf("Likes: %d\n", aux.like);
        printf("Dislikes: %d\n", aux.dislike);
        printf("\n");
    }
    system("pause");
    system("cls");
}
void consultar(){
    titulo();
    Filme aux;
    int n, status = 0;
    FILE * arquivo = fopen(FILENAME, "rb");

    if (arquivo == NULL){
        printf("ERRO AO ABRIR O ARQUIVO!\n");
        exit(1);
    }
    printf("Digite o ID desejado: ");
    scanf("%d", &n);
    while(fread(&aux, sizeof(Filme), 1, arquivo)){
        if(n == aux.id){
            status = 1;
            break;
        }
    }
    if(status){
        printf("\nId: %d\n", aux.id);
        printf("Titulo: %s\n", aux.titulo);
        printf("Tipo: %s\n", aux.tipo);
        printf("Ano: %d\n", aux.ano);
        printf("Genero: %s\n", aux.genero);
        printf("Classificacao indicativa: %d anos\n", aux.classificacao);
        printf("Duracao: %d minutos\n", aux.duracao);
        printf("Likes: %d\n", aux.like);
        printf("Dislikes: %d\n\n", aux.dislike);
    }else{
        printf("\nRegistro nao encontrado!\n\n");
    }
    system("pause");
}
void alterar(){
    fclose(fopen(FILENAME_AUX, "wb"));
    titulo();
    Filme aux, aux2;
    int n, status = 0, result, flag=0;
    FILE * arquivo = fopen(FILENAME, "rb");
    FILE * arquivo2 = fopen(FILENAME_AUX, "ab");

    if (arquivo == NULL || arquivo2 == NULL){
        printf("ERRO AO ABRIR O ARQUIVO!\n");
        exit(1);
    }

    printf("Digite o ID desejado: ");
    scanf("%d", &n);
    getchar();

    while(fread(&aux, sizeof(Filme), 1, arquivo)){
        if(n == aux.id){
            flag = 1;
            aux2.id = aux.id;
            printf("\nTitulo: ");
            fgets(aux2.titulo, 50, stdin);
            aux2.titulo[strlen(aux2.titulo) - 1] = '\0';
            printf("Tipo: ");
            fgets(aux2.tipo, 10, stdin);
            aux2.tipo[strlen(aux2.tipo) - 1] = '\0';
            printf("Ano de lancamento: ");
            scanf("%d", &aux2.ano);
            getchar();
            printf("Genero: ");
            fgets(aux2.genero, 50, stdin);
            aux2.genero[strlen(aux2.genero) - 1] = '\0';
            printf("Classificacao indicativa: ");
            scanf("%d", &aux2.classificacao);
            printf("Duracao (minutos): ");
            scanf("%d", &aux2.duracao);
            printf("Likes: ");
            scanf("%d", &aux2.like);
            printf("Dislikes: ");
            scanf("%d", &aux2.dislike);
            result = fwrite(&aux2, sizeof(Filme), 1, arquivo2);
            continue;
        }else{
            fwrite(&aux, sizeof(Filme), 1, arquivo2);
        }
    }

    if(flag){
        printf("\nRegistro alterado com sucesso!\n\n");
    } else {
        printf("\nRegistro nao encontrado!\n\n");
    }

    fclose(arquivo2);
    fclose(arquivo);
    troca_dados();

    system("pause");
}
void excluir(){
    titulo();
    fclose(fopen(FILENAME_AUX, "wb"));
    Filme aux, aux2;
    int n, status = 0, result, flag=0;
    FILE * arquivo = fopen(FILENAME, "rb");
    FILE * arquivo2 = fopen(FILENAME_AUX, "ab");
    if (arquivo == NULL || arquivo2 == NULL){
        printf("ERRO AO ABRIR O ARQUIVO!\n");
        exit(1);
    }
    printf("Digite o ID desejado: ");
    scanf("%d", &n);
    getchar();
    while(fread(&aux, sizeof(Filme), 1, arquivo)){
        if(n == aux.id){
            flag = 1;
            continue;
        } else {
            fwrite(&aux, sizeof(Filme), 1, arquivo2);
        }
    }

    if(flag){
        printf("\nRegistro excluido com sucesso!\n\n");
    } else {
        printf("\nRegistro nao encontrado!\n\n");
    }
    fclose(arquivo2);
    fclose(arquivo);
    troca_dados();
    system("pause");
}


int main(){
    int op, id;
    id = verifica_id();
    do{
        titulo();
        printf("[1] Cadastrar\n[2] Consultar\n[3] Listar\n[4] Alterar\n[5] Excluir\n[0] Sair\nOpcao: ");
        scanf("%d", &op);
        getchar();
        switch (op) {
            case 1:
                id++;
                if (cadastrar(id)){
                    printf("Item cadastrado com sucesso!\n");
                } else {
                    printf("Nao foi possivel cadastrar!\n");
                }
                break;
            case 2:
                consultar();
                break;
            case 3:
                listar();
                break;
            case 4:
                alterar();
                break;
            case 5:
                excluir();
                break;
        }
    }while(op != 0);

    return 0;
}
