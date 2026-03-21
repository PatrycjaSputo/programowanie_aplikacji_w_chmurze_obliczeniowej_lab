# syntax=docker/dockerfile:1
 
# Powinno się używać konkretnej wersji zamiast "latest", ale w ramach zadania zostało użyte "latest"
FROM ubuntu:latest 

# Podanie autora i adresu email
LABEL author="Patrycja Sputo s101672@pollub.edu.pl"

# Zaktualizowanie systemu ubuntu i zainstalowanie serwera Apache, a następnie usunięcie zbędnych plików
RUN apt-get update && \
    apt-get install -y apache2 && \
    apt-get clean

# Skopiowanie lokalnego pliku do serwera Apache
# Strona zawiera imię, nazwisko oraz grupę dziekańską
COPY web/index.html /var/www/html/index.html

# Informacja o tym, że kontener będzie nasłuchiwał na porcie 80.
# Port 80 to srandardowy port dla HTTP.
EXPOSE 80

# Uruchomienie serwera Apache. Zostało do tego użyte polecenie apachectl.
# -D Ustawia parametr konfiguracyjny
# -DFOREGROUND zapobiega wywołaniu przez rodzica sesid() i innych
# Dzięki temu kontener nie wyłączy się od razu
CMD ["apachectl", "-D", "FOREGROUND"]
