#include "../include/PauseButton.h"
#include "../include/PauseStatus.h"
#include <utility> // std::move
#include <stdexcept> // std::runtime_error

namespace rn1 {
    PauseButton::PauseButton(Dimension pos, Dimension siz,
                             PauseStatus &pauseStatus)
        : label_{ &toggleOn_ },
          toggleButton_{ pos.getX(), pos.getY(),
              siz.getX(), siz.getY(),
              label_->data() },
          pauseStatus_{ pauseStatus } {
        toggleButton_.value(0); // toggled off by default
        toggleButton_.callback(&pauseButtonClicked, this);
    }

    void PauseButton::pauseButtonClicked(Fl_Widget *widget, void *data) {
        auto pPauseButton = static_cast<this_type *>(data);
        if (widget != &pPauseButton->toggleButton_) {
            throw std::runtime_error{ "widget was not equal &pPauseButton->toggleButton_ in PauseButton::pauseButtonClicked" };
        }
        auto pToggleButton = static_cast<ToggleButton *>(widget);
        if (pToggleButton->value()) { // if toggled on
            pPauseButton->label_ = &pPauseButton->toggleOff_;
        } else { // if toggled off
            pPauseButton->label_ = &pPauseButton->toggleOn_;
        }
        pToggleButton->label(pPauseButton->label_->data());
        pPauseButton->pauseStatus_.toggle();
    }

} /* namespace rn1 */
