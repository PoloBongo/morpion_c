#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void nouvellegrille(int morpion[3][3])
{
    int i, j;
    FILE *fichier = fopen("morpion_save.txt", "w");
    if (fichier != NULL)
    {
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                if (morpion[i][j] == 1)
                {
                    putchar('X');
                    fputc('X', fichier);
                }else if (morpion[i][j] == 2)
                {
                    putchar('O');
                    fputc('O', fichier);
                }else if (morpion[i][j] == 0)
                {
                    putchar('.');
                    fputc('.', fichier);
                }
                
            }
            putchar('\n');
            fputc('\n', fichier);
        }
        fclose(fichier);
    }
}

bool condition_victoire(int morpion[3][3])
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
        // vérif des lignes et colonnes
        if (morpion[i][0] == 1 && morpion[i][1] == 1 && morpion[i][2] == 1 || morpion[0][i] == 1 && morpion[1][i] == 1 && morpion[2][i] == 1)
        {
            return true;
        }
        if (morpion[i][0] == 2 && morpion[i][1] == 2 && morpion[i][2] == 2 || morpion[0][i] == 2 && morpion[1][i] == 2 && morpion[2][i] == 2)
        {
            return true;
        }

        // vérif des diagonales
        if (morpion[0][0] == 1 && morpion[1][1] == 1 && morpion[2][2] == 1 || morpion[0][2] == 1 && morpion[1][1] == 1 && morpion[2][0] == 1)
        {
            return true;
        }
        if (morpion[0][0] == 2 && morpion[1][1] == 2 && morpion[2][2] == 2 || morpion[0][2] == 2 && morpion[1][1] == 2 && morpion[2][0] == 2)
        {
            return true;
        } 
    }
    return false;
}

int main()
{
    int morpion[3][3];
    int nb_tour = 9;
    int saisie_croix, saisie_croix_col, saisie_rond, saisie_rond_col = 0;
    bool player1_joue = true, player2_joue = false;

    bool parti_fini = condition_victoire(morpion);


    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            morpion[i][j] = 0;
            putchar('.');
        }
        putchar('\n');
    }

    do
    {
        if (player1_joue){
            nb_tour-=1;
            printf("Joueur 1 : X\nChoissisez la ligne\n");
            scanf("%d", &saisie_croix);

            printf("Joueur 1 : X\nChoissisez la colonne\n");
            scanf("%d", &saisie_croix_col);
        
            if (morpion[saisie_croix][saisie_croix_col] == 0) {
                morpion[saisie_croix][saisie_croix_col] = 1;
                player1_joue = false;
                player2_joue = true;
            } else {
                printf("Il y a deja une crois ici, choisissez une autre case\n");
                nb_tour++;
                continue;
            }

            nouvellegrille(morpion);
            parti_fini = condition_victoire(morpion);
            if (parti_fini == true)
            {
                printf("Les Croix ont gagne");
                break;
            }
            if (nb_tour == 0)
            {
                printf("Match Null!");
                break;
            }
        }
        if(player2_joue){
            nb_tour-=1;
            printf("Joueur 2 : O\nChoissisez la ligne\n");
            scanf("%d", &saisie_rond);

            printf("Joueur 2 : O\nChoissisez la colonne\n");
            scanf("%d", &saisie_rond_col);

            if (morpion[saisie_rond][saisie_rond_col] == 0) {
                morpion[saisie_rond][saisie_rond_col] = 2;
                player1_joue = true;
                player2_joue = false;
            } else {
                printf("Il y a deja un rond ici, choisissez une autre case\n");
                nb_tour++;
                continue;
            }

            nouvellegrille(morpion);
            parti_fini = condition_victoire(morpion);
            if (parti_fini == true)
            {
                printf("Les Ronds ont gagne");
                break;
            }
            printf("%d\n", nb_tour);
            if (nb_tour == 0)
            {
                printf("Match Null!");
                break;
            }
        }

    } while (nb_tour > 0);

    return 0;
}