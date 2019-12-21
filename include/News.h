#pragma once
#include <string> // std::string

namespace rn1 {
	enum class News {
		Info, Warn, Corr
	};

	auto const amtOfNewsTypes = 3;
	using String = std::string;
	using NewsIndexType = int;

	String toString(News news);
	NewsIndexType toIndex(News news) noexcept;
	News toNews(NewsIndexType idx);
	String toString(News news, String const &text);

} /* namespace rn1 */
