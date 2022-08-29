#pragma once
#include <cerrno>
#include <concepts>
#include <system_error>
#include <utility>
// #include <source_location>

// this header handle the error, convert error code to exception

namespace ezli {
template <auto fn, typename... Args>
constexpr decltype(auto) call(Args&&... args) requires(std::invocable<decltype(fn), Args...>)
{
    decltype(auto) val = fn(std::forward<Args>(args)...);
    if (errno != 0)
        throw std::system_error(errno, std::system_category());

    return val;
}

template <typename Fn, typename... Args>
constexpr decltype(auto) call(Fn func, Args&&... args) requires(std::invocable<Fn, Args...>)
{
    decltype(auto) val = func(std::forward<Args>(args)...);
    if (errno != 0)
        throw std::system_error(errno, std::system_category());

    return val;
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