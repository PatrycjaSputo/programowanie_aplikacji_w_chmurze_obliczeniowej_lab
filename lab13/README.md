# Lab13 - część obowiązkowa i dodatkowa
Zbudowanie prostego pliku docker-compose.yml, który pozwoli na uruchomienie stack-a LEMP wraz z phpMyAdmin.
## Część obowiązkowa

Początkowo (w części obowiązkowej zadania) dane wrażliwe zostały dodane do pliky .env.

**Komenda uruchamiająca kontenery:** `docker compose up -d`.

<details>
<summary>Wynik komendy:</summary>

```
[+] up 6/6
 ✔ Network lab13_backend        Created 0.0s
 ✔ Network lab13_frontend       Created 0.0s
 ✔ Container lab13-php-1        Created 0.0s
 ✔ Container lab13-mysql-1      Created 0.0s
 ✔ Container lab13-phpmyadmin-1 Created 0.0s
 ✔ Container lab13-nginx-1      Created    
```

</details>
<br>

**Komenda wyłączająca kontenery:** `docker compose down`.

<details>
<summary>Wynik komendy:</summary>

```
[+] down 6/6
 ✔ Container lab13-phpmyadmin-1 Removed 1.1s
 ✔ Container lab13-nginx-1      Removed 0.2s
 ✔ Container lab13-php-1        Removed 0.1s
 ✔ Container lab13-mysql-1      Removed 0.6s
 ✔ Network lab13_backend        Removed 0.1s
 ✔ Network lab13_frontend       Removed 0.2s
```

</details>
<br>

**Strona:** http://localhost:4001/

**Phpmyadmin:** http://localhost:6001/

### Potwierdzenie działania kontenerów

`docker ps`
```
CONTAINER ID   IMAGE                           COMMAND                  CREATED          STATUS          PORTS                                     NAMES
3d39f67715ec   nginx:1.31-alpine               "/docker-entrypoint.…"   11 minutes ago   Up 10 minutes   0.0.0.0:4001->80/tcp, [::]:4001->80/tcp   lab13-nginx-1
34051fff1d93   phpmyadmin/phpmyadmin:5.2       "/docker-entrypoint.…"   11 minutes ago   Up 10 minutes   0.0.0.0:6001->80/tcp, [::]:6001->80/tcp   lab13-phpmyadmin-1
37ae4dfead90   php:8.2-fpm-alpine              "docker-php-entrypoi…"   11 minutes ago   Up 10 minutes   9000/tcp                                  lab13-php-1
e360095edbff   mysql:9.7.0                     "docker-entrypoint.s…"   11 minutes ago   Up 10 minutes   3306/tcp, 33060/tcp                       lab13-mysql-1
```
### Potwierdzenie działania sieci

`docker network inspect lab13_backend`
<details>
<summary>Wynik komendy:</summary>

```
[
    {
        "Name": "lab13_backend",
        "Id": "8867fa1e81252febfdea92f6252e667538e30835f8e90a740352b527e5e8ea68",
        "Created": "2026-06-05T11:11:24.195651186+02:00",
        "Scope": "local",
        "Driver": "bridge",
        "EnableIPv4": true,
        "EnableIPv6": false,
        "IPAM": {
            "Driver": "default",
            "Options": null,
            "Config": [
                {
                    "Subnet": "172.28.0.0/16",
                    "Gateway": "172.28.0.1"
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
        "Labels": {
            "com.docker.compose.config-hash": "303a5c6a665d112f4cfee901befcc7bb1f43b97b72bbbccd3bbe862f5d0e35b7",
            "com.docker.compose.network": "backend",
            "com.docker.compose.project": "lab13",
            "com.docker.compose.version": "5.0.2"
        },
        "Containers": {
            "34051fff1d9309ca5c4593742a4ae816508812f19d8b53c648c3082b661e9a5f": {
                "Name": "lab13-phpmyadmin-1",
                "EndpointID": "3478b471b459c0352fb335cea419cd516fee7ebf807be09ed05c249b676db4b0",
                "MacAddress": "9e:53:72:4c:50:29",
                "IPv4Address": "172.28.0.4/16",
                "IPv6Address": ""
            },
            "37ae4dfead9076cf21609feadac04f81362710e0f374692b5a5d4c4d44d8210d": {
                "Name": "lab13-php-1",
                "EndpointID": "f3306828fd17a1bbc3d3892568e6432046838ae794106e54daf49fafa95084c5",
                "MacAddress": "ea:a9:5c:40:de:55",
                "IPv4Address": "172.28.0.3/16",
                "IPv6Address": ""
            },
            "3d39f67715ec181c28bf838b38a4098e9a83cb3a076cc813250656b86398d2f3": {
                "Name": "lab13-nginx-1",
                "EndpointID": "42497d2d7c63fb003bbec56f9cf5dfd4f7dc4a632d39f3f1d06e7fc3b2a21b5f",
                "MacAddress": "72:14:0b:56:23:68",
                "IPv4Address": "172.28.0.5/16",
                "IPv6Address": ""
            },
            "e360095edbffbc6f02a30e4a320fa1f7ce8ec529ada02cabe22efd3793d097f1": {
                "Name": "lab13-mysql-1",
                "EndpointID": "05976619ec7e0cdc0c5b45ac35254b61775180b492e14eb2b0246b093dbe7836",
                "MacAddress": "6e:cd:04:fd:ad:27",
                "IPv4Address": "172.28.0.2/16",
                "IPv6Address": ""
            }
        },
        "Status": {
            "IPAM": {
                "Subnets": {
                    "172.28.0.0/16": {
                        "IPsInUse": 7,
                        "DynamicIPsAvailable": 65529
                    }
                }
            }
        }
    }
]
```


</details>
<br>

`docker network inspect lab13_frontend`

<details>
<summary>Wynik komendy:</summary>

```
[
    {
        "Name": "lab13_frontend",
        "Id": "2f63a0ad27c2490764fe340251a51670fff368757e5f042351acd2062b9c514f",
        "Created": "2026-06-05T11:11:24.217578438+02:00",
        "Scope": "local",
        "Driver": "bridge",
        "EnableIPv4": true,
        "EnableIPv6": false,
        "IPAM": {
            "Driver": "default",
            "Options": null,
            "Config": [
                {
                    "Subnet": "172.29.0.0/16",
                    "Gateway": "172.29.0.1"
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
        "Labels": {
            "com.docker.compose.config-hash": "c99dfed360a6944db43f183a5bd3f4016b0c10584adeeaa2e535a0bc34386287",
            "com.docker.compose.network": "frontend",
            "com.docker.compose.project": "lab13",
            "com.docker.compose.version": "5.0.2"
        },
        "Containers": {
            "3d39f67715ec181c28bf838b38a4098e9a83cb3a076cc813250656b86398d2f3": {
                "Name": "lab13-nginx-1",
                "EndpointID": "797d5158b55b56dd095622de9dde7baddf7a014bfba4251a7778839cfcc13324",
                "MacAddress": "c6:63:de:49:a9:ba",
                "IPv4Address": "172.29.0.2/16",
                "IPv6Address": ""
            }
        },
        "Status": {
            "IPAM": {
                "Subnets": {
                    "172.29.0.0/16": {
                        "IPsInUse": 4,
                        "DynamicIPsAvailable": 65532
                    }
                }
            }
        }
    }
]
```

</details>

### Potwierdzenie działania strony

![strona](img/1.png)
Strona index.php

### Potwierdzenie działania phpmyadmin

![phpmyadmin](img/2.png)
Logowanie do phpmyadmin

![phpmyadmin](img/3.png)
Phpmyadmin - użytkownik zalogowany.

## Część dodatkowa

Dodanie folderu `secrets/` i dodanie go do `.gitignore`.
W secrets zostały umieszczone dane wrażliwe.



