#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fonction.h"

void transfert(char *file_name)  
{
    char ligne[taille_maximalle];
    float ST;
    int acc1, acc2, t1 = 0, t2 = 0;
    Account account;

    //ouverture de fichiers
    FILE* fichier = fopen(file_name,"r");
    if (!fichier) 
    {
        printf("Erreur : Impossible d'ouvrir le fichier %s.\n", file_name);
        return;
    }
    FILE* temp = fopen("/Users/mac/Desktop/ProjetEC/csv_files/temp.CSV", "w");
    if (!temp) 
    {
        printf("Erreur : Impossible de créer le fichier temporaire.\n");
        fclose(fichier);
        return;
    }
    printf("Donnee le numero de compte 1 : ");
    scanf("%d", &acc1);
    printf("Donnee le numero de compte 2 : ");
    scanf("%d", &acc2);
    printf("Donner le montant a deposer dans le compte de numero %d: ", acc2); //ST c'est solde a transferer, account1 c'est source
    scanf("%f",&ST);
    while(fgets(ligne, taille_maximalle, fichier))
    {
        sscanf(ligne, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%f,%s",
               &account.account_number, account.first_name, account.last_name,
               account.address, account.email, account.phone,
               &account.balance, account.status);
        if (acc1 == account.account_number)
        {
            if (account.balance > ST && ST > 0)
            {
                t1 = 1;
                account.balance = account.balance - ST; //Retirer de l'argent du account1
            }
            else
            {
                printf("Solde insuffisant\n");
                fclose(fichier);
                fclose(temp);
                remove("/Users/mac/Desktop/ProjetEC/csv_files/temp.CSV");
                return;
            }
        }
        if (acc2 == account.account_number)
        {
            t2 = 1;
            account.balance = account.balance + ST; //Ajouter de l'argent sur le account2
        }


        fprintf(temp, "%d,%s,%s,%s,%s,%s,%.2f,%s\n",
                account.account_number, account.first_name, account.last_name,
                account.address, account.email, account.phone,
                account.balance, account.status);
    }

    if (!t1 || !t2) 
    {
        printf("L'un des comptes n'existe pas.\n");
        fclose(fichier);
        fclose(temp);
        remove("/Users/mac/Desktop/ProjetEC/csv_files/temp.CSV");
        return;
    }
    
    fclose(fichier);
    fclose(temp);

    remove(file_name);
    rename("/Users/mac/Desktop/ProjetEC/csv_files/temp.CSV", file_name);

    FILE* f = fopen("/Users/mac/Desktop/ProjetEC/csv_files/transactions.CSV", "a");
    if (f == NULL)
    {
        printf("Impossible d'ouvrir le fichier\n");
        return;
    }
    fprintf(f, "Transfert de %.3f vers le compte %d est effectuer.\n", ST,acc2);
    fclose(f);
}
/*-------------------------------------------------------------------------
---------------------------------------------------------------------------
---------------------------------------------------------------------------*/
// effectuer un dépôt
void makeDeposit(int acc_num, char file_name[]) {
    Account account;
    float montant;
    char ligne[taille_maximalle];
    int t = 0;
    FILE* fichier = fopen(file_name,"r");
    FILE* temp = fopen("/Users/mac/Desktop/ProjetEC/csv_files/temp.CSV", "w");
    while(fgets(ligne,taille_maximalle,fichier ))
    {
		sscanf(ligne, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%f,%s",
               &account.account_number, account.first_name, account.last_name,
               account.address, account.email, account.phone,
               &account.balance, account.status);

        if (acc_num == account.account_number)
        {
            t = 1;
            printf("Donner le montant a deposer dans votre compte de numero %d: ", acc_num);
            scanf("%f",&montant);
            if (montant > 0) 
            {
                account.balance += montant;
                printf("depot de %.3f effectué avec succès :) pour le compte %d !!\n", montant,account.account_number);
                printf("Nouveau solde : %.3f\n", account.balance);
            }
            else 
            {
                printf("Le montant du dépôt doit être positif :( .\n");
            }
        }
        
                fprintf(temp, "%d,%s,%s,%s,%s,%s,%.2f,%s\n",
                        account.account_number,
                        account.first_name,
                        account.last_name,
                        account.address,
                        account.email,
                        account.phone,
                        account.balance,
                        account.status);
                
    }
    if (!t)
    {
        fclose(fichier);
        fclose(temp);
        printf("le compte n'existe pas!!\n");
        remove("/Users/mac/Desktop/ProjetEC/csv_files/temp.CSV");
        return;

    }
    
    fclose(fichier);
    fclose(temp);
    remove(file_name);
    rename("/Users/mac/Desktop/ProjetEC/csv_files/temp.CSV", file_name);
            
    FILE* f = fopen("/Users/mac/Desktop/ProjetEC/csv_files/transactions.CSV", "a");
    if (f == NULL)
    {
        printf("Impossible d'ouvrir le fichier\n");
        return;
    }
    fprintf(f, "depot de %.3f pour le compte %d est effectuer.\n", montant,acc_num);
    fclose(f);
    
}
//effectuer un retrait
/*-------------------------------------------------------------------------
---------------------------------------------------------------------------
---------------------------------------------------------------------------*/
void makeWithdrawal(int acc_num, char file_name[]) {
    Account account;
    float montant;
    int t = 0;
    char ligne[taille_maximalle];
    FILE* fichier = fopen(file_name,"r");
    FILE* temp = fopen("/Users/mac/Desktop/ProjetEC/csv_files/temp.CSV", "w");
    while(fgets(ligne ,taille_maximalle ,fichier ))
    {
		sscanf(ligne, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%f,%s",
               &account.account_number, account.first_name, account.last_name,
               account.address, account.email, account.phone,
               &account.balance, account.status);

        if (acc_num == account.account_number)
        {
            t = 1;
            printf("Donner le montant a retrait dans votre compte de numero %d: ", acc_num);
            scanf("%f",&montant);
            if (montant > 0 && montant <= account.balance) 
            {
                account.balance -= montant;
                printf("retrait de %.3f effectué avec succès :) pour le compte %d !!\n", montant,account.account_number);
                printf("Nouveau solde : %.3f\n", account.balance);
            }
            else 
            {
                printf("Le montant du retrait doit être positif :( .\n");
            }
        }
        
                fprintf(temp, "%d,%s,%s,%s,%s,%s,%.2f,%s\n",
                        account.account_number,
                        account.first_name,
                        account.last_name,
                        account.address,
                        account.email,
                        account.phone,
                        account.balance,
                        account.status);
                
    }
    if (!t)
    {
        fclose(fichier);
        fclose(temp);
        printf("le compte n'existe pas!!\n");
        remove("/Users/mac/Desktop/ProjetEC/csv_files/temp.CSV");
        return;

    }

    fclose(fichier);
    fclose(temp);
    remove(file_name);
    rename("/Users/mac/Desktop/ProjetEC/csv_files/temp.CSV", file_name);

    FILE* f = fopen("/Users/mac/Desktop/ProjetEC/csv_files/transactions.CSV", "a");
    
    if (f == NULL)
    {
        printf("Impossible d'ouvrir le fichier\n");
        return;
    }
    fprintf(f, "depot de %.3f pour le compte %d est effectuer.\n", montant,acc_num);
    fclose(f);

}
/*-------------------------------------------------------------------------
---------------------------------------------------------------------------
---------------------------------------------------------------------------*/