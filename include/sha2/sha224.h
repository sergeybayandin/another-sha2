#ifndef SHA224_H
#define SHA224_H

#include "hash.h"

#include "hidden/sha2_state_engine.h"

namespace sha2 {

class Sha224 final {
  public:
      using OutputHash = sha2::Hash<28>;

      Sha224() noexcept;

      [[ nodiscard ]]
      OutputHash finalize() noexcept;

      template <hidden::common::ContiguousBytesRange R>
      inline Sha224 &update(R &&range) noexcept {
          state_engine_.run(std::forward<R>(range));
          return *this;
      }

      inline Sha224 &update(std::string_view str) noexcept {
          return update(std::as_bytes(std::span(str)));
      }

  private:
      hidden::Sha256StateEngine state_engine_;
};

} // sha2

#endif // SHA224_H
