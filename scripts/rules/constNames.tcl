# constants must have a leading followed by a capitalized letter or have a 
# trailing _e

foreach file [getSourceFileNames] {
    foreach token [getTokens $file 1 0 -1 -1 {const}] {
        set tokenLength [string length [lindex $token 0]]
        set tokenLine [lindex $token 1]
        set startCol [expr [lindex $token 2] + $tokenLength]

		set prevToken $token
		foreach t [getTokens $file $tokenLine $startCol -1 -1 {}] {
			set type [lindex $t 3]
			if { $type == "assign" } {
				set compareText [lindex $lastIdentifier 0]
			    if { ![regexp {(^k[A-Z])|(_c$)} $compareText] } {
					report $file $tokenLine "constants must start with a leading k followed by an uppercase letter or end in _c"
		        }         
			} elseif {$type == "leftparen" } { 
				break
			} elseif {$type == "identifier"} {
				set lastIdentifier $t
			}
		}
    }
}
