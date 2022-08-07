#ifndef SHA256_H
#define SHA256_H

namespace sha2 {

template <std::size_t Size>
class Hash;

} // sha2

namespace sha2 {

class Sha256 final {
  public:
      using OutputHash = sha2::Hash<32>;

      inline Sha256() noexcept;

      inline Sha256 &reset() noexcept;
      OutputHash finalize() noexcept;

      template <hidden::common::ContiguousBytesRange R>
      Sha256 &update(R &&range) noexcept;

      template <hidden::common::ContiguousBytesRange R>
      OutputHash operator()(R &&range) noexcept;

  private:
      hidden::Sha2StateEngine<
          hidden::common::rounds<64>,
          hidden::common::chunk_size<64>,
          hidden::common::WordType<std::uint32_t>
      > state_engine_;
};

} // sha2

#endif // SHA256_H
