#ifndef THE_STATION_RESOURCE_POOL_H
#define THE_STATION_RESOURCE_POOL_H

#include <memory>
#include <unordered_map>

template <class T>
class ResourcePool {
public:
    typedef std::shared_ptr<T> ptr;
    typedef std::unordered_map<std::string, ptr> storage_t;
protected:
    storage_t storage;
    virtual typename storage_t::iterator loadResource(const std::string& id) = 0;

public:
    ptr getResourceById(const std::string& id) {
        auto iter = storage.find(id);
        if (iter == storage.end()) {
            iter = loadResource(id);
        }
        return iter->second;
    }

};


#endif //THE_STATION_RESOURCE_POOL_H
