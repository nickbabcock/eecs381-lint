# Do not define a TRUE or FALSE

foreach file [getSourceFileNames] {
    foreach token [getTokens $file 1 0 -1 -1 {pp_define}] {
        set tokenLength [string length [lindex $token 0]]
        set tokenLine [lindex $token 1]
        set startCol [expr [lindex $token 2] + $tokenLength]

        set identifier [getTokens $file $tokenLine $startCol -1 -1 {identifier}]
        set compareText [lindex [lindex $identifier 0] 0]
        if { $compareText == "TRUE" || $compareText == "FALSE" } {
            report $file $tokenLine "Do not define a TRUE or FALSE"
        }
    }
}