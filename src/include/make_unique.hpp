#pragma once

#include <memory>

namespace std {
    template<typename T, typename... A>
    std::unique_ptr<T>
    make_unique(A&&... x) {
        return std::move(std::unique_ptr<T>(
            new T(std::forward<A>(x)...)));
    }

    template<typename T>
    std::unique_ptr<T>
    make_unique(std::size_t size) {
        return std::move(std::unique_ptr<T>(
            new T[size]));
    }
}
