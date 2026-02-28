#ifndef MAIN_CPP
#define MAIN_CPP

#include <stdio.h>
#include <iostream>
#include <filesystem>
#include <regex>
#include <string>
#include <fstream>
#include <curl/curl.h>
#include <unistd.h>


bool validUrl(const std::string& url) {
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

size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata){
    // https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
}

int performRequest(const CURL* c, const std::string& url, std::string& html){
    CURLcode result;
    curl_easy_setopt(c, CURLOPT_URL, url);
    curl_easy_setopt(c, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(c, CURLOPT_WRITEDATA, html);

    result = curl_easy_perform(c);

    if(result == CURLE_OK) {
    }
}
        

    

void printResult(const long &code, const std::string &payload) {
    std::string color = "\033[1;31m";

    if (code == 200) color = "\033[1;32m";

    std::cout << color << "[" << code << "]\033[0m " << payload << std::endl; 
}

int main(int argc, char *argv[]) {
    if(argc != 5 || !validInput(argv, argc){
        std::cout << "usage: ./LFI-scan -u [target url] -w [wordlist]" << std::endl;
    }

	std::string filename(argv[4]);
	std::string url(argv[2]);

	std::ifstream file(filename);
	std::string line;

    CURL* curl = curl_easy_init();
    std::string base_html;

    if(!curl) {
        std::cout << "something went wrong with curl..." << std::endl;
        return 0;
    }

    // store default HTML for comparison
    
    if(performRequest(curl, url, base_html)){
         

	while (std::getline(file, line)) {
        std::string target = url + line;

	    // perform request with payload
	}

	file.close();
    curl_easy_cleanup(curl);
    

    return 0;
}

#endif
