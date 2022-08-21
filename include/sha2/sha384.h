#ifndef SHA384_H
#define SHA384_H

#include "hash.h"

#include "hidden/sha2_state_engine.h"

namespace sha2 {

class Sha384 final {
  public:
      using OutputHash = sha2::Hash<48>;

      Sha384() noexcept;

      [[ nodiscard ]]
      OutputHash finalize() noexcept;

      template <hidden::common::ContiguousBytesRange R>
      inline Sha384 &update(R &&range) noexcept {
          state_engine_.run(std::forward<R>(range));
          return *this;
      }

      inline Sha384 &update(std::string_view str) noexcept {
          return update(std::as_bytes(std::span(str)));
      }

  private:
      hidden::Sha512StateEngine state_engine_;
};

} // sha2

#endif // SHA384_H
