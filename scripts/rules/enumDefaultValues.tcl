# the values in the enum should use the default, compilier assigned values

foreach file [getSourceFileNames] {
	foreach token [getTokens $file 1 0 -1 -1 {enum}] {
		set tokenLength [string length [lindex $token 0]]
		set tokenLine [lindex $token 1]
		set startCol [expr [lindex $token 2] + $tokenLength]

		foreach token [getTokens $file 1 0 -1 -1 {}] {
			set name [lindex $token 3]
			if { $name == "rightbrace" } {
				break;
			} elseif { $name == "assign" } {
				report $file $tokenLine "Use only default values for enum Values"
			}
		}
	}
}
