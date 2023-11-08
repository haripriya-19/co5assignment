#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<vector>

#define NUM_VERTICES 6

using namespace std;

struct graph_node
{
    char name;
    vector<graph_node*>ptr;
};

struct adjacency_list_node
{
    char name;
    struct adjacency_list_node *nextptr = NULL;
};

struct vertex_array_node
{
    char name;
    graph_node *node_arr = NULL;
    adjacency_list_node *list_base_adr = NULL;
    vertex_array_node *next_node;
};

adjacency_list_node *al_tail = NULL;

vertex_array_node *head = NULL;
vertex_array_node *tail = NULL;

void cerate_adjacency_linked_list(adjacency_list_node *new_node,vertex_array_node *vertex_node)
{
    if(al_tail == NULL)
    {
        vertex_node->list_base_adr = new_node;
        al_tail = new_node;
    }

    else
    {
        al_tail->nextptr = new_node;
        al_tail = new_node;
    }

}

void create_vertex_array(vertex_array_node *new_node)
{
    if (tail == NULL)
    {
        tail = new_node;
        head = tail;
    }

    else 
    {
        tail->next_node = new_node;
        tail = new_node;
       
    }
}

void traverse_adjacency_list(adjacency_list_node *base_addr)
{
while(base_addr != NULL)
{
    printf("%c -> ",base_addr->name);
    base_addr = base_addr->nextptr;
}
    printf("NULL");
}


int main()
{
    srand(time(NULL));
    bool is_edge;

    adjacency_list_node *al_new_node;
    graph_node *new_node;
    vertex_array_node *va_new_node;

    for (size_t i = 0; i < NUM_VERTICES; i++)
    {
        va_new_node = (vertex_array_node*)calloc(1,sizeof(vertex_array_node));
        va_new_node->name = (65+i);
        new_node = (graph_node*)calloc(1,sizeof(graph_node));
        new_node->name = (65+i); 
        va_new_node->node_arr = new_node;
        create_vertex_array(va_new_node);

        al_tail = NULL;
        

        for (size_t j = 0; j < NUM_VERTICES; j++)
        {
            if (i == j)
            continue;

            else
            {
                is_edge = rand()%2;

                if (is_edge == true)
                {
                    al_new_node = (adjacency_list_node*)calloc(1,sizeof(adjacency_list_node));
                    al_new_node->name = (65+j);
                    cerate_adjacency_linked_list(al_new_node,va_new_node);
                }

            }
        }
        
    }

    printf("Following is the information about the graph to be constructed\n\n");
    
    tail = head;

    while (tail != NULL)
    {
        printf("Adjacency List of Node %c is: ",tail->name);
        traverse_adjacency_list(tail->list_base_adr);
        printf("\n");
        tail = tail->next_node;
    }
    tail = head;

for (size_t i = 0; i < NUM_VERTICES; i++)
{
    al_tail = tail->list_base_adr;//adjacency list's tail is set to its base address or head
    
    graph_node* current_graph_node = tail->node_arr;//current graph node is set to adjacency list's graph node address

    while (al_tail != NULL)//tail is set to head and after linkage it will get to NULL
    {
        char target_node_name = al_tail->name;//node name is stored in target node name

        vertex_array_node* target_vertex_node = head;//pointed to head
        while (target_vertex_node != NULL && target_vertex_node->name != target_node_name)//to move to all but not repeat anyone
        {
            target_vertex_node = target_vertex_node->next_node;//step to next node
        }

        if (target_vertex_node != NULL)
        {
            current_graph_node->ptr.push_back(target_vertex_node->node_arr);//push back function to link graph nodes
        }

        al_tail = al_tail->nextptr;//to reach next adjacency list
    }

    tail = tail->next_node;//to move to next graph node
}


    return 0;
}
