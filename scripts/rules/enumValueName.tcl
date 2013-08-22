# Uppercase values in an enum

foreach file [getSourceFileNames] {
	foreach token [getTokens $file 1 0 -1 -1 {enum}] {
		set tokenLength [string length [lindex $token 0]]
		set tokenLine [lindex $token 1]
		set startCol [expr [lindex $token 2] + $tokenLength]

		#skip the enum name
		set identifier [lindex [getTokens $file $tokenLine $startCol -1 -1 {identifier}] 0]
		set tokenLength [string length [lindex $identifier 0]]
		set tokenLine [lindex $identifier 1]
		set startCol [expr [lindex $identifier 2] + $tokenLength]

		foreach innerToken [getTokens $file $tokenLine $startCol -1 -1 {identifier rightbrace}] {
			set tokenClass [lindex $innerToken 3]
			if { $tokenClass == "rightbrace" } {
				break
			}

			set identifier [lindex $innerToken 0]
			if { ![regexp {^[A-Z]+$} $identifier]} {
				report $file $tokenLine "Enum values must be all in uppercase"
			}
		}
	}
}
