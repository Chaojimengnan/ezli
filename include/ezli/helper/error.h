#pragma once
#include <cerrno>
#include <concepts>
#include <system_error>
#include <utility>
// #include <source_location>

// this header handle the error, convert error code to exception

namespace ezli {

template <typename T>
inline constexpr void handle_return_val(const T& val)
{
    if constexpr (std::is_pointer_v<T>)
    {
        if (val == nullptr)
            throw std::system_error(errno, std::system_category());
    } else if (std::is_integral_v<T>)
    {
        if (val == -1)
            throw std::system_error(errno, std::system_category());
    }
}

template <auto fn, typename... Args>
constexpr decltype(auto) call(Args&&... args) requires(std::invocable<decltype(fn), Args...>)
{
    if constexpr (!std::same_as<decltype(fn(std::forward<Args>(args)...)), void>)
    {
        decltype(auto) val = fn(std::forward<Args>(args)...);
        handle_return_val(val);
        return val;
    } else {
        return fn(std::forward<Args>(args)...);
    }
}

template <typename Fn, typename... Args>
constexpr decltype(auto) call(Fn func, Args&&... args) requires(std::invocable<Fn, Args...>)
{
    if constexpr (!std::same_as<decltype(func(std::forward<Args>(args)...)), void>)
    {
        decltype(auto) val = func(std::forward<Args>(args)...);
        handle_return_val(val);
        return val;
    } else {
        return func(std::forward<Args>(args)...);
    }
}

// This feature is not steady, so comment it

// template <auto fn>
// struct call_loc
// {
//     constexpr call_loc(const std::source_location& cur_loc = std::source_location::current()) : loc(cur_loc) { }

//     template <typename... Args>
//     constexpr decltype(auto) operator()(Args&&... args)
//     {
//         decltype(auto) val = fn(std::forward<Args>(args)...);
//         if (errno != 0)
//             throw std::system_error(errno, std::system_category(), loc.file_name() + "(" + std::to_string(loc.line()) + ")");

//         return val;
//     }

//     const std::source_location loc; // NOLINT
// };
} // namespace ezli