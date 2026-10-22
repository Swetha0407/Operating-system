#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Employee {
    int empId;
    char empName[50];
    float empSalary;
};
int main() {
    FILE *filePtr;
    struct Employee emp;
    int choice, id;
    filePtr = fopen("employee.dat", "rb+");
    if (filePtr == NULL) {
        filePtr = fopen("employee.dat", "wb+");
        if (filePtr == NULL) {
            perror("Error creating the file");
            return 1;
        }
    }
    do {
        printf("\nEmployee Database Menu:\n");
        printf("1. Add Employee\n");
        printf("2. Display Employee Details\n");
        printf("3. Update Employee Details\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            fclose(filePtr);
            return 1;
        }
        switch (choice) {
            case 1:
                printf("Enter Employee ID (positive number): ");
                scanf("%d", &id);
                if (id <= 0) {
                    printf("Invalid employee ID.\n");
                    break;
                }
                fseek(filePtr, (long)(id - 1) * sizeof(struct Employee), SEEK_SET);
                printf("Enter Employee Name (no spaces): ");
                scanf("%49s", emp.empName);
                printf("Enter Employee Salary: ");
                scanf("%f", &emp.empSalary);
                if (emp.empSalary < 0) {
                    printf("Invalid salary.\n");
                    break;
                }
                emp.empId = id;
                if (fwrite(&emp, sizeof(struct Employee), 1, filePtr) == 1)
                    printf("Employee details added successfully.\n");
                else
                    printf("Error writing employee details.\n");
                fflush(filePtr);
                break;
            case 2:
                printf("Enter Employee ID to display: ");
                scanf("%d", &id);
                if (id <= 0) {
                    printf("Invalid employee ID.\n");
                    break;
                }
                fseek(filePtr, (long)(id - 1) * sizeof(struct Employee), SEEK_SET);
                if (fread(&emp, sizeof(struct Employee), 1, filePtr) == 1 && emp.empId == id) {
                    printf("Employee ID: %d\n", emp.empId);
                    printf("Employee Name: %s\n", emp.empName);
                    printf("Employee Salary: %.2f\n", emp.empSalary);
                }
                else
                    printf("Employee record not found.\n");
                break;
            case 3:
                printf("Enter Employee ID to update: ");
                scanf("%d", &id);
                if (id <= 0) {
                    printf("Invalid employee ID.\n");
                    break;
                }
                fseek(filePtr, (long)(id - 1) * sizeof(struct Employee), SEEK_SET);
                if (fread(&emp, sizeof(struct Employee), 1, filePtr) != 1 || emp.empId != id) {
                    printf("Employee record not found.\n");
                    break;
                }
                printf("Enter new Employee Name (no spaces): ");
                scanf("%49s", emp.empName);
                printf("Enter new Employee Salary: ");
                scanf("%f", &emp.empSalary);
                if (emp.empSalary < 0) {
                    printf("Invalid salary.\n");
                    break;
                }
                fseek(filePtr, (long)(id - 1) * sizeof(struct Employee), SEEK_SET);
                if (fwrite(&emp, sizeof(struct Employee), 1, filePtr) == 1)
                    printf("Employee details updated successfully.\n");
                else
                    printf("Error updating employee details.\n");
                fflush(filePtr);
                break;
            case 4:
                printf("Exiting Employee Database.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
    fclose(filePtr);
    return 0;
}
