#include "../include/Output.h"
#include "../include/ThreadContainer.h"
#include <utility> // std::move
#ifdef _MSC_VER
#   pragma warning(push)
#   pragma warning(disable:4100) // unreferenced formal parameter
#   pragma warning(disable:4244) // possible info loss
#   pragma warning(disable:4458) // declaration hides member
#endif
#include <FL/Fl.H>
#ifdef _MSC_VER
#   pragma warning(pop)
#endif

namespace rn1 {
	Output::Output(Dimension pos, Dimension size, string_type title, ThreadContainer &thCont)
		: title_{ std::move(title) },
		  disp_{ pos.getX(), pos.getY(), size.getX(), size.getY(), title_.data() },
          thCont_{ thCont } {
			  disp_.buffer(buf_);
		  }

	void Output::clear() noexcept {
		currentText_ = "";
		cpyCurTxtToBuf();
	}

	void Output::append(string_type const &str) {
		currentText_.append(str);
		cpyCurTxtToBuf();
	}

	void Output::cpyCurTxtToBuf() noexcept {
        buf_.text(currentText_.data());
        Fl::check(); // From the documentation: "Calling this during a big calculation will keep the screen up to date and the interface responsive"
	}
} /* namespace rn1 */
