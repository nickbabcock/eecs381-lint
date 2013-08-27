# constants must have a leading followed by a capitalized letter or have a 
# trailing _e

foreach file [getSourceFileNames] {
    foreach token [getTokens $file 1 0 -1 -1 {const}] {
        set tokenLength [string length [lindex $token 0]]
        set tokenLine [lindex $token 1]
        set startCol [expr [lindex $token 2] + $tokenLength]

        set identifier [getTokens $file $tokenLine $startCol -1 -1 {identifier}]
        set compareText [lindex [lindex $identifier 0] 0]
        if { ![regexp {(^k[A-Z])|(_c$)} $compareText] } {
            report $file $tokenLine "constants must start with a leading k followed by an uppercase letter or end in _e"
        }         
    }
}