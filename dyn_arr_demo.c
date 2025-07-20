#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <inttypes.h>

#include "dyn_arr.h"


// Custom Struct Demo
typedef struct {
    int age;
    const char* name;
} Person;

int print_person(void *iterator, void *arg, int64_t pos){
    Person person = *(Person*) iterator;
    printf("%lld. %s is %d old\n", pos, person.name, person.age);
    return 0;
}

int main(int argc, char** argv) {
    
    int person_count = 20;
    if(argc > 1) person_count = (int) strtoimax(argv[1], NULL, 10);

    srand(time(NULL));
    printf("--- dynamic array demo ---\n");    
    // Integer Demo
    Dyn int_dyn;
    Init_dyn(&int_dyn, sizeof(int));
    
    for(int i = 0; i < 100; i += 1){
        Push_dyn(&int_dyn, &i);
        int *arr = int_dyn.start; 
        printf("index %d value %d\n", i, arr[i]); 
    }
    printf("---------- Set -----------\n");
    
    int insert = 69; 
    Set_dyn(&int_dyn, 98, &insert);
    int *int_arr = int_dyn.start; 
    printf("index %d value %d\n", 98, int_arr[98]); 
    
    //Costum Struct Demo
    Dyn person_dyn;
    Init_dyn(&person_dyn, sizeof(Person));
    
    const char *germanNames[] = {
        "Anna", "Bernd", "Claudia", "David", "Emilia", 
        "Felix", "Gisela", "Hans", "Ida", "Jakob", 
        "Klara", "Lukas", "Maria", "Nico", "Olivia", 
        "Paul", "Silke", "Thomas", "Ute", "Volker"
    };
    
    printf("---------- Custom struct -----------\n");
    for(int i = 0; i < person_count; i += 1) {
        Person person = {.age = i, .name = germanNames[rand() % 20] };
        Push_dyn(&person_dyn, &person);
        Person *person_arr = person_dyn.start;
        printf("index %d age %d name %s\n", i, person_arr[i].age, person_arr[i].name); 
    }
    int rand_person = rand() % person_count;
    Person *person = Get_dyn(&person_dyn, rand_person);
    printf("---------- Get -----------\n");
    printf("index %d age %d name %s\n", rand_person, person->age, person->name); 

    printf("---------- Insertion -----------\n");
    Person a_person = {.age = 1234, .name = "####Inserted####" };
    int rand_insertion_place = rand() % person_count;
    Insert_dyn(&person_dyn, rand_insertion_place, &a_person);
    Person *person_arr = person_dyn.start;
    for(int i = 0; i < person_dyn.cursor; i += 1) {
        printf("index %d age %d name %s\n", i, person_arr[i].age, person_arr[i].name); 
    }
    
    printf("--------- For Each ---------- \n");
    For_each_dyn(&person_dyn, print_person, NULL); 

    return 0;
}
