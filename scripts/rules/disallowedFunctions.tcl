# Do not use these functions in a C program

set functions {
    calloc
    realloc
    strdup
    memmove
    memcpy
    memset
}

foreach file [getSourceFileNames] {
    foreach token [getTokens $file 1 0 -1 -1 {identifier}] {
        set val [lindex $token 0]
        set index [lsearch $functions $val]
        if { $index != -1 } {
            report $file [lindex $token 1] "Usage of a disallowed function"
        }
    }
}