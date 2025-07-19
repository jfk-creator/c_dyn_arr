# c_dyn_arr
A naiv impl of a dynamic array in c

# How to use it
´´´c
typedef struct {
    int age;
    char name[255];
    } Person;

Dyn person_dyn; // create a uninitialzed dyn struct
Init_dyn(&dyn, sizeof(Person)) // init person_dyn

Person person = { .age = 31, .name = "Julian" };
Push_dyn(&dyn, &person); // appends item to the last element
Insert_dyn(&dyn, 5, &person); // inserts into the array at a specific place, only if this place exists
Person *get_person = (Person*) Get_gyn(&dyn, 5, &person); // gets the element from a specific place

Person *person_arr = person_dyn.start; // you now have access via the c array syntax
Person julian = person_arr[0]; 
´´´


