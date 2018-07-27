/********************************************
 * Author: banbo <banbo777@163.com>
 * File: demo_connector.h
 * Date: 2018-07-23
 * Version: 1.0.0.0
 * Brief:
 ********************************************/

#include <signal.h>                 // signal
#include <iostream>                 // cout

/******* Http Server *******/
#include "server.h"                 // HttpServer
#include "demo_connector.h"         // DemoConnector

#include "bbc_log.h"                // log

#define ADD_CONNECTOR(conn)                                         \
    do {                                                            \
        conn *c = new (std::nothrow) conn();                        \
        if (c == NULL || c->init() != 0) {                          \
            LOG(FATAL) << "Failed to create " << #conn; \
            return -1;                                              \
        }                                                           \
        if (server.connector_registor(c) != 0) {                    \
            LOG(FATAL) << "Failed to add " << #conn;    \
            return -1;                                              \
        }                                                           \
    } while (0)    

bool g_signal_quit = false;
void sigint_handler(int sig) {
    if (sig == SIGINT || sig == SIGTERM) {
        g_signal_quit = true;
    }
}

int main(int argc, char *argv[]) {
    // Signal handler.
    signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigint_handler);

    bbc::init_log();

    // Http Server
    bbc::HttpServer server;

    //API
    ADD_CONNECTOR(bbc::DemoConnector);

    if (server.start(g_signal_quit) != 0) {
        LOG(FATAL) << "Fail to start http server.";
        return -1;
    } else {
        // Exit.
        bbc::close_log();
        LOG(INFO) << "Server exitting...";
        return 0;
    }
}                          