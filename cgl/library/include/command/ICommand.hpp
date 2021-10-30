/**
 * @file ICommand.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for command interface
 * @version 0.1
 * @date 2021-10-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_COMMAND_ICOMMAND_HPP_
#define CGL_LIBRARY_INCLUDE_COMMAND_ICOMMAND_HPP_

#include <system_error>

namespace cgl {
namespace command {
/**
 * @brief The command interface.
 */
class ICommand {
public:
    virtual ~ICommand() = default;
    /**
     * @brief Execute the command.
     * 
     * @return std::error_condition The command result.
     */
    virtual auto Execute() -> std::error_condition = 0;
};

}  // namespace command
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_COMMAND_ICOMMAND_HPP_ */
