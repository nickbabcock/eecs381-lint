# Do not compare against 0 or NULL

foreach file [getSourceFileNames] {
    foreach token [getTokens $file 1 0 -1 -1 {notequal equal}] {
        set tokenLength [string length [lindex $token 0]]
        set tokenLine [lindex $token 1]
        set startCol [expr [lindex $token 2] + $tokenLength]

        set identifier [getTokens $file $tokenLine $startCol -1 -1 {identifier intlit}]
        set compareText [lindex [lindex $identifier 0] 0]
        if { $compareText == "NULL" || $compareText == "0" } {
            report $file $tokenLine "Do not perform equality checks against NULL or 0"
        }
    }
}