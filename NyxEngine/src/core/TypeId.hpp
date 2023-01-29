#pragma once

#include "../pch.hpp"

namespace NYX {
    constexpr uint64_t INVALID_ID = 0;

    NYX_INLINE const uint64_t GetUniqueTypeID() {
        static uint64_t type = 0u;
        return ++type;
    }

    template <typename T>
    NYX_INLINE const uint64_t TypeID() {
        static const uint64_t type = GetUniqueTypeID();
        return type;
    }
}