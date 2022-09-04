// A. Any bit is 1
// If any bit is set, this number will not be 0
// so below will always eval to 1 if it is set
x && 1;

// Alternative answer
// any bit is set e.g x > 0 | !x => 0
// ! again to get 1
// !!x
// B. Any bit is 0
// XOR with ~0 (0xFFFFF) to make all 1s 0s and all 0s 1s
// Then same pattern as above
(x ^ ~0) && 1 //

// Alternative answer
// !!~x

// C. Any bit in least significant byte has 1
x = 0xFF & x; // unset every bit not in the least significant byte
x && 1; // check to make sure x isn't 0 after doing so
// D. Any bit in most significant byte has 0
int mask = INT_MAX >> 7; // create a bit mask where most significant byte is 0s
// and all other bytes are 1s. INT_MAX will be 011111.. because of 2's complement
// representation and we are doing arithmetic right shifts so 0 will drag
x = (x | mask); // set all bytes but the most significant byte to 1s
(x ^ ~0) && 1 // use pattern from above