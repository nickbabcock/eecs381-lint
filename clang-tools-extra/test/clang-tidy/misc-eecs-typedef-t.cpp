// RUN: %check_clang_tidy %s misc-eecs-typedef-t %t

struct Point {
    int x;
    int y;
};

typedef struct Point Point_t;

typedef struct Point Pointed;
// CHECK-MESSAGES: :[[@LINE-1]]:22: warning: typedefs must end in `_t` ('Pointed') [misc-eecs-typedef-t]

typedef struct Thing {
   int cheese;
} Thing;
// CHECK-MESSAGES: :[[@LINE-1]]:3: warning: typedefs must end in `_t` ('Thing') [misc-eecs-typedef-t]

typedef struct Book {
   int author;
} Book_t;
