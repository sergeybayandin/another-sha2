#ifndef SHA512_H
#define SHA512_H

namespace sha2 {

class Sha512 final {
  public:
      using OutputHash = sha2::Hash<64>;

      inline Sha512() noexcept;

      inline Sha512 &reset() noexcept;
      OutputHash finalize() noexcept;

      template <utils::ContiguousBytesRange R>
      Sha512 &update(R &&range) noexcept;

      template <utils::ContiguousBytesRange R>
      OutputHash operator()(R &&range) noexcept;

  private:
      hidden::Sha2StateEngine<
          hidden::round<80>,
          hidden::chunk_size<128>,
          hidden::WordType<std::uint64_t>
      > state_engine_;
};

} // sha2

#endif // SHA512_H
