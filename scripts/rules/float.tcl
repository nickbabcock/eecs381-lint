# Nothing should be declared as a float

foreach file [getSourceFileNames] {
	foreach float [getTokens $file 1 0 -1 -1 {float}] {
		set line [lindex $float 1]
		report $file $line "remove all float usages"
	}
}
