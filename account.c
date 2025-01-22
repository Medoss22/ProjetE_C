#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "fonction.h"

/*-------------------------------------------------------------------------
---------------------------------------------------------------------------
---------------------------------------------------------------------------*/
// signe up admin
void s_admin()
{
    admin admin;
    pass_admin P_admin;
    FILE *file = fopen(Acc_admin, "a");
    if (file == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier CSV.\n");
        return;
    }

    printf("CNE: ");
    scanf("%s", admin.CNE);

    printf("Nom : ");
    scanf("%s", admin.last_name);

    printf("Prénom : ");
    scanf("%s", admin.first_name);

    printf("Adresse: ");
    scanf("%s", admin.address);

    printf("Email: ");
    scanf("%s", admin.email);

    printf("Téléphone: ");
    scanf("%s", admin.phone);

    printf("Entrez votre mot de passe: ");
    scanf("%s", P_admin.password);
    strcpy(P_admin.CNE_admin, admin.CNE);

    FILE *file1 = fopen(password_admin, "a");
    if (!file1)
    {
        perror("Erreur lors de l'ouverture du fichier CSV");
        return;
    }
    fwrite(&P_admin, sizeof(pass_admin), 1, file1);
    fclose(file1);

    fprintf(file, "%s, %s, %s, %s, %s\n", admin.CNE, admin.last_name, admin.first_name, admin.address, admin.email, admin.phone);
    fclose(file);
    printf("\033[1;32m");
    printf("Admin enregistré avec succès !\n");
    printf("\033[0m");
    printf("------------------------------\n");
}

// fonction qui permete de creer un compte client
void registerAccount(char *filename)
{
    srand(time(NULL));
    Account account;
    pass P;
    char line[taille_maximalle];
    int account_number;
    FILE *file = fopen(filename, "r"); // Open the file in read mode
    if (file == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier CSV.\n");
        return;
    }

    while (fgets(line, taille_maximalle, file))
    {
        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%f,%s",
               &account.account_number, account.first_name, account.last_name,
               account.address, account.email, account.phone,
               &account.balance, account.status);

        account_number = (rand() % 900000) + 100000;
        if (account_number == account.account_number)
        {
            account_number = (rand() % 900000) + 100000;
        }
    }

    fclose(file);
    printf("Nom : ");
    scanf("%s", account.last_name);

    printf("Prénom : ");
    scanf("%s", account.first_name);

    printf("Adresse : ");
    scanf(" %[^\n]", account.address);

    printf("Email : ");
    scanf("%s", account.email);

    printf("Téléphone : ");
    scanf("%s", account.phone);

    printf("Solde initial : ");
    scanf("%f", &account.balance);

    printf("entree le mote de passe: ");
    scanf("%s", P.password);
    P.Acc_nb = account_number;

    strcpy(account.status, "actif"); // Par défaut, le compte est actif

    printf("\033[1;32m");
    printf("Compte enregistré avec succès !\n");
    printf("\033[0m");
    printf("Numéro de compte est : ");
    printf("\033[1;33m");
    printf("%d\n", account_number);
    printf("\033[0m");
    printf("--------------------------------\n");
    printf("--------------------------------\n");
    FILE *file1 = fopen(filename, "a"); // Ouvre le fichier en mode ajout
    if (!file)
    {
        perror("Erreur lors de l'ouverture du fichier CSV");
        return;
    }

    fprintf(file1, "%d, %s, %s, %s, %s, %s, %.2f, %s\n",
            account_number,
            account.last_name,
            account.first_name,
            account.address,
            account.email,
            account.phone,
            account.balance,
            account.status);

    fclose(file1);
    FILE *file2 = fopen(password_c, "a");
    if (!file2)
    {
        perror("Erreur lors de l'ouverture du fichier CSV");
        return;
    }
    fwrite(&P, sizeof(pass), 1, file2);
    fclose(file2);
}

/*-------------------------------------------------------------------------
---------------------------------------------------------------------------
---------------------------------------------------------------------------*/
bool loge_in(int i)
{
    int account_number;
    char CNE[10];
    char password[50];
    pass P;
    pass_admin P_admin;
    if (i == 1)
    {
        FILE *f_admin = fopen(password_admin, "r");
        if (!f_admin)
        {
            printf("Erreur: Impossible d'ouvrir le fichier.\n");
            return false;
        }
        printf("Entrez votre CNE : ");
        scanf("%s", CNE);
        printf("Entrez votre mot de passe : ");
        scanf("%s", password);
        while (fread(&P_admin, sizeof(pass_admin), 1, f_admin))
        {
            if (strcmp(CNE, P_admin.CNE_admin) == 0 && strcmp(password, P_admin.password) == 0)
            {
                fclose(f_admin);
                clearScreen();
                printf("\033[1;32m");
                printf("Connexion réussie.\n");
                printf("\033[1;33m");
                printf("S'il vous plaît, attendez.\n");
                printf("\033[0m");
                sleep(2);
                return true;
            }
        }
    }

    else if (i == 2)
    {
        FILE *file = fopen(password_c, "r");
        if (!file)
        {
            printf("Error: Unable to open the password file.\n");
            return false;
        }

        printf("Entrez votre numéro de compte : ");
        scanf("%d", &account_number);

        printf("Entrez votre mot de passe : ");
        scanf("%s", password);

        rewind(file);
        while (fread(&P, sizeof(pass), 1, file))
        {
            if (account_number == P.Acc_nb && strcmp(password, P.password) == 0)
            {
                fclose(file);
                clearScreen();
                printf("\033[1;32m");
                printf("Connexion réussie.\n");
                printf("\033[1;33m");
                printf("S'il vous plaît, attendez.\n");
                printf("\033[0m");
                sleep(2);
                return true;
            }
        }
    }

    printf("\033[1;31m");
    printf("Numéro de compte ou mot de passe incorrect.\n");
    printf("\033[0m");
    sleep(1);
    return false;
}

/*-------------------------------------------------------------------------
---------------------------------------------------------------------------
---------------------------------------------------------------------------*/

// fonction qui permete de modifier un compte client
void modifyAcc(int num_acc, char *filename)
{
    Account account;
    int choice, found = 0;
    char line[taille_maximalle];
    FILE *file = fopen(filename, "r"); // Open the file in read mode
    if (file == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier CSV.\n");
        return;
    }

    FILE *temp_file = fopen(f_temp, "w");
    if (temp_file == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier CSV.\n");
        fclose(file);
        return;
    }

    while (fgets(line, taille_maximalle, file))
    {
        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%f,%s",
               &account.account_number, account.first_name, account.last_name,
               account.address, account.email, account.phone,
               &account.balance, account.status);

        if (num_acc == account.account_number)
        {
            found = 1;
            printf("\n=== Account Found ===\n");
            printf("1: Modify Address\n");
            printf("2: Modify Email\n");
            printf("3: Modify Phone\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                printf("Enter new address: ");
                scanf(" %[^\n]s", account.address);
                break;
            case 2:
                printf("Enter new email: ");
                scanf(" %s", account.email);
                break;
            case 3:
                printf("Enter new phone: ");
                scanf(" %s", account.phone);
                break;
            default:
                printf("Invalid choice.\n");
                break;
            }
        }

        fprintf(temp_file, "%d,%s,%s,%s,%s,%s,%.2f,%s\n",
                account.account_number,
                account.first_name,
                account.last_name,
                account.address,
                account.email,
                account.phone,
                account.balance,
                account.status);
    }

    fclose(file);
    fclose(temp_file);
    remove(filename);
    rename(f_temp, filename);

    if (!found)
    {
        printf("Le compte n'existe pas!!\n");
        remove(f_temp);
    }
}

/*-------------------------------------------------------------------------
---------------------------------------------------------------------------
---------------------------------------------------------------------------*/

// supprimer un compte
void delete_client(int num, char File_name[])
{
    Account account;
    int t = 0;
    char ligne[taille_maximalle];
    FILE *fichier;
    FILE *temp;

    fichier = fopen(File_name, "r");
    temp = fopen(f_temp, "w");

    while (fgets(ligne, taille_maximalle, fichier))
    {
        sscanf(ligne, "%d", &account.account_number);
        sscanf(ligne, "%s", account.first_name);
        sscanf(ligne, "%s", account.last_name);
        sscanf(ligne, "%s", account.address);
        sscanf(ligne, "%s", account.email);
        sscanf(ligne, "%s", account.phone);
        sscanf(ligne, "%f", account.balance);
        sscanf(ligne, "%s", account.status);
        if (num != account.account_number)
        {
            fprintf(temp, "%s", ligne);
        }
        else
            t = 1;
    }

    fclose(fichier);
    fclose(temp);

    if (t)
    {
        remove(File_name);
        rename(f_temp, File_name);
        printf("le compte est supprime.\n");
    }
    else
    {
        remove(f_temp);
        printf("le compte n'existe pas :( !!!\n");
    }
}

/*-------------------------------------------------------------------------
---------------------------------------------------------------------------
---------------------------------------------------------------------------*/

// affichier les listes de compte
void displayaccounts(char filename[])
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("erreur:impossible d'ouvrir le fichier %s \n", filename);
        return;
    }
    Account account;
    char ligne[taille_maximalle];
    printf("\n Liste des comptes enregistrés:\n");
    printf("------------------------------------------------------------------------------------------------\n");
    printf("Numéro de compte|Nom|Prénom|Solde|Email|Statut du compte\n");
    printf("------------------------------------------------------------------------------------------------\n");
    while (fgets(ligne, sizeof(ligne), file) != NULL)
    {
        printf("%s", ligne);
        printf("\033[1;34m");
        printf("----------------------------------------------------------------------------\n");
        printf("----------------------------------------------------------------------------\n");
        printf("\033[0m");
    }
    fclose(file);
}
/*-------------------------------------------------------------------------
---------------------------------------------------------------------------
---------------------------------------------------------------------------*/

int recherche_Compte(char File_name[])
{
    int num;
    char nom[50], ligne[taille_maximalle];
    int i = 0;
    Account account;
    FILE *fichier;
    fichier = fopen(File_name, "r");
    if (!fichier)
    {
        printf("Erreur: Impossible d'ouvrir le fichier.\n");
        return -1;
    }

    printf("enter le numero du compte :");
    scanf("%d", &num);
    while (fgets(ligne, taille_maximalle, fichier) != NULL)
    {
        sscanf(ligne, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%f,%9s",
               &account.account_number, account.first_name, account.last_name,
               account.address, account.email, account.phone,
               &account.balance, account.status);
        i++;
        if (account.account_number == num)
        {
            fclose(fichier);
            printf("------------------------------\n");
            printf("------------------------------\n");
            printf("Le compte existe (index %d).\n", i);
            printf("------------------------------\n");
            printf("------------------------------\n");
            return i; // retourner indice account
        }
    }
    fclose(fichier);
    printf("le compte n'existe pas!!\n");
    return -1; // compte introuvable
}
/*-------------------------------------------------------------------------
---------------------------------------------------------------------------
---------------------------------------------------------------------------*/
// de trier les comptes dans le fishier CSV par solde
void trier_compte(char File_name[])
{
    Account accounts[taille_maximalle];
    int t = 0;
    char ligne[taille_maximalle];
    FILE *fichier = fopen(File_name, "r");
    if (!fichier)
    {
        printf("Erreur : Impossible d'ouvrir le fichier %s.\n", File_name);
        return;
    }
    FILE *stored = fopen(f_stored, "w"); // le fishier dans le quelle on peut stockee les comte trier
    if (!fichier)
    {
        printf("Erreur : Impossible d'ouvrir le fichier %s.\n", f_stored);
        return;
    }

    Account temp;
    while (fgets(ligne, taille_maximalle, fichier))
    {
        Account account;
        sscanf(ligne, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%f,%s",
               &account.account_number, account.first_name, account.last_name,
               account.address, account.email, account.phone,
               &account.balance, account.status);
        accounts[t] = account;
        t++;
    }
    fclose(fichier);
    for (int i = 0; i < t; i++)
    {
        for (int j = i + 1; j < t; j++)
        {
            if (accounts[i].balance < accounts[j].balance)
            {
                temp = accounts[i];
                accounts[i] = accounts[j];
                accounts[j] = temp;
            }
        }
    }
    for (int i = 0; i < t; i++)
    {
        fprintf(stored, "%d,%s,%s,%s,%s,%s,%.2f,%s\n",
                accounts[i].account_number, accounts[i].first_name, accounts[i].last_name,
                accounts[i].address, accounts[i].email, accounts[i].phone,
                accounts[i].balance, accounts[i].status);
    }
    fclose(stored);
    printf("Tri des comptes effectué avec succès.\n");
}
/*-------------------------------------------------------------------------
---------------------------------------------------------------------------
---------------------------------------------------------------------------*/