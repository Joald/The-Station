#ifndef THE_STATION_RESOURCE_POOL_H
#define THE_STATION_RESOURCE_POOL_H

#include <memory>
#include <unordered_map>

template <class T>
class ResourcePool {
public:
    using ptr = std::shared_ptr<T>;
    using storage_t = std::unordered_map<std::string_view, ptr>;
protected:

    storage_t& getStorage() {
        return storage;
    }

    virtual typename storage_t::iterator loadResource(std::string_view id) = 0;

public:
    ptr getResourceById(std::string_view id) {
        auto iter = storage.find(id);
        if (iter == storage.end()) {
            iter = loadResource(id);
        }
        return iter->second;
    }

private:
    storage_t storage;
};


#endif //THE_STATION_RESOURCE_POOL_H
