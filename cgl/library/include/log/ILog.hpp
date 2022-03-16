/**
 * @file ILog.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for Log interface
 * @version 0.1
 * @date 2022-01-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_LOG_ILOG_HPP
#define CGL_LIBRARY_INCLUDE_LOG_ILOG_HPP

#include <string>

namespace cgl {
namespace log {
/**
 * @brief The log interface
 */
class ILog {
public:
    /**
     * @brief Log severity
     */
    enum class Severity {
        Verbose = 0UL,
        Info,
        Debug,
        Warning,
        Error,
        Critical,
        Unknown
    };
    /**
     * @brief Log Category
     */
    enum class Category {
        Application = 0UL,
        Error,
        Assert,
        System,
        Audio,
        Video,
        Render,
        Input,
        Test,
        Unknown
    };
    virtual ~ILog() = default;
    /**
     * @brief Push a log entry.
     * 
     * @param entry The entry to be pushed.
     */
    virtual auto Push(const std::string& entry) -> void = 0;
    /**
     * @brief Push a log entry.
     * 
     * @param severity The log severity. 
     * @param category The log category. 
     * @param entry The entry to be pushed.
     */
    virtual auto Push(const Severity& severity, const Category& category,
        const std::string& entry) -> void = 0;
};
}  // namespace log
}  // namespace cgl

#endif  // CGL_LIBRARY_INCLUDE_LOG_ILOG_HPP