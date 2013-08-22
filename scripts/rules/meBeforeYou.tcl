# project specific header files come before standard library

foreach file [getSourceFileNames] {
	set mylast [lindex [lindex [getTokens $file 1 0 -1 -1 {pp_qheader}] end] 1]
	set theirLast [lindex [lindex [getTokens $file 1 0 -1 -1 {pp_hheader}] 0] 1]

	if {$mylast > $theirLast} {
		report $file $theirLast "project specific includes must occur others"
	}
}