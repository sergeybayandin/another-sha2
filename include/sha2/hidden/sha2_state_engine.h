#ifndef SHA2_EXECUTOR_H
#define SHA2_EXECUTOR_H

#include "common/consts.h"

namespace sha2::hidden {

template <
    std::size_t rounds,
    std::size_t chunk_size,
    class       WordType
>
class Sha2StateEngine final {
  public:
      inline Sha2StateEngine(const std::initializer_list<WordType> &initializers) noexcept {
          initialize_with(initializers);
      }

      void initialize_with(const std::initializer_list<WordType> &initializers) noexcept {
          std::ranges::copy(initializers, h_.begin())
          message_size_ = chunk_size_ = 0;
      }

      void transform_chunk() noexcept {
          std::array<WordType, rounds> words;
          std::array<WordType, 8>      h;

          
          for (auto i : std::views::iota(16, rounds)) {

          }

          for (auto i : std::views::iota(0, rounds)) {

          }

          for (auto i : std::views::iota(0, 8)) {
              h_[i] += h[i];
          }
      }

      inline auto h() noexcept {
          return std::span(h_);
      }

      inline auto chunk() noexcept {
          return std::span(chunk_);
      }

      inline std::size_t message_size() const noexcept {
          return message_size_;
      }

      inline std::size_t chunk_size() const noexcept {
          return chunk_size_;
      }

  private:
      std::array<WordType, 8> h_;
      std::array<std::byte, chunk_size> chunk_;

      std::size_t message_size_, chunk_size_;
};

} // hidden

#endif // SHA2_EXECUTOR_H
