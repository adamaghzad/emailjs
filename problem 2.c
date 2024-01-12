#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Article {
    int code;
    char nom[50];
    float PRUN;
};

void LIAR(struct Article articles[], int n) {
    for (int i = 0; i < n; ++i) {
        printf("\nEnter information for article %d:\n", i + 1);

        printf("\nCode: ");
        scanf("%d", &articles[i].code);
        printf("\nNom: ");
        scanf("%s", articles[i].nom);
        printf("\nPrix unitaire: ");
        scanf("%f", &articles[i].PRUN);
    }
}

void AFFAR(struct Article articles[], int n) {
    printf("\nList of Articles:\n");
    for (int i = 0; i < n; ++i) {
        printf("Code: %d, Nom: %s, Prix unitaire: %.2f\n", articles[i].code, articles[i].nom, articles[i].PRUN);
    }
}

void SUPAR(struct Article articles[], int *n, int code) {
    int i, j;
    for (i = 0; i < *n; ++i) {
        if (articles[i].code == code) {
            for (j = i; j < *n - 1; ++j) {
                articles[j] = articles[j + 1];
            }
            (*n)--;
            printf("Article with code %d deleted successfully.\n", code);
            return;
        }
    }
    printf("Article with code %d not found.\n", code);
}

void AJART(struct Article articles[], int *n) {
    if (*n == 0) {
        articles = (struct Article *)malloc(sizeof(struct Article));
    } else {
        articles = (struct Article *)realloc(articles, (*n + 1) * sizeof(struct Article));
    }

    printf("\nEnter information for the new article:\n");
    printf("Code: ");
    scanf("%d", &articles[*n].code);
    printf("Nom: ");
    scanf("%s", articles[*n].nom);
    printf("Prix unitaire: ");
    scanf("%f", &articles[*n].PRUN);
    (*n)++;

    char fileName[50];
    sprintf(fileName, "%d_%s.txt", articles[*n - 1].code, articles[*n - 1].nom);
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fprintf(file, "Code: %d\nNom: %s\nPrix unitaire: %.2f\n", articles[*n - 1].code, articles[*n - 1].nom, articles[*n - 1].PRUN);
    fclose(file);

    printf("Article added successfully.\n");

    SAART(articles, *n);
}

void triByNom(struct Article articles[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (strcmp(articles[j].nom, articles[j + 1].nom) > 0) {
                struct Article temp = articles[j];
                articles[j] = articles[j + 1];
                articles[j + 1] = temp;
            }
        }
    }

    AFFAR(articles, n);
}

void triByPrix(struct Article articles[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (articles[j].PRUN < articles[j + 1].PRUN) {
                struct Article temp = articles[j];
                articles[j] = articles[j + 1];
                articles[j + 1] = temp;
            }
        }
    }

    AFFAR(articles, n);
}

void SAALLAR(struct Article articles[], int n) {
     FILE *file = fopen("all_articles.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(file, "Code\tNom\tPrix unitaire\n");
    for (int i = 0; i < n; ++i) {
        fprintf(file, "%d\t%s\t%.2f\n", articles[i].code, articles[i].nom, articles[i].PRUN);
    }

    fclose(file);
    printf("All articles saved successfully.\n");
}


void SAART(struct Article articles[], int n) {
    int lastArticleIndex = n - 1;
    char fileName[50];
    sprintf(fileName, "%d_%s-info.txt", articles[lastArticleIndex].code, articles[lastArticleIndex].nom);
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fprintf(file, "Code: %d\nNom: %s\nPrix unitaire: %.2f\n", articles[lastArticleIndex].code, articles[lastArticleIndex].nom, articles[lastArticleIndex].PRUN);
    fclose(file);
    printf("Article information saved successfully.\n");
}

int main() {
    int choice;
    int n = 0;
    struct Article *articles = NULL;

    do {
        printf("\nMenu:\n");
        printf("1: Lire les articles\n");
        printf("2: Afficher les articles classés par ordre alphabétique des noms\n");
        printf("3: Afficher les articles classés du plus cher au moins cher\n");
        printf("4: Ajouter un nouvel article\n");
        printf("5: Supprimer un article\n");
        printf("6: Enregistrer les articles\n");
        printf("7: Quitter le programme\n");
        printf("Tapez votre choix: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEntrez le nombre d'articles: ");
                scanf("%d", &n);
                articles = malloc(n * sizeof(struct Article));
                LIAR(articles, n);
                break;
            case 2:
                triByNom(articles, n);
                break;
            case 3:
                triByPrix(articles, n);
                break;
            case 4:
                AJART(articles, &n);
                break;
            case 5:
                if (n > 0) {
                    int code;
                    printf("\nEntrez le code de l'article à supprimer: ");
                    scanf("%d", &code);
                    SUPAR(articles, &n, code);
                } else {
                    printf("Aucun article à supprimer. Ajoutez des articles d'abord.\n");
                }
                break;
            case 6:
                SAALLAR(articles, n);
                break;
            case 7:
                printf("Quitter le programme.\n");
                break;
            default:
                printf("Choix invalide. Réessayez.\n");
        }

    } while (choice != 7);

    free(articles);

    return 0;
}
