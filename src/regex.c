#include <regex.h>

regex_t href_regex;
regex_t href_clean_regex;

int compile_regex(void)
{
	if (regcomp(&href_regex, "href=([\"'])(.*?)\\1", 0))
		return 1;
	return 0;
}
int free_regex(void)
{
	if (regfree(&href_regex))
		return 1;
	return 0;
}
int extract_urls(const char * html)
{


}
