
typedef struct {
    char * name;
    int age;
} person;


void main() {
  // Dynamic allocation of memory helps us store data
  // without initially knowing the size of the data
  person *myperson = (person *)malloc(sizeof(person));
  // We want to allocate just enough memory to hold a person
  // And malloc will return us a pointer to that memory

  // Note: sizeof is NOT a function, the compiler
  // interprets it and translates it to the actual
  // size of the person struct

  // We MUST 'release' that memory using free, otherwise it's a memory leak!
  free(myperson);

  // You might be thinking: what's up with that weird parenthesis?
  // We are casting the pointer returned by malloc!
  // Malloc returns type void *, we want to case it to person *
};
