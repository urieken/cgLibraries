/**
 * @file SDLLog.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.co)
 * @brief Header for SDL_Log wrapper
 * @version 0.1
 * @date 2022-01-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_LOG_SDL_LOG_HPP
#define CGL_LIBRARY_INCLUDE_LOG_SDL_LOG_HPP

#include <log/ILog.hpp>

#include <string>

#include <SDL2/SDL.h>

namespace cgl {
namespace log {
/**
 * @brief Wrapper class for SDL_Log
 */
class SDLLog final : public ILog {
public:
    SDLLog();
    virtual ~SDLLog();
    /**
     * @brief Push a log entry.
     * 
     * @param entry The entry to be pushed.
     */
    auto Push(const std::string& entry) -> void override;
    /**
     * @brief Push a log entry.
     * 
     * @param severity The log severity. 
     * @param category The log category. 
     * @param entry The entry to be pushed.
     */
    auto Push(const Severity& severity,
        const Category& category,
        const std::string& entry) -> void override;
private:
    SDL_mutex* mLogMutex;
};

}  // namespace log
}  // namespace cgl

#endif  // CGL_LIBRARY_INCLUDE_LOG_SDL_LOG_HPP