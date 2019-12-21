#pragma once
#include "../include/ThreadSafeQueue.h"
#include "../include/Output.h"

namespace rn1 {
    class AliveState;
	void consFunc(ThreadSafeQueue &q, AliveState &aliveState, Output &out);
} /* namespace rn1 */
