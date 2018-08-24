#include "webcrawler.hpp"
#include <regex>

int main (int argc, char * argv[]) {
	if (argc != 3) {
		std::cout << "Usage:" << std::endl;
		std::cout << "    ./app.e [url] [depth]" << std::endl;
		std::cout << "Description:" << std::endl;
		std::cout << "    [url]   - url of page to start crawling in format www.[PAGE].[pl/com/org/...]/[rest of link]" << std::endl;
		std::cout << "    [depth] - depth of crawling, 0 - crawl only in input page" << std::endl;
		std::cout << "Example:" << std::endl;
		std::cout << "    ./app.e 'https://panoramafirm.pl/szukaj?k=notariusz' 2" << std::endl;
		return 1;
	}

	std::regex emailRegex("[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+");
	
	WebCrawler wc(emailRegex);
	wc.crawl(argv[1], std::stoi(argv[2]), std::cout);
	
	return 0;
}