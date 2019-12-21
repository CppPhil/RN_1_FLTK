#include <stdexcept> // std::logic_error
#include "../include/News.h"

namespace rn1 {
	String toString(News news) {
		switch (news) {
		case News::Info : return "INFO";
		case News::Warn : return "WARN";
		case News::Corr : return "CORR";
		default :
			throw std::logic_error{ "invalid news in rn1::asString(News)" };
		}
	}

	NewsIndexType toIndex(News news) noexcept {
		return static_cast<NewsIndexType>(news);
	}

	News toNews(NewsIndexType idx) {
		switch (idx) {
		case 0 : return News::Info;
		case 1 : return News::Warn;
		case 2 : return News::Corr;
		default :
			throw std::logic_error{ "invalid index in rn1::toNews(NewsIndexType)" };
		}
	}

	String toString(News news, String const &text) {
		auto str = toString(news);
		str.append("\t");
		str.append(text);
		str.append("\n");
		return str;
	}

} /* namespace rn1 */
