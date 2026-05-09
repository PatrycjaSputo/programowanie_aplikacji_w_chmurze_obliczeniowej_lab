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

# CZĘŚĆ DODATKOWA (3)

Stworzenie buildera: 

`docker buildx create --name builder1 --driver docker-container --use`

Zmienna GIT_BRANCH może zostać pominięta, gdy pliki znajdują się na gałęzi main.
Zbudowanie obrazu (logi CACHED potwierdzaja użycie cache):

```
docker buildx build --build-arg GIT_BRANCH=zadanie_1 --platform linux/amd64,linux/arm64 --ssh default=$HOME/.ssh/id_ed25519 --cache-to type=registry,ref=patrycjasputo/laby:cache,mode=max --cache-from type=registry,ref=patrycjasputo/laby:cache -t patrycjasputo/laby:pogoda --push .
[+] Building 13.0s (31/31) FINISHED                                                                                      docker-container:builder1
 => [internal] load build definition from Dockerfile                                                                                          0.0s
 => => transferring dockerfile: 3.29kB                                                                                                        0.0s
 => resolve image config for docker-image://docker.io/docker/dockerfile:1                                                                     2.3s
 => [auth] docker/dockerfile:pull token for registry-1.docker.io                                                                              0.0s
 => CACHED docker-image://docker.io/docker/dockerfile:1@sha256:2780b5c3bab67f1f76c781860de469442999ed1a0d7992a5efdf2cffc0e3d769               0.0s
 => => resolve docker.io/docker/dockerfile:1@sha256:2780b5c3bab67f1f76c781860de469442999ed1a0d7992a5efdf2cffc0e3d769                          0.0s
 => [linux/amd64 internal] load metadata for docker.io/library/alpine:3.19                                                                    1.3s
 => [linux/arm64 internal] load metadata for docker.io/library/alpine:3.19                                                                    1.3s
 => [auth] library/alpine:pull token for registry-1.docker.io                                                                                 0.0s
 => [internal] load .dockerignore                                                                                                             0.0s
 => => transferring context: 2B                                                                                                               0.0s
 => importing cache manifest from patrycjasputo/laby:cache                                                                                    3.4s
 => => inferred cache manifest type: application/vnd.oci.image.manifest.v1+json                                                               0.0s
 => [linux/arm64 builder 1/7] FROM docker.io/library/alpine:3.19@sha256:6baf43584bcb78f2e5847d1de515f23499913ac9f12bdf834811a3145eb11ca1      0.0s
 => => resolve docker.io/library/alpine:3.19@sha256:6baf43584bcb78f2e5847d1de515f23499913ac9f12bdf834811a3145eb11ca1                          0.0s
 => [linux/amd64 builder 1/7] FROM docker.io/library/alpine:3.19@sha256:6baf43584bcb78f2e5847d1de515f23499913ac9f12bdf834811a3145eb11ca1      0.0s
 => => resolve docker.io/library/alpine:3.19@sha256:6baf43584bcb78f2e5847d1de515f23499913ac9f12bdf834811a3145eb11ca1                          0.0s
 => [auth] patrycjasputo/laby:pull token for registry-1.docker.io                                                                             0.0s
 => CACHED [linux/arm64 builder 2/7] RUN apk add --no-cache build-base wget git openssh-client                                                0.0s
 => CACHED [linux/arm64 builder 3/7] WORKDIR /build                                                                                           0.0s
 => CACHED [linux/arm64 builder 4/7] RUN mkdir -p -m 0700 ~/.ssh && ssh-keyscan github.com >> ~/.ssh/known_hosts                              0.0s
 => CACHED [linux/arm64 builder 5/7] RUN --mount=type=ssh git clone --filter=blob:none --no-checkout -b zadanie_1 git@github.com:PatrycjaSpu  0.0s
 => CACHED [linux/arm64 builder 6/7] RUN wget -O ZADANIE_1/src/httplib.h https://raw.githubusercontent.com/yhirose/cpp-httplib/ec5ce17929c56  0.0s
 => CACHED [linux/arm64 builder 7/7] RUN g++ -Os -static -flto -ffunction-sections -fdata-sections -Wl,--gc-sections ZADANIE_1/src/main.cpp   0.0s
 => CACHED [linux/arm64 stage-1 1/2] COPY --from=builder /build/server /server                                                                0.0s
 => CACHED [linux/arm64 stage-1 2/2] COPY --from=builder /build/ZADANIE_1/web /web/                                                           0.0s
 => CACHED [linux/amd64 builder 2/7] RUN apk add --no-cache build-base wget git openssh-client                                                0.0s
 => CACHED [linux/amd64 builder 3/7] WORKDIR /build                                                                                           0.0s
 => CACHED [linux/amd64 builder 4/7] RUN mkdir -p -m 0700 ~/.ssh && ssh-keyscan github.com >> ~/.ssh/known_hosts                              0.0s
 => CACHED [linux/amd64 builder 5/7] RUN --mount=type=ssh git clone --filter=blob:none --no-checkout -b zadanie_1 git@github.com:PatrycjaSpu  0.0s
 => CACHED [linux/amd64 builder 6/7] RUN wget -O ZADANIE_1/src/httplib.h https://raw.githubusercontent.com/yhirose/cpp-httplib/ec5ce17929c56  0.0s
 => CACHED [linux/amd64 builder 7/7] RUN g++ -Os -static -flto -ffunction-sections -fdata-sections -Wl,--gc-sections ZADANIE_1/src/main.cpp   0.0s
 => CACHED [linux/amd64 stage-1 1/2] COPY --from=builder /build/server /server                                                                0.0s
 => CACHED [linux/amd64 stage-1 2/2] COPY --from=builder /build/ZADANIE_1/web /web/                                                           0.0s
 => exporting to image                                                                                                                        5.8s
 => => exporting layers                                                                                                                       0.0s
 => => exporting manifest sha256:58f301f58645ea8f46ac361d35147b300de078ef9bf218b650d685478da48e6a                                             0.0s
 => => exporting config sha256:3919cf33b0a68ae48a92434eb096a81610a0d9fa231b719436a452de9f3b7158                                               0.0s
 => => exporting attestation manifest sha256:728e0c8dc0314256f8e1dc1f7d16393034831a1046526a72ec6fca6966b23407                                 0.0s
 => => exporting manifest sha256:a0fc6cef3f6e484ec9e43962346fb742402d21a31115afc5544aee1ae1ba818e                                             0.0s
 => => exporting config sha256:a3178be9bd93f4cbdf351ca0545bec17bb0b2858fdfebba2c36ae41aaaea0259                                               0.0s
 => => exporting attestation manifest sha256:5470d667a294c201603faf82153d31599826284b3ebbc43e947de47f5129fc3f                                 0.0s
 => => exporting manifest list sha256:caa1a51f6396f6245b87772afa5c6fc552bff88fa2490c38cea27d0cc3f67f6a                                        0.0s
 => => pushing layers                                                                                                                         2.2s
 => => pushing manifest for docker.io/patrycjasputo/laby:pogoda@sha256:caa1a51f6396f6245b87772afa5c6fc552bff88fa2490c38cea27d0cc3f67f6a       3.5s
 => exporting cache to registry                                                                                                               4.6s
 => => preparing build cache for export                                                                                                       0.1s
 => => sending cache export                                                                                                                   4.5s
 => => writing layer sha256:29796a4cb7b53801896bad8c2cbcadae6dea96b4d6ab8b3e955ae2cac89c4694                                                  0.9s
 => => writing layer sha256:1b15e6e74d8b9b85925a0f5e529388b5ae30b3ee8b532b8c37887bafa3bdab5c                                                  0.8s
 => => writing layer sha256:27edafa84f8ef8b33b442c675d74b08dcf32f2aec94099b4ad676c3a35e198bf                                                  0.8s
 => => writing layer sha256:17a39c0ba978cc27001e9c56a480f98106e1ab74bd56eb302f9fd4cf758ea43f                                                  0.8s
 => => writing layer sha256:299645ead3da49b8dd9b784d2d2d3d73f47fc4dd212e4cb06fb29e0c38fb58d0                                                  0.2s
 => => writing layer sha256:32a60f2b5a04fea103457f52028504b1069566281f3fb51ac26cd4ffbda04fd6                                                  0.2s
 => => writing layer sha256:3f1d2e9b1b8fc6631f4e2c309e1757f3cc6ae3c82978459cf005db519ccebba8                                                  0.2s
 => => writing layer sha256:4f0febe38dfd9439e6a8d108294672a91cdf9f762fe7e4994895563bcc0426b4                                                  0.1s
 => => writing layer sha256:5711127a7748d32f5a69380c27daf1382f2c6674ea7a60d2a3e338818590fea1                                                  0.1s
 => => writing layer sha256:b1de27af9e8780a4a198ae52cef8c99ab23040e76a08176c3e41f346a46cbc07                                                  0.1s
 => => writing layer sha256:b4ba06ef45af333d692eda04628a6825b95fb302ace44a9a8ddbf0d974642a60                                                  0.2s
 => => writing layer sha256:b72c03ac7afb2dea79eab8367f1e4f113d5b4096c7e36ff287a4120160a08991                                                  0.1s
 => => writing layer sha256:c8c59082d08958234c35e0db415b1b62c314c7241932ec0ea142f8df8b2d7a5b                                                  0.1s
 => => writing layer sha256:de6153073d7a67389cb69e9d8b75ed936c9a50eea307a142f88235c5d98d0e6f                                                  0.1s
 => => writing layer sha256:e5532a6a211ad5f4020de31194de25357d7f5f7aeb4006361e07d1c5666b9fba                                                  0.2s
 => => writing layer sha256:e8b2c062f4cb5d9be6470e6983cda1bcbd89cb213435e91006da46a4d1b5a40e                                                  0.2s
 => => writing layer sha256:ef97d6a6851a9f3e643985cf602e61d395df2682622927f6e29577eaaa7236f9                                                  0.1s
 => => writing layer sha256:fbb07027bfc70138963e5291c908f562a745c778184d0c8bdee8d0a1359a30ca                                                  0.1s
 => => writing config sha256:5803dc20fff7613e704ac46bf3c4dd988cf811f9e08503e929becf5cab8777b7                                                 1.1s
 => => writing cache image manifest sha256:f6382529c107d2d100405bace0a1f9be7ae9ce96850fdc18d79e0d1f9326c475                                   2.0s
 => [auth] patrycjasputo/laby:pull,push token for registry-1.docker.io                                                                        0.0s

View build details: docker-desktop://dashboard/build/builder1/builder10/all97i5nrsf33iaydsa5vppv5

```

Potwierdzenie wieloarchitekturowości (Platform):

```
docker buildx imagetools inspect patrycjasputo/laby:pogoda
Name:      docker.io/patrycjasputo/laby:pogoda
MediaType: application/vnd.oci.image.index.v1+json
Digest:    sha256:caa1a51f6396f6245b87772afa5c6fc552bff88fa2490c38cea27d0cc3f67f6a
           
Manifests: 
  Name:        docker.io/patrycjasputo/laby:pogoda@sha256:58f301f58645ea8f46ac361d35147b300de078ef9bf218b650d685478da48e6a
  MediaType:   application/vnd.oci.image.manifest.v1+json
  Platform:    linux/amd64
               
  Name:        docker.io/patrycjasputo/laby:pogoda@sha256:a0fc6cef3f6e484ec9e43962346fb742402d21a31115afc5544aee1ae1ba818e
  MediaType:   application/vnd.oci.image.manifest.v1+json
  Platform:    linux/arm64
               
  Name:        docker.io/patrycjasputo/laby:pogoda@sha256:728e0c8dc0314256f8e1dc1f7d16393034831a1046526a72ec6fca6966b23407
  MediaType:   application/vnd.oci.image.manifest.v1+json
  Platform:    unknown/unknown
  Annotations: 
    vnd.docker.reference.digest: sha256:58f301f58645ea8f46ac361d35147b300de078ef9bf218b650d685478da48e6a
    vnd.docker.reference.type:   attestation-manifest
               
  Name:        docker.io/patrycjasputo/laby:pogoda@sha256:5470d667a294c201603faf82153d31599826284b3ebbc43e947de47f5129fc3f
  MediaType:   application/vnd.oci.image.manifest.v1+json
  Platform:    unknown/unknown
  Annotations: 
    vnd.docker.reference.digest: sha256:a0fc6cef3f6e484ec9e43962346fb742402d21a31115afc5544aee1ae1ba818e
    vnd.docker.reference.type:   attestation-manifest
```

Sprawdzanie vulnerabilities (linux/amd64)

```
docker scout cves patrycjasputo/laby:pogoda
    ✓ Pulled
    ✓ Image stored for indexing
    ✓ Indexed 0 packages
    ✓ Provenance obtained from attestation
    ✓ No vulnerable package detected


## Overview

                   │                                    Analyzed Image                                    
───────────────────┼──────────────────────────────────────────────────────────────────────────────────────
 Target            │  patrycjasputo/laby:pogoda                                                           
   digest          │  58f301f58645                                                                        
   platform        │ linux/amd64                                                                          
   provenance      │ git@github.com:PatrycjaSputo/programowanie_aplikacji_w_chmurze_obliczeniowej_lab.git 
                   │  37f17485292d0f7989a02e6283932025bc311977                                            
   vulnerabilities │    0C     0H     0M     0L                                                           
   size            │ 401 kB                                                                               
   packages        │ 0                                                                                    


## Packages and Vulnerabilities

  No vulnerable packages detected
```

Sprawdzanie vulnerabilities (linux/arm64)

```
docker scout cves --platform linux/arm64 patrycjasputo/laby:pogoda
    ✓ Pulled
    ✓ Image stored for indexing
    ✓ Indexed 0 packages
    ✓ Provenance obtained from attestation
    ✓ No vulnerable package detected


## Overview

                   │                                    Analyzed Image                                    
───────────────────┼──────────────────────────────────────────────────────────────────────────────────────
 Target            │  patrycjasputo/laby:pogoda                                                           
   digest          │  a0fc6cef3f6e                                                                        
   platform        │ linux/arm64                                                                          
   provenance      │ git@github.com:PatrycjaSputo/programowanie_aplikacji_w_chmurze_obliczeniowej_lab.git 
                   │  37f17485292d0f7989a02e6283932025bc311977                                            
   vulnerabilities │    0C     0H     0M     0L                                                           
   size            │ 408 kB                                                                               
   packages        │ 0                                                                                    


## Packages and Vulnerabilities

  No vulnerable packages detected

```

Powyższe polecenia potwierdziły, że zbudowane obrazy nie mają żadnych wykrytych podatności.

