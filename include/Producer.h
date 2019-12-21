#pragma once
#include "../include/ThreadSafeQueue.h"

namespace rn1 {
    class AliveState;
    class PauseStatus;
    void prodFunc(ThreadSafeQueue &q, AliveState &aliveState, PauseStatus &pauseStatus);
} /* namespace rn1 */
