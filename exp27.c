#include <stdio.h>
#include <string.h>
int main() {
    char fn[100], pat[100], temp[200];
    FILE *fp;
    printf("\nEnter file name: ");
    scanf("%99s", fn);
    printf("Enter the pattern: ");
    scanf("%99s", pat);
    fp = fopen(fn, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    while (fgets(temp, sizeof(temp), fp) != NULL) {
        if (strstr(temp, pat) != NULL) {
            printf("%s", temp);
        }
    }
    fclose(fp);
    return 0;
}
