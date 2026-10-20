#include <stdio.h>
void allocate(int mp[], int p[], int n, int m, int choice) {
    int used[20] = {0};
    for (int i = 0; i < m; i++) {
        int selected = -1;
        for (int j = 0; j < n; j++) {
            if (!used[j] && mp[j] >= p[i]) {
                if (choice == 1) {
                    selected = j; 
                    break;
                }
                else if (choice == 2 && (selected == -1 || mp[j] < mp[selected])) {
                    selected = j;       
                }
                else if (choice == 3 && (selected == -1 || mp[j] > mp[selected])) {
                    selected = j;     
                }
            }
        }
        if (selected != -1) {
            printf("Process %d (%d KB) allocated to partition %d (%d KB)\n", i + 1, p[i], selected + 1, mp[selected]);
            used[selected] = 1;
        }
        else {
            printf("Process %d (%d KB) must wait\n", i + 1, p[i]);
        }
    }
}
int main() {
    int m, n, mp[20], p[20], ch;
    printf("Number of memory partitions: ");
    scanf("%d", &n);
    printf("Number of processes: ");
    scanf("%d", &m);
    if (n < 1 || n > 20 || m < 1 || m > 20) {
        printf("Invalid number of partitions or processes.\n");
        return 1;
    }
    printf("Enter the memory partition sizes:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &mp[i]);
    printf("Enter process sizes:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &p[i]);
    printf("1. First Fit\n2. Best Fit\n3. Worst Fit\nEnter your choice: ");
    scanf("%d", &ch);
    if (ch >= 1 && ch <= 3)
        allocate(mp, p, n, m, ch);
    else
        printf("Invalid choice.\n");
    return 0;
}
