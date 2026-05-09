#include "httplib.h"
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <ctime>
#include <cstdlib>

const char* AUTHOR = "Patrycja Sputo";

httplib::Server* global_svr_ptr = nullptr;

std::string load_html(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) return "Blad ladowania pliku HTML.";
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main(int argc, char* argv[]) {
int port = 3000; 
    if (const char* env_p = std::getenv("APP_PORT")) {
        try {
            port = std::stoi(env_p);
        } catch (...) {
            printf("[WARN] Nieprawidlowy APP_PORT, uzywam domyslnego: 3000\n");
        }
    }
// tryb healthcheck
if (argc > 1 && std::string(argv[1]) == "--health") {
        
        httplib::Client cli("127.0.0.1", port);
        cli.set_connection_timeout(2, 0); 
        
        if (auto res = cli.Get("/health")) {
            if (res->status == 200) {
                return 0; // Zwraca kod 0 = Healthy
            }
        }
        return 1; // Zwraca kod 1 = Unhealthy
    }

//tryb serwera

    // Logi przy starcie
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
// std::ctime domyślnie dodaje enter na końcu, więc go ucinamy dla ładnego formatowania
    std::string start_time = std::ctime(&now_time);
    start_time.pop_back();
    
    printf("[LOG] Data uruchomienia: %s (czas UTC)\n", start_time.c_str());
    fflush(stdout);
    
    printf("[LOG] Autor programu: %s\n", AUTHOR);
    fflush(stdout);

    printf("[LOG] Aplikacja nasluchuje na porcie TCP: %d\n", port);
    fflush(stdout);

    httplib::Server svr;
    global_svr_ptr = &svr;

    // Endpoint serwujący plik HTML
    svr.Get("/", [](const httplib::Request &req, httplib::Response &res) {
    printf("[LOG] Odwiedzono strone glowna (IP: %s)\n", req.remote_addr.c_str());
        fflush(stdout);
        std::string html = load_html("/web/index.html"); 
        res.set_content(html, "text/html; charset=utf-8");
    });

    // Endpoint dla Docker Healthcheck
    svr.Get("/health", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("OK", "text/plain");
    });

// Endpoint serwujący plik JSON
    svr.Get("/miasta.json", [](const httplib::Request &, httplib::Response &res) {
        std::string json = load_html("/web/miasta.json"); 
        res.set_content(json, "application/json; charset=utf-8");
    });

    svr.listen("0.0.0.0", port);
    return 0;

}
