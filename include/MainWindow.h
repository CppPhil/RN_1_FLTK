#pragma once
#ifdef _MSC_VER
#   pragma warning(push)
#   pragma warning(disable:4100) // unreferenced formal parameter
#   pragma warning(disable:4244) // possible info loss
#   pragma warning(disable:4458) // declaration hides member
#endif
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#ifdef _MSC_VER
#   pragma warning(pop)
#endif
#include <string> // std::string, std::to_string
#include "../include/utils.h"
#include "../include/Output.h"
#include "../include/News.h"
#include "../include/ThreadContainer.h"
#include "../include/PauseButton.h"

namespace rn1 {
    class MainWindow final {
    public:
        using this_type = MainWindow;
        using string_type = std::string;

        MainWindow(ThreadContainer::size_type threadCount,
                   Dimension windowSize, string_type windowTitle,
                   Dimension inpPos, Dimension inpSize, string_type inpLabel,
                   Dimension butPos, Dimension butSize, string_type butLabel,
                   Dimension outFieldPos, Dimension outFieldSize, string_type outFieldTxt,
                   Dimension choicePos, Dimension choiceSize, string_type choiceLabel,
                   Dimension pauseButPos, Dimension pauseButSize);
        static int run();
        void show();

    private:
        static void buttonClicked(Fl_Widget *widget, void *data);
        static void exitClicked(Fl_Widget *widget, void *data);

        string_type windowLabel_;
        Fl_Window window_;
        string_type userInputLabel_;
        Fl_Input userInput_;
        string_type sendInputButtonLabel_;
        Fl_Button sendInputButton_;
        Output outField_;
        string_type choiceLabel_;
        Fl_Choice choice_;
        string_type choiceString_;
        ThreadContainer::prod_func_type prodFunc_;
        ThreadContainer::cons_func_type consFunc_;
        ThreadContainer threads_;
        PauseButton pauseButton_;
    };
} /* namespace rn1 */
