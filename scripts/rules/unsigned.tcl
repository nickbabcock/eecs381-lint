# Nothing should be declared as a unsigned

foreach file [getSourceFileNames] {
	foreach unsigned [getTokens $file 1 0 -1 -1 {unsigned}] {
		set line [lindex $unsigned 1]
		report $file $line "remove all unsigned usages"
	}
}
