# syntax=docker/dockerfile:1
FROM alpine:3.21 AS builder

RUN apk add --no-cache git openssh-client

RUN mkdir -p -m 0700 ~/.ssh && ssh-keyscan github.com >> ~/.ssh/known_hosts

# Ustawienie katalogu roboczego na /app
WORKDIR /app

RUN --mount=type=ssh git clone git@github.com:PatrycjaSputo/pawcho6.git .

FROM nginx:1.28.3-alpine

COPY --from=builder /app/index.html /usr/share/nginx/html/index.html
COPY --from=builder /app/config.template.json /app/config.template.json
COPY --from=builder /app/start.sh /start.sh

# Nadanie uprawnień do wykonania skryptu
RUN chmod +x /start.sh

ARG VERSION
ENV APP_VERSION=$VERSION

EXPOSE 80

# Sprawdzanie stanu kontenera (autodiagnostyka)
HEALTHCHECK --interval=5m --timeout=3s \
  CMD curl -f http://localhost/ || exit 1

# Zawsze zostanie uruchomione po starcie kontenera
ENTRYPOINT ["/start.sh"]
