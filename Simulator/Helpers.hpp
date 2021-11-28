//
// Created by ggonz on 2/15/2021.
//

#pragma once

namespace M68K{
    // https://mklimenko.github.io/english/2018/08/22/robust-endian-swap/
    template <typename T>
    void SwapEndian(T &val);

    template <typename, template <typename...> typename>
    struct IsInstanceImpl : public std::false_type {};

    template <template <typename...> typename U, typename...Ts>
    struct IsInstanceImpl<U<Ts...>, U> : public std::true_type {};
}