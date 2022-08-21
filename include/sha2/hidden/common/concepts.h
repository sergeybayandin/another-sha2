#ifndef CONCEPTS_H
#define CONCEPTS_H

namespace sha2::hidden::common {

template <class R>
concept ContiguousBytesRange = std::ranges::contiguous_range<R> &&
                               std::ranges::sized_range<R> &&
                               std::same_as<std::remove_cv_t<typename std::remove_cvref_t<R>::value_type>, std::byte>;

template <class W>
concept AvailableWordType = std::same_as<W, std::uint32_t> || std::same_as<W, std::uint64_t>;

} // common

#endif // CONCEPTS_H
