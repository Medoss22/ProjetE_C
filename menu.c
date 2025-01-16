#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "fonction.h"

void showMenu() {
    printf("\n=== Menu de gestion bancaire ===\n");
    printf("1. Modifier un compte\n");
    printf("2. Supprimer un compte\n");
    printf("3. Afficher tous les comptes\n");
    printf("4. Fait un dépôt\n");
    printf("5. Fait un retrait\n");
    printf("6. Fait un transfert\n");
    printf("7. Rechercher un compte par le numéro de compte\n");
    printf("8. Trier les comptes par solde\n");
    printf("0. Quitter\n");
    printf("Votre choix : ");
}

void menu0()
{
    printf("Bienvenue dans notre application de gestion bancaire\n");
        printf("-----------------------------------------------------\n");
        printf("1. Sign Up\n");
        printf("2. Log In\n");
        printf("0. Quit\n");
        printf("Votre choix : ");
}

void showMenu2() {
    int a;
    printf("Entrez 1 pour retourner au menu principal ou 0 pour quitter : ");
    scanf("%d", &a);
    if (a == 0) {
        // Cross-platform clearing and exit message
        #ifdef _WIN32
            system("cls"); // Clear screen for Windows
        #else
            system("clear"); // Clear screen for macOS/Linux
        #endif
        printf("(^^) Au revoir !!\n");
        exit(0);
    } else {
        // Cross-platform clearing for return to the main menu
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
}

void start() 
{
    int choix1, choix2, account_number;
    int t = 1;
    bool log = false;

    while (1) 
    {
        system("clear"); 
        menu0();
        if (scanf("%d", &choix1) != 1) 
        {
            printf("Entrée invalide.\n");
            exit(0);
        }

        switch (choix1) 
        {
            case 1:
                registerAccount("/Users/mac/Desktop/ProjetEC/csv_files/accounts.csv");
                showMenu2();
                break;
            case 2: 
                log = loge_in();
                if (log)
                {
                    t = 1;
                }
                
                if (log) {
                    while (t) 
                    {
                        system("clear");
                        showMenu();
                        if (scanf("%d", &choix2) != 1) 
                        {
                            printf("Entrée invalide.\n");
                            exit(0);
                        }

                        system("clear");
                        switch (choix2) 
                        {
                            case 1:
                                printf("Entrez le numéro de compte : ");
                                scanf("%d", &account_number);
                                modifyAcc(account_number, "/Users/mac/Desktop/ProjetEC/csv_files/accounts.csv");
                                showMenu2();
                                break;
                            case 2:
                                printf("Entrez le numéro de compte à supprimer : ");
                                scanf("%d", &account_number);
                                delete_client(account_number, "/Users/mac/Desktop/ProjetEC/csv_files/accounts.csv");
                                showMenu2();
                                break;
                            case 3:
                                displayaccounts("/Users/mac/Desktop/ProjetEC/csv_files/accounts.csv");
                                showMenu2();
                                break;
                            case 4:
                                printf("Entrez le numéro de compte : ");
                                scanf("%d", &account_number);
                                makeDeposit(account_number, "/Users/mac/Desktop/ProjetEC/csv_files/accounts.csv");
                                showMenu2();
                                break;
                            case 5:
                                printf("Entrez le numéro de compte : ");
                                scanf("%d", &account_number);
                                makeWithdrawal(account_number, "/Users/mac/Desktop/ProjetEC/csv_files/accounts.csv");
                                showMenu2();
                                break;
                            case 6:
                                transfert("/Users/mac/Desktop/ProjetEC/csv_files/accounts.csv");
                                showMenu2();
                                break;
                            case 7:
                                recherche_Compte("/Users/mac/Desktop/ProjetEC/csv_files/accounts.csv");
                                showMenu2();
                                break;
                            case 8:
                                trier_compte("/Users/mac/Desktop/ProjetEC/csv_files/accounts.csv");
                                displayaccounts("/Users/mac/Desktop/ProjetEC/csv_files/accounts.csv");
                                showMenu2();
                                break;
                            case 0:
                                printf("(^^) Au revoir !!\n");
                                sleep(1);
                                t = 0;
                                break;
                            default:
                                printf("Choix invalide, veuillez réessayer.\n");
                        }
                    }
                }
                break;
            case 0:
                printf("(^^) Au revoir !!\n");
                return;
            default:
                printf("Choix invalide. Réessayez.\n");
        }
    }
}