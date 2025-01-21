#include <stdbool.h>
#define taille_maximalle 1000


typedef struct {
    char CNE[10];
    char first_name[50];
    char last_name[50];
    char address[100];
    char email[50];
    char phone[15];
} admin;
typedef struct {
    int account_number;
    char first_name[50];
    char last_name[50];
    char address[100];
    char email[50];
    char phone[15];
    float balance;
    char status[10];  // "actif" ou "inactif"
} Account;

typedef struct 
{
    int Acc_nb;
    char password[50];
}pass;

typedef struct
{
    char CNE_admin[10];
    char password[50];
}pass_admin;


// Fonctions liées à la gestion des comptes
void registerAccount(char *filename); //ajouter un compte client
void displayaccounts( char filename[]); //affichier les listes de compte client
void modifyAcc(int num_acc, char *filename); //modifier un compte client
void delete_client(int num, char File_name[]); //supprimer un compte client
void transfert(char *file_name); //fait un transfert d'argent
void makeDeposit( int acc_num, char file_name[]); //effectuer un dépot
void makeWithdrawal(int acc_num, char file_name[]); //effectuer un retrait
void trier_compte(char File_name[]); //de trier les comptes dans le fishier CSV par solde
int recherche_Compte(char File_name[]); //recherche un compte client
bool loge_in(int i); //connexion au systeme
void showMenu2(); //Efface ou quitter
void menu0(); //menu principal
void start(); //fonction principale
void s_admin(); // ajouter un admin
void clearScreen(); // Efface l'écran
void menu_C(); //menu du client
void menu_admin(); //menu de l'admin