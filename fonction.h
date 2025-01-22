#include <stdbool.h>
#define taille_maximalle 1000
#define Acc_csv "/Users/mac/Desktop/ProjetEC/csv_files/accounts.csv"
#define Acc_admin "/Users/mac/Desktop/ProjetEC/csv_files/Admin.csv"
#define password_admin "/Users/mac/Desktop/ProjetEC/csv_files/password_admin.dat"
#define password_c "/Users/mac/Desktop/ProjetEC/csv_files/password.dat"
#define f_temp "/Users/mac/Desktop/ProjetEC/csv_files/temp.CSV"
#define f_stored "/Users/mac/Desktop/ProjetEC/csv_files/stored.CSV"
#define transactions_f "/Users/mac/Desktop/ProjetEC/csv_files/transactions.CSV"

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