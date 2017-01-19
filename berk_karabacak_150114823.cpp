// Berk Karabacak 150114823 Data Structures Project 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int depth=0;

//case insensitive comparison
int icmp (const char *p1, const char *p2)
{
    register unsigned char *s1 = (unsigned char *) p1;
    register unsigned char *s2 = (unsigned char *) p2;
    unsigned char c1, c2;

    do
    {
        c1 = (unsigned char) toupper((int)*s1++);
        c2 = (unsigned char) toupper((int)*s2++);
        if (c1 == '\0')
        {
            return c1 - c2;
        }
    }
    while (c1 == c2);

    return c1 - c2;
}

struct Tree {
    char data [128];
    int id;
    int numberofinternship;
    char name[128];
    char surname[128];
    int depth;
    struct Tree *left, *right;
};

struct Tree *root = NULL;

/* create a new node with the given data */
struct Tree * createNode(int id, int numberofinternship, char name[], char surname[], char data[]) {
    struct Tree *newNode;
    newNode = (struct Tree *) malloc(sizeof (struct Tree));
    strcpy(newNode->data,data);
    strcpy(newNode->name,name);
    strcpy(newNode->surname,surname);
    newNode->id = id;
    newNode->numberofinternship = numberofinternship;
    newNode->left = NULL;
    newNode->right = NULL;
    return(newNode);
}

/* insertion in binary search tree */
//Data is the line from input file
//We want to to insert new line into our tree
void insertion(struct Tree **node, char data []) {
    int nodeid;
    int nodenumberofinternship;
    int id;
    int numberofinternship;
//Create temp array,so that we can keep our orijinal data(strtok() does change structure of array)
    char temp[200];
    strcpy(temp,data);

    char parsedline[4][128];
    char * pch;
    int x=0;
    pch = strtok (temp," ");
//Parse new line
    while (pch != NULL)
    {
        strcpy(parsedline[x],pch);
        pch = strtok (NULL, " ");
        x++;
    }

    sscanf(parsedline[0], "%d", &id);
    sscanf(parsedline[3], "%d", &numberofinternship);
//Do similar parsing on node (which we are going to compare with our new data)
    char parsednodeline[4][128];
    char * pch2;
    int x2=0;
    char temp2[128];

    if( *node != NULL){

        strcpy(temp2,(*node)->data);
        pch2 = strtok (temp2," ");

        while (pch2 != NULL)
        {
            strcpy(parsednodeline[x2],pch2);

            pch2 = strtok (NULL," ");
            x2++;
        }
        sscanf(parsednodeline[0], "%d", &nodeid);
        sscanf(parsednodeline[3], "%d", &nodenumberofinternship);
    }
//4-d insertion as stated in HW sheet
    switch(depth%4) {


        //insert according to name
        case 0:

            if (*node == NULL) {
                *node = createNode(id,numberofinternship,parsedline[1],parsedline[2],data);
                (*node)->depth=depth;
                depth=0;
            }
            else if ( icmp(parsedline[1], parsednodeline[1])>=0) {
                depth++;
                insertion(&(*node)->right,data);
            } else if ( icmp(parsedline[1], parsednodeline[1])<0) {
                depth++;
                insertion(&(*node)->left,data);
            }

            break;

            //insert according to surname

        case 1:

            if (*node == NULL) {
                *node = createNode(id,numberofinternship,parsedline[1],parsedline[2],data);
                (*node)->depth=depth;
                depth=0;
            }
            else if ( icmp(parsedline[2], parsednodeline[2])>=0) {
                depth++;
                insertion(&(*node)->right,data);
            } else if ( icmp(parsedline[2], parsednodeline[2])<0) {
                depth++;
                insertion(&(*node)->left,data);
            }
            break;

            //insert according to id
        case 2:

            if (*node == NULL) {
                *node = createNode(id,numberofinternship,parsedline[1],parsedline[2],data);
                (*node)->depth=depth;
                depth=0;
            }
            else if ( nodeid > id) {
                depth++;
                insertion(&(*node)->left,data);
            } else if ( nodeid < id) {
                depth++;
                insertion(&(*node)->right,data);
            }

            break;

            //insert according to numberofinternship
        case 3:
            if (*node == NULL) {
                *node = createNode(id,numberofinternship,parsedline[1],parsedline[2],data);
                (*node)->depth=depth;
                depth=0;
            }
            else if ( nodenumberofinternship > numberofinternship) {
                depth++;
                insertion(&(*node)->left,data);
            } else if ( nodenumberofinternship < numberofinternship) {
                depth++;
                insertion(&(*node)->right,data);
            }
            break;
    }
}

//Traverse Functions
void inordertraverse(struct Tree *node) {
    if (node != NULL) {
        inordertraverse(node->left);
        printf("Depth= %d| %s",  node->depth,node->data);
        inordertraverse(node->right);
    }
    return;
}

void preordertraverse(struct Tree *node) {
    if (node != NULL) {
        printf("Depth= %d| %s",  node->depth,node->data);
        preordertraverse(node->left);
        preordertraverse(node->right);
    }
    return;
}

void postordertraverse(struct Tree *node) {
    if (node != NULL) {
        postordertraverse(node->left);
        postordertraverse(node->right);
        printf("Depth= %d| %s",  node->depth,node->data);

    }
    return;
}
//This inorder traverse function used for Part 3 of Project
void findtraverse(struct Tree *node, int id, int idComp, int day, int dayComp, char name[100], int nameComp, char surname[], int surnameComp) {

    int idbool=0,daybool=0,namebool=0,surnamebool=0;

    if (node != NULL) {
        if(idComp>0){
            idbool = node->id>id;

        }
        else if(idComp==0){
            idbool = node->id<id;
        }

        if(dayComp>0){
            daybool = node->numberofinternship>day;

        }
        else if(dayComp==0){
            daybool = node->numberofinternship<day;
        }
        if(nameComp>0){
            namebool = icmp(node->name,name);
        }
        else if(nameComp==0){
            namebool = icmp(name,node->name);
        }
        if(surnameComp>0){
            surnamebool = icmp(node->surname,surname);
        }
        else if(nameComp==0){
            surnamebool = icmp(surname,node->surname);
        }

        if(surnamebool>0&&namebool>0&&daybool&&idbool){

            printf("Depth= %d| %s",  node->depth,node->data);
        }

        findtraverse(node->left,id,idComp,day,dayComp,name,nameComp,surname,surnameComp);
        findtraverse(node->right,id,idComp,day,dayComp,name,nameComp,surname,surnameComp);
    }
    return;
}

int main() {

    int nameComp;
    int surnameComp;
    int idComp;
    int dayComp;
    int id;
    int day;
    char name [100];
    char surname [100];

    static const char filepath[] = "C:\\Users\\CHANGETHIS\\Desktop\\input.txt";
    FILE *file = fopen (filepath, "r" );
    if ( file != NULL )
    {
        char line [ 128 ];

        while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
        {
            if(strlen(line)>6){
                insertion(&root,line);
            }
        }
        fclose ( file );
    }
    else
    {

        printf("Please check input file path\n" );
        perror (filepath); /*Reason */
        getchar();

    }

    int  ch;
    while (1) {

        printf("\n1. Preorder traversal\n");
        printf("2. Inorder traversal\n");
        printf("3. Postorder traversal\n");
        printf("4. Find Greater and Lower Elements\n");

        printf("Enter your choice:");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("Preorder Traversal:\n");
                preordertraverse(root);
                printf("\n");
                exit(0);
            case 2:
                printf("Inorder Traversal:\n");
                inordertraverse(root);
                printf("\n");
                exit(0);
            case 3:
                printf("Postorder Traversal:\n");
                postordertraverse(root);
                printf("\n");
                exit(0);
            case 4:
                printf("\n\nPart 3-Find Greater or Less Combinations\n");

                printf("Enter id\n:");
                scanf("%d", &id);

                printf("Id should be bigger or smaller?Enter 1 for bigger,0 for smaller:\n");
                scanf("%d", &idComp);

                printf("Enter intership day:\n");
                scanf("%d", &day);

                printf("Day should be bigger or smaller?Enter 1 for bigger,0 for smaller:\n");
                scanf("%d", &dayComp);

                printf("Enter name:\n");
                scanf("%s", &name);

                printf("Name should be bigger or smaller?Enter 1 for bigger,0 for smaller:\n");
                scanf("%d", &nameComp);

                printf("Enter surname:\n");
                scanf("%s", &surname);

                printf("Surname should be bigger or smaller?Enter 1 for bigger,0 for smaller:\n");
                scanf("%d", &surnameComp);
                findtraverse(root,id,idComp,day,dayComp,name,nameComp,surname,surnameComp);
                exit(0);

            default:
                printf("Wrong option\n");
                break;
        }
    }

}