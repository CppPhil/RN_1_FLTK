#pragma once
#include <mutex> // std::mutex
#include <condition_variable> // std::condition_variable

namespace rn1 {
    class AliveState;

    class PauseStatus final {
    public:
        using this_type = PauseStatus;
        using mutex_type = std::mutex;
        using lock_type = std::unique_lock<mutex_type>;
        using condvar_type = std::condition_variable;
        using value_type = bool;

        friend AliveState;

        PauseStatus() noexcept;
        void toggle() noexcept;
        void waitUntilResume() noexcept;

    private:
        value_type isPaused() const noexcept;

        value_type isPaused_;
        mutex_type mutable mu_;
        condvar_type cvResumed_;
    };
} /* namespace rn1 */
