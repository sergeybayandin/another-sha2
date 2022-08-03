#ifndef UTILS_HASH_H
#define UTILS_HASH_H

namespace sha2::utils {

template <class R>
concept ContiguousBytesRange = std::ranges::contiguous_range<R> &&
                               std::ranges::sized_range<R> &&
                               std::same_as<std::remove_cv_t<typename std::remove_cvref_t<R>::value_type>, std::byte>;

inline int to_hex(int ch) noexcept {
    return ch < 10 ? ch + '0' : ch + 'a' - 10;
}

inline std::byte to_byte(int lch, int rch) noexcept {
    return std::byte(((std::isdigit(lch) ? lch - '0' : lch - 'a' + 10) << 4) | 
                      (std::isdigit(rch) ? rch - '0' : rch - 'a' + 10));
}

} // utils

#endif // UTILS_HASH_H
