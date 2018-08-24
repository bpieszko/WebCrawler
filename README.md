# WebCrawler

## Description
Webcrawler written in C++. It requires url of page to start crawling, regular expression of strings to search for and depth of recursion in which to look for strings defined by regular expression.

## Compile
```
g++-7 --std=c++17 -c webcrawler.hpp -lcurl
g++-7 --std=c++17 -o app.e webcrawler.o main.cpp -lcurl
```

## Using
```
./app [url] [depth]
    [url] - url of page to start crawling in format www.[PAGE].[pl/com/org/...]/[rest of link]
    [regex] - regex of strings to search for
    [depth] - depth of crawling, 0 - crawl only in input page
```

## Example
```
./app.e 'https://panoramafirm.pl/szukaj?k=notariusz' '[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+' 2
```

## Author
Bartosz Pieszko <br/>
bartosz.pieszko@gmail.com