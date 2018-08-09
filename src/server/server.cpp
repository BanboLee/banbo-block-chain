/********************************************
 * Author: banbo <banbo777@163.com>
 * File: server.cpp
 * Date: 2018-07-19
 * Version: 1.0.0.0
 * Brief:
 ********************************************/

#include "bbc_log.h"
#include "server.h"
#include <iostream>

namespace bbc {

void HttpServer::ev_handler(Connection *c, int ev, void *p) {
    if (ev == MG_EV_HTTP_REQUEST) {
        Request *hm = (Request *) p;
        std::string uri(hm->uri.p, hm->uri.len);
        std::string method(hm->method.p, hm->method.len);
        LOG(INFO) << "uri: " << uri;
        LOG(INFO) << "method: " << method;
        std::map<std::string, Connector*>::iterator it = bbc::_connectors.find(uri);
        if (it != bbc::_connectors.end()) {
            Connector *connector = it->second;
            if (method == HTTP_METHOD_GET) {
                connector->get(c, hm);
            } else {
                connector->post(c, hm); 
            }
        } else {
            reply_404(c);
        }
    }
}

int HttpServer::start(bool &g_signal_quit) {
    struct mg_mgr mgr;
    struct mg_connection *c;
    mg_mgr_init(&mgr, NULL);
    c = mg_bind(&mgr, _port.c_str(), ev_handler);
    mg_set_protocol_http_websocket(c);

    while (!g_signal_quit) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
    return 0;
}

int HttpServer::connector_registor(Connector *connector) {
    LOG(INFO) << "Add connector for : " << connector->uri();
    _connectors[connector->uri()] = connector;
    return 0;
}

}