# Don't start variable or function names or #deﬁne symbols with underscores.

set definitions {
	int
	float
	double
	long
	char
	pp_define
}

foreach file [getSourceFileNames] {
	foreach token [getTokens $file 1 0 -1 -1 $definitions] {
		set tokenLength [string length [lindex $token 0]]
		set tokenLine [lindex $token 1]
		set startCol [expr [lindex $token 2] + $tokenLength]

		set identifier [getTokens $file $tokenLine $startCol -1 -1 {identifier}]
		set compareText [lindex [lindex $identifier 0] 0]
		if {[regexp {^_} $compareText]} {
			report $file $tokenLine "Do not start variables or defines with an underscore"
		}
	}
}
