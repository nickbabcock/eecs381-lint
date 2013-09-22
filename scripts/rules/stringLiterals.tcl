# constant string literals should be used in the pointer form

foreach file [getSourceFileNames] {
    foreach token [getTokens $file 1 0 -1 -1 {char}] {
        set tokenLength [string length [lindex $token 0]]
        set tokenLine [lindex $token 1]
        set startCol [expr [lindex $token 2] + $tokenLength]

        set token [lindex [getTokens $file $tokenLine $startCol -1 -1 {}] 1]
        if { [lindex $token 3] != "identifier" } {
            continue
        }

        set tokenLength [string length [lindex $token 0]]
        set tokenLine [lindex $token 1]
        set startCol [expr [lindex $token 2] + $tokenLength]
        set problem 0
        foreach token [getTokens $file $tokenLine $startCol -1 -1 {}] {
            set name [lindex $token 3]
            if { $name == "newline" || $name == "space" } {
                continue
            } elseif { $name == "leftbracket" } {
                set problem 1
                continue
            } elseif { $problem == 1 && $name != "identifier" && $name != "intlit"  } {
                report $file $tokenLine "String literals shouldn't be intialized to an array of char"
                set problem 0
            }
            break;
        }
    }
}
