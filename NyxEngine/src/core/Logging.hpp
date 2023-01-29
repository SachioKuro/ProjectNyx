#pragma once

#ifdef NYX_DEBUG
    constexpr int32_t basename_index(const char* const path, const int32_t index = 0, const int32_t slash_index = -1) {
        return path[index]
            ? (path[index] == '/' or path[index] == '\\'
                ? basename_index(path, index + 1, index)
                : basename_index(path, index + 1, slash_index)
                )
            : (slash_index + 1)
            ;
    }
    
    #define STRINGIZE_DETAIL(x) #x
    #define STRINGIZE(x) STRINGIZE_DETAIL(x)

    #define __FILELINE__ [](){ \
        static const int32_t basename_idx = basename_index(__FILE__); \
        static_assert (basename_idx >= 0, "compile-time basename"); \
        std::stringstream ss; \
        ss << std::string(__FILE__).substr(basename_idx) << ':' << STRINGIZE(__LINE__) << ": "; \
        return ss.str(); \
    }()

    #define NYX_LOG(level, message, ...) \
            {std::string msg = "[%s] %s "; \
            msg = msg.append(std::string(message)); \
            printf(msg.c_str(), level, __FILELINE__.c_str(), ##__VA_ARGS__);}
    #define NYX_DEBUG_P(message, ...)    NYX_LOG("DEBUG", message, ##__VA_ARGS__)
    #define NYX_INFO(message, ...)       NYX_LOG("INFO", message, ##__VA_ARGS__)
    #define NYX_WARNING(message, ...)    NYX_LOG("WARNING", message, ##__VA_ARGS__)
    #define NYX_ERROR(message, ...)      NYX_LOG("ERROR", message, ##__VA_ARGS__)
#else
    #define NYX_DEBUG_P(message, ...)
    #define NYX_INFO(message, ...)
    #define NYX_WARNING(message, ...)
    #define NYX_ERROR(message, ...)
#endif