#pragma once
#include <string>
#ifdef _MSC_VER
#   pragma warning(push)
#   pragma warning(disable:4100) // unreferenced formal parameter
#   pragma warning(disable:4244) // possible info loss
#   pragma warning(disable:4458) // declaration hides member
#endif
#include <FL/Fl_Text_Display.H>
#ifdef _MSC_VER
#   pragma warning(pop)
#endif
#include "../include/utils.h"

namespace rn1 {
    class ThreadContainer;

	class Output final {
	public:
		using this_type = Output;
		using string_type = std::string;
		Output(Dimension pos, Dimension size, string_type title, ThreadContainer &thCont);
		void clear() noexcept;
		void append(string_type const &str);
	private:
		void cpyCurTxtToBuf() noexcept;

		string_type title_;
		Fl_Text_Buffer buf_;
		Fl_Text_Display disp_;
		string_type currentText_;
        ThreadContainer &thCont_;
	};
} /* namespace rn1 */
