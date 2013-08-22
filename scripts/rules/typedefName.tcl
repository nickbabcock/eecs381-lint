# Distinguish typedef names with a ﬁnal "_t", as in Thing_list_t

foreach file [getSourceFileNames] {
	foreach token [getTokens $file 1 0 -1 -1 {typedef}] {
		set tokenLength [string length [lindex $token 0]]
		set tokenLine [lindex $token 1]
		set startCol [expr [lindex $token 2] + $tokenLength]

		set identifier [getTokens $file $tokenLine $startCol -1 -1 {identifier}]
		set compareText [lindex [lindex $identifier 1] 0]
		if { ![regexp {_t$} $compareText]} {
			report $file $tokenLine "typedefs must end in _t"
		}
	}
}
