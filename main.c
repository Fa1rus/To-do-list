#include <stdio.h>    // For file handling (fopen, fclose, fprintf, fscanf) and printing (printf, scanf)
#include <stdlib.h>   // For memory management (if needed) and exit()
#include <string.h>   // For string manipulation (strcpy, strcat, strcmp)


void editTask() {
    char task[99];  
    FILE *file = fopen("data.txt", "a");  

    if (file == NULL) {
        printf("Error: Cannot open file!\n");
        return;     // No return 1 because it's a void function
    }

    printf("What is your task?\n   : ");
    while (getchar() != '\n');     // Clear leftover newline
    fgets(task, sizeof(task), stdin);

    fprintf(file, "[ ] %s", task);  // Corrected syntax
    fclose(file);
    printf("Task added successfully!\n");
}

void viewTasks() {
    char task[99];  // Buffer to store each task
    FILE *file = fopen("data.txt", "r");  // Open file in read mode

    if (file == NULL) {
        printf("No tasks found!\n");  // If file doesn't exist
        return;
    }

    printf("\nYour To-Do List:\n");
    int taskNumber = 1;
    while (fgets(task, sizeof(task), file) != NULL) {  // Read each line
        printf("%d. %s", taskNumber,task);  // Print task
        taskNumber++;
    }

    fclose(file);  // Close file
}

void markTaskAsComplete(){
    FILE *file = fopen("data.txt", "r");
    if (file == NULL){
        printf("No task found!\n");
        return;
    }
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error: Cannot create temp file!\n");
        fclose(file); //Close file before returning
        return;
    }
    viewTasks(); // Show task number with numbers

    printf("\nEnter the task number to mark as complete: ");
    int taskNumber, currentTask = 1;
    scanf("%d", &taskNumber);
    getchar();   // Clear newline from input buffer

    char task[99];
    while (fgets(task, sizeof(task), file) != NULL) {
        if (currentTask == taskNumber && strncmp(task, "[ ]", 3) == 0) {  
            task[1] = 'X';  // Change [ ] to [X]
        }
        fprintf(tempFile, "%s", task);  // Write to temp file
        currentTask++;
    }

    fclose(file);
    fclose(tempFile);

    remove("data.txt");           // Delete old file
    rename("temp.txt", "data.txt");  // Rename temp to original

    printf("Task %d marked as complete!\n", taskNumber);
}

void deleteTask(){
    FILE *file = fopen("data.txt","r");
    if (file == NULL){
        printf("Error: no task found!\n");
        return;
    }
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error: cannot create temp file!\n");
        fclose(file);
        return;
    }
    viewTasks(); //show task numbers before deletion

    printf("\nEnter the task number to delete: ");
    int taskNumber, currentTask = 1;
    scanf("%d", &taskNumber);
    getchar();  // Clear newline from input buffer
    
    char task[99];
    int taskDeleted = 0;

    while (fgets(task, sizeof(task), file) != NULL) {
        if (currentTask == taskNumber) {
            taskDeleted =1;     // Mark that we deleted a task
        } else {
            fprintf(tempFile, "%s", task);
        }
        currentTask++;
    }
    fclose(file);
    fclose(tempFile);
    if (taskDeleted)
    {
        remove("data.txt");             // Delete old file
        rename("temp.txt", "data.txt");   //rename temp file to data.txt
        printf("task %d deleted successfully!\n", taskNumber);
    } else {
        remove("temp.txt"); // If no task was deleted, discard temp file
        printf("Invalid task number! No task deleted.\n");
    }
    
}
int main(){
    printf("Hello there!\n");
    printf("Which action do you want to do?\n w: Write Task\n r: Read Tasks\n c: Delete Task\n m: Mark task\n:");
    char ch;
    scanf(" %c",&ch);

    while (1) {  // Infinite loop, use break to exit
        if (ch == 'w') {
            editTask();
        } else if (ch == 'r') {
            printf("Reading tasks...\n");
            viewTasks();
        } else if (ch == 'm') {
            markTaskAsComplete();
        } else if (ch == 'd') {
            printf("Deleting task...\n");
            deleteTask();
        } else {
            printf("Invalid choice! Try again.\n");
        }

        printf("\nWhich action do you want to do next? (w/r/m/d or q to quit): ");
        scanf(" %c", &ch);
        if (ch == 'q') break;  // Quit the loop if user enters 'q'
    }
    printf("Goodbye!\n Remember you are the BEST one :)");
    return 0;
}