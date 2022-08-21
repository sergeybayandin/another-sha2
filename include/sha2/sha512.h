#ifndef SHA512_H
#define SHA512_H

#include "hash.h"

#include "hidden/sha2_state_engine.h"

namespace sha2 {

class Sha512 final {
  public:
      using OutputHash = sha2::Hash<64>;

      Sha512() noexcept;
 
      [[ nodiscard ]]
      OutputHash finalize() noexcept;

      template <hidden::common::ContiguousBytesRange R>
      inline Sha512 &update(R &&range) noexcept {
          state_engine_.run(std::forward<R>(range));
          return *this;
      }

      inline Sha512 &update(std::string_view str) noexcept {
          return update(std::as_bytes(std::span(str)));
      }

  private:
      hidden::Sha512StateEngine state_engine_;
};

} // sha2

#endif // SHA512_H
