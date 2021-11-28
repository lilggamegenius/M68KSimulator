//
// Created by ggonz on 6/12/2021.
//

#include <array>
#include "Helpers.hpp"

template <typename T>
void M68K::SwapEndian(T &val) {
    union U {
        T val;
        std::array<std::uint8_t, sizeof(T)> raw;
    } src, dst;

    src.val = val;
    std::reverse_copy(src.raw.begin(), src.raw.end(), dst.raw.begin());
    val = dst.val;
}

template <typename T, template <typename ...> typename U>
using IsInstance = M68K::IsInstanceImpl<std::decay_t<T>, U>;