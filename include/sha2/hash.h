#ifndef HASH_H
#define HASH_H

#include <span>
#include <array>
#include <ranges>
#include <string>
#include <optional>
#include <algorithm>
#include <string_view>

#include "utils/hash.h"

namespace sha2 {

template <std::size_t Size>
class Hash final {
  public:
      inline Hash() noexcept {
          storage_.fill(std::byte(0));
      }

      template <utils::ContiguousBytesRange R> [[ nodiscard ]]
      static std::optional<Hash> from_range(R &&range) noexcept {
          if (range.size() != Size) {
              return std::nullopt;
          }

          Hash hash;

          std::ranges::copy(range, hash.as_bytes().begin());

          return hash;
      }

      [[ nodiscard ]]
      static std::optional<Hash> from_str(std::string_view str) noexcept {
          if (str.size() != Size * 2) {
              return std::nullopt;
          }

          Hash hash;
          auto it = str.begin();

          for (auto &byte : hash.as_bytes()) {
              if (!std::isxdigit(*it) || !std::isxdigit(*(it + 1))) {
                  return std::nullopt;
              }

              byte = utils::to_byte(std::tolower(*it), std::tolower(*(it + 1)));

              it += 2;
          }

          return hash;
      }     

      [[ nodiscard ]]
      std::string to_str() const {
          std::string str;

          str.reserve(Size * 2);

          for (auto byte : as_bytes()) {
              str += utils::to_hex(std::to_integer<int>(byte >> 4));
              str += utils::to_hex(std::to_integer<int>(byte & std::byte(0xf)));
          }

          return str;
      }

      [[ nodiscard ]]
      inline auto as_bytes() noexcept {
          return std::span(storage_);
      }

      [[ nodiscard ]]
      inline auto as_bytes() const noexcept {
          return std::span(storage_);
      }

      inline bool operator==(const Hash &other) const noexcept {
          return storage_ == other.storage_;
      }

  private:
      std::array<std::byte, Size> storage_;
};

} // sha2

#endif // HASH_H
