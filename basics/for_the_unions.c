void main() {
  // Unions; similar to C structs, except instead of containing
  // multiple variables each with their own memory, a Union
  // allows for multiple sames of the same var;
  // These names can treat the memory as different types and the
  // size of the union will be size of the largest type + any padding
  // the compiler might give it

  union intParts {
    int theInt;
    char bytes[sizeof(int)];
  };


  // We can also use Unions with structs
  struct operator {
    int type;
    union {
      int intNum;
      float floatNum;
      double doubleNum;
    } types;
  };
  // operator op;
  // op.types.intNum = 323;

  // We can also keep the union unnamed and access it directly via the struct
  struct operator_evolved {
    int type;
    union {
      int intNum;
      float floatNum;
      double doubleNum;
    };
  };

  // operator op;
  // operator.intNum = 352;

  // Here's another example of a struct inside a union
  union Coins {
    struct {
        int quarter;
        int dime;
        int nickel;
        int penny;
    }; // anonymous struct acts the same way as an anonymous union, members are on the outer container
    int coins[4];
  };

}
