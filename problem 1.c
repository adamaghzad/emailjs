#include <stdio.h>
#include <stdlib.h>

struct client
{
    int id;
    char nom[50];
    float salaire;
    int heuresTravaillees;
};

int main()
{

    struct client* clients = NULL;
    int Nclients;
    int Caclients = 0;
    int DerID = 0;


    clients = malloc(Caclients * sizeof(struct client));

    if (clients == NULL)
    {
        printf("Erreur lors de l'allocation de la mémoire.\n");
        return 1;
    }

    do
    {

        printf("Entrez le nombre clients : ");
        scanf("%d", &Nclients);


        if (Nclients > Caclients)
        {

            Caclients = Nclients;
            clients = realloc(clients, Caclients * sizeof(struct client));

            if (clients == NULL)
            {
                printf("Erreur lors de la réallocation de la mémoire.\n");
                return 1;
            }
        }


        printf("Entrez le dernier ID utilisé : ");
        scanf("%d", &DerID);


        for (int i = 0; i < Nclients; ++i)
        {
            clients[i].id = DerID + 1;
            DerID = clients[i].id;
            printf("\nEntrez les informations pour client %d :\n",DerID);
            printf("Nom : ");
            scanf("%s", clients[i].nom);
            printf("Salaire : ");
            scanf("%f", &clients[i].salaire);
            printf("Heures travaillees : ");
            scanf("%d", &clients[i].heuresTravaillees);

            char nomFichier[50];
            sprintf(nomFichier, "%d_%s.txt", clients[i].id, clients[i].nom);
            FILE* fichierclient = fopen(nomFichier, "w");

            if (fichierclient == NULL)
            {
                printf("Erreur lors de l'ouverture du fichier pour l'client %d.\n", i + 1);
                return 1;
            }

            fprintf(fichierclient, "ID: %d\nNom: %s\nSalaire: %.2f\nHeures travaillees: %d\n",
                    clients[i].id, clients[i].nom, clients[i].salaire, clients[i].heuresTravaillees);

            fclose(fichierclient);
        }

        FILE* fichierGlobal = fopen("clients_global.txt", "a");
        if (fichierGlobal == NULL)
        {
            printf("Erreur lors de l'ouverture du fichier global.\n");
            return 1;
        }

        for (int i = 0; i < Nclients; ++i)
        {
            fprintf(fichierGlobal, "ID: %d\nNom: %s\nSalaire: %.2f\nHeures travaillees: %d\n\n",
                    clients[i].id, clients[i].nom, clients[i].salaire, clients[i].heuresTravaillees);
        }

        fclose(fichierGlobal);

        printf("Processus d'ajout terminé.\n");

        printf("Voulez-vous ajouter un autre client ? (1 pour Oui, 0 pour Non) : ");
        scanf("%d", &Nclients);

    }
    while (Nclients == 1);

    free(clients);

    return 0;
}
