#include <stdio.h>
#include <strings.h>
#include <stdint.h>
#include <stdbool.h>
/*
Built-in types:
Primitives:

int, char, void, bool, float, double, short, long, long long,
unsigned flavors of int, char, short, long, long long

signed is implicit can be also be specified

but first, what is signed vs unsigned?

unsigned char is 1 byte (8 bits) and you can represent 0 -> (2^8)-1 (255)

_ _ _ _ _ _ _ _

What if you need to represent a negative number?
A `signed char` devotes 1 bit to whether or not the number is negative!

1 _ _ _ _ _ _ _ is negative
0 _ _ _ _ _ _ _ is positive

So, a `signed char` (aka just a plain old `char`) can represent
from -2^7 -> 2^7 - 1 (-128 to 127)

(signed) char x = 200; (actually -73 I think)

Other types: struct, a function, function pointer, union, array, enum
TODO: homework - read about "Two's-Complement"
*/
// A common pattern is to leverage typedef to provide more abstracted types
// or, in the case of enums and structs, prevent having to prefix with a type
// for every use
// Allows for abstraction and can enhance readability
typedef int my_number_t;

typedef enum gender_t {
  MALE = 0,
  FEMALE = 1,
  TRANS = 2,
  NON_BINARY = 3,
} gender_t;

typedef struct person_t {
  char first_name[30]; // 30 bytes (per respected standards)
  char last_name[30]; // 30 bytes (per respected standards)
  int age; // 4 bytes (per respected standards)
  bool is_uggo; // 1 byte (per respected standards)
  gender_t gender; // depends on the compiler, brosky!
} person_t;

void person_printer(person_t person) {
  printf("<person name: %s %s>\n", person.first_name, person.last_name);
}

int main(int argv, char *argc[]) {
  person_t jimbo = {
    .first_name = "Jimbo",
    .last_name = "Bobo",
    .age = 74,
    .is_uggo = true,
    .gender = MALE
  };

  printf("argv is %d\n", argv);
  person_printer(jimbo);

  return 0;
}
