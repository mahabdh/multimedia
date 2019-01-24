//*******************************************************************
// Description:
//                  Ce programme couvre le concept d'encodage de Huffman.
// On lit d'abord un fichier, à partir duquel on compte le nombre de caractères, puis on calcule la fréquence
// de chaque lettre individuellement. La fréquence de chaque lettre est stockée dans un nœud avec son caractère respectif.
// Ce nœud est stocké dans un tableau de 26 éléments (élément 0 -> 'A', élément 1 -> 'B' ... élément 25 -> 'Z').
// Chaque élément est un pointeur et chaque pointeur est supposé être la racine d'un arbre (sous-arbre).
// Après avoir traité tous les caractères du texte (lu dans un fichier), on se retrouve avec un tableau avec
// 25 éléments NULL. Le seul élément qui n'est pas NULL est la racine de l'arbre qui regroupe les différents
// nœuds de chaque lettre.
// Déduire le codage de chaque lettre s'il est effectué avec l'intermédiaire du préfixe traversal.
// Pour résumer, le pseudo-code est:
// - Initialise le tableau de lettres
// - Lire le fichier
// - Incrémente chaque fréquence de lettre + calcule le nombre de caractères du fichier
// - stocke dans le noeud du tableau la fréquence de chaque lettre
// - Calcule le nombre (N) de caractères impliqués (Parfois, les textes n'incluent pas toutes les lettres. Dans notre cas, "Q" et "Z" sont absents).
// - Boucle N fois
// - trouver Minimum et deuxième minimum
// - crée un nouveau noeud, son enfant de gauche contient le minimum et l'enfant de droite contient le second minimum
// - points de position minimum sur le nouveau noeud, et points de position du tableau du second minimum sur NULL
// - Parcourt le tableau jusqu'à ce que l'élément unique non NULL soit rencontré
// - invoque la fonction de traversée de préfixes
// - construit l'encodage de chaque caractère
// - affiche la lettre et ses caractéristiques lorsqu'elles sont trouvées.
// - Enfin, lisez le fichier de sortie pour interpréter son contenu
// - si la racine contient un caractère (A - Z), caractère d'affichage
// - sinon, si le caractère actuel est '1', parcourez la feuille de gauche
// - sinon, si le caractère actuel est '0', parcourez la feuille de droite
//
//*******************************************************************
#include <stdio.h>
#include<math.h>//log
#define NBR_OF_LETTERS 26

#define LEFT 'L'
#define RIGHT 'R'

#define CODE_SIZE 128

#define TYPED_ALLOC(type) (type *) malloc( sizeof(type) )
#define BYTE_SIZE 8

#define IN_PATH "Rym.txt"
#define OUT_PATH "r.txt"

typedef struct tree_node_s {
    float frequency;
    char c;
    char code[CODE_SIZE];
    struct tree_node_s *left;
    struct tree_node_s *right;
} tree_node_t;

tree_node_t *arr[NBR_OF_LETTERS], *letters[NBR_OF_LETTERS];


void findMinAndSecondMin(tree_node_t **, float *, int *, float *, int *);
void printTree(tree_node_t *);
void interpret(char *, int *, tree_node_t *);
void printTree(tree_node_t *);
void encode(tree_node_t *, tree_node_t **, char, short, char*);

//______________________________________________________________________//
int main() {
    char str[CODE_SIZE];
    int fileReadingVerdict;
    int i, j, k, index, n;
    float min, secondMin;
    float somme;
    int li;
    int minIndex, secondMinIndex;
    int numberOfCharacters = 0;
    tree_node_t *tree;
    FILE *in = fopen(IN_PATH, "r");
    FILE *out;
    if ( in == NULL ) {
        printf("\nFichier non trouvé");
        return 0;
    } else {
        /*
         *  DEBUT : initialisation de tableau
         */
        for (i = 'A'; i <= 'Z'; i++) {
            index = i - 'A';
            arr[index] = NULL;
        }
        //FIN de l'initialisation de tableau

        numberOfCharacters = 0;
        fileReadingVerdict = fgets(str, CODE_SIZE, in) != NULL;
        while(!feof(in) || fileReadingVerdict) {
            n = strlen(str);
            printf("\nContenu de fichier %s", str);
            for (i = 0; i < n ; i ++ ) {
                str[i] = toupper(str[i]);
                if (str[i] >= 'A' && str[i] <= 'Z') {
                    numberOfCharacters ++;
                    index = str[i] - 'A';
                    if (arr[index] == NULL) {
                        arr[index] = TYPED_ALLOC(tree_node_t);// malloc(sizeof(tree_node_t));
                        arr[index]->c = str[i];
                        arr[index]->frequency = 1;
                        arr[index]->left = arr[index]->right = NULL;
                    } else {
                        arr[index]->frequency += 1;
                    }
                }
            }
            if (fileReadingVerdict) {
                fileReadingVerdict = fgets(str, CODE_SIZE, in) != NULL;
            }
        }
    }
    fclose(in);

    for ( i = 0, n = 0 ; i < NBR_OF_LETTERS ; i ++ ) {
        letters[i] = arr[i];
        if (arr[i] != NULL) {
            arr[i]->frequency /= numberOfCharacters;    // Computing the frequency.
            n ++;
            li=floor((-(log2(arr[i]->frequency))) + 0.5);
        somme=somme+(li*arr[i]->frequency);
        printf("\n %c LI %d somme %f",arr[i]->c,li,somme);                                     // n is the number of involved letters which is going to be consumed in the do while loop's condition
        }

    }

    j = 1;
    do {
        findMinAndSecondMin(arr, &min, &minIndex, &secondMin, &secondMinIndex);

        if (minIndex != -1 && secondMinIndex != -1 && minIndex != secondMinIndex) {
            tree_node_t *temp;
            tree = TYPED_ALLOC(tree_node_t);// malloc(sizeof(tree_node_t));
            tree->frequency = arr[minIndex]->frequency + arr[secondMinIndex]->frequency;
            tree->c = j;
            tree->left = arr[minIndex];
            temp = TYPED_ALLOC(tree_node_t);// malloc(sizeof(tree_node_t));
            temp->c = arr[secondMinIndex]->c;
            temp->frequency = arr[secondMinIndex]->frequency;
            temp->left = arr[secondMinIndex]->left;
            temp->right = arr[secondMinIndex]->right;
            tree->right = temp;

            arr[minIndex] = tree;

            arr[secondMinIndex] = NULL;
        }
        j ++;
    } while( j < n );

    for ( i = 0 ; i < NBR_OF_LETTERS ; i ++ ) {
        if (arr[i] != NULL)  {
            char code[CODE_SIZE];
            strcpy(code, "");
            encode(tree = arr[i], letters, 0, 0, code);
            puts("\ncodage avec succes");
            printTree(arr[i]);
            break;
        }
    }
    in = fopen(IN_PATH, "r");
    out = fopen(OUT_PATH, "w");
    fileReadingVerdict = fgets(str, CODE_SIZE, in) != NULL;
    while(!feof(in) || fileReadingVerdict) {
        n = strlen(str);
        for (i = 0; i < n ; i ++ ) {
            str[i] = toupper(str[i]);//to majuscule
            if (str[i] >= 'A' && str[i] <= 'Z') {
                index = str[i] - 'A';
                fputs(letters[index]->code, out);


            }
        }
        if (fileReadingVerdict) {
            fileReadingVerdict = fgets(str, CODE_SIZE, in) != NULL;
        }
    }

/*char stTemp[2];
sprintf(stTemp,"%c",somme);
int sum=atoi(stTemp);*/
printf("voilaaaaa %c",(char)somme);
//fputs(somme,out);
    fclose(in);
    fclose(out);

    printf("\nTaille fichier input :   %d bits", numberOfCharacters * BYTE_SIZE);

    out = fopen(OUT_PATH, "r");
    fileReadingVerdict = fgets(str, CODE_SIZE, out) != NULL;
    numberOfCharacters = 0;
    while(!feof(out) || fileReadingVerdict) {
        numberOfCharacters += strlen(str);
        if (fileReadingVerdict) {
            fileReadingVerdict = fgets(str, CODE_SIZE, out) != NULL;
        }
    }
    fclose(out);

    printf("\nTaille fichier output : %d bits", numberOfCharacters);

    printf("\nInterpreting output file:\n");
    out = fopen(OUT_PATH, "r");
    fileReadingVerdict = fgets(str, CODE_SIZE, out) != NULL;
    while(!feof(out) || fileReadingVerdict) {
        n = strlen(str);
        i = 0 ;
        while(i < n) {
            interpret(str, &i, tree);
        }
        if (fileReadingVerdict) {
            fileReadingVerdict = fgets(str, CODE_SIZE, out) != NULL;
        }
    }
    fclose(out);

    puts("\n");
    return 0;
}
//___________________________________________________________________________________________________//




void encode(tree_node_t *node, tree_node_t **letters, char direction, short level, char* code) {
    int n;
    if ( node != NULL ) {
        if ((n = strlen(code)) < level) {
            if (direction == RIGHT) {
                strcat(code, "0");
            } else {
                if (direction == LEFT) {
                    strcat(code, "1");
                }
            }
        } else {
            if (n >= level) {
                code[n - (n - level) - 1] = 0;
                if (direction == RIGHT) {
                    strcat(code, "0");
                } else {
                    if (direction == LEFT) {
                        strcat(code, "1");
                    }
                }
            }
        }
        if (node->c >= 'A' && node->c <= 'Z') {
            strcpy(node->code, code);
            strcpy(letters[node->c - 'A']->code, code);
        }
        encode(node->left, letters, LEFT, level + 1, code);
        encode(node->right, letters, RIGHT, level + 1, code);
    }
}

void printTree(tree_node_t *node) {
    int n;
    if ( node != NULL ) {
        if (node->c >= 'A' && node->c <= 'Z') {
            printf("\t%c - frequency: %.10f\tencoding: %s\n", node->c, node->frequency, node->code);
        }
        printTree(node->left);
        printTree(node->right);
    }
}

/*
 *  Begin:  Minimum and second minimum
 */
void findMinAndSecondMin(tree_node_t *arr[], float *min, int *minIndex, float *secondMin, int *secondMinIndex) {
    int i, k;
    k = 0;
    *minIndex = -1;
    /*
     * Skipping all the NULL elements.
     */
    while (k < NBR_OF_LETTERS && arr[k] == NULL) k++;

    *minIndex = k;
    *min = arr[k]->frequency;

    for ( i = k ; i < NBR_OF_LETTERS; i ++ ) {
        if ( arr[i] != NULL && arr[i]->frequency < *min ) {
            *min = arr[i]->frequency;
            *minIndex = i;
        }
    }

    k = 0;
    *secondMinIndex = -1;
    /*
     * Skipping all the NULL elements.
     */
    while ((k < NBR_OF_LETTERS && arr[k] == NULL) || (k == *minIndex && arr[k] != NULL)) k++;

    *secondMin = arr[k]->frequency;
    *secondMinIndex = k;

    if (k == *minIndex) k ++;

    for ( i = k ; i < NBR_OF_LETTERS; i ++ ) {
        if ( arr[i] != NULL && arr[i]->frequency < *secondMin && i != *minIndex ) {
            *secondMin = arr[i]->frequency;
            *secondMinIndex = i;
        }
    }
    /*
     *  End:    Minimum and second minimum
     */
}

void interpret(char *str, int *index, tree_node_t *tree) {
    int n = strlen(str);
    if (tree->c >= 'A' && tree->c <= 'Z') {
        printf("%c ", tree->c);
        return ;
    } else {
        if ( *index < n ) {
            if (str[*index] == '0') {
                (*index) ++;
                interpret(str, index, tree->left);
            } else {
                if (str[*index] == '1') {
                    (*index) ++;
                    interpret(str, index, tree->right);
                }
            }
        }
    }
}
