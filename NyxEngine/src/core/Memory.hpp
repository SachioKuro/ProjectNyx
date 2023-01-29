#pragma once

#ifdef NYX_DEBUG
    #define NYX_DELETE(object) \
            {if (object != nullptr) { \
                delete object; \
                object = nullptr; \
            } else { \
                NYX_ERROR("Tried to delete nullptr: %s", object); \
            }}
#else
    #define NYX_DELETE(object) \
            {delete object; \
            object = nullptr;}
#endif