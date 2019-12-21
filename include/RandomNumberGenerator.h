#pragma once
#include <random> // std::mt19937, std::random_device
#include <type_traits> // std::is_integral
namespace rn1 {

class RandomNumberGenerator {
public:

    RandomNumberGenerator() : rd_{ }, mt_ { rd_() } { }

	template <class Numeric>
	Numeric getRandomNumber(Numeric lowerBound, Numeric upperBound) {
		static_assert(std::is_integral<Numeric>::value,
				"Numeric in RandomNumberGenerator::getRandomNumber was not an integral type");
		std::uniform_int_distribution<Numeric> dist{ lowerBound, upperBound };
		return dist(mt_);
	}

private:
    std::random_device rd_;
    std::mt19937 mt_;
};

} /* namespace rn1 */

