#ifndef RESPONSE_H
#define RESPONSE_H

struct Response {
    unsigned int code;
    size_t length;
    std::string body;
    double time; 
};

#endif
