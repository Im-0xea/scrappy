#!/bin/sh
extract_urls () {
	curl --max-time 5 "$1" 2>/dev/zero | \
	grep -o -e "href='\?https\?://[^']\+" -e "href=\"\?https\?://[^\"]\+" | \
	sed -e "s/href=['\"]\?https\?:\/\///" -e 's/\/$//' -e '/^.\{101,\}$/d' \
	-e "s/href=['\"]\?https\?:\/\///" -e 's/\/$//' -e '/^.\{101,\}$/d'
}
dump_site () {
	url="$1"
	echo "dumping: $url"
	output=$(extract_urls "$url")
	rc=$?
	if [ $rc -ne 0 ]; then
		echo "error: dumping $url failed"
		return
	fi
	sqlite3 sql.db "UPDATE urls SET dumped = '1' WHERE id = '${2}';"
	while IFS= read -r url; do
		sqlite3 sql.db "INSERT INTO urls (url) VALUES ('${url}');"
	done <<< "$output"
}
sc_init () {
	mkdir -p dump dump/sites && cd dump
	if ! test -e sql.db; then
		sqlite3 sql.db ""
		sqlite3 sql.db "CREATE TABLE urls (
			id INTEGER PRIMARY KEY,
			url TEXT,
			dumped BOOLEAN DEFAULT '0',
			referenced INTEGER DEFAULT '1'
		);"
		sqlite3 sql.db "INSERT INTO urls (url, referenced) VALUES ('${1}', '0');"
	fi
}

sc_init "$1"

while :
do
	echo false > cond
	sqlite3 -csv sql.db "SELECT id, url FROM urls WHERE dumped = 0;" | while IFS=, read -r id url; do
		test "$url" == "" && break
		dump_site "$url" "$id"
		echo true > cond
	done
	test "$(cat cond)" == "false" && break
done

echo "error: ran out of websites"
