#include <Logging/Logger.h>
#include <random>
#include <functional>
#include <cstring>
#include "GameObject.h"

namespace {
template <typename T = std::mt19937>
auto random_generator() -> T {
    auto constexpr seed_bytes = sizeof(typename T::result_type) * T::state_size;
    auto constexpr seed_len = seed_bytes / sizeof(std::seed_seq::result_type);
    auto seed = std::array<std::seed_seq::result_type, seed_len>();
    auto dev = std::random_device();
    std::generate_n(begin(seed), seed_len, std::ref(dev));
    auto seed_seq = std::seed_seq(begin(seed), end(seed));
    return T{seed_seq};
}

std::string generateRandom(int len = 32) {
    static constexpr auto chars =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    thread_local auto rng = random_generator<>();
    thread_local auto dist = std::uniform_int_distribution{{}, std::strlen(chars) - 1};
    auto result = std::string(len, '\0');
    std::generate_n(begin(result), len, [&] { return chars[dist(rng)]; });
    return result;
}
} // namespace

GameObject::GameObject(std::string id) : ID(std::move(id)) {
    if (!ID.empty() and ids.contains(ID)) {
        logger(WARNING) << "Manually-set id " << ID << " duplicated, overwriting.";
    }

    while (ID.empty() or ids.contains(ID)) {
        ID = generateRandom();
    }
    ids.emplace(ID);
}

std::string_view GameObject::generateID(std::string_view key) {
    if (!idCache.contains(key)) {
        using namespace std::string_literals;
        idCache[key] = getID().data() + "_"s + key.data();
    }
    return idCache[key];
}