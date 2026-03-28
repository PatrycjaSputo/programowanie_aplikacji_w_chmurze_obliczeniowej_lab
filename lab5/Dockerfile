# Etap 1
# Uzycie obrazu bazowego "scratch"
FROM scratch AS builder

ADD alpine-minirootfs-3.23.3-x86_64.tar /

# Zdefiniowanie argumentu wersji przekazywanego przy budowie
ARG VERSION

# Ustawienie katalogu roboczego na /app
WORKDIR /app

# Skopiowanie plików do kontenera
COPY index.html .
COPY config.template.json .
COPY start.sh .

# Etap 2
FROM nginx:1.28.3-alpine

# Przeniesienie plików z poprzedniego etapu
COPY --from=builder /app/index.html /usr/share/nginx/html/index.html
COPY --from=builder /app/config.template.json /app/config.template.json
COPY --from=builder /app/start.sh /start.sh

# Nadanie uprawnień do wykonania skryptu
RUN chmod +x /start.sh

# Zadeklarowanie ARG ponownie, żeby był dostępny w sekcji CMD
ARG VERSION
ENV APP_VERSION=$VERSION

EXPOSE 80

# Sprawdzanie stanu kontenera (autodiagnostyka)
HEALTHCHECK --interval=5m --timeout=3s \
  CMD curl -f http://localhost/ || exit 1

# Zawsze zostanie uruchomione po starcie kontenera
ENTRYPOINT ["/start.sh"]
