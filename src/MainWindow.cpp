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
#include <utility> // std::move
#include <functional> // std::bind
#include <stdexcept> // std::runtime_error
#include "../include/MainWindow.h"
#include "../include/Producer.h"
#include "../include/Consumer.h"
#include "../include/News.h"

namespace rn1 {
    MainWindow::MainWindow(ThreadContainer::size_type threadCount,
                           Dimension windowSize, string_type windowTitle,
                           Dimension inpPos, Dimension inpSize, string_type inpLabel,
                           Dimension butPos, Dimension butSize, string_type butLabel,
                           Dimension outFieldPos, Dimension outFieldSize, string_type outFieldTxt,
                           Dimension choicePos, Dimension choiceSize, string_type choiceLabel,
                           Dimension pauseButPos, Dimension pauseButSize)
        : windowLabel_{ std::move(windowTitle) },
          window_{ windowSize.getX(), windowSize.getY(), windowLabel_.data() },
          userInputLabel_{ std::move(inpLabel) },
          userInput_{ inpPos.getX(), inpPos.getY(), inpSize.getX(), inpSize.getY(), userInputLabel_.data() },
          sendInputButtonLabel_{ std::move(butLabel) },
          sendInputButton_{ butPos.getX(), butPos.getY(),
              butSize.getX(), butSize.getY(), sendInputButtonLabel_.data() },
          outField_{ std::move(outFieldPos), std::move(outFieldSize), std::move(outFieldTxt),
              threads_ },
          choiceLabel_{ std::move(choiceLabel) },
          choice_{ choicePos.getX(), choicePos.getY(), choiceSize.getX(), choiceSize.getY() },
          prodFunc_{ &prodFunc },
          consFunc_{ &consFunc },
          threads_{ threadCount, prodFunc_, consFunc_, outField_ },
          pauseButton_{ std::move(pauseButPos), std::move(pauseButSize), threads_.getPauseStatus() } {
        sendInputButton_.callback(&this_type::buttonClicked, this);
        for (auto i = 0; i < amtOfNewsTypes; ++i) {
            choiceString_.append(toString(toNews(i)));
            choiceString_.append("|"); // see http://www.fltk.org/doc-1.3/classFl__Menu__.html#a67b693829c184e98bb9b9cd0eb165a84
        }
        choice_.add(choiceString_.data());
        choice_.value(toIndex(News::Info));
        show(); // make main window visible
        window_.callback(&MainWindow::exitClicked, this); // register exit function callback
    }

    int MainWindow::run() {
        return Fl::run();
    }

    void MainWindow::show() {
        window_.show();
    }

    void MainWindow::buttonClicked(Fl_Widget *widget, void *data) {
        auto ptrToCurMainWindow = static_cast<this_type *>(data);
        if (&ptrToCurMainWindow->sendInputButton_ != widget) {
            throw std::runtime_error{ "widget was not sendInputButton in MainWindow::buttonClicked" };
        }
        auto str = toString(toNews(ptrToCurMainWindow->choice_.value()),
                            ptrToCurMainWindow->userInput_.value());
        ptrToCurMainWindow->threads_.getQueue().push(std::move(str));
        ptrToCurMainWindow->userInput_.value(""); // clear the userInput field
    }

    void MainWindow::exitClicked(Fl_Widget *widget, void *data) {
        auto pMainWin = static_cast<this_type *>(data);
        if (widget != &pMainWin->window_) {
            throw std::runtime_error{ "widget was not &pMainWin->window_ in MainWindow::exitClicked" };
        }
        auto window = static_cast<Fl_Window *>(widget);
        window->hide(); // close the main window
        pMainWin->threads_.getAliveState().killThreads();
        pMainWin->threads_.joinAll(); // join threads
    }
} /* namespace rn1 */
