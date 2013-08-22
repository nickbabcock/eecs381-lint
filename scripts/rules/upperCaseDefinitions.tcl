# Use an initial upper-case name for your own types (enums, classes, structs,
# typedef names).

foreach file [getSourceFileNames] {
	foreach token [getTokens $file 1 0 -1 -1 {enum class struct typedef}] {
		set tokenLength [string length [lindex $token 0]]
		set tokenLine [lindex $token 1]
		set startCol [expr [lindex $token 2] + $tokenLength]

		set identifier [getTokens $file $tokenLine $startCol -1 -1 {identifier}]
		set compareText [lindex [lindex $identifier 0] 0]
		if { ![regexp {^[A-Z]} $compareText]} {
			report $file $tokenLine "Identities defined must being with an upper-case letter"
		}
	}
}
