#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// A struct for the single graph
typedef struct{
    // Distance between the first node and the current node
    unsigned int dist;
    // 1 if the node has been visited, 0 otherwise
    int visited;
} graph_node;

// A struct for the list
typedef struct list_node{
    // Total costs of the graph
    unsigned int cost;
    // Index of the graph, which is the order of insertion
    unsigned int idx;
    // Previous graph on the list
    struct list_node * prev;
    // Next graph on the list
    struct list_node * next;
} list_node;

// A struct to preserve the beginning and end of the list
typedef struct{
    list_node * head;
    list_node * last;
} list;


unsigned int compute_graph_cost(unsigned int d){
    unsigned min_dist = 0, min_node = 1, count = 0, cost = 0;
    char s[1000000];
    unsigned int adj_matrix[d][d];
    graph_node cost_matrix[d - 1];
    char * ns;

    // Reading the adjacent matrix
    for(unsigned i = 0; i < d; i++){
        if(!fgets(s, 1000000, stdin)){
            printf("Error\n");
        }
        adj_matrix[i][0] = strtol(s, &ns, 10);
        for(unsigned j = 1; j < d; j++){
            adj_matrix[i][j] = strtol(ns + 1, &ns, 10);
        }
    }

    // Set the cost matrix and check if the total cost of the graph is zero
    for(unsigned i = 0; i < d - 1; i++){
        // Set the matrix
        cost_matrix[i].dist = adj_matrix[0][i + 1];
        cost_matrix[i].visited = 0;
        // Search for the nearest node to the first node
        if(min_dist > adj_matrix[0][i + 1] || min_dist == 0){
            if(adj_matrix[0][i + 1] != 0){
                min_dist = adj_matrix[0][i + 1];
                min_node = i + 1;
            }
        }
    }
    // If no node was reached by the first, the total cost of the graph is zero
    if(min_dist == 0)
        return cost;

    cost += min_dist;
    cost_matrix[min_node - 1].visited = 1;
    count ++;

    unsigned i, j;
    while(count < d - 1){
        min_dist = 0;
        j = min_node;
        for(i = 0; i < d - 1; i++){
            // If the node has already been visited, continue
            if(cost_matrix[i].visited == 1)
                continue;

            // Update the distance of the node
            if(adj_matrix[j][i + 1] != 0){
                // If the i + 1 node is reached by the current node, check if it is convenient to update the distance
                if(cost_matrix[i].dist == 0 || cost_matrix[j - 1].dist + adj_matrix[j][i + 1] < cost_matrix[i].dist)
                    cost_matrix[i].dist = cost_matrix[j - 1].dist + adj_matrix[j][i + 1];
            }
            // Find the next node to consider (the one with the minimum distance among the non visited ones)
            if(min_dist > cost_matrix[i].dist || min_dist == 0){
                if(cost_matrix[i].dist != 0){
                    min_dist = cost_matrix[i].dist;
                    min_node = i + 1;
                }
            }
        }

        // If it is not possible to reach any other node
        if(min_dist == 0)
            return cost;

        // Update the cost, visited nodes and count
        cost_matrix[min_node - 1].visited = 1;
        cost += min_dist;
        count ++;
    }

    return cost;
}

list_node * create_new_graph(unsigned int cost, unsigned int idx){
    // Create a new node for the list of graphs
    list_node * new_node = malloc(sizeof(list_node));
    new_node->idx = idx;
    new_node->cost = cost;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

list insert_graph(list graphs, unsigned int k, unsigned int cost, unsigned int num){
    list_node * new_node = NULL;
    if(num < k)
        new_node = create_new_graph(cost, num);
    else{
        if(cost >= graphs.last->cost)
            return graphs;
        // Use the last node in the list, since this will be removed anyway
        new_node = graphs.last;
        graphs.last = graphs.last->prev;
        graphs.last->next = NULL;
        new_node->next = NULL;
        new_node->prev = NULL;
        new_node->cost = cost;
        new_node->idx = num;
    }

    if(num == 0){
        // The graph is the first one
        graphs.head = new_node;
        graphs.last = new_node;
    } else {
        if(cost < graphs.head->cost){ // The graph has the lowest cost
            new_node->next = graphs.head;
            graphs.head->prev = new_node;
            graphs.head = new_node;
        } else if(cost >= graphs.last->cost){ // The graph has the highest cost
            new_node->prev = graphs.last;
            graphs.last->next = new_node;
            graphs.last = new_node;
        } else { // The graph is in the middle
            list_node * p = graphs.head;
            while(p->cost <= new_node->cost){
                p = p->next;
            }
            new_node->next = p;
            new_node->prev = p->prev;
            p->prev = new_node;
            (new_node->prev)->next = new_node;
        }
    }

    return graphs;
}

void print_top_k(list graphs){
    list_node * p = graphs.head;
    // Print the index of the graphs
    while(p != NULL){
        if(p->next == NULL){
            printf("%u", p->idx);
        } else{
            printf("%u ", p->idx);
        }
        p = p->next;
    }
    printf("\n");
}


int main() {
    unsigned int d, k, cost, num = 0;
    char s1[1000000];
    list graphs = {NULL, NULL};

    // Read the constants
    if(!scanf("%u %u\n", &d, &k)){
        printf("Errore\n");
    }

    while(fgets(s1, 1000000, stdin) != NULL){
        switch(s1[0]){
            case 'A': // Add a graph
                cost = compute_graph_cost(d);
                graphs = insert_graph(graphs, k, cost, num);
                num++;
                break;
            case 'T': // Print top k graphs
                print_top_k(graphs);
                break;
        }
    }

    return 0;
}
