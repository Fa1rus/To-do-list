#include<stdio.h>

void SayHello(){
        printf("Hello, World\n");
    }

void addTask(){
    int i, n;
    char task[99];
    FILE *file =fopen("data.txt","a");
    if (file == NULL)
    {
        printf("Error opening file!\n");
    }
        
}

int main(){
    SayHello();    
    return 0;
}

