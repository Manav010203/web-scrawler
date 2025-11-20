#include <iostream>
#include <string>
#include <curl/curl.h>

size_t writefunc(void *ptr, size_t size, size_t nmemb, std::string *data) {
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

int main() {
    curl_global_init(CURL_GLOBAL_ALL);

    CURL* curl = curl_easy_init();
    std::string result;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);

        CURLcode res = curl_easy_perform(curl);
        std::cout << "curl result code = " << res << std::endl;
        std::cout << "Received data:\n" << result << std::endl;

        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Failed to init curl" << std::endl;
    }

    curl_global_cleanup();
    return 0;
}
