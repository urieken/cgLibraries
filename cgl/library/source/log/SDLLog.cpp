/**
 * @file SDLLog.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Source for SDL_Log wrapper
 * @version 0.1
 * @date 2022-01-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "log/ILog.hpp"
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_mutex.h>
#include <log/SDLLog.hpp>

namespace cgl {
namespace log {
/**
 * @brief Convert ILog::Category to SDL_LogCategory.
 * 
 * @param category The log category.
 * @return SDL_LogCategory The equivalent SDL log category.
 */
constexpr auto LogCategory(const ILog::Category& category)
    -> SDL_LogCategory {
    switch(category){
        case ILog::Category::Application : return SDL_LOG_CATEGORY_APPLICATION;
        case ILog::Category::Error : return SDL_LOG_CATEGORY_ERROR;
        case ILog::Category::Assert : return SDL_LOG_CATEGORY_ASSERT;
        case ILog::Category::System : return SDL_LOG_CATEGORY_SYSTEM;
        case ILog::Category::Audio : return SDL_LOG_CATEGORY_AUDIO;
        case ILog::Category::Video : return SDL_LOG_CATEGORY_VIDEO;
        case ILog::Category::Render : return SDL_LOG_CATEGORY_RENDER;
        case ILog::Category::Input : return SDL_LOG_CATEGORY_INPUT;
        case ILog::Category::Test : return SDL_LOG_CATEGORY_TEST;
        case ILog::Category::Unknown :
        default : return SDL_LOG_CATEGORY_CUSTOM;
    }
    // Unreachable code?
    return SDL_LOG_CATEGORY_CUSTOM;
}

/**
 * @brief Convert ILog::Severity to SDL_LogProirity.
 * 
 * @param severity The log severity.
 * @return SDL_LogPriority The equivalent SDL log priority.
 */
constexpr auto LogSeverity(const ILog::Severity& severity)
    -> SDL_LogPriority {
    switch(severity) {
        case ILog::Severity::Verbose : return SDL_LOG_PRIORITY_VERBOSE;
        case ILog::Severity::Info : return SDL_LOG_PRIORITY_INFO;
        case ILog::Severity::Debug : return SDL_LOG_PRIORITY_DEBUG;
        case ILog::Severity::Warning : return SDL_LOG_PRIORITY_WARN;
        case ILog::Severity::Error : return SDL_LOG_PRIORITY_ERROR;
        case ILog::Severity::Critical : return SDL_LOG_PRIORITY_CRITICAL;
        case ILog::Severity::Unknown :
        default: return SDL_NUM_LOG_PRIORITIES;
    }
    // Unreachable code?
    return SDL_NUM_LOG_PRIORITIES;
}

SDLLog::SDLLog() :
    mLogMutex{::SDL_CreateMutex()} {
}

SDLLog::~SDLLog() {
    // ?
    //mLogMutex = nullptr
    // ?
}

auto SDLLog::Push(const std::string& entry) -> void {
    ::SDL_LockMutex(mLogMutex);
    ::SDL_Log("%s", entry.c_str());
    ::SDL_UnlockMutex(mLogMutex);
}

auto SDLLog::Push(const Severity &severity,
    const Category& category,
    const std::string &entry) -> void {
    ::SDL_LockMutex(mLogMutex);
    switch (severity) {
        case ILog::Severity::Verbose : {
            ::SDL_LogVerbose(LogCategory(category), "%s", entry.c_str());
        }break;
        case ILog::Severity::Info : {
            ::SDL_LogInfo(LogCategory(category), "%s", entry.c_str());
        }break;
        case ILog::Severity::Debug : {
            ::SDL_LogDebug(LogCategory(category), "%s", entry.c_str());
        }break;
        case ILog::Severity::Warning : {
            ::SDL_LogWarn(LogCategory(category), "%s", entry.c_str());
        }break;
        case ILog::Severity::Error : {
            ::SDL_LogError(LogCategory(category), "%s", entry.c_str());
        }break;
        case ILog::Severity::Critical : {
            ::SDL_LogCritical(LogCategory(category), "%s", entry.c_str());
        }break;
        case ILog::Severity::Unknown :
        default : ::SDL_Log("%s", entry.c_str()); break;
    }
    ::SDL_UnlockMutex(mLogMutex);
}

}  // namespace log
}  // namespace cgl
