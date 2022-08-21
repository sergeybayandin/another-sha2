#ifndef SHA2_STATE_ENGINE_H
#define SHA2_STATE_ENGINE_H

#include <ranges>

#include "common/consts.h"

namespace sha2::hidden {

template <
    std::size_t               rounds,
    std::size_t               chunk_size,
    common::AvailableWordType WordType
>
class Sha2StateEngine final {
  public:
      inline Sha2StateEngine(const std::initializer_list<WordType> &initializers) noexcept {
          initialize_with(initializers);
      }

      void initialize_with(const std::initializer_list<WordType> &initializers) noexcept {
          std::ranges::copy(initializers, states_.begin());
          transformed_bytes_count_ = chunked_bytes_count_ = 0;
      }

      void transform_chunk() noexcept {
          std::array<WordType, rounds> words;
          std::array<WordType, 8>      states;
          
          WordType t1, t2;

          for (auto i : std::views::iota(0, 16)) {
              words[i] = common::pack_as<WordType>(chunk().subspan(sizeof(WordType) * i, sizeof(WordType)));
          }

          for (auto i : std::views::iota(std::size_t(16), rounds)) {
              words[i] = words[i - 16] + common::s0(words[i - 15]) + words[i - 7]  +
                         common::s1(words[i -  2]);
          }

          std::ranges::copy(states_, states.begin());

          for (auto i : std::views::iota(std::size_t(0), rounds)) {
              t2 = common::sig0(states[0]) + common::ma(states[0], states[1], states[2]);
              
              t1 = states[7] + 
                   common::sig1(states[4]) + 
                   common::ch(states[4], states[5], states[6]) + 
                   common::consts<WordType, rounds>[i] +
                   words[i];

              states[7] = states[6];
              states[6] = states[5];
              states[5] = states[4];
              states[4] = states[3] + t1;
              states[3] = states[2];
              states[2] = states[1];
              states[1] = states[0];
              states[0] = t1 + t2;
          }

          for (auto i : std::views::iota(0, 8)) {
              states_[i] += states[i];
          }
      }

      template <common::ContiguousBytesRange R>
      void run(R &&range) noexcept {
          auto begin = range.begin(), end = range.end();

          if (chunked_bytes_count_) {
              auto advance = std::copy_n(
                  begin,
                  std::min(chunk_size - chunked_bytes_count_, range.size()),
                  unchunked().begin()
              ) - unchunked().begin();
              
              begin += advance;
              chunked_bytes_count_ += advance;

              if (chunked_bytes_count_ == chunk_size) {           
                  transform_chunk();
                  transformed_bytes_count_ += chunked_bytes_count_;
                  chunked_bytes_count_ = 0;
              }
          }

          for (; end - begin > chunk_size; begin += chunk_size) {
              std::copy_n(begin, chunk_size, chunk_.begin());            
              transform_chunk();
          }

          chunked_bytes_count_      = end - begin;
          transformed_bytes_count_ += begin - range.begin();

          std::copy(begin, end, chunk_.begin());
      }

      inline auto states() noexcept {
          return std::span(states_);
      }

      inline auto chunk() noexcept {
          return std::span(chunk_);
      }

      inline auto chunked() noexcept {
          return chunk().first(chunked_bytes_count_);
      }

      inline auto unchunked() noexcept {
          return chunk().last(chunk_size - chunked_bytes_count_);
      }

      inline auto transformed_bytes_count() const noexcept {
          return transformed_bytes_count_;
      }

  private:
      std::array<WordType, 8> states_;
      std::array<std::byte, chunk_size> chunk_;

      std::size_t transformed_bytes_count_, chunked_bytes_count_;
};

using Sha256StateEngine = Sha2StateEngine<
    common::rounds<64>,
    common::chunk_size<64>,
    common::WordType<std::uint32_t>
>;

using Sha512StateEngine = Sha2StateEngine<
    common::rounds<80>,
    common::chunk_size<128>,
    common::WordType<std::uint64_t>
>;

} // hidden

#endif // SHA2_STATE_ENGINE_H
