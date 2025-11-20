#include <iostream>
#include <string>
#include <curl/curl.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
using namespace std;
string get_Request(const string& url) {
    CURL* curl = curl_easy_init();
    string result;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        // Write callback
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,
            +[](void* contents, size_t size, size_t nmemb, void* userp) {
                size_t total = size * nmemb;
                string* s = (string*)userp;
                s->append((char*)contents, total);
                return total;
            }
        );
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);

        // Perform
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            cerr << "curl error inside get_Request: "
                 << curl_easy_strerror(res) << endl;
        }

        curl_easy_cleanup(curl);
    }
    return result;
}


int main(){
    curl_global_init(CURL_GLOBAL_ALL);
    xmlInitParser();  
    string html_document = get_Request("https://www.scrapingcourse.com/ecommerce");
    cout << html_document <<endl;
    xmlCleanupParser();  
    curl_global_cleanup();
    return 0;
}