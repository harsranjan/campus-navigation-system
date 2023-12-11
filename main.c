#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

#define MAX_LOCATIONS 100
#define INF INT_MAX

struct Location {
    char name[50];
};

struct Graph {
    int numLocations;
    struct Location locations[MAX_LOCATIONS];
    int routes[MAX_LOCATIONS][MAX_LOCATIONS];
};

void initGraph(struct Graph* graph, int numLocations) {
    graph->numLocations = numLocations;
    for (int i = 0; i < numLocations; ++i) {
        for (int j = 0; j < numLocations; ++j) {
            if (i == j) {
                graph->routes[i][j] = 0;
            } else {
                graph->routes[i][j] = INF;
            }
        }
    }
}

void addLocation(struct Graph* graph, int index, const char* name) {
    strncpy(graph->locations[index].name, name, sizeof(graph->locations[index].name));
}

void addRoute(struct Graph* graph, int from, int to, int weight) {
    graph->routes[from][to] = weight;
    graph->routes[to][from] = weight;  // Assuming bidirectional routes
}

void printPath(struct Graph* graph, int parent[MAX_LOCATIONS][MAX_LOCATIONS], int i, int j) {
    if (parent[i][j] == i) {
        printf(" -> %s", graph->locations[i].name);
        return;
    }
    printPath(graph, parent, i, parent[i][j]);
    printf(" -> %s", graph->locations[j].name);
}

void floydWarshall(struct Graph* graph, int source, int destination) {
    int dist[MAX_LOCATIONS][MAX_LOCATIONS];
    int parent[MAX_LOCATIONS][MAX_LOCATIONS];

    for (int i = 0; i < graph->numLocations; ++i) {
        for (int j = 0; j < graph->numLocations; ++j) {
            dist[i][j] = graph->routes[i][j];
            if (dist[i][j] != INF && i != j) {
                parent[i][j] = i;
            } else {
                parent[i][j] = -1;
            }
        }
    }

    for (int k = 0; k < graph->numLocations; ++k) {
        for (int i = 0; i < graph->numLocations; ++i) {
            for (int j = 0; j < graph->numLocations; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    parent[i][j] = parent[k][j];
                }
            }
        }
    }

    printf("Optimal route from %s to %s:", graph->locations[source].name, graph->locations[destination].name);
    printPath(graph, parent, source, destination);
    printf("\nTotal distance: %d\n", dist[source][destination]);
}

void readFunctionsFromFile(struct Graph* graph, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (strstr(buffer, "addLocation") != NULL) {
            int index;
            char name[50];
            sscanf(buffer, "addLocation(&graph, %d, \"%49[^\"]\")", &index, name);
            addLocation(graph, index, name);
        } else if (strstr(buffer, "addRoute") != NULL) {
            int from, to, weight;
            sscanf(buffer, "addRoute(&graph, %d, %d, %d)", &from, &to, &weight);
            addRoute(graph, from, to, weight);
        }
    }

    fclose(file);
}

int main() {
    struct Graph graph;
    initGraph(&graph, 6);

    // Read functions from external file and add locations/routes to the graph
    readFunctionsFromFile(&graph, "functions.txt");

    printf("Campus Navigation System\n");
    printf("Locations available in the campus are : \n");
    printf("0.Main Gate\n");
    printf("1.Mac\n");
    printf("2.Library\n");
    printf("3.Gandhi Chowk\n");
    printf("4.11th Block\n");
    printf("5.Food Court\n");

    int source, destination;
    printf("Enter source location index (0 to %d): ", graph.numLocations - 1);
    scanf("%d", &source);
    printf("Enter destination location index (0 to %d): ", graph.numLocations - 1);
    scanf("%d", &destination);

    if (source < 0 || source >= graph.numLocations || destination < 0 || destination >= graph.numLocations) {
        printf("Invalid source or destination\n");
        return 1;
    }

    floydWarshall(&graph, source, destination);

    return 0;
}
