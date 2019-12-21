#include "../include/PauseStatus.h"

namespace rn1 {
    PauseStatus::PauseStatus() noexcept : isPaused_{ false } { }

    void PauseStatus::toggle() noexcept {
        lock_type lck{ mu_ };
        isPaused_ = !isPaused_;
        if (!isPaused_) { // notify all if it's now unpaused
            cvResumed_.notify_all();
        }
    }

    void PauseStatus::waitUntilResume() noexcept {
        lock_type lck{ mu_ };
        cvResumed_.wait(lck, [this] {
                            return !isPaused_;
                        });
    }

    PauseStatus::value_type PauseStatus::isPaused() const noexcept {
        lock_type lck{ mu_ };
        return isPaused_;
    }
} /* namespace rn1 */
