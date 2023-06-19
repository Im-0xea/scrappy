#include <curl/curl.h>

void scrape_init(void)
{
	curl_global_init(CURL_GLOBAL_DEFAULT);
}
void scrape_cleanup(void)
{
	curl_global_cleanup();
}

const char * scrape(const char * url)
{
	CURL * curl;
	CURLcode res;
	
	curl = curl_easy_init();
	if (!curl) {
		ewarn("failed to scrape %s", url)
		return NULL;
	}
	curl_easy_setopt(curl, CURLOPT_URL, url);
	
}
