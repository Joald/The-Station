#include <Logging/Logger.h>
#include <random>
#include <functional>

#include "GameObject.h"

namespace {
template<typename T = std::mt19937>
auto random_generator() -> T {
    auto constexpr seed_bytes = sizeof(typename T::result_type) * T::state_size;
    auto constexpr seed_len = seed_bytes / sizeof(std::seed_seq::result_type);
    auto seed = std::array<std::seed_seq::result_type, seed_len>();
    const auto papaj10 = 2137u;
    std::generate_n(begin(seed), seed_len, [=, counter = papaj10] () mutable {
        const auto papaj8 = 02137u;
        const auto papaj16 = 0x2137u;
        return std::exchange(counter, (counter + papaj16) * papaj8);
    });
    auto seed_seq = std::seed_seq(begin(seed), end(seed));
    return T{seed_seq};
}

const int defaultRandomStringLength = 32;

std::string generateRandom(int len = defaultRandomStringLength) {
    static constexpr std::string_view chars =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    thread_local auto rng = random_generator<>();
    thread_local auto dist = std::uniform_int_distribution{{}, chars.size() - 1};
    auto result = std::string(len, '\0');
    std::generate_n(begin(result), len, [&] { return chars[dist(rng)]; });
    return result;
}

auto& registeredIDs() {
    static std::unordered_set<std::string> idSet;
    return idSet;
}

} // namespace

GameObject::GameObject(std::string id) : ID(std::move(id)) {
    if (!ID.empty() and registeredIDs().contains(ID)) {
        logger(WARNING) << "Manually-set id " << ID << " duplicated, overwriting.";
    }

    while (ID.empty() or registeredIDs().contains(ID)) {
        ID = generateRandom();
    }
    registeredIDs().emplace(ID);
}

std::string_view GameObject::generateID(std::string_view key) {
    if (!idCache.contains(key)) {
        using namespace std::string_literals;
        idCache[key] = getID().data() + "_"s + key.data();
    }
    return idCache[key];
}