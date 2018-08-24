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
./app [url] [regex] [depth]
    [url] - url of page to start crawling in format www.[PAGE].[pl/com/org/...]/[rest of link]
    [regex] - regex of strings to search for
    [depth] - depth of crawling, 0 - crawl only in input page
```

## Example
```
./app.e 'www.panoramafirm.pl/szukaj?k=notariusz' '[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+' 0
```

## Output
```
notariusz@kancelariarejenta.pl
notariusze@kn.wroc.pl
kancelaria@walewska.eu
kancelariakielce@gmail.com
biuro@notariusz24.com
kancelaria@notariusze-wroclaw.com
notariusz@bankosz.pl
lewicka@notar.pl
kancelaria@notariuszkielce.com
pbakalska@notariusz-kancelaria24.pl
mikolajczyk@kancelarie-notarialne.info.pl
ewapluta@notariusz.pl
tomaszzawadzki@rejent.pl
biuro@notariuszerondowroclaw.pl
anna.oskaldowicz@notariusz.lodz.pl
katarzynastencel@rejent.pl
kancelaria@notariusz-tarnowskiegory.pl
agnieszka.bunkowska@gdin.pl
biuro@notariusz-wroclaw.net
a.karczewska@post.pl
kancelaria@krakowskinotariusz.pl
solanowski@notariusze.waw.pl
eniro@eniro.pl
iod@eniro.com
```



## Author
Bartosz Pieszko <br/>
bartosz.pieszko@gmail.com
