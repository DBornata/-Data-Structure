#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define LEN_ARR_DONE 1 /// are to verify that The first two conditions they are activated
int x=0;
int y=0;
int l=0;
int d=0;
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
    struct Node*next;
};
struct Node*h_Q[20]= {NULL};
struct Node*h_D[20]= {NULL};
int Collision_Q=0;
int Collision_D=0;

int hash(char* key)
{
    int hashValue = 0;
    while( *key != '\0' )
    {
        hashValue += *key++;
        return (hashValue %20);
    }
}
int hash_D(char* key)
{
    int hashValue = 0;
    while( *key != '\0' )
    {
        hashValue += *key++;
        return hashValue;
    }
}
//Add new data  to the hash function
struct Node*insert_Q(char Course[50],int CreditHours, char CourseCode[50],char Department[50],char topic[50])
{
    x++;
    struct Node *node = (struct Node*) malloc(sizeof(struct Node));
    strcpy( node->Course,Course);
    node->CreditHours=CreditHours;
    strcpy( node->CourseCode,CourseCode);
    strcpy (node->Department,Department);
    strcpy(node->topic,topic);

    int hashIndex = hash(node->Course);
    //move in array until an empty or deleted cell
    int i=1;
    if(h_Q[hashIndex] != NULL )
    {
        Collision_Q++;
        //go to next cell
        hashIndex= (hashIndex+pow(i,2));        //wrap around the table
        hashIndex %= 20;
        i++;
        l++;
    }
    h_Q[hashIndex] = node;


    return h_Q;

}
//Add new data  to the hash function

struct Node*insert_double(char Course[50],int CreditHours, char CourseCode[50],char Department[50],char topic[50])
{
    y++;
    struct Node *node = (struct Node*) malloc(sizeof(struct Node));
    strcpy( node->Course,Course);
    node->CreditHours=CreditHours;
    strcpy( node->CourseCode,CourseCode);
    strcpy (node->Department,Department);
    strcpy(node->topic,topic);
    int index,i,flag=0,hkey,hash2;
    int x=hash_D(node->Course);
    printf("%d",x);
    hkey=x%20;
    hash2 = 7-(x %7);
    for(i=0; i<20; i++)
    {
        index=(hkey+i*hash2)%20;
        if(h_D[index] == NULL)
        {
            h_D[index]=node->Course;
            break;
        }
        else
        {
            Collision_D++;

            continue;
        }
        d++;
    }
    return h_D;
}
//Deleting a specific data from the table and setting its value -1
void del_Q(char l[50])
{
    int r=hash(l);
    int key = r% 20;
    for(int i=0 ; i<20; i++)
    {
        if(strcmp(h_Q[key]->Course,l)==0)
        {
            h_Q[key] =NULL;
            key++;
            return;
        }
    }
}
//Deleting a specific data from the table and setting its value -1
void del_double(char l[50])
{
    int i=0;
    int hkey,hash2,index;
    printf("\n enter search element\n");
    int r=hash(l);
    hkey=r%20;
    hash2 = 7-(r%7);
    index=(hkey+i*hash2)%20;
    if(strcmp(h_D[index],l)==0)
    {
        h_D[index] = NULL;
        return;
    }
    else
        printf("%d not present in the hash table\n",l);
}
//Printing the hashtable and writing the data in each node and writing the empty node as well
void display_Q()
{

    for(int i = 0; i<20; i++)
    {
        if(h_Q[i]!=NULL)
            printf("(%s %d  %s   %s   %s  )->->index=%d",h_Q[i]->Course,h_Q[i]->CreditHours,h_Q[i]->CourseCode,h_Q[i]->Department,h_Q[i]->topic,i);
        else
            printf("( NULL  )->->index=%d",i);
        printf("\n");
    }
    printf("\n");
}
//Read data from the file, cut it and put it in a hash
struct Node* read_file_Quadratic(struct Node* node)
{
    FILE*Courses;
    int i=0;
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
        if(token!=NULL)
            strcpy(To,token);
        node=insert_Q(CN,CH,CC,D,To);

    }
    return node;
}
//Read data from the file, cut it and put it in a hash
struct Node* read_file_Double(struct Node* node)
{
    FILE*Courses;
    int i=0;
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
        if(token!=NULL)
            strcpy(To,token);
        node=insert_double(CN,CH,CC,D,To);

    }
    return node;
}
//Search for a specific node in the hash and send its location and if it exists or not
void search_Q(char c[100])
{
    int index;
    int hashIndex = hash(c);

    for (int i = 0; i <20; i++)
    {
        index = (hashIndex + i*i) %20;
        if(strcmp(h_Q[index]->Course,c)==0)
        {
            printf("\n\n \t*********value is found at index %d********\n",index);
            return;
        }
    }
    printf("\n sorry value not found \n");
}
//Search for a specific node in the hash and send its location and if it exists or not
void search_double(char key[100])
{
    int index,i,hash2,hkey;

    int x=hash_D(key);
    hkey=x%20;
    hash2 = 7-(x %7);
    for(i=0; i<20; i++)
    {
        index=(hkey+i*hash2)%20;
        if(strcmp(h_D[index]->Course,key)==0)
        {
            printf("\n\n \t*********value is found at index %d********\n",index);
            return;
        }
    }
    if(i == 20)
        printf("\n value is not found\n");
}
//Printing the hashtable and showing the empty places
void display_double()
{

    int i;
    printf("\nelements in the hash table are \n");
    for(i=0; i< 20; i++)
        printf("\n at index %d \t   %s",i,h_D[i]);
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

//It is a menu of operations that are required
void displayChoices()
{
    printf("Choose from the menu below:\n");
    printf("1. Print hashed tables (including empty spots). \n");
    printf("2. Print out table size and the load factor\n");
    printf("3. Print out the used hash functions..\n");
    printf("4. Insert a new record to hash table (insertion will be done on both hash tables). \n");
    printf("5. Search for a specific word (specify which table to search in). .\n");
    printf("6. Delete a specific record (from both tables).\n");
    printf("7. Compare between the two methods in terms of number of collisions occurred. \n");
    printf("8. Save hash table back to a file named saved_courses.txt (of the double hashing)\n");
    printf("9) Exit.\n");
}
void saveHashTable()
{
    FILE *outputHash;
    outputHash= fopen("offered_courses.txt","w");
    for (int i = 0; i < 20; ++i)
        fprintf(outputHash, "Index : %d\t Name: %s\n", i,h_D[i]->Course );


    fclose(outputHash);


}
void displayMenu(struct Node*Q,struct Node*D)
{
    struct Node*node_Q=Q;
    struct Node*node_D=D;
    int choice;
    int array_done[LEN_ARR_DONE];//This array to assure that we complete  the registration process before we ask anything else
    for (int i = 0; i<1 ; i++) //In This loop, the array represents flags for choice
    {
        array_done[i]=0;
    }

    displayChoices();

    while(1)
    {
        scanf("%d", &choice);
        if(choice ==9)
        {
            printf("Goodbye\n");
            break;
        }

        switch(choice)
        {
        case 1:
            if(!array_done[0])
            {
//Print hashed tables (including empty spots)
                printf("*********************Quadratic**********************\n");
                node_Q=read_file_Quadratic(node_Q);
                display_Q();
                printf("\n----------------------------------------------------\n");
                printf("*********************Double**********************\n");

                node_D=read_file_Double(node_D);
                display_double();
                printf("\n----------------------------------------------------\n");


                array_done[0] = 1;

            }
            break;

        case 2:
            if(is_selected(array_done, LEN_ARR_DONE))  // -1 is for just checking the first two values from array
            {
                //Print out table size and the load factor
                printf("The Size Of Hash Table(Quadratic) is : %d\t\tThe Number Of Elements In The Table is : %d\n",20,x);

                printf("The Size Of Hash Table(double) is : %d\t\tThe Number Of Elements In The Table is : %d\n",20,y);

            }
            break;

        case 3:
            if(is_selected(array_done, LEN_ARR_DONE - 1))  // -1 is for just checking the first two values from array
            {
                //Print out the used hash functions.
                printf("\n I USED Hashing  BY Quadratic Hashing\n");
                display_Q();
                printf("\n\n____________________________________________________\n\n");
                printf("\n I USED Hashing BY Double Hashing\n");
                display_double();

            }
            break;

        case 4:
            if(is_selected(array_done, LEN_ARR_DONE))
            {
                //Insert a new record to hash table (insertion will be done on both hash tables).
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
                insert_double(course,hours,code,dep,topic);
                insert_Q(course,hours,code,dep,topic);
                printf("\n******************************The result is in the two tables after adding*****************************\n");
                printf("\n  Hashing  BY Quadratic Hashing\n");
                display_Q();
                printf("\n____________________________________________________\n");
                printf("\n  Hashing BY Double Hashing\n");
                display_double();

            }
            break;

        case 5:

            if(is_selected(array_done, LEN_ARR_DONE))
            {
//Search for a specific word (specify which table to search in)
                int select;
                char c[100];
                printf("\n enter search element\n");
                scanf(" %[^\n]",c);
                printf("if you want to search from double table enter 1 or in Q enter 2:\n");
                scanf("%d",&select);
                if(select==1)
                    search_double(c);
                else
                    search_Q(c);
            }
            break;



        case 6:
            if(is_selected(array_done, LEN_ARR_DONE))
            {
                //. Delete a specific record (from both tables)
                char l[100];
                printf("\n enter search element\n");
                scanf(" %[^\n]",l);
                del_Q(l);
                del_double(l);
                printf("\n******************************The result is in the two tables after deleting *****************************\n");
                printf("\n  Hashing  BY Quadratic Hashing\n");
                display_Q();
                printf("\n____________________________________________________\n");
                printf("\n  Hashing BY Double Hashing\n");
                display_double();

            }
            break;
        case 7:
            if(is_selected(array_done, LEN_ARR_DONE))
            {
                //Compare between the two methods in terms of number of collisions occurred.
                printf("Collision in hash double==%d\t\t ",Collision_D);
                printf("Collision in hash Q==%d\n\n",Collision_Q);
                if(Collision_D>Collision_Q)
                {
                    printf("There are more in the double table\n");
                }
                else if(Collision_D<Collision_Q)
                {
                    printf("There is less in the double table\n");
                }
                else
                    printf("equals\n");

            }
            break;

        case 8:
            if(is_selected(array_done, LEN_ARR_DONE))
            {
                //Save hash table back to a file named saved_courses.txt (of the double hashing
                saveHashTable();

            }
            break;

        default:
            printf("Please number from 1 to 8\n");
        }

        printf("\n\n");
        displayChoices();
    }
}
int main()
{
    struct Node*node=(struct Node*)malloc(sizeof(struct Node));
    struct Node*node_double=(struct Node*)malloc(sizeof(struct Node));
    displayMenu(node,node_double);

}