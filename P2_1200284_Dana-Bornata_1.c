#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN_ARR_DONE 1 /// are to verify that The first two conditions they are activated

char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s));
}
// An AVL tree node
struct Node
{
    char Course[50];
    int CreditHours;
    char CourseCode[50];
    char topic[500];
    char Department[50];
    struct Node *left;
    struct Node *right;
    int height;
};

/* Helper function that allocates a new node with the given data from file and
	NULL left and right pointers. */
struct Node* newNode_cours(  char Course[100],int CreditHours, char CourseCode[100], char topic[100],char Department[100])
{
    struct Node* node = (struct Node*)
                        malloc(sizeof(struct Node));
    strcpy( node->Course,Course);
    node->CreditHours=CreditHours;
    strcpy( node->CourseCode,CourseCode);
    strcpy (node->Department,Department);
    strcpy( node->topic,topic);
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // new node is initially added at leaf
    return(node);
}

struct Node * minValueNode(struct Node* node)
{
    struct Node* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}
// A utility function to get height of the tree
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}

/* Update heights, then return new root */

struct Node*single_rotate_with_left(  struct Node* nodee)
{
    struct Node*  K1;

    K1 = nodee->left;
   nodee->left = K1->right;
    K1->right = nodee;

    nodee->height = max( height(nodee->left ), height(nodee->right ) ) + 1;
    K1->height = max( height( K1->left ), nodee->height ) + 1;

    return K1;  /* New root */
}

/* Update heights, then return new root */

struct Node*single_rotate_with_right( struct Node* dana_node  )
{
    struct Node* K2;

    K2 = dana_node ->right;
    dana_node ->right = K2->left;
    K2->left = dana_node;

   dana_node ->height = max( height(dana_node ->left ), height(dana_node ->right ) ) + 1;
    K2->height = max( height( K2->right ), dana_node ->height ) + 1;

    return K2;  /* New root */
}


/* Update heights, then return new root */

struct Node* double_rotate_with_left(  struct Node*dana_node  )
{
    /* Rotate between K1 and K2 */
    dana_node ->left =single_rotate_with_right(dana_node ->left );

    /* Rotate between K3 and K2 */
    return single_rotate_with_left(dana_node );
}


struct Node* double_rotate_with_right( struct Node*dana_node  )
{
    /* Rotate between K3 and K2 */
   dana_node ->right = single_rotate_with_left( dana_node ->right );

    /* Rotate between K1 and K2 */
    return single_rotate_with_right(dana_node  );
}

// Get Balance factor of node N
int getBalance(struct Node *dana_node )
{
    if (dana_node == NULL)
        return 0;
    return height(dana_node ->left) - height(dana_node ->right);
}

//To insert the dictionary into the AVL
struct Node* Insert(char CN[100],int CH,char CC [100],char D[100],char To [500],struct Node *T )
{
    if( T == NULL )
    {
        /* Create and return a one-node tree */
        T = malloc( sizeof( struct node*) );
        if( T == NULL )
            printf( "Out of space!!!" );
        else
        {
            T= newNode_cours(CN,CH,CC,D,To);
        }

    }

    else if( strcmp(CC,T->CourseCode)<0 )
    {
        T->left = Insert(CN,CH,CC,D,To,T->left );
        if( height( T->left ) - height( T->right ) == 2 )
        {
            if(strcmp(CC, T->left->CourseCode)<0)
                T =single_rotate_with_left(T);
            else
                T = (T);
        }
    }
    else if(strcmp(CC,T->CourseCode)>0)
    {
        T->right = Insert(CN,CH,CC,D,To,T->right );
        if( height( T->right ) - height( T->left ) == 2 )
        {
            if( strcmp(CC,T->right->CourseCode)>0 )
                T = single_rotate_with_right( T );
            else
                T =double_rotate_with_right( T );
        }


    }
    /* Else X is in the tree already; we'll do nothing */
    T->height = max( height( T->left ), height( T->right ) ) + 1;
    return T;

}
// This function reads from the file and correctly saves the data to a linked list cours and prints what is in that list
struct node*read_file_cours(struct Node* node)
{
    FILE*Courses;
    Courses=fopen("courses.txt","r");
    char Line[500];
    char CN [100];
    int CH ;
    char CC [100];
    char D[100];
    char To [500];

    while(fgets(Line,500,Courses)!= NULL)
    {

        Line[strlen(Line)-1]='\0';
        char *token;
        token = strtok(Line,":");
        token =trim(token);
        strcpy(CN,token);
        token = strtok(NULL,"#");
        token =trim(token);

        CH=atoi(token);
        token =strtok(NULL,"#");
        token= trim(token);

        strcpy(CC,token);

        token = strtok(NULL,"/");

        token =trim(token);

        strcpy(D,token);

        token = strtok(NULL,"\n");
        strcpy(To,token);
        node = Insert(CN,CH,CC,D,To,node);

}
  fclose(Courses);


    return node;

}
//Delete a course by the name of the course
struct Node* del(struct Node*dana_Tree,char dep[100])
{
    if(!(dana_Tree))
     return dana_Tree;
    if(strcmp(dep,dana_Tree->topic)==-1)
       dana_Tree->left = del(dana_Tree->left,dep);
    else
        if(strcmp(dep,dana_Tree->topic)==1)
            dana_Tree->right = del(dana_Tree->right,dep);
        else
            if((dana_Tree->left) && (dana_Tree->right))
            {
                struct Node*tmp=minValueNode(dana_Tree->right);
                strcpy(dana_Tree->topic,tmp->topic);
                if(dana_Tree->right->left)
                    dana_Tree->right = del(dana_Tree->right,dana_Tree->right->left->topic);
                else dana_Tree->right = del(dana_Tree->right,dana_Tree->right->topic);
                }
            else
                if(dana_Tree->left)
                    dana_Tree = dana_Tree->left;
                else
                    dana_Tree = dana_Tree->right;
                return dana_Tree;
}
//Delete a dep by the name of the course
struct Node* del_dep(struct Node*dana_Tree,char Course_code[100])
{

    if(!(dana_Tree))
     return dana_Tree;
    if(strcmp(Course_code,dana_Tree->Department)==-1)
        dana_Tree->left = del(dana_Tree->left,Course_code);
    else
        if(strcmp(Course_code ,dana_Tree->Department)==1)
            dana_Tree->right = del(dana_Tree->right, Course_code);
        else
            if((dana_Tree->left) && (dana_Tree->right))
            {
                struct Node*tmp=minValueNode(dana_Tree->right);
                strcpy(dana_Tree->Department,tmp->Department);
                if(dana_Tree->right->left)
                   dana_Tree->right = del(dana_Tree->right,dana_Tree->right->left->Department);
                else dana_Tree->right = del(dana_Tree->right,dana_Tree->right->Department);
                }
            else
                if(dana_Tree->left)
                    dana_Tree = dana_Tree->left;
                else
                    dana_Tree = dana_Tree->right;
                return dana_Tree;
}

//Delete a dep by the name of the course
struct Node* print_dep(struct Node*tTree,char dep_code[100])
{
    if(!(tTree))
     return tTree;
    if(strcmp(dep_code,tTree->topic)==-1)
        tTree->left =  print_dep(tTree->left,dep_code);
    else
        if(strcmp(dep_code,tTree->topic)==1)
            tTree->right = print_dep(tTree->right,dep_code);
        else
            if((tTree->left) && (tTree->right))
            {
                struct Node*tmp=minValueNode(tTree->right);
                strcpy(tTree->topic,tmp->topic);
                if(tTree->right->left)
                    tTree->right =printf("the same dep ->->code->-> %s",tTree->CourseCode);
                else tTree->right =printf("the same dep ->->code->-> %s",tTree->CourseCode);
                }
            else
                if(tTree->left)
                    tTree = tTree->left;
                else
                    tTree = tTree->right;
                return tTree;
}
//in-order print to see the elements
void PrintInOrder( struct Node * root)
{
    if( root != NULL)
    {

        PrintInOrder( root->left );
        printf("%s__%d__%s__%s_%s\n",root->Course,root->CreditHours, root->CourseCode,root->Department,root->topic);
        PrintInOrder( root->right );
    }
}
//Search for a specific course by code
struct Node* searchCode(struct Node* root, char searchedCode[100])
{
         if( root == NULL ){
        return NULL;
         }
        if (strcmp(searchedCode, root->CourseCode) ==-1)
        {
            return  searchCode(root->left, searchedCode);
        }
        else if (strcmp(searchedCode, root->CourseCode)==1)
        {
            return  searchCode(root->right, searchedCode);
        }
        else if (strcmp(searchedCode, root->CourseCode) == 0)

        {
                int x;
                printf("Do you want to update its information? If yes, press 1 and if no press 2\n");
                scanf("%d",&x);
                if(x==1)
                {
                    char course[100];
                    char code[100];
                    int hours;
                    char dep[100];
                    char topic[100];

                    printf("Enter cours's Name update:\n");
                    scanf("%s",course);
                    printf("Enter code cours Name update:\n");
                    scanf("%s",code);
                    printf("Enter the CreditHours update:\n");
                    scanf("%d", &hours);
                    printf("Enter the Department update:\n");
                    scanf("%s",dep);
                    printf("Enter the topic update:\n");
                    scanf("%s",topic);
                    strcpy( root->Course,course);
                    root->CreditHours=hours;
                    strcpy(  root->CourseCode,code);
                    strcpy ( root->Department,dep);
                    strcpy( root->topic,topic);
                    PrintInOrder(root);
                }
                else
                    return root;
            }



    else
    {
        printf("Not found");
        return NULL;
    }
}
//Search for a specific course by code
int searchCode_topic(struct Node* root, char searchedCode[100])
{
        if (strcmp(searchedCode, root->CourseCode) < 0)
        {
            return   searchCode_topic(root->left, searchedCode);
        }
        else if (strcmp(searchedCode, root->CourseCode) > 0)
        {
            return  searchCode_topic(root->right, searchedCode);
        }
        else if (strcmp(searchedCode, root->CourseCode) == 0)

        {
            printf("%s",root->Department);
        }

        else
            {
        return NULL;
        }
}
// Open the existing file offered_courses.txt using fopen()
// in write mode using "w" attribute
void print_in_file(struct Node* T,FILE* save_data )
{
    if (T != NULL)
    {
        print_in_file(T->left,save_data);
        fprintf(save_data,"%s_%d_%s_%s_%s\n",T->Course,T->CreditHours, T->CourseCode,T->Department,T->topic);
        print_in_file(T->right,save_data);
    }
}


//List all topics associated with a given course.
void List_topic(struct Node*p,char Cours[1])
{
searchCode_topic(p,Cours);
}
//Search for a specific course by code
int searchCode_cours_specific(struct Node* root, char searchedCode[1])
{
        if (strcmp(searchCode_cours_specific, root->CourseCode[0]) < 0)
        {
            return   searchCode_topic(root->left, searchedCode);
        }
        else if (strcmp(searchCode_cours_specific, root->CourseCode[0]) > 0)
        {
            return  searchCode_topic(root->right, searchedCode);
        }
        else if (strcmp(searchCode_cours_specific, root->CourseCode[0]) == 0)

        {
            printf("%s",root->Department);
        }

        else
            {
        return NULL;
        }
}
//List all topics associated with a given course.
void List_course_specific(struct Node*p,char Cours[100])
{
searchCode_cours_specific(p,Cours);
}

//It is a menu of operations that are required
void displayChoices()
{
    printf("Choose from the menu below:\n");
    printf("1. Read the file courses.txt file and create the tree.\n");
    printf("2. Insert a new course from the user with all its associated data.\n");
    printf("3. Find a course and support updating of its information.\n");
    printf("4. List courses in lexicographic order with their associated \n");
    printf("5. List all topics associated with a given course.\n");
    printf("6. List all courses in lexicographic order that belong to the same department.\n");
    printf("7. Delete a course. \n");
    printf("8. Delete all courses that start with a specific letter.\n");
    printf("9. Delete all courses belong to a given department.\n");
    printf("10. Save all words in file offered_courses.txt .\n");
    printf("11) Exit.\n");
}
//Find out what was chosen in the case
int is_selected(int a[LEN_ARR_DONE], int len)
{
    int flag = len;
    for(int i = 0; i < len; i++)
    {
        if(a[i])
            flag--;
    }
    if(a[0] == 0)
        printf("\n\n*** Please check that you get courses and students information from files in option 1 ***\n\n");
    return !flag;
}
void displayMenu(struct Node* node)
{
    struct Node*l=node;
struct Node*node_new=NULL;
    int choice;
    int array_done[LEN_ARR_DONE];//This array to assure that we complete  the registration process before we ask anything else
    for (int i = 0; i<2 ; i++) //In This loop, the array represents flags for choice
    {
        array_done[i]=0;
    }

    displayChoices();

    while(1)
    {
        scanf("%d", &choice);
        if(choice ==11)
        {
            printf("Goodbye\n");
            break;
        }

        switch(choice)
        {
        case 1:
            if(!array_done[0])
            {
            l=read_file_cours(node);

                    printf("Hello Read the file done \n");

                array_done[0] = 1;
            }
            break;

        case 2:
            if(is_selected(array_done, LEN_ARR_DONE))  // -1 is for just checking the first two values from array
            {
                //  Insert a new course from the user with all its associated data.
                char course[100];
                char code[100];
                int hours;
                char dep[100];
                char topic[100];

                printf("Enter cours's Name:\n");
                scanf("%s",course);
                printf("Enter code cours Name:\n");
                scanf("%s",code);
                printf("Enter the CreditHours:\n");
                scanf("%d", &hours);
                printf("Enter the Department:\n");
                scanf("%s",dep);
                printf("Enter the topic:\n");
                scanf("%s",topic);
                newNode_cours(course,hours,code,topic,dep);
                node=Insert(course,hours,code,dep,topic,node) ;// insert the new book to library
                PrintInOrder(node);
                printf("The book has been added!\n");
            }
            break;

        case 3:
            if(is_selected(array_done, LEN_ARR_DONE - 1))  // -1 is for just checking the first two values from array
            {
                char CODE_SERCH[100];
                printf("Enter code cours Name:\n");
                scanf("%s",CODE_SERCH);
                searchCode(l,CODE_SERCH);
                array_done[2] = 1;
            }
            break;

        case 4:
            if(is_selected(array_done, LEN_ARR_DONE))
            {

              PrintInOrder(l);
                array_done[3] = 1;
            }
            break;

        case 5:

            if(is_selected(array_done, LEN_ARR_DONE))
            {

                char topic_code[100];
                printf("please enter code topic you want to find it\n ");
                scanf("%s",topic_code);
                List_topic(l,topic_code);

            }
            break;



        case 6:
            if(is_selected(array_done, LEN_ARR_DONE))
            {
           printf("please enter the dep code you want to add it:\n");
                char depp[100];

                scanf("%s",depp);
              print_dep(l,depp);
            }
            break;
        case 7:
            if(is_selected(array_done, LEN_ARR_DONE))
            {
                printf("please enter the course code you want to delete it:\n");
                char coursee[100];
                scanf("%s",coursee);
               del(l,coursee);
                printf("after delete: \n");
               PrintInOrder(l);

            }
            break;

        case 8:
            if(is_selected(array_done, LEN_ARR_DONE))
            {
                printf("please enter specific letter :\n");
                char xx[1];
                scanf("%s",xx);
                            List_course_specific(l,xx);


            }
            break;


        case 9:
            if(is_selected(array_done, LEN_ARR_DONE))
            {
                printf("please enter the dep code you want to delete it:\n");
                char depar[100];

                scanf("%s",depar);
               del_dep(l,depar);
                printf("\nafter delete\n");
              PrintInOrder(l);

            }
            break;
        case 10:
            if(is_selected(array_done, LEN_ARR_DONE))
            {

                FILE *save_data;
                save_data = fopen("offered_courses.txt","w");
                print_in_file(l,save_data);
                printf("save data done\n");

                fclose(save_data);

            }
            break;
        default:
            printf("Please number from 1 to 11\n");
        }

        printf("\n\n");
        displayChoices();
    }
}
int main()
{
    //create AVL
struct Node*a=NULL;

    displayMenu(a);

    return 0;
}
