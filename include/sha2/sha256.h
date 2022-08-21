#ifndef SHA256_H
#define SHA256_H

#include "hash.h"

#include "hidden/sha2_state_engine.h"

namespace sha2 {

class Sha256 final {
  public:
      using OutputHash = sha2::Hash<32>;

      Sha256() noexcept;

      [[ nodiscard ]]
      OutputHash finalize() noexcept;

      template <hidden::common::ContiguousBytesRange R>
      inline Sha256 &update(R &&range) noexcept {
          state_engine_.run(std::forward<R>(range));
          return *this;
      }

      inline Sha256 &update(std::string_view str) noexcept {
          return update(std::as_bytes(std::span(str)));
      }

  private:
      hidden::Sha256StateEngine state_engine_;
};

} // sha2

#endif // SHA256_H
