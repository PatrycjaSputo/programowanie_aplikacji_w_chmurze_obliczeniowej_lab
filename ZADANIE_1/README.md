# Zadanie 1

Polecenia: 

Zbudowanie obrazu: `docker build -t patrycjasputo/pogoda:v1 .`

Uruchomienie kontenera na podstawie zbudowanego obrazu: `docker run -d --rm -p 9999:3000  --name pogoda-serwer patrycjasputo/pogoda:v1 `
* `-d` odłącza kontener od terminala, żeby działał w tle
* `--rm` usuwa kontener od razu po jego zatrzymaniu
* `-p 9999:3000` przekazuje port z kontenera (3000) na port na komputerze (9999)

Sposób uzyskania informacji z logów: `docker logs pogoda-serwer`.

```
docker logs pogoda-serwer 
[LOG] Data uruchomienia: Mon May  4 08:33:06 2026 (czas UTC)
[LOG] Autor programu: Patrycja Sputo
[LOG] Aplikacja nasluchuje na porcie TCP: 3000
[LOG] Odwiedzono strone glowna (IP: 172.17.0.1)
```

Sprawdzenie, ile warstw posiada zbudowany obraz: `docker history`.

```
docker history patrycjasputo/pogoda:v1 | grep -v 0B
IMAGE          CREATED         CREATED BY                                      SIZE      COMMENT
<missing>      8 minutes ago   COPY web/ /web/ # buildkit                      20.5kB    buildkit.dockerfile.v0
<missing>      8 minutes ago   COPY /build/server /server # buildkit           307kB     buildkit.dockerfile.v0
<missing>      8 minutes ago   COPY /etc/group /etc/group # buildkit           12.3kB    buildkit.dockerfile.v0
<missing>      8 minutes ago   COPY /etc/passwd /etc/passwd # buildkit         12.3kB    buildkit.dockerfile.v0

```

Sprawdzenie, jaki jest rozmiar obrazu: `docker images patrycjasputo/pogoda:v1`. Sekcja DISK USAGE.

```
docker images patrycjasputo/pogoda:v1
                                                                                                                                                                     i Info →   U  In Use
IMAGE                     ID             DISK USAGE   CONTENT SIZE   EXTRA
patrycjasputo/pogoda:v1   892b07a5792f        660kB          308kB        

```

# Część nieobowiązkowa
