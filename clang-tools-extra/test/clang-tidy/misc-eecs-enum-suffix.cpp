// RUN: %check_clang_tidy %s misc-eecs-enum-suffix %t

enum X {
// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: enum declarations must end in `_e` ('X') [misc-eecs-enum-suffix]
  A, B, C
};

enum X_e {
  AA, BB, CC
};
