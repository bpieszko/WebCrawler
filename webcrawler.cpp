#include "webcrawler.hpp"

WebCrawler::WebCrawler(const std::regex & r)
	: regexUrls("(http|ftp|https)://([\\w_-]+(?:(?:\\.[\\w_-]+)+))([\\w.,@?^=%&:/~+#-]*[\\w@?^=%&/~+#-])?") {
	regexArg = r;
}

void WebCrawler::crawl(const std::string & url, const int depth, std::ostream & out) {
	std::queue<std::pair<std::string, unsigned> > qUrls;
	qUrls.push({url, 0});

	std::set<std::string> visitedMatch;
	std::set<std::string> visitedUrls;
	visitedUrls.insert(url);

	while (!qUrls.empty()) {
		std::pair<std::string, unsigned> actUrl = qUrls.front();
		qUrls.pop();

		std::string result;
		CURL * curl = curl_easy_init();

		if (!curl) {
			std::cerr << "Error: Cannot init curl!" << std::endl;
			return;
		}

		setOptCURL(curl, actUrl.first, &result);
		CURLcode rest = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		auto queryBegin = std::sregex_iterator(result.begin(), result.end(), regexArg);
		auto queryEnd = std::sregex_iterator();

		for (std::sregex_iterator i = queryBegin; i != queryEnd; ++i) {
			std::string matchQuery = (*i).str();
			if (visitedMatch.find(matchQuery) == visitedMatch.end()) {
				out << matchQuery << " : " << actUrl.first << std::endl;
				visitedMatch.insert(matchQuery);
			}
		}

		auto urlBegin = std::sregex_iterator(result.begin(), result.end(), regexUrls);
		auto urlEnd = std::sregex_iterator();

		for (std::sregex_iterator i = urlBegin; i != urlEnd; ++i) {
			std::string matchUrl = (*i).str();
			if (matchUrl.substr(0, 8) == "https://")
				matchUrl.replace(0, 8, "");
			if (matchUrl.substr(0, 7) == "http://")
				matchUrl.replace(0, 7, "");
			if (matchUrl.substr(0, 4) != "www.")
				matchUrl = "www." + matchUrl;
			if (actUrl.second < depth && visitedUrls.find(matchUrl) == visitedUrls.end()) {
				qUrls.push({matchUrl, actUrl.second + 1});
				visitedUrls.insert(matchUrl);
			}
		}
	}
}

void threadCrawl(const std::string & url, const int depth, std::ostream & out) {
	
}

void WebCrawler::setOptCURL(CURL * curl, const std::string & url, std::string * result) {
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, result);
	curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
	curl_easy_setopt(curl, CURLOPT_UNRESTRICTED_AUTH, 1L);
	curl_easy_setopt(curl, CURLOPT_PROXYAUTH, CURLAUTH_ANY);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
}

size_t WebCrawler::WriteCallback(void * contents, size_t size, size_t nmemb, void * userp) {
	((std::string *) userp)->append((char *) contents, size * nmemb);
	return size * nmemb;
}