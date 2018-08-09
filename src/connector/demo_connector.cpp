/********************************************
 * Author: banbo <banbo777@163.com>
 * File: demo_connector.cpp
 * Date: 2018-07-23
 * Version: 1.0.0.0
 * Brief:
 ********************************************/

#include <string>

#include "demo_connector.h"
#include "common_utils.h"

namespace bbc {

int DemoConnector::get(Connection *conn, Request *request) {
    std::string hw = "hello world!";
    reply_text(conn, hw);
    return 0;
}

}