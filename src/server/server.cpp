#include <iostream>            // cout

#include "bbc_log.h"
#include "server.h"

namespace bbc {

void HttpServer::ev_handler(Connection *c, int ev, void *p) {
    if (ev == MG_EV_HTTP_REQUEST) {
        Request *hm = (Request *) p;
        std::string uri(hm->uri.p, hm->uri.len);
        LOG(INFO) << "uri: " << uri;
        std::map<std::string, Connector*>::iterator it = bbc::_connectors.find(uri);
        if (it != bbc::_connectors.end()) {
            Connector *connector = it->second;
            connector->run(c, hm);
        } else {
            std::string s = "Page Not Found";
            mg_send_head(c, HTTP_STATUS_URI_NOT_FOUND,  s.size(),"Content-Type: text/plain");
            mg_send(c, s.c_str(), s.size());
        }
    }
}

int HttpServer::start(bool &g_signal_quit) {
    /* for debug
    LOG(INFO) << "=====================";
    for (std::map<std::string, Connector*>::iterator it = bbc::_connectors.begin(); it != bbc::_connectors.end(); it++) {
        LOG(INFO) << it->first;
    }
    LOG(INFO) << "=====================";
    */

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
    _connectors[connector->uri()] = connector;
    return 0;
}

// Reply text response.
int HttpServer::reply_text(Connection *conn, std::string &response) {
    mg_send_head(conn, HTTP_STATUS_OK,  response.size(), "Content-Type: text/plain");
    mg_send(conn, response.c_str(), response.size());
    return 0;
}

}