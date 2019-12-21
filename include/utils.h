#pragma once
#ifdef DEBUG
#   include <iostream> // std::cerr
#   include <utility> // std::forward
#   include <mutex> // std::mutex
#   include <thread> // std::this_thread::get_id
#   include <initializer_list> // std::initializer_list
#endif
#include <cstddef> // std::size_t
#include <iostream> // std::ostream

namespace rn1 {
	class Dimension final {
	public:
		using this_type = Dimension;
		using value_type = int;
		Dimension(value_type x, value_type y) noexcept;
		value_type getX() const noexcept;
		value_type getY() const noexcept;

        this_type &operator+=(Dimension const &other);
        this_type &operator-=(Dimension const &other);
        this_type &operator*=(double factor);
        this_type &operator/=(double divisor);

        friend bool operator==(Dimension const &a, Dimension const &b);
        friend bool operator<(Dimension const &a, Dimension const &b);

	private:
		value_type x_;
		value_type y_;
	};

    bool operator!=(Dimension const &a, Dimension const &b);
    bool operator>(Dimension const &a, Dimension const &b);
    bool operator<=(Dimension const &a, Dimension const &b);
    bool operator>=(Dimension const &a, Dimension const &b);
    Dimension operator+(Dimension const &a, Dimension const &b);
    Dimension operator-(Dimension const &a, Dimension const &b);
    Dimension operator*(Dimension const &a, double factor);
    Dimension operator/(Dimension const &a, double divisor);
    std::ostream &operator<<(std::ostream &os, Dimension const &dim);

    template <class ...Args>
#if !defined(DEBUG) && defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable:4100) // unreferenced formal parameter
#endif
    void printDebug(Args &&...args) noexcept {
#if !defined(DEBUG) && defined(_MSC_VER)
#   pragma warning(pop)
#endif
#   ifdef DEBUG
        static std::mutex mu{ };
        std::unique_lock<decltype(mu)> lck{ mu };
        static_cast<void>(std::initializer_list<int>{
            (std::cerr << args, 0)...
        });
        std::cerr << " ID: " << std::this_thread::get_id() << '\n';
#   else // in release mode
        // do nothing
#   endif
    } // END of printDebug

    std::size_t getProducerCount(int argc, char **argv) noexcept;
    Dimension getDesktopResolution();

} /* namespace rn1 */
