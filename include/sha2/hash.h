#ifndef HASH_H
#define HASH_H

#include <span>
#include <array>
#include <optional>
#include <algorithm>
#include <string_view>

namespace sha2 {

namespace details {

inline constexpr char to_hexi(std::byte byte) noexcept {
    const auto integer = std::to_integer<int>(byte);
    return integer < 10 ? '0' + integer : 'a' + integer - 10;
}

} // details

template <std::size_t Size>
class Hash final {
  public:
      constexpr Hash() noexcept {
          storage_.fill(std::byte(0));
      }

      [[ nodiscard ]]
      constexpr std::string to_str() const {
          std::string shash;

          shash.reserve(Size * 2);

          for (auto byte : as_bytes()) {
              shash += details::to_hexi(byte >> 4);
              shash += details::to_hexi(byte & std::byte(0xf));
          }

          return shash;
      }

      [[ nodiscard ]]
      inline constexpr auto as_bytes() noexcept {
          return std::span(storage_);
      }

      [[ nodiscard ]]
      inline constexpr auto as_bytes() const noexcept {
          return std::span(storage_);
      }

      [[ nodiscard ]]
      static constexpr std::optional<Hash> from_str(std::string_view str) noexcept {
          if (shexi.size() != Size * 2) {
              return std::nullopt;
          }

          Hash hash;

          for (auto &byte : hash.as_bytes()) {
              
          }

          return hash;
      }

      template <std::size_t Extent> [[ nodiscard ]]
      static constexpr std::optional<Hash> from_bytes(const std::span<std::byte, Extent> &bytes) noexcept {
          if (bytes.size() != Size) {
              return std::nullopt;
          }

          Hash hash;

          std::ranges::copy(bytes, hash.as_bytes().begin());

          return hash;
      }

  private:
      std::array<std::byte, Size> storage_;
};

} // sha2

#endif // HASH_H
