#include <stdio.h>
#include <string.h>

#define MAX 100

int graph_matrix[MAX][MAX];
int node_count;
char nodes[MAX];
int visited_nodes[MAX];
int total_weight = 0;

void bfs(int start)
{
    int queue[MAX], front = 0, back = 0;
    visited_nodes[start] = 1;

    queue[back++] = start;

    printf("BFS Travesal Path: ");
    int first_print = 1;
    while(front < back)
    {
        int u = queue[front++];

        if(!first_print)
            printf(" -> ");
        printf("%c", nodes[u]);

        first_print = 0;

        for(int v = 0; v < node_count; v++)
        {
            if(graph_matrix[u][v] > 0 && !visited_nodes[v])
            {
                visited_nodes[v] = 1;
                queue[back++] = v;
            }
        }
    }
    printf("\n");
}

int main()
{
    FILE *fp = fopen("graph.txt", "r");

    if (!fp)
    {
        printf("Could not open the file graph.txt.\n");
        return 1;
    }
    
    fscanf(fp, "%d", &node_count);


    //reading the text file and identifying the nodes in it.
    for(int i = 0; i < node_count; i++)
    {
        fscanf(fp, " %c", &nodes[i]);
        visited_nodes[i] = 0;

        //initializing the adjacency matrix and setting all the values to 0.
        for(int j = 0; j < node_count; j++)
        {
            graph_matrix[i][j] = 0;
        }
    }

    char type[15];
    fscanf(fp, " %s", type);

    char a, b;
    int w;

    while(fscanf(fp, " %c %c %d", &a, &b, &w) != EOF)
    {
        int u = a - 'A';
        int v = b - 'A';
        graph_matrix[u][v] = w; 

        total_weight += w;

        if(strcmp(type, "undirected") == 0)
        {
            graph_matrix[v][u] = w;
        }
    }
    fclose(fp);

    for (int i = 0; i < node_count; i++)
    {
        visited_nodes[i] = 0;
    }

    bfs(0);

    int unreachable_check = 0;

    printf("Total Weight: %d\n", total_weight);

    printf("Unreachable Nodes: ");

    for (int i = 0; i < node_count; i++)
    {
        if (!visited_nodes[i])
        {
            printf("%c ", nodes[i]);
            unreachable_check = 1;
        }   
    }

    if (unreachable_check == 0)
    {
        printf("None");
    }
    
    printf("\n");

    return 0;
}