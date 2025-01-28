#include <stdio.h>

int main() {
  int n, m;
  scanf ("%d %d", &n, &m);
  int maze[n][m];

  for (int i = 0; i < n; i++){
    for (int j = 0; j < m; j++){
        char space;
        scanf ("%d", maze[i][j]);
        scanf ("%c", space);
    }
  }
  return 0;
}
