#include "../include/Consumer.h"
#include "../include/AliveState.h"
#include <string> // std::string

namespace rn1 {
	void consFunc(ThreadSafeQueue &q, AliveState &aliveState, Output &out) {
		std::string curVal{ };
		for (;;) {
            if (!aliveState.areThreadsAlive()) {
                return;
            }
			curVal = q.pop();
			out.append(curVal);
		}
	}
} /* namespace rn1 */
