/********************************************
 * Author: banbo <banbo777@163.com>
 * File: demo_connector.cpp
 * Date: 2018-07-23
 * Version: 1.0.0.0
 * Brief:
 ********************************************/

#include "demo_connector.h"
#include <iostream>            // cout
#include <string>

namespace bbc {

int DemoConnector::run(Connection *conn, Request *request) {
    std::string hw = "hello world!";
    mg_send_head(conn, HTTP_STATUS_OK,  hw.size(), "Content-Type: text/plain");
    mg_send(conn, hw.c_str(), hw.size());
    return 0;
}

}