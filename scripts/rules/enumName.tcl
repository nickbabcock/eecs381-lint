# Give the type a name starting with an upper-case letter terminated with "_e"
# or similar

foreach file [getSourceFileNames] {
	foreach token [getTokens $file 1 0 -1 -1 {enum}] {
		set tokenLength [string length [lindex $token 0]]
		set tokenLine [lindex $token 1]
		set startCol [expr [lindex $token 2] + $tokenLength]

		set identifier [getTokens $file $tokenLine $startCol -1 -1 {identifier}]
		set compareText [lindex [lindex $identifier 0] 0]
		if { ![regexp {_e$} $compareText] || ![regexp {^[A-Z]} $compareText]} {
			report $file $tokenLine "Enums must end in _e"
		}
	}
}
