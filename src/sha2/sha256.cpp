#include "sha2/sha256.h"

namespace sha2 {

Sha256::Sha256() noexcept
    : state_engine_(hidden::common::sha256_initializers)
{}

Sha256::OutputHash Sha256::finalize() noexcept {
    auto chunked   = state_engine_.chunked();
    auto unchunked = state_engine_.unchunked();

    unchunked.front() = std::byte(0x80);

    std::fill(unchunked.begin() + 1, unchunked.end(), std::byte(0));

    if (chunked.size() >= 56) {
        state_engine_.transform_chunk();
        std::ranges::fill(state_engine_.chunk().first<56>(), std::byte(0));
    }

    hidden::common::unpack_as<std::uint64_t>(
        unchunked.last<8>(), 
        (state_engine_.transformed_bytes_count() + chunked.size()) * 8
    );

    state_engine_.transform_chunk();

    OutputHash hash;

    auto bytes  = hash.as_bytes();
    auto states = state_engine_.states();

    for (auto i : std::views::iota(0, 8)) {
        hidden::common::unpack_as(bytes.subspan(i * 4, 4), states[i]);
    }

    state_engine_.initialize_with(hidden::common::sha256_initializers);

    return hash;
}

} // sha2
