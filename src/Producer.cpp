#include <limits> // std::numeric_limits
#include <chrono> // std::chrono::seconds
#include <string> // std::to_string
#include <thread> // std::this_thread::sleep_for
#include "../include/RandomNumberGenerator.h"
#include "../include/Producer.h"
#include "../include/News.h"
#include "../include/AliveState.h"
#include "../include/PauseStatus.h"

namespace rn1 {
	void prodFunc(ThreadSafeQueue &q, AliveState &aliveState, PauseStatus &pauseStatus) {
		RandomNumberGenerator rng{ };
		using Seconds = std::chrono::seconds;
		auto const minSleepSeconds = 1;
		auto const maxSleepSeconds = 5;
		for (;;) {
            if (!aliveState.areThreadsAlive()) {
                return;
            }
            pauseStatus.waitUntilResume();
			auto msgText = std::to_string(rng.getRandomNumber(std::numeric_limits<long long>::min(),
					std::numeric_limits<long long>::max()));
			auto msgType = toNews(rng.getRandomNumber(toIndex(News::Info),
							      toIndex(News::Corr)));
			Seconds sleepTime{ rng.getRandomNumber(minSleepSeconds, maxSleepSeconds) };
			q.push(toString(msgType, msgText));
			std::this_thread::sleep_for(sleepTime);
		}
	}
} /* namespace rn1 */
