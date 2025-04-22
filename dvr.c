#include <stdio.h>
#define INF 99999
#define MAX_NODES 10  
int nxt[100][100];

void printTable(int a[MAX_NODES][MAX_NODES], int n) {
    	printf("\nRouting Table:\n");
    	printf("\t");
    	for (int i = 0; i < n; i++) {
        	printf("%d\t", i);
    	}
    	printf("\n");

    	for (int i = 0; i < n; i++) {
        	printf("%d\t", i);
        	for (int j = 0; j < n; j++) {
            		if (a[i][j] == INF)
                		printf("INF\t");
            		else
              	 		printf("%d\t", a[i][j]);
        	}
        	printf("\n");
    	}
    	
    	
    	for(int i=0;i<n;i++){
    		printf("Table of %d\n",i);
    		printf("Dest\tDist\tNxtHop\n");
    		for(int j=0;j<n;j++){
    			printf("%d\t%d\t%d\n",j,a[i][j],nxt[i][j]);
    		}
    	}
}

void bellmanford(int a[MAX_NODES][MAX_NODES], int n) {
	for(int c=0;c<n-1;c++){
        	for (int i = 0; i < n; i++) {
            		for (int j = 0; j < n; j++) {
                		for (int k = 0; k < n; k++) {
                    			if (a[i][k] != INF && a[k][j] != INF && a[i][k] + a[k][j] < a[i][j]) {
                        			a[i][j] = a[i][k] + a[k][j];
                        			if(i==j){
                        				nxt[i][j]=i;
                        			}else{
                        				nxt[i][j]=k;
                        			}
                    			}
                		}
            		}
        	}
	}

    printTable(a, n);
}

int main() {
    	int a[MAX_NODES][MAX_NODES];
    	int n;

    	printf("Enter the number of nodes: ");
    	scanf("%d", &n);

    	printf("Enter adjacency matrix (99999 for no edge):\n");
    	for (int i = 0; i < n; i++) {
        	for (int j = 0; j < n; j++) {
        		printf("Edge(%d->%d)\n",i,j);
            		scanf("%d", &a[i][j]);
        	}
    	}

    	bellmanford(a, n);

    	return 0;
}
