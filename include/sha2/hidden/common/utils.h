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

template <class WordType>
inline WordType pack_as(const std::span<std::byte> &bytes) noexcept {
    if constexpr (std::same_as<WordType, std::uint64_t>) {
        return  std::to_integer<WordType>(bytes[7])        | 
               (std::to_integer<WordType>(bytes[6]) << 8)  |
               (std::to_integer<WordType>(bytes[5]) << 16) |
               (std::to_integer<WordType>(bytes[4]) << 24) |
               (std::to_integer<WordType>(bytes[3]) << 32) |
               (std::to_integer<WordType>(bytes[2]) << 40) |
               (std::to_integer<WordType>(bytes[1]) << 48) |
               (std::to_integer<WordType>(bytes[0]) << 56) ;
    }

    return  std::to_integer<WordType>(bytes[3])        | 
           (std::to_integer<WordType>(bytes[2]) << 8)  |
           (std::to_integer<WordType>(bytes[1]) << 16) |
           (std::to_integer<WordType>(bytes[0]) << 24) ;
}

template <class WordType>
inline void unpack_as(std::span<std::byte> bytes, WordType w) noexcept {
    if constexpr (std::same_as<WordType, std::uint64_t>) {
        bytes[0] = std::byte(w >> 56);
        bytes[1] = std::byte(w >> 48);
        bytes[2] = std::byte(w >> 40);
        bytes[3] = std::byte(w >> 32);
        bytes[4] = std::byte(w >> 24);
        bytes[5] = std::byte(w >> 16);
        bytes[6] = std::byte(w >> 8);
        bytes[7] = std::byte(w);
    } else {
        bytes[0] = std::byte(w >> 24);
        bytes[1] = std::byte(w >> 16);
        bytes[2] = std::byte(w >> 8);
        bytes[3] = std::byte(w);
    }
}

template <std::size_t N, class WordType>
inline WordType rotr(WordType w) noexcept {
    return (w << (sizeof(WordType) * 8 - N)) | (w >> N);
}

template <class WordType>
inline WordType ch(WordType x, WordType y, WordType z) noexcept {
    return (x & y) ^ (~x & z);
}

template <class WordType>
inline WordType ma(WordType x, WordType y, WordType z) noexcept {
    return (x & y) ^ (x & z) ^ (y & z);
}

template <class WordType>
inline WordType s0(WordType x) noexcept {
    if constexpr (std::same_as<WordType, std::uint64_t>) {
        return rotr<1>(x) ^ rotr<8>(x) ^ (x >> 7);
    }

    return rotr<7>(x) ^ rotr<18>(x) ^ (x >> 3);
}

template <class WordType>
inline WordType s1(WordType x) noexcept {
    if constexpr (std::same_as<WordType, std::uint64_t>) {
        return rotr<19>(x) ^ rotr<61>(x) ^ (x >> 6);
    }

    return rotr<17>(x) ^ rotr<19>(x) ^ (x >> 10);
}

template <class WordType>
inline WordType sig0(WordType x) noexcept {
    if constexpr (std::same_as<WordType, std::uint64_t>) {
        return rotr<28>(x) ^ rotr<34>(x) ^ rotr<39>(x);
    }

    return rotr<2>(x) ^ rotr<13>(x) ^ rotr<22>(x);
}

template <class WordType>
inline WordType sig1(WordType x) noexcept {
    if constexpr (std::same_as<WordType, std::uint64_t>) {
        return rotr<14>(x) ^ rotr<18>(x) ^ rotr<41>(x);
    }

    return rotr<6>(x) ^ rotr<11>(x) ^ rotr<25>(x);
}

} // common

#endif // UTILS_H
