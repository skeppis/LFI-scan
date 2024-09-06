#include <stdio.h>
#include <iostream>
#include <filesystem>
#include <regex>
#include <string>
#include <fstream>
#include <curl/curl.h>
#include <unistd.h>

bool validUrl(const std::string& url) {  // Pass by const reference
    const std::regex urlRegex(R"(^(https?:\/\/)(([\da-z\.-]+)\.([a-z\.]{2,6})|(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}))(:\d{1,5})?(\/[\w\.-]*)*(\?[;&a-z\.-]*)?(#\w*)?$)");

    return std::regex_match(url, urlRegex);
}

bool fileExists(const std::string& file) {
    return std::filesystem::exists(file);
}

bool validInput(char* const arg[], int count) { 
    if (std::string(arg[1]) != "-u" || !validUrl(arg[2])) {
       	std::cout << "Invalid URL format, please try again\n" << std::endl;
       	return false;
    }
    
    if (std::string(arg[3]) != "-w" || !fileExists(arg[4])) {
        std::cout << "Invalid wordlist, please try again\n" << std::endl;
        return false;
    }

    return true;
}

long sendRequest(const std::string &url) {
    CURL* curl;
    CURLcode res;
    long code = 0;

    curl = curl_easy_init();

    if(curl) {
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	// send HTTP GET request
	res = curl_easy_perform(curl);

	if(res != CURLE_OK) {
	    std::cerr << "curl request failed: " << curl_easy_strerror(res) << std::endl;
	}
	else {
	    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);
	}

	curl_easy_cleanup(curl);
    }
    return code;
}

void printResult(const long &code, const std::string &payload) {
    std::string color = "\033[1;31m";

    if (code == 200) color = "\033[1;32m";

    std::cout << color << "[" << code << "]\033[0m " << payload << std::endl; 
}

int main(int argc, char *argv[]) {
    if (argc == 5 && validInput(argv, argc)) {
	    std::string filename(argv[4]);
	    std::string url(argv[2]);

	    std::ifstream file(filename);
	    std::string line;
	    long responseCode;

	    while (std::getline(file, line)) {
		std::string target = url + line;

		responseCode = sendRequest(target);

		if(responseCode != 404) printResult(responseCode, target);

		sleep(1);
	    }

	    file.close();
         
    }
    else {
        std::cout << "usage: ./LFI-scan -u [target url] -w [wordlist]" << std::endl;
    }

    return 0;
}

