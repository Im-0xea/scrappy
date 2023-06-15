#!/bin/sh
extract_urls () {
	curl --max-time 5 "$1" 2>/dev/zero | \
	grep -o -e "href='\?https\?://[^']\+" -e "href=\"\?https\?://[^\"]\+" | \
	sed -e "s/href=['\"]\?https\?:\/\///" -e 's/\/$//' -e '/^.\{101,\}$/d' \
	-e "s/href=['\"]\?https\?:\/\///" -e 's/\/$//' -e '/^.\{101,\}$/d' \
	> "sites/${2}.log"
}
dump_site () {
	url="$1"
	file="$(echo "$url" | tr '/' '-')"
	if ! test -e "sites/${file}.log"; then
		echo "dumping: $url"
		extract_urls "$url" "$file" 
		if [ $? -ne 0 ]; then
			echo "error: dumping $url failed"
			rm "sites/${file}.log"
			return
		fi
		cat sites/${file}.log >> all.log
	fi
	url="$(echo "$url" | cut -d '/' -f1)"
	file="$(echo "$url" | tr '/' '-')"
	test -e "sites/${file}.log" && return
	echo "dumping: $url"
	extract_urls "$url" "$file" 
	cat sites/${file}.log >> all.log
}
mkdir -p dump dump/sites && cd dump
dump_site "$1"
timeout 10 tail -n +1 -f all.log | while IFS= read -r site; do
	dump_site "$site"
done
echo "error: ran out of websites"
