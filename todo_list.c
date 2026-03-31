#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char *title;
    int done; // 0 = not done, 1 = done
} Task;

typedef struct{
    Task *tasks;
    int size;
    int capacity;
}TodoList;

void initTodoList(TodoList *list){
    list->size = 0;
    list->capacity = 5;
    list->tasks = malloc(sizeof(Task) * list->capacity);
}

void addTask(TodoList *list, const char *title){
    if(list->size != list->capacity){
        // resize array
        list->capacity *= 2;
        list->tasks = realloc(list->tasks, sizeof(Task) * list->capacity);
    }

    list->tasks[list->size].title = malloc(strlen(title) + 1);
    strcpy(list->tasks[list->size].title, title);
    list->tasks[list->size].done = 0;
    list->size++;
    printf("Task added: %s\n", title);
}

void completeTask(TodoList *list, int index){
    if(index < 0 || index >= list->size){
        printf("Invalid task number!\n");
        return;
    }

    if(list->tasks[index].done == 1){
        printf("Task is already completed!\n");
        return;
    }

    list->tasks[index].done = 1;
    printf("Task completed: %s\n", list->tasks[index].title);
}

void deleteTask(TodoList *list, int index){
    if(index < 0 || index >= list->size){
        printf("Invalid task number!\n");
        return;
    }
    printf("Deleting task: %s\n", list->tasks[index].title);
    
    free(list->tasks[index].title);
    
    for(int i = index; i < list->size -1; i++){
        list->tasks[i] = list->tasks[i + 1];
    }
    list->size--;
}

void listTasks(TodoList *list){
    printf("\n--- Your Tasks ---\n");
    for(int i = 0; i < list->size; i++){
        printf("%d. [%c] %s\n", i+1, list->tasks[i].done ? 'X' : ' ', list->tasks[i].title);
    }
    printf("------------------\n");
}

void freeTodoList(TodoList *list){
    for(int i = 0; i < list->size; i++){
        free(list->tasks[i].title);
    }
    free(list->tasks);
}

void saveTodoList(TodoList *list, const char *filename){
    FILE *file = fopen(filename, "wb"); // write binary mode

    if(!file){
        printf("Failed to open file for writing\n");
        return;
    }
    
    fwrite(&list->size, sizeof(int), 1, file);

    for(int i = 0; i<list->size; i++){
        size_t len = strlen(list->tasks[i].title) + 1; // title size + null terminator
        fwrite(&len, sizeof(size_t), 1, file); 
        fwrite(list->tasks[i].title, sizeof(char), len, file); 
        fwrite(&list->tasks[i].done, sizeof(int), 1, file);  
    }

    fclose(file);
    printf("Tasks saved to %s\n", filename);
}

void loadTodoList(TodoList *list, const char *filename){
    FILE *file = fopen(filename, "rb"); // read binary mode
    
    if(!file){
        printf("Failed to open file for reading\n");
        return;
    }

    freeTodoList(list);
    initTodoList(list);

    int taskCount;
    fread(&taskCount, sizeof(int), 1, file);

    for(int i = 0; i < taskCount; i++){
        size_t len;
        fread(&len, sizeof(size_t), 1, file);

        char *title = malloc(len);
        fread(title, sizeof(char), len, file);

        int done;
        fread(&done, sizeof(int), 1, file);

        addTask(list, title);
        list->tasks[i].done = done;

        free(title);
    }

    fclose(file);
    printf("Tasks loaded from %s\n", filename);
}

int main(int argc, char **argv){
    TodoList myList;
    initTodoList(&myList);
    loadTodoList(&myList, "tasks.dat");

    int choice;
    char buffer[256];

    while(1){
        printf("\n1. Add task\n2. Complete Task\n3. Delete task\n4. List tasks\n5. Quit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1:
            printf("Enter task title: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            addTask(&myList, buffer);
            break;
        
        case 2:
            printf("Enter task number to complete: ");
            int taskNum;
            scanf("%d", &taskNum);
            completeTask(&myList, taskNum - 1);
            getchar();
            break;
        case 3: 
            printf("Enter task number to delete: ");
            int delNum;
            scanf("%d", &delNum);
            getchar();
            deleteTask(&myList, delNum - 1);
            break;
        case 4: 
            listTasks(&myList);
            break;
        case 5: 
            saveTodoList(&myList, "tasks.dat");
            freeTodoList(&myList);
            printf("Goodbye!\n");
            return 0;
        default:
            printf("Invalid choice!\n");
        }
    }
}