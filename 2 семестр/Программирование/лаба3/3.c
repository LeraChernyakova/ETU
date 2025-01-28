#include <stdio.h>

int main() {
    int n, m;
    int arr[n][m];
    scanf("%d %d",&n,&m);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++)
            scanf ("%d", &arr[i][j]);
    }
    printf ("massiv:/n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++)
            printf ("%d ", arr[i][j]);
        printf ("\n");
    }
}
