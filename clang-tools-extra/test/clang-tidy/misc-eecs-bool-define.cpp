// RUN: %check_clang_tidy %s misc-eecs-bool-define %t

#define TRUE 1
// CHECK-MESSAGES: :[[@LINE-1]]:9: warning: Do not define TRUE or FALSE macros: 'TRUE' [misc-eecs-bool-define]

#define TODO 100
