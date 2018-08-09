/********************************************
 * Author: banbo <banbo777@163.com>
 * File: connector.h
 * Date: 2018-07-23
 * Version: 1.0.0.0
 * Brief:
 ********************************************/
#ifndef BANBO__CHAIN_CONNECTOR_H
#define BANBO__CHAIN_CONNECTOR_H

#include "common_utils.h"

namespace bbc {

class Connector {
public:
    virtual ~Connector() {}
    virtual int init() { return 0; }
    virtual const char* uri() const = 0;
    virtual int get(Connection *conn, Request *request) { return bbc::reply_404(conn); }
    virtual int post(Connection *conn, Request *request) { return bbc::reply_404(conn); }

};

}

#endif  //BANBO__CHAIN_CONNECTOR_H