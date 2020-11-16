//
// Created by moaty on 11.11.20.
//

#ifndef LWM2M_CLIENT_CPP_STRING_H
#define LWM2M_CLIENT_CPP_STRING_H

#include <sys/util.h>
#include <string.h>

namespace nx {

    /***
     * @brief template class to help create pre-allocated strings at compile time, and make it easy to use string functions generally
     * @tparam str_len the max length of the string buffer. once buffer created, it cannot be expanded nor shrunk
     */
    template<size_t str_len>
    class string {
    public:
        string() = default;
        explicit string(const char* str);
        ~string() = default;

        const char* to_char_array() const;

        string& operator = (const char* str);

    public:
        const size_t str_length{str_len};
    private:
        char str_[str_len]{0};
    };

    template<size_t str_len>
    string<str_len>::string(const char *str) {
        memcpy(str_, str, MIN(str_length, strlen(str)));
    }

    template<size_t str_len>
    string<str_len> &string<str_len>::operator=(const char *str) {
        memcpy(str_, str, str_length);
        return *this;
    }

    template<size_t str_len>
    const char *string<str_len>::to_char_array() const {
        return str_;
    }
}


#endif //LWM2M_CLIENT_CPP_STRING_H
