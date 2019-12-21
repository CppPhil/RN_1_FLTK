#pragma once
#include <mutex> // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable

namespace rn1 {
    class ThreadSafeQueue;
    class PauseStatus;

    class AliveState final {
    public:
        using this_type = AliveState;
        using mutex_type = std::mutex;
        using lock_type = std::unique_lock<mutex_type>;
        using value_type = bool;

        AliveState(ThreadSafeQueue &, PauseStatus &) noexcept;
        AliveState(this_type const &) = delete;
        value_type areThreadsAlive() const noexcept;
        void killThreads() noexcept;

    private:
        mutex_type mutable mu_;
        value_type aliveState_;
        std::condition_variable &cv_;
        ThreadSafeQueue &q_;
        PauseStatus &pauseStatus_;
    };
} /* namespace rn1 */
