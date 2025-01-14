#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonction.h"


// Fichier CSV pour stocker les comptes
#define ACCOUNT_FILE "data/accounts.csv"

// Fonction pour enregistrer un nouveau compte
/*void registerAccount(char *filename) {
    Account account;
    printf("Numéro de compte : ");
    scanf("%d", &account.account_number);

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

    strcpy(account.status, "actif"); // Par défaut, le compte est actif

    printf("Compte enregistré avec succès !\n");
    printf("--------------------------------\n");
    printf("********************************\n");
    printf("--------------------------------\n");    
    FILE *file = fopen(filename, "a"); // Ouvre le fichier en mode ajout
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier CSV");
        return;
    }

    fprintf(file, "%d, %s, %s, %s, %s, %s, %.2f, %s\n",
            account.account_number,
            account.last_name,
            account.first_name,
            account.address,
            account.email,
            account.phone,
            account.balance,
            account.status);

    fclose(file);
}
*/
/*-------------------------------------------------------------------------
---------------------------------------------------------------------------
---------------------------------------------------------------------------*/

//affichier les listes de compte
void displayaccounts(char filename[]){
    FILE*file=fopen(filename,"r");
    if(file==NULL){
            printf("erreur:impossible d'ouvrir le fichier %s \n",filename);
return ;} 
Account account;
char ligne[taille_maximalle];
printf("\n Liste des comptes enregistrés:\n"); 
printf("------------------------------------------------------------------------------------------------\n");
printf("Numéro de compte|Nom|Prénom|Solde|Email|Statut du compte\n");
printf("------------------------------------------------------------------------------------------------\n");
while(fgets(ligne, sizeof(ligne),file) != NULL){
    printf("%s", ligne);
    printf("----------------------------------------------------------------------------\n");
    printf("----------------------------------------------------------------------------\n");

}
fclose(file);
}

/*-------------------------------------------------------------------------
---------------------------------------------------------------------------
---------------------------------------------------------------------------*/

//fonction qui permete de modifier un compte client
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
    
    FILE *temp_file = fopen("/Users/mac/Desktop/ProjetEC/csv_files/temp.CSV", "w");
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
                    scanf(" %49s", account.email);
                    break;
                case 3:
                    printf("Enter new phone: ");
                    scanf(" %49s", account.phone);
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
    rename("/Users/mac/Desktop/ProjetEC/csv_files/temp.CSV", filename);

    if(!found)
    {
        printf("Le compte n'existe pas!!\n");
        remove("/Users/mac/Desktop/ProjetEC/csv_files/temp.CSV");
    }
}

/*-------------------------------------------------------------------------
---------------------------------------------------------------------------
---------------------------------------------------------------------------*/

//supprimer un compte 
void delete_client(int num, char File_name[]){
    Account account;
	int t=0;
	char ligne[taille_maximalle];
	FILE* fichier; 
	FILE* temp;
	
	fichier = fopen(File_name,"r");
	temp = fopen("/Users/mac/Desktop/ProjetEC/csv_files/temp.CSV", "w");
	
	while(fgets(ligne,taille_maximalle,fichier )){
		sscanf(ligne,"%d",&account.account_number);
        sscanf(ligne,"%s",account.first_name);
        sscanf(ligne,"%s",account.last_name);
        sscanf(ligne,"%s",account.address);
        sscanf(ligne,"%s",account.email);
        sscanf(ligne,"%s",account.phone);
        sscanf(ligne,"%f",account.balance);
        sscanf(ligne,"%s",account.status);
		if(num != account.account_number){
		 fprintf(temp,"%s",ligne);}
		else
		t = 1;
	}

	fclose(fichier);	 
    fclose(temp);
    
	    if(t){
    	remove(File_name);
    	rename("/Users/mac/Desktop/ProjetEC/csv_files/temp.CSV",File_name);
    	printf("le compte est supprime.\n");}
	    else {
        remove("/Users/mac/Desktop/ProjetEC/csv_files/temp.CSV");
	    printf("le compte n'existe pas :( !!!"); }
} 
/*-------------------------------------------------------------------------
---------------------------------------------------------------------------
---------------------------------------------------------------------------*/

//de trier les comptes dans le fishier CSV par solde
void trier_compte(char File_name[])
{
    Account accounts[taille_maximalle];
    int t=0; 
    char ligne[taille_maximalle];
    FILE* fichier = fopen(File_name,"r");
    if (!fichier) 
    {
        printf("Erreur : Impossible d'ouvrir le fichier %s.\n", File_name);
        return;
    }
    FILE* stored = fopen("/Users/mac/Desktop/ProjetEC/csv_files/stored.CSV","w"); // le fishier dans le quelle on peut stockee les comte trier
    if (!fichier) 
    {
        printf("Erreur : Impossible d'ouvrir le fichier %s.\n", "/Users/mac/Desktop/ProjetEC/csv_files/stored.CSV");
        return;
    }

    Account temp;
    while(fgets(ligne,taille_maximalle,fichier ))
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
int recherche_Compte(char File_name[]) {
  	int num;
	char nom[50],ligne[taille_maximalle];
    int i=0;
    Account account ;
    FILE* fichier;
    fichier=fopen(File_name,"r");
    if (!fichier) {
        printf("Erreur: Impossible d'ouvrir le fichier.\n");
        return -1;
    }
    /*
    printf("entrez votre nom s'il vous plait!!");
    scanf("%s",nom);
    */
    printf("enter le numero du compte :");
    scanf("%d",&num);
    while(fgets(ligne,taille_maximalle,fichier)!=NULL){
            sscanf(ligne, "%d,%49[^,],%49[^,],%99[^,],%99[^,],%14[^,],%f,%9s",
                   &account.account_number, account.first_name, account.last_name,
                   account.address, account.email, account.phone,
                   &account.balance, account.status);
            i++;
            if ((account.account_number == num) /*&& (strcmp(account.last_name,nom)==0)*/){    
                fclose(fichier);
                printf("------------------------------\n");
                printf("------------------------------\n");
                printf("Le compte existe (index %d).\n", i);
                printf("------------------------------\n");
                printf("------------------------------\n");
                return i; // retourner indice account
            }
	 	      
     	}
        fclose (fichier);
        printf("le compte n'existe pas!!\n");
        return -1; //compte introuvable
	    }


 /*
  int recherche_Compte(char File_name[],Account account []) {
  	int num;
	char nom,ligne[taille_maximalle];
    int i=0;
    File*fichier;
    fichier=fopen(File_name,"r");
    printf("entrez votre nom s'il vous plait!!");
    gets(nom);
    printf("enter le numero du compte :");
    scanf("%d",&num);
    while(fgets(ligne,taille_maximalle,fichier)!=NULL){
            if ((account.account_number == num )&&(strcmp(account[i].last_name,nom)==0)){    
            	fclose(fichier);
                return i; // retourner indice account
            }
	 	      i++;
     	}
			fclose (fichier);
                return -1; //compte introuvable
	    } 
*/


void registerAccount(char *filename) {
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
    scanf("%s",P.password);
    P.Acc_nb = account_number;

    strcpy(account.status, "actif"); // Par défaut, le compte est actif

    printf("Compte enregistré avec succès !\n");
    printf("Numéro de compte est : %d\n", account_number);
    printf("--------------------------------\n");
    printf("--------------------------------\n");    
    FILE *file1 = fopen(filename, "a"); // Ouvre le fichier en mode ajout
    if (!file) {
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
    FILE *file2 = fopen("/Users/mac/Desktop/ProjetEC/csv_files/password.dat", "a"); 
    if (!file2) {
        perror("Erreur lors de l'ouverture du fichier CSV");
        return;
    }
    fwrite(&P, sizeof(pass), 1, file2);
    fclose(file2);
}


/*-------------------------------------------------------------------------
---------------------------------------------------------------------------
---------------------------------------------------------------------------*/
bool loge_in() {
    int account_number;
    char password[50];
    pass P;

    FILE *file = fopen("/Users/mac/Desktop/ProjetEC/csv_files/password.dat", "r");
    if (!file) { 
        printf("Error: Unable to open the password file.\n");
        return false;
    }

    printf("Entrez votre numéro de compte : ");
    scanf("%d", &account_number);

    printf("Entrez votre mot de passe : ");
    scanf("%49s", password); 

    while (fread(&P, sizeof(pass), 1, file)) {
        if (account_number == P.Acc_nb && strcmp(password, P.password) == 0) {
            fclose(file); 
            printf("Connexion réussie.\n");
            return true;
        }
    }

    fclose(file);
    printf("Numéro de compte ou mot de passe incorrect.\n");
    return false;
}