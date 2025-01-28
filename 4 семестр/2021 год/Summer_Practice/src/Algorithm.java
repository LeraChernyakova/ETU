import java.util.Scanner;
public class Algorithm {
    public static int [][] graph;
    public static int [] visited;
    public static int [] cost;
    public static int start;
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        int n,e, INF = Integer.MAX_VALUE;
        n = sc.nextInt();
        e = sc.nextInt();

        graph = new int [n][n];
        visited = new int [n];
        cost = new int[n];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                graph[i][j] = -1;
            }
        }

        for (int i = 0; i < e; i++) {
            int u = sc.nextInt();
            int v = sc.nextInt();
            int w = sc.nextInt();
            graph[u][v] = w;
            graph[v][u] = w;
        }

        start = sc.nextInt();

        for (int i = 0; i < n; i++) {
            cost[i]=INF;
        }
        cost[start]=0;

        dijkstra(start);
        printResult();
    }

    /* Recursive function to find the minimum distance of each node from given start node*/
    public static void dijkstra(int start){
        for (int i = 0; i <cost.length; i++) {
            if (graph[start][i] > -1 && cost[i] > (graph[start][i] + cost[start]) ){
                cost[i] = graph[start][i] + cost[start];
            }
        }

        int j = minDist();
        if (j  == -1 )
            return;

        visited[j] = 1;
        dijkstra(j);
    }

    /* Function to print the distance of each node from given start node*/
    public static void printResult(){
        for (int i = 0; i <cost.length; i++) {
            System.out.println("Distance of node "+i+" from node "+start+" is "+cost[i]);
        }
    }

    /* Function to find non-visited node with minimum distance*/
    public static int minDist(){
        int minDistance = Integer.MAX_VALUE;
        int index = -1;
        for (int i=0; i<cost.length; i++){
            if (minDistance>cost[i] && visited[i] == 0){
                minDistance = cost[i];
                index = i;
            }
        }
        return index;
    }
}
