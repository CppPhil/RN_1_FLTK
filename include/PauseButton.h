#pragma once
#ifdef _MSC_VER
#   pragma warning(push)
#   pragma warning(disable:4100) // unreferenced formal parameter
#   pragma warning(disable:4244) // possible info loss
#   pragma warning(disable:4458) // declaration hides member
#endif
#include <FL/Fl_Toggle_Button.H>
#ifdef _MSC_VER
#   pragma warning(pop)
#endif
#include <string> // std::string
#include "../include/utils.h"

namespace rn1 {
    class PauseStatus;

    class PauseButton final {
    public:
        using this_type = PauseButton;
        using String = std::string;
        using ToggleButton = Fl_Toggle_Button;

        PauseButton(Dimension pos, Dimension siz, PauseStatus &pauseStatus);

    private:
        static void pauseButtonClicked(Fl_Widget *widget, void *data);
        String const *label_;
        String const toggleOn_ = "pause producers";
        String const toggleOff_ = "resume producers";
        ToggleButton toggleButton_;
        PauseStatus &pauseStatus_;
    }; // END of class PauseButton

} /* namespace rn1 */
