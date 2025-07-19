#include <stdio.h>
#include "dyn_arr.h"

int main(int argc, char** argv) {
    printf("--- dynamic array demo 0.1 ---\n");    
    // Integer Demo
    Dyn int_dyn;
    Init_dyn(&int_dyn, sizeof(int));
    
    for(int i = 0; i < 100; i += 1){
        Push_dyn(&int_dyn, &i);
        int *arr = int_dyn.start; 
        printf("index %d value %d\n", i, arr[i]); 
    }
    
    int insert = 69; 
    Insert_dyn(&int_dyn, 98, &insert);
    int *int_arr = int_dyn.start; 
    printf("index %d value %d\n", 98, int_arr[98]); 
    
    // Custom Struct Demo
    typedef struct {
        int age;
        const char* name;
    } Person;

    Dyn person_dyn;
    Init_dyn(&person_dyn, sizeof(Person));
    
    const char *germanNames[] = {
        "Anna", "Bernd", "Claudia", "David", "Emilia", 
        "Felix", "Gisela", "Hans", "Ida", "Jakob", 
        "Klara", "Lukas", "Maria", "Nico", "Olivia", 
        "Paul", "Silke", "Thomas", "Ute", "Volker"
    };
    
    for(int i = 0; i < 100; i += 1) {
        Person person = {.age = i, .name = germanNames[rand() % 20] };
        Push_dyn(&person_dyn, &person);
        Person *person_arr = person_dyn.start;
        printf("index %d age %d name %s\n", i, person_arr[i].age, person_arr[i].name); 
    }

    Person *person = Get_dyn(&person_dyn, 69);
    Person *person_arr = person_dyn.start;
    printf("index %d age %d name %s\n", 69, person_arr[69].age, person_arr[69].name); 

    return 0;
}
