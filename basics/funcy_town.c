
// Arguments in C copied value,
// Cannot change them unless we use pointers
// Must define functions before using them,
// They are not hoisted
// But we can declare them, at the top of a file
// Or in the header file and implement them later
int declared(int bar);

int foo(int bar) {
  return bar * 2;
}

void main(int argv, char *argc[]) {


}

int declared(int bar) {
  // I'm implemented later!
}

// Static
// When applied to a var, opens its scope, it persists!
// When applied to a func, scope of func is limited to the file containing it
int runner() {
  // I persist and am limited to the scope of this function
  static count = 0;
}

// I'm available only in this file!
static int shy_runner() {

}
