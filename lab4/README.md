# ETAP 1
Stworzony został plik Dockerfile za pomocą narzędzia `docker init`.

# ETAP 2
Zmodyfikowany został plik Dockerfile.
Dodano folder web, w którym został umieszczony plik html z imieniem i nazwiskiem oraz grupą dziekańską.
**Modyfikacje zostały uzasadnione w komentarzach w pliku Dockerfile**.
Zbudowany został obraz o nazwie web100 za pomocą komendy `docker build -t patrycjasputo/web100:1.0.0 .`.
W tym poleceniu patrycjasputo to nazwa użytkownika, web100 to nazwa obrazu, a 1.0.0 to wersja.
Obraz udało się poprawnie zbudować.
Liczbę warstw sprawdzamy poleceniem `docker history [nazwa obrazu]`, gdzie nazwa obrazu to patrycjasputo/web100:1.0.0.

Wynik polecenia `docker history patrycjasputo/web100:1.0.0`:

| IMAGE | CREATED | CREATED BY | SIZE | COMMENT |
| :--- | :--- | :--- | :--- | :--- |
|`721ee436ded8`|  About a minute ago |  CMD ["apachectl" "-D" "FOREGROUND"]      |       0B |      buildkit.dockerfile.v0 |
|`<missing>` |  About a minute ago  | EXPOSE [80/tcp]                              |   0B       | buildkit.dockerfile.v0 |
|`<missing>` |  About a minute ago  | COPY web/index.html /var/www/html/index.html… |  20.5kB   | buildkit.dockerfile.v0 |
|`<missing>` |  About a minute ago  | RUN /bin/sh -c apt-get update &&     apt-get…  | 177MB    | buildkit.dockerfile.v0 |
|`<missing>` |  About a minute ago  | LABEL author=Patrycja Sputo s101672@pollub.e…   |0B       | buildkit.dockerfile.v0 |
|`<missing>` |  3 weeks ago         | /bin/sh -c #(nop)  CMD ["/bin/bash"]           | 0B       || 
|`<missing>` |  3 weeks ago         | /bin/sh -c #(nop) ADD file:3f78aa860931e0853…  | 87.6MB    ||
|`<missing>` |  3 weeks ago         | /bin/sh -c #(nop)  LABEL org.opencontainers.…  | 0B ||
|`<missing>` | 3 weeks ago          | /bin/sh -c #(nop)  LABEL org.opencontainers.…  | 0B ||
|`<missing>` | 3 weeks ago          | /bin/sh -c #(nop)  ARG LAUNCHPAD_BUILD_ARCH    | 0B ||

Z wyniku tego polecenia wynika, że obraz ma 3 warstwy, ponieważ tylko 3 z nich mają niezerowe wpisy.

