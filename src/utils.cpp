#include "../include/utils.h"
#include <cstring> // std::strcmp
#include <tuple> // std::tie
#ifdef _WIN32
#   include <Windows.h>
#elif defined(__linux__)
#   include <X11/Xlib.h>
#endif
#include <stdexcept> // std::logic_error
#include <iostream> // std::cerr

namespace rn1 {
    Dimension::Dimension(value_type x, value_type y) noexcept
        : x_{ x }, y_{ y } { }

    Dimension::value_type Dimension::getX() const noexcept {
        return x_;
    }

    Dimension::value_type Dimension::getY() const noexcept {
        return y_;
    }

    Dimension::this_type &Dimension::operator+=(Dimension const &other) {
        *this = *this + other;
        return *this;
    }

    Dimension::this_type &Dimension::operator-=(Dimension const &other) {
        *this = *this - other;
        return *this;
    }

    Dimension::this_type &Dimension::operator*=(double factor) {
        *this = *this * factor;
        return *this;
    }

    Dimension::this_type &Dimension::operator/=(double divisor) {
        *this = *this / divisor;
        return *this;
    }

    bool operator==(Dimension const &a, Dimension const &b) {
        return std::tie(a.x_, a.y_) == std::tie(b.x_, b.y_);
    }

    bool operator!=(Dimension const &a, Dimension const &b) {
        return !(a == b);
    }

    bool operator<(Dimension const &a, Dimension const &b) {
        return std::tie(a.x_, a.y_) < std::tie(b.x_, b.y_);
    }

    bool operator>(Dimension const &a, Dimension const &b) {
        return b < a;
    }

    bool operator<=(Dimension const &a, Dimension const &b) {
        return !(b < a);
    }

    bool operator>=(Dimension const &a, Dimension const &b) {
        return !(a < b);
    }

    Dimension operator+(Dimension const &a, Dimension const &b) {
        return { a.getX() + b.getX(), a.getY() + b.getY() };
    }

    Dimension operator-(Dimension const &a, Dimension const &b) {
        return { a.getX() - b.getX(), a.getY() - b.getY() };
    }

    Dimension operator*(Dimension const &a, double factor) {
        return { static_cast<Dimension::value_type>(a.getX() * factor),
            static_cast<Dimension::value_type>(a.getY() * factor) };
    }

    Dimension operator/(Dimension const &a, double divisor) {
        if (divisor == 0.0) {
            throw std::logic_error{ "divisor in operator/ was 0.0" };
        }
        return { static_cast<Dimension::value_type>(a.getX() / divisor),
            static_cast<Dimension::value_type>(a.getY() / divisor) };
    }

    std::ostream &operator<<(std::ostream &os, Dimension const &dim) {
    	return os << "x: " << dim.getX() << " y: " << dim.getY();
    }

    std::size_t getProducerCount(int argc, char **argv) noexcept {
        static auto constexpr text = "please enter -p followed by the amount of producer threads.\n"
            "Like so: ./rn1.out -p 2\n"; // error text
        if (argc < 3) { // to prevent out of bounds access
            goto err;
        }

        if (std::strcmp(argv[1], "-p") == 0) {
            return argv[2][0] - '0'; // return the producer count if it was found
        }

    err: // error case
        std::cerr << text; // print the text
        return 0U; // 0U indicates failure to extract producerCount
    } // END of getProducerCount

    Dimension getDesktopResolution() {
#   ifdef _WIN32
        return { GetSystemMetrics(SM_CXSCREEN),
            GetSystemMetrics(SM_CYSCREEN) };
#   elif defined(__linux__)
        auto disp = XOpenDisplay(nullptr);
        if (disp == nullptr) {
            throw std::runtime_error{ "could not get disp from XOpenDisplay in getDesktopResolution" };
        }
        auto scrn = DefaultScreenOfDisplay(disp);
        return { scrn->width, scrn->height };
#   endif
    }

} /* namespace rn1 */
