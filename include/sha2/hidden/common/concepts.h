#ifndef CONCEPTS_H
#define CONCEPTS_H

namespace sha2::hidden::common {

template <class R>
concept ContiguousBytesRange = std::ranges::contiguous_range<R> &&
                               std::ranges::sized_range<R> &&
                               std::same_as<std::remove_cv_t<typename std::remove_cvref_t<R>::value_type>, std::byte>;

} // common

#endif // CONCEPTS_H
