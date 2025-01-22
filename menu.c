#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "fonction.h"

void clearScreen()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void menu_C()
{
    printf("\033[1;32m");
    printf("\n\t\t\t\t=== Bonjour cher client(e) ===\n");
    printf("\t\t\t-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n\n");
    printf("\033[0m");
    printf("1. Modifier un compte\n");
    printf("2. Fait un dépôt\n");
    printf("3. Fait un retrait\n");
    printf("4. Fait un transfert\n");
    printf("0. Quitter\n");
    printf("Votre choix : ");
}

void menu_admin() 
{
    printf("\033[1;32m");
    printf("\n\t\t\t\t=== Menu de gestion bancaire ===\n");
    printf("\t\t\t-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n\n");
    printf("\033[0m");
    printf("1. Supprimer un compte\n");
    printf("2. Afficher tous les comptes\n");
    printf("3. Rechercher un compte par le numéro de compte\n");
    printf("4. Trier les comptes par solde\n");
    printf("0. Quitter\n");
    printf("Votre choix : ");
}

void menu0()
{
        printf("\033[1;32m");
        printf("\n\t\t\tBienvenue dans notre application de gestion bancaire\n");
        printf("\t\t\t-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n\n");
        printf("\033[0m");
        printf("||1. Sign Up\n");
        printf("||2. Log In\n");
        printf("||3. sign up admin\n");
        printf("||0. Quit\n");
        printf("Votre choix : ");
}

void showMenu2() {
    int a;
    printf("Entrez 1 pour retourner au menu principal ou 0 pour quitter : ");
    scanf("%d", &a);
    if (a == 0) {
        // Cross-platform clearing and exit message
        clearScreen();
        printf("\033[96m");
        printf("(^^) Au revoir !!\n");
        printf("\033[0m");
        exit(0);
    } else {
        // Cross-platform clearing for return to the main menu
        clearScreen();
    }
}

void start() 
{
    int choix1, choix2, account_number, i;
    int t = 1;
    bool log = false;
    while (1) 
    {
        clearScreen();
        menu0();
        if (scanf("%d", &choix1) != 1)
        {
            printf("Entrée invalide.\n");
            exit(0);
        }

        switch (choix1) 
        {
            case 1:
                registerAccount(Acc_csv);
                showMenu2();
                break;
            case 2:
                clearScreen();
                printf("1. Admin\n2. Client\nVotre choix : ");
                if (scanf("%d", &i) != 1) 
                {
                    printf("Entrée invalide.\n");
                    exit(0);
                }
                clearScreen();
                log = loge_in(i);
                if (log)
                {
                    t = 1;
                }
                
                if (log) 
                {
                    while (t) 
                    {
                        clearScreen();

                        if (i == 1) 
                        {
                            menu_admin();
                            if (scanf("%d", &choix2) != 1) 
                            {
                                printf("Entrée invalide.\n");
                                exit(0);
                            }
                            clearScreen();
                            switch (choix2)
                            {
                                case 1:
                                    printf("Entrez le numéro de compte à supprimer : ");
                                    scanf("%d", &account_number);
                                    delete_client(account_number, Acc_csv);
                                    showMenu2();
                                    break;
                                case 2:
                                    displayaccounts(Acc_csv);
                                    showMenu2();
                                    break;
                                case 3:
                                    recherche_Compte(Acc_csv);
                                    showMenu2();
                                    break;
                                case 4:
                                    trier_compte(Acc_csv);
                                    displayaccounts(Acc_csv);
                                    showMenu2();
                                    break;
                                case 0:
                                    printf("Loading...\n");
                                    sleep(1);
                                    t = 0;
                                    break;
                                default:
                                    printf("Choix invalide, veuillez réessayer.\n");
                                    break;
                            }
                        } 
                        else 
                        {
                            menu_C();
                            if (scanf("%d", &choix2) != 1) 
                            {
                                printf("Entrée invalide.\n");
                                exit(0);
                            }
                            clearScreen();

                            switch (choix2) 
                            {
                                case 1:
                                    printf("Entrez le numéro de compte : ");
                                    scanf("%d", &account_number);
                                    modifyAcc(account_number, Acc_csv);
                                    showMenu2();
                                    break;
                                case 2:
                                    printf("Entrez le numéro de compte : ");
                                    scanf("%d", &account_number);
                                    makeDeposit(account_number, Acc_csv);
                                    showMenu2();
                                    break;
                                case 3:
                                    printf("Entrez le numéro de compte : ");
                                    scanf("%d", &account_number);
                                    makeWithdrawal(account_number, Acc_csv);
                                    showMenu2();
                                    break;
                                case 4:
                                    transfert(Acc_csv);
                                    showMenu2();
                                    break;
                                case 0:
                                    printf("Loading...\n");
                                    sleep(1);
                                    t = 0;
                                    break;
                                default:
                                    printf("Choix invalide, veuillez réessayer.\n");
                                    break;
                            }
                        }
                    }
                }
                break;
            case 3:
                s_admin();
                showMenu2();
                break;
            case 0:
                printf("(^^) Au revoir !!\n");
                return;
            default:
                printf("Choix invalide. Réessayez.\n");
        }
    }
}