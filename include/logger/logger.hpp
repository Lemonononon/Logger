#ifndef LOGGER_LOGGER_HPP
#define LOGGER_LOGGER_HPP
#include <spdlog/spdlog.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <memory>
#include <iostream>

class Logger {
public:
    // 使用静态局部变量实现单例
    static spdlog::logger& getInstance() {
        static auto instance = []() {

            auto pathEnv = std::getenv("LOG_PATH");
            std::string logPath;
            if ( pathEnv != nullptr ){
                logPath = pathEnv;
            }else{
                logPath = "logs/log";
            }

            auto logger = spdlog::daily_logger_mt("Logger", logPath, 0, 0);
            logger->set_level(spdlog::level::info);  // 仅在初始化时设置日志级别
            logger->flush_on(spdlog::level::info);   // 仅在初始化时设置刷新策略

            return logger;
        }();
        return *instance;
    }

    // 禁用拷贝构造、拷贝赋值、移动构造和移动赋值
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;

private:
    Logger() = default;  // 私有化构造函数
};

// 定义简化的宏，方便直接使用
#define LOG(level, ...) Logger::getInstance().level(__VA_ARGS__)


#endif //LOGGER_LOGGER_HPP
