#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json; //loh man внатуре лох человек

std::string test(const std::string& API_URL) {
	
    std::string type = "spectate"; // team, scid_requests, ...
    std::string key = "ENTER_YOUR_KEY_HERE";
    std::string tag = "#2PP";
    std::string url = API_URL + "/launch?key=" + key + "&type=" + type + "&tag=" + tag; // чертовски
	
    CURL *curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        std::string response_string; //hui
		
		
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [](char* ptr, size_t size, size_t nmemb, std::string* data) {
            data->append(ptr, size * nmemb);
            return size * nmemb;
        });
		
		
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        CURLcode res = curl_easy_perform(curl);
		
        if(res != CURLE_OK) {
            std::cerr << "suka nahui\n";
            exit(1);
        }

        curl_easy_cleanup(curl);

        return response_string;
    } else {
		std::cerr << "CURL POPIERDOLIŁO JAK TEN JS\n";
        exit(1);
	}

    return "";
}

int main() {
    std::string SERVERS_LIST_URL = "https://raw.githubusercontent.com/rldv1/SCRE1_API_CLIENT/main/actual_nodes_prod.json";
    std::cout << "DL Server list from: " << SERVERS_LIST_URL << std::endl;

    srand(time(nullptr)); //каво
	
	
    CURL *curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, SERVERS_LIST_URL.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // НУ КААКОГО ХУЯ БЛЯДЬ ПИЗДЕЦ КРАШИЛ

        std::string response_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [](char* ptr, size_t size, size_t nmemb, std::string* data) {
            data->append(ptr, size * nmemb);
            return size * nmemb;
        });
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        CURLcode res = curl_easy_perform(curl);
		
        if(res != CURLE_OK) {
            std::cerr << "suka nahui\n";
            exit(1);
        }

        curl_easy_cleanup(curl);

        auto json_data = json::parse(response_string); // а потом хуяк протечка памяти
		
        std::vector<std::vector<std::string>> api_nodes = json_data["api_nodes"];
        std::vector<std::string> selected_server = api_nodes[rand() % api_nodes.size()];

        std::string API_URL = "http://" + selected_server[0];
        std::cout << "Picked API: " << selected_server[1] << std::endl;
        std::cout << test(API_URL) << std::endl;
		
        // {"success": True, "uses_left": 666, .....}
        // {"success": False, "reason": "flood_wait", "try_after": 66, .....}
    }

    return 0;
}
