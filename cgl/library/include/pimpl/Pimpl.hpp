/**
 * @file Pimpl.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for Pimpl
 * @version 0.1
 * @date 2021-10-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_PIMPL_PIMPL_HPP_
#define CGL_LIBRARY_INCLUDE_PIMPL_PIMPL_HPP_

#include <memory>

namespace cgl {
namespace pimpl {

/**
 * @brief The Pimpl class
 * 
 * @tparam T The type to be implemented.
 */
template <typename T>
class Pimpl {
public:
    /**
     * @brief Construct a new Pimpl object
     */
    Pimpl() :
        mPimpl{new T{}}{
    }
    /**
     * @brief Construct a new Pimpl object
     * 
     * @tparam Args The argument types to be forwarded.
     * @param args The arguments to be forwarded.
     */
    template<typename ...Args>
    Pimpl(Args&&  ...args) :
        mPimpl{new T{std::forward<args>(args)... }} {
    }
    /**
     * @brief Return a pointer to the Pimpl instance.
     * 
     * @return T* The pointer to the Pimpl instance.
     */
    auto operator->() const -> T* {
        return mPimpl.get();
    }
    /**
     * @brief Return a reference to the Pimpl instance.
     * 
     * @return T& The reference to the Pimpl instance.
     */
    auto operator*() const -> T& {
        return *mPimpl;
    }
private:
    /**
     * @brief Pointer to the implementation instance.
     */
    std::unique_ptr<T> mPimpl;
};

}  // namesapce pimpl
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_PIMPL_PIMPL_HPP_ */
