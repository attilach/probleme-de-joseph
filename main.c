/************************************************
 * Nom : Estalella
 * Kevin : Kevin
 * Date: 04.05.2015
 * Version: 1.0
 * Titre: Problème de Joseph
 * Description: Résoudre le problème de Joseph
                à l'aide des listes dynamiques circulaires.
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct Element Element;
struct Element
{
    int nombre;
    Element *suivant;
};

typedef struct Liste Liste;
struct Liste
{
    Element *premier;
    Element *dernier;
    Element *courant;
};

Liste *initialisation(int n, int k);
void insertion(Liste *liste, int nvNombre);
int suppression(Liste *liste);
void afficherListe(Liste *liste);

int main()
{
    int n = 8;
    int k = 3;

    Liste *maListe = initialisation(n, k);

    while (maListe->premier != maListe->dernier)
    {
        int i;
        for(i=0;i<k-1;i++)
        {
            maListe->courant = maListe->courant->suivant;
        }

        printf("%d", suppression(maListe));
        printf("\n\n");
    }
    printf("%d", suppression(maListe));
    printf("\n\n");

    return 0;
}

/*
 * Titre: initialisation
 *
 * Description: Initialise une liste avec un nombre
 *
 * Retour: Liste
 */
Liste *initialisation(int n, int k)
{
    Liste *liste = malloc(sizeof(*liste));
    Element *element = malloc(sizeof(*element));

    if (liste == NULL || element == NULL)
    {
        exit(EXIT_FAILURE);
    }

    element->nombre = 1;
    element->suivant = NULL;
    liste->premier = element;
    liste->courant = NULL;
    liste->dernier = element;

    int i;
    for(i=2;i<=n;i++)
    {
        insertion(liste, i);
    }

    liste->courant = liste->dernier;

    return liste;
}

/*
 * Titre: insertion
 *
 * Description: Insert un nouveau nombre dans la liste
 *
 * Retour: Aucun
 */
void insertion(Liste *liste, int nvNombre)
{
    //Création du nouvel élément
    Element *nouveau = malloc(sizeof(*nouveau));
    if (liste == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }

    nouveau->nombre = nvNombre;

    //Le dernier élément de la liste pointe sur le premier
    nouveau->suivant = liste->premier;

    //L'ancien dernier pointe sur le nouveau dernier
    liste->dernier->suivant = nouveau;

    //Le nouveau est a présent considéré comme le dernier de la liste
    liste->dernier = nouveau;
}

/*
 * Titre: suppression
 *
 * Description: supprime un nombre dans la liste
 *
 * Retour: Integer. Retourne le nombre du pointeur supprimé
 */
int suppression(Liste *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if (liste->courant != NULL)
    {
        int nombreCourant;
        Element *aSupprimer = liste->courant->suivant;
        liste->courant->suivant = liste->courant->suivant->suivant;

        if (aSupprimer == liste->premier)
        {
            liste->premier = liste->premier->suivant;
        }

        if (aSupprimer == liste->dernier)
        {
            liste->dernier = liste->courant;
        }

        nombreCourant = aSupprimer->nombre;

        free(aSupprimer);

        return nombreCourant;
    }
}

/*
 * Titre: afficherListe
 *
 * Description: affiche la liste du premier pointeur au dernier
 *
 * Retour: Integer. Retourne le nombre du pointeur supprimé
 */
void afficherListe(Liste *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Element *actuel = liste->premier;

    while (actuel != liste->dernier)
    {
        printf("%d -> ", actuel->nombre);
        actuel = actuel->suivant;
    }
    printf("%d", actuel->nombre);
}
