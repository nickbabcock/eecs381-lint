# project specific header files come before standard library

foreach file [getSourceFileNames] {
	set myHeaders [getTokens $file 1 0 -1 -1 {pp_qheader}]
	set theirHeaders [getTokens $file 1 0 -1 -1 {pp_hheader}]

	if {![llength $myHeaders] || ![llength $theirHeaders]} {
		continue
	}

	set mylast [lindex [lindex $myHeaders end] 1]
	set theirLast [lindex [lindex $theirHeaders 0] 1]

	if {$mylast > $theirLast} {
		report $file $theirLast "project specific includes must occur before others"
	}
}
