#include "ResourceNotFoundError.h"

const char* ResourceNotFoundError::what() const noexcept {
    return std::runtime_error::what();
}
