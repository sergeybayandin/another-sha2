#ifndef UTILS_H
#define UTILS_H

namespace sha2::hidden::common {

inline int to_hex(int ch) noexcept {
    return ch < 10 ? ch + '0' : ch + 'a' - 10;
}

inline std::byte to_byte(int lch, int rch) noexcept {
    return std::byte(((std::isdigit(lch) ? lch - '0' : lch - 'a' + 10) << 4) | 
                      (std::isdigit(rch) ? rch - '0' : rch - 'a' + 10));
}

} // common

#endif // UTILS_H
