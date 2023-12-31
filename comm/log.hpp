#pragma once

#include <iostream>
#include <string>
#include "util.hpp"

namespace ns_log
{
    using namespace ns_util;
    // 日志等级
    enum
    {
        INFO,
        DEBUG,
        WARNING,
        ERROR,
        FATAL
    };

    // LOG() << "message"
    inline std::ostream &Log(const std::string &level, const std::string &file_name, int line)
    {
        // 添加日志等级
        std::string message = "[";
        message += level;
        message += "]";

        // 添加报错文件名称
        message += "[";
        message += file_name;
        message += "]";

        // 添加报错行
        message += "[";
        message += std::to_string(line);
        message += "]";

        // 日志时间戳
        message += "[";
        message += TimeUtil::GetTimeStamp();
        message += "]";

        // cout 内部是包含缓冲区的
        std::cout << message; //不要使用endl刷新

        return std::cout;
    }

    // LOG(INFO) << "message" << "\n";
    //开放式日志
    #define LOG(level) Log(#level, __FILE__, __LINE__)

}