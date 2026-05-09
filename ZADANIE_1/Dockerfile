# ETAP 1: Builder
# W tym etapie skompilowany zostanie kod.
FROM alpine:3.19 AS builder

# Pobieranie niezbędnych narzędzi:
# - build-base: zestaw narzędzi do kompilacji (zawiera m.in. g++)
# - wget: narzędzie do pobierania plików z internetu (użyte do pobrania biblioteki)
# - upx: Ultimate Packer for eXecutables (zaawansowany kompresor plików binarnych)
RUN apk add --no-cache build-base wget upx

# Ustawienie katalogu roboczego na czas budowania
WORKDIR /build

# Pobranie biblioteki do serwera HTTP (Release v0.43.3)
RUN wget https://raw.githubusercontent.com/yhirose/cpp-httplib/ec5ce17929c56c8bb7f0307ce2af496bd017a3c9/httplib.h

# Skopiowanie kodu źródłowego serwera do kontenera
COPY src/main.cpp ./

# Kompilacja i optymalizacja kodu w C++:
# -Os : Optymalizacja pod kątem rozmiaru pliku wynikowego (Optimize size)
# -static : Kompilacja statyczna (wszystkie zależności w jednym pliku, niezbędne dla obrazu 'scratch')
# -flto : Link-Time Optimization (optymalizacja na etapie łączenia kodu, kompiluje sie na końcu)
# -ffunction-sections -fdata-sections -Wl,--gc-sections : Eliminacja martwego kodu (usuwa z pliku binarnego funkcje z bibliotek, których program nigdy nie używa)
# -pthread : Włączenie obsługi wielowątkowości (wiele użytkowników na raz)
# && strip server : Usunięcie symboli debugowania z pliku (usuwa nazwy, wszystko jest zapisywane jak najkrócej)
# && upx --best --lzma server : program kompresujący z algorytmem lzma
RUN g++ -Os -static -flto -ffunction-sections -fdata-sections -Wl,--gc-sections main.cpp -o server -pthread \
    && strip server \
    && upx --best --lzma server

#Skopiowanie plików html i json
COPY web/ /web/

# ETAP 2: Docelowy (Scratch)
# Dzięki użyciu Scractch, kontener będzie zawierał tylko plik serwera.
FROM scratch

# Metadane obrazu (dobre praktyki)
LABEL org.opencontainers.image.authors="Patrycja Sputo" \
      org.opencontainers.image.title="Zaliczenie 1"


# Deklaracja domyślnego portu jako zmiennej (żeby potem dostać się do niej w C++)
ENV APP_PORT=3000

# Skopiowanie gotowego, skompresowanego pliku binarnego z pierwszego etapu (buildera).
COPY --from=builder /build/server /server
COPY --from=builder /web /web/

# Zmiana usera
USER 1000:1000

# Informacja o porcie, na którym nasłuchuje aplikacja.
EXPOSE ${APP_PORT}

HEALTHCHECK --interval=30s --timeout=3s --start-period=3s --retries=3 \
  CMD ["/server", "--health"]

# entrypoint (nie da sie nadpisac polecenia)
ENTRYPOINT ["/server"]
