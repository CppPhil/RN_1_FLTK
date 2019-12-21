#include "../include/AliveState.h"
#include "../include/ThreadSafeQueue.h"
#include "../include/PauseStatus.h"
#include <condition_variable> // std::condition_variable

namespace rn1 {
    AliveState::AliveState(ThreadSafeQueue &q, PauseStatus &pauseStatus) noexcept
        : aliveState_{ true },
        cv_{ q.cvHasMsgs_ },
        q_{ q },
        pauseStatus_{ pauseStatus } { }

    AliveState::value_type AliveState::areThreadsAlive() const noexcept {
        lock_type lck{ mu_ };
        return aliveState_;
    }

    void AliveState::killThreads() noexcept {
        lock_type lck{ mu_ };
        aliveState_ = false;
        q_.push(""); // add element to queue so that consumer can wake up
        cv_.notify_all(); // wake the consumer up
        if (pauseStatus_.isPaused()) {
            pauseStatus_.toggle(); // resume producers
        }
    }
} /* namespace rn1 */
