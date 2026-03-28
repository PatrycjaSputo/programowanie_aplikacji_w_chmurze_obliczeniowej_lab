#!/bin/sh
set -e

# Zdefiniowanie zmiennych dla szablonu
export APP_IP=$(hostname -i)
export APP_HOST=$(hostname)

# envsubst czyta szablon, wstawia zmienne i zapisuje gotowy config.json
envsubst < /app/config.template.json > /usr/share/nginx/html/config.json

# Uruchomienie Nginx jako główny proces
exec nginx -g 'daemon off;'
