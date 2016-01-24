/\w+.*\,/ {
    split($0, parts, ",")
    split(parts[1], parts, "=")
    gsub(/\s+/, "", parts[1])
    
    label = "CASE"
    
    if (parts[1] ~ /WORD|DECIMAL|REAL/) {
	label = "VALUE_CASE"
    }
    
    print label "(" parts[1] ");"
}
