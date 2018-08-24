#ifndef WEBCRAWLER_HPP
#define WEBCRAWLER_HPP

#include <curl/curl.h>
#include <iostream>
#include <string>
#include <thread>
#include <regex>
#include <queue>
#include <set>

class WebCrawler {
private:
	const std::regex regexUrls;
	std::regex regexArg;

	virtual void setOptCURL(CURL * curl, const std::string & url, std::string * result);
	static size_t WriteCallback(void * contents, size_t size, size_t nmemb, void * userp);

public:
	WebCrawler(const std::regex & r);
	virtual void crawl(std::string url, const int depth, std::ostream & out);
};

#endif // WEBCRAWLER_HPP