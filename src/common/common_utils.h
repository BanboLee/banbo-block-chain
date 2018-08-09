/********************************************
 * Author: banbo <banbo777@163.com>
 * File: common_utils.h
 * Date: 2018-08-02
 * Version: 1.0.0.0
 * Brief:
 ********************************************/

#ifndef BANBO_CHAIN_COMMON_UTILS_H
#define BANBO_CHAIN_COMMON_UTILS_H

#include <string>
#include <vector>
#include <picosha2/picosha2.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h" 
#include "rapidjson/stringbuffer.h"   
#include "mongoose.h"
#include "bbc_log.h"

namespace bbc {

typedef http_message Request;
typedef mg_connection Connection;

enum HttpStatusCode {
    HTTP_STATUS_OK = 200,
    HTTP_STATUS_URI_NOT_FOUND = 404
};

// Http text response
inline int reply_text(Connection *conn, std::string &rsp_text) {
    mg_send_head(conn, HTTP_STATUS_OK,  rsp_text.size(), "Content-Type: text/plain");
    mg_send(conn, rsp_text.c_str(), rsp_text.size());
    return 0;
}

// Http json response
inline int reply_json(Connection *conn, std::string &rsp_text) {
    mg_send_head(conn, HTTP_STATUS_OK,  rsp_text.size(), "Content-Type: application/json");
    mg_send(conn, rsp_text.c_str(), rsp_text.size());
    return 0;
}

// Http 404 response
inline int reply_404(Connection *conn) {
    std::string s = "Page Not Found";
    mg_send_head(conn, HTTP_STATUS_URI_NOT_FOUND,  s.size(),"Content-Type: text/plain");
    mg_send(conn, s.c_str(), s.size());
    return 0;
} 

inline std::string hash(std::string& input) {
    return picosha2::hash256_hex_string(input);
}

inline std::string serialize(rapidjson::Document& document) {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    return buffer.GetString();
}

}   // End bbc

#endif  // BANBO_CHAIN_COMMON_UTILS_H
