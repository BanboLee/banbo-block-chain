/********************************************
 * Author: banbo <banbo777@163.com>
 * File: bbc_log.cpp
 * Date: 2018-07-26
 * Version: 1.0.0.0
 * Brief:
 ********************************************/

#include "bbc_log.h"

namespace bbc {

void init_log() {
    FLAGS_log_dir = "./log";
    google::InitGoogleLogging("block-chain");
    google::SetLogDestination(FATAL, "./log/bbc.chainer.log.wf");
    google::SetLogDestination(ERROR, "./log/bbc.chainer.log.wf");
    google::SetLogDestination(WARNING, "./log/bbc.chainer.log.wf");

    google::SetLogDestination(INFO, "./log/bbc.chainer.log.info");
}

void close_log() {
    google::ShutdownGoogleLogging();
}

}    // end namespace bbc