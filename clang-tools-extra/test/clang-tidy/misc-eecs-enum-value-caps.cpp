// RUN: %check_clang_tidy %s misc-eecs-enum-value-caps %t

enum Fruit_e {
    APPLES,
    bANANAS
    // CHECK-MESSAGES: :[[@LINE-1]]:5: warning: enum values must be uppercased ('bANANAS') [misc-eecs-enum-value-caps]
};
