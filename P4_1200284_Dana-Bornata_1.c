//project 4
//In this project, you will implement Dijkstra�s algorithm to find the
//shortest path between two cities.
//Dana bornata_1200284
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#define LEN_ARR_DONE 1 /// are to verify that The first one conditions they are activated
#include <string.h>
#include <ctype.h>
char *ltrim(char *s)
{
    while (isspace(*s)) s++;
    return s;
}

char *rtrim(char *s)
{
    char *back = s + strlen(s);
    while (isspace(*--back));
    *(back + 1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s));
}

int N = 0;
int Adj[15][15];

char name1[50][50];

int to_int(char *key)
{
    for (int i = 0; i < N; i++)
    {
        if (strcmp(name1[i], key) == 0)
            return i;
    }
    strcpy(name1[N], key);
    return N++;
}


void addEdge(int Adj[][N], int city1, int city2, int d)
{
    Adj[city1][city2] = d;
    Adj[city2][city1] = d;
}
//Read data from the file
void read_file()
{
    FILE *City;
    char Line[500];
    City = fopen("cities.txt", "r");
    char C1[500];
    char C2[100];

    int D;


    printf("\n---------Jerusalem is a capital of Palestine-------\n");
// Number of vertices
    while (fgets(Line, 500, City) != NULL)
    {

        Line[strlen(Line) - 1] = '\0';
        char *token;
        //Trim the data in the file by space \t
        token = strtok(Line, "\t");
        token = trim(token);
        //C1->first city
        strcpy(C1, token);
        printf("%s|->->     ", C1);
        token = strtok(NULL, "\t");
        token = trim(token);
        //C2->>> The second city
        strcpy(C2, token);
        printf("%s|->->     ", C2);
        token = strtok(NULL, " ");
        token = trim(token);
        //D->>>The distance between the two cities
        D = atoi(token);
        printf("%d    ", D);
        printf("\n********-------************------************-------**\n");
        //Add the first and second city and the distance you are reading from the file to the graph between them
        int t1 = to_int(C1);
        int t2 = to_int(C2);
                // Given Edges
        addEdge(Adj, t1, t2, D);
    }
    printf("\n---------Jerusalem is a capital of Palestine-------\n\n\n");

}

// Function to print the created
// Adjacency Matrix
void printAdj(int Adj[][N], int N)
{
    for (int j = 0; j < N; j++)
    {
        printf("   %s", name1[j]);
    }
    printf("\n");

    // Traverse the Adj[][]
    for (int i = 0; i < N; i++)
    {
        printf("%s ", name1[i]);

        for (int j = 0; j < N; j++)
        {
            // Print the value at Adj[i][j]
            printf("   %d", Adj[i][j]);
        }
        printf("\n");
    }
    printf("\nWe will liberate all our occupied land and the blessed land by force, God willing, and we will be victorious soon \n(Prayer ablution in Al-Aqsa Mosque is close)\n");
}
// the set of vertices not yet included in shortest path tree
int min_D(int distance[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < N; v++)
        if (sptSet[v] == false && distance[v] <= min)
            min = distance[v], min_index = v;

    return min_index;
}
// Function that implements Dijkstra's single source shortest path algorithm
void pojram_distance_Dijkstra(int Adj[N][N], char city1[50], char city2[50])
{
    int from = to_int(city1), to = to_int(city2);

    int dist[N]; // The output array.  dist[i] will hold the shortest

    bool S[N]; // S[i] will be true if vertex i is included in shortest
    for (int i = 0; i < N; i++)
        dist[i] = INT_MAX, S[i] = false;

    // Distance of source vertex from itself is always 0
    dist[from] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < N - 1; count++)
    {
        // Pick the minimum distance vertex from the set of vertices not
        int u = min_D(dist, S);

        // Mark the picked vertex as processed
        S[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int T = 0; T < N; T++)
            if (!S[T] && Adj[u][T] && dist[u] != INT_MAX
                    && dist[u] + Adj[u][T] < dist[T])
                dist[T] = dist[u] + Adj[u][T];
    }

    printf("\n\n distance from %s to %s =>>>>> %d\n\n", city1, city2, dist[to]);
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
        printf("\n\n*** Please check that you get  information from files in option 1 ***\n\n");
    return !flag;
}

//It is a menu of operations that are required
void displayChoices()
{
    printf("Choose from the menu below:\n");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf("1.Read the file and print the data in it\n");
    printf("\n******************************************************************************************\n");

    printf("2.Print the graph for each city What cities are associated with them and how far they are\n");
    printf("\n******************************************************************************************\n");

    printf("3. Enter the names of the two cities you want the shortest distance between them \nand  print the result to a file called shortest_path.txt\n");
    printf("\n******************************************************************************************\n");

    printf("4) Exit.\n");
    printf("\n******************************************************************************************\n");
}
void displayMenu()
{
    int choice;
    //  struct Graph* graph = createGraph(V);

    int array_done[LEN_ARR_DONE];//This array to assure that we complete  the registration process before we ask anything else
    for (int i = 0; i<1 ; i++) //In This loop, the array represents flags for choice
    {
        array_done[i]=0;
    }

    displayChoices();

    while(1)
    {
        scanf("%d", &choice);
        if(choice ==4)
        {
            printf("----------------------Thank you for using my simple program, I hope you like it--------------------------\n");
            break;
        }

        switch(choice)
        {
        case 1:
            if(!array_done[0])
            {
//Print hashed tables (including empty spots)

                printf("\n----------------------------------------------------\n");
                printf("from         from_to           distance\n\n");
                read_file();
                printf("\n\n____________________________________________________\n\n");

                array_done[0] = 1;

            }
            break;

        case 2:
            if(is_selected(array_done, LEN_ARR_DONE))  // -1 is for just checking the first two values from array
            {
                printf("Print each city and other cities you connect to\n");
                printAdj(Adj, N);

            }
            break;

        case 3:
            if(is_selected(array_done, LEN_ARR_DONE - 1))  // -1 is for just checking the first two values from array
            {
                char in[50];
                char to[50];
                printf("Welcome ....Please enter the name of the city you are in:\n");
                scanf("%s",in);
                printf("Please enter the name of the city you want to go to:\n");
                scanf("%s",to);
    pojram_distance_Dijkstra(Adj, in,to);
            }
            break;
        default:
            printf("Please number from 1 to 4\n");
        }

        printf("\n\n");
        displayChoices();
    }
}

// Driver Code
int main()
{
displayMenu();
    return 0;
}
