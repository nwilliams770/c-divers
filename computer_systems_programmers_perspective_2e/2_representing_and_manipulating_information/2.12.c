// A. All bits other than least significant byte set to 0
x & 0xff (1111 1111)

// B. All but least significant byte complemented
(~x) ^ 0xff

// C. Least significant bytes all 1s, all other bytes unchanged
x | 0xff