#include <stdbool.h>
#define taille_maximalle 1000


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


// Fonctions liées à la gestion des comptes
void registerAccount(char *filename);
void displayaccounts( char filename[]);
void modifyAcc(int num_acc, char *filename);
void modifyAccCSV(char *filename, int num_copmte);
void delete_client(int num, char File_name[]);
void transfert(char *file_name);
void makeDeposit( int acc_num, char file_name[]);
void makeWithdrawal(int acc_num, char file_name[]);
void trier_compte(char File_name[]);
int recherche_Compte(char File_name[]);
bool loge_in();
void showMenu();
void showMenu2();
void menu0();
void start();
