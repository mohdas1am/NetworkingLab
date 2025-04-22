#include <stdio.h>

#define INF 99999
#define MAX_NODES 10  

struct PriorityQueue {
    	int node;
    	int distance;
};

struct PriorityQueue queue[MAX_NODES];
int size = 0;

void insert(int node, int distance) {
    	int i;
    	for (i = size - 1; i >= 0 && queue[i].distance > distance; i--) {
        	queue[i + 1] = queue[i];  // Shift elements
    	}
    	queue[i + 1].node = node;
    	queue[i + 1].distance = distance;
    	size++;
}

int deleteMin() {
    	if (size == 0) return -1;
    
    	int node = queue[0].node;
    	for (int i = 0; i < size - 1; i++) {
        	queue[i] = queue[i + 1];  // Shift left
    	}
    	size--;
    	return node;
}

void dijkstra(int graph[MAX_NODES][MAX_NODES], int n, int src) {
    	int dist[MAX_NODES];
    	int visited[MAX_NODES] = {0};

    	for (int i = 0; i < n; i++) {
        	dist[i] = INF;
    	}
    	dist[src] = 0;
    
    	insert(src, 0);

    	while (size > 0) {
        	int u = deleteMin();
        	if (visited[u]) continue;
        	visited[u] = 1;

        	for (int v = 0; v < n; v++) {
            		if (graph[u][v] != INF && !visited[v]) {
                		int newDist = dist[u] + graph[u][v];
                		if (newDist < dist[v]) {
                    			dist[v] = newDist;
                    			insert(v, newDist);
                		}
            		}
       		}
    	}

    	printf("\nShortest distances from node %d:\n", src);
    	for (int i = 0; i < n; i++) {
        	printf("To %d: %d\n", i, dist[i] == INF ? -1 : dist[i]);
    	}
}

int main() {
    	int graph[MAX_NODES][MAX_NODES];
    	int n, src;

    	printf("Enter the number of nodes: ");
    	scanf("%d", &n);

    	printf("Enter adjacency matrix (99999 for no edge):\n");
    	for (int i = 0; i < n; i++) {
        	for (int j = 0; j < n; j++) {
            		printf("Edge(%d->%d): ", i, j);
            		scanf("%d", &graph[i][j]);
        	}
    	}

    	printf("Enter source node: ");
    	scanf("%d", &src);

    	dijkstra(graph, n, src);

    	return 0;
}

