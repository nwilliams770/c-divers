
void main() {
  // A Pointer: a memory address
  char *name = 'Nicholas';
  // What does this declaration really?
  // - Allocate local stack variable called 'name'
  // - 'Nicholas' appears somewhere in program memory
  //   post-compilation and execution
  // - Initializes name to point to where 'N' char resides
  //   which is directly followed by the rest of the str in memory

  // Deferencing: refering to where the pointer points
  int foo = 1;
  int *pointer_to_foo = &foo;

  foo += 1;

  // Deference the pointer, then increment
  *pointer_to_foo += 1;

  *pointer_to_foo = *pointer_to_foo + 1;
  // foo is now 3!
}
