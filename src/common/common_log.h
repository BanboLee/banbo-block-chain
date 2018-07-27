/********************************************
 * Author: banbo <banbo777@163.com>
 * File: common_log.h
 * Date: 2018-07-26
 * Version: 1.0.0.0
 * Brief:
 ********************************************/

#ifndef BANBO_CHAIN_COMMON_LOG_H
#define BANBO_CHAIN_COMMON_LOG_H

#include <glog/logging.h>

extern const google::LogSeverity FATAL;
extern const google::LogSeverity ERROR;
extern const google::LogSeverity WARNING;

extern const google::LogSeverity INFO;
extern const uint32_t DEBUG_LV;

#endif  //BANBO_CHAIN_COMMON_LOG_H