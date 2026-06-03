# Lab12 - Tworzenie sieci

## Utworzenie sieci
```
docker network create lab12net
ae6adcbf165b629cc340a2f85e01620ce54b4cb779851084c1bf5a08c576d53d
```

## Uruchomienie kontenerów

Ścieżka dla --mount musi byż bezwzględna. Dlatego użytko $PWD - obezcna lokalizacja. Komendy zostały uruchomione z folderu lab12.

### Uruchomienie kontenera web1

```
docker run -d --name web1 \
  --network lab12net \
  -p 8081:80 \
  --mount type=bind,source=$PWD/index.html,target=/usr/share/nginx/html/index.html,readonly \
  --mount type=bind,source=$PWD/web1_logs,target=/var/log/nginx \
  nginx:latest
```

<details>
<summary>Wynik polecenia</summary>

  ```
  Unable to find image 'nginx:latest' locally
  latest: Pulling from library/nginx
  13fd728be9eb: Pull complete 
  b4a248c845e5: Pull complete 
  7f8b1a2b17d8: Pull complete 
  45381ecb0e2f: Pull complete 
  5431d0092ffd: Pull complete 
  830625e1ac85: Pull complete 
  cc5f57206478: Download complete 
  5e6b66b5e5f1: Download complete 
  Digest: sha256:5aca99593157f4ae539a5dec1092a0ad8762f8e2eb1789085a13a0f5622369f6
  Status: Downloaded newer image for nginx:latest
  5a87799b2fdd04f405a30c106eab7a7280b6434da7a979eb7e35a565ae458da1
  ```

</details>

### Uruchomienie kontenera web2

```
docker run -d --name web2 \
  --network lab12net \
  -p 8082:80 \
  --mount type=bind,source=$PWD/index.html,target=/usr/share/nginx/html/index.html,readonly \
  --mount type=bind,source=$PWD/web2_logs,target=/var/log/nginx \
  nginx:latest
```

<details>

<summary>Wynik polecenia</summary>

```
373f5f437924aee9ba8d439d7450386a87e9465141c919b3254f8c7bcc82c5c7
```

</details>



### Uruchomienie kontenera web3

```
docker run -d --name web3 \
  --network lab12net \
  -p 8083:80 \
  --mount type=bind,source=$PWD/index.html,target=/usr/share/nginx/html/index.html,readonly \
  --mount type=bind,source=$PWD/web3_logs,target=/var/log/nginx \
  nginx:latest
```

<details>

<summary>Wynik polecenia</summary>

```
e853219b81a1e7d4eee9b5c4d193b4df96d3f55017bb07ff41ebc5d5d022101d
```

</details>

## Weryfikacja poprawności sieci

`docker network inspect lab12net `

<details>

<summary>Wynik polecenia</summary>

```
[
    {
        "Name": "lab12net",
        "Id": "ae6adcbf165b629cc340a2f85e01620ce54b4cb779851084c1bf5a08c576d53d",
        "Created": "2026-06-03T10:11:49.051360539+02:00",
        "Scope": "local",
        "Driver": "bridge",
        "EnableIPv4": true,
        "EnableIPv6": false,
        "IPAM": {
            "Driver": "default",
            "Options": {},
            "Config": [
                {
                    "Subnet": "172.27.0.0/16",
                    "Gateway": "172.27.0.1"
                }
            ]
        },
        "Internal": false,
        "Attachable": false,
        "Ingress": false,
        "ConfigFrom": {
            "Network": ""
        },
        "ConfigOnly": false,
        "Options": {},
        "Labels": {},
        "Containers": {
            "373f5f437924aee9ba8d439d7450386a87e9465141c919b3254f8c7bcc82c5c7": {
                "Name": "web2",
                "EndpointID": "6df5c81c05853f160f8733b994fbc61e2760cadb86066081aaf4f050e4c433da",
                "MacAddress": "3e:c1:f4:58:53:e5",
                "IPv4Address": "172.27.0.3/16",
                "IPv6Address": ""
            },
            "5a87799b2fdd04f405a30c106eab7a7280b6434da7a979eb7e35a565ae458da1": {
                "Name": "web1",
                "EndpointID": "717fcfbf030befed535d4fda7103151b6560cbacfadf27361b278a815885ef9e",
                "MacAddress": "12:eb:1d:aa:57:a4",
                "IPv4Address": "172.27.0.2/16",
                "IPv6Address": ""
            },
            "e853219b81a1e7d4eee9b5c4d193b4df96d3f55017bb07ff41ebc5d5d022101d": {
                "Name": "web3",
                "EndpointID": "eaafb8039d3c57702a31eb7dc135681366f2b0dfe23886875f83be2c07e961b0",
                "MacAddress": "4a:08:22:71:77:e2",
                "IPv4Address": "172.27.0.4/16",
                "IPv6Address": ""
            }
        },
        "Status": {
            "IPAM": {
                "Subnets": {
                    "172.27.0.0/16": {
                        "IPsInUse": 6,
                        "DynamicIPsAvailable": 65530
                    }
                }
            }
        }
    }
]

```

</details>

Jak widać powyżej, do sieci dołączone są 3 kontenery - web1, web2, web3.


## Otworzenie stron html

Dostęp z sieci zewnętrznej - z laptopa.

`curl http://localhost:8081`

<details>

<summary>Wynik polecenia</summary>

```
<!doctype html>
<html>
  <head>
    <title>Lab12</title>
  </head>
  <body>
    <div>
    <p>Laboratorium 12</p>
    <p>Patrycja Sputo</p>
    </div>
  </body>
</html>
```

</details>

`curl http://localhost:8082`

<details>

<summary>Wynik polecenia</summary>

```
<!doctype html>
<html>
  <head>
    <title>Lab12</title>
  </head>
  <body>
    <div>
    <p>Laboratorium 12</p>
    <p>Patrycja Sputo</p>
    </div>
  </body>
</html>
```

</details>

`curl http://localhost:8083`

<details>

<summary>Wynik polecenia</summary>

```
<!doctype html>
<html>
  <head>
    <title>Lab12</title>
  </head>
  <body>
    <div>
    <p>Laboratorium 12</p>
    <p>Patrycja Sputo</p>
    </div>
  </body>
</html>
```

</details>

**Strony działają poprawnie.**

## Weryfikacja logów na laptopie

Logi znajdują się w folderach: `web1_logs`, `web2_logs`, `web3_logs`.

### Logi z kontenera web1
```
cat web1_logs/access.log 
172.27.0.1 - - [03/Jun/2026:09:28:45 +0000] "GET / HTTP/1.1" 200 168 "-" "curl/8.5.0" "-"
172.27.0.1 - - [03/Jun/2026:09:41:50 +0000] "GET / HTTP/1.1" 200 168 "-" "Mozilla/5.0 (X11; Linux x86_64; rv:150.0) Gecko/20100101 Firefox/150.0" "-"
172.27.0.1 - - [03/Jun/2026:09:41:51 +0000] "GET /favicon.ico HTTP/1.1" 404 153 "http://localhost:8081/" "Mozilla/5.0 (X11; Linux x86_64; rv:150.0) Gecko/20100101 Firefox/150.0" "-"
```
### Logi z kontenera web2
```
cat web2_logs/access.log 
172.27.0.1 - - [03/Jun/2026:09:28:48 +0000] "GET / HTTP/1.1" 200 168 "-" "curl/8.5.0" "-"
172.27.0.1 - - [03/Jun/2026:09:45:50 +0000] "GET / HTTP/1.1" 200 168 "-" "curl/8.5.0" "-"
```
### Logi z kontenera web3
```
cat web3_logs/access.log 
172.27.0.1 - - [03/Jun/2026:09:28:51 +0000] "GET / HTTP/1.1" 200 168 "-" "curl/8.5.0" "-"
```






