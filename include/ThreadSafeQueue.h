#pragma once
#include <queue> // std::queue
#include <string> // std::string
#include <mutex> // std::mutex
#include <condition_variable> // std::condition_variable
#include "../include/AliveState.h"

namespace rn1 {
	class ThreadSafeQueue final {
	public:
        friend AliveState;
		using this_type = ThreadSafeQueue;
		using value_type = std::string;
		using container_type = std::queue<value_type>;
		using mutex_type = std::mutex;
		using lock_type = std::unique_lock<mutex_type>;

		value_type pop();
		void push(value_type const &data);
		void push(value_type &&data);
	private:
		container_type cont_;
		mutex_type mu_;
		std::condition_variable cvHasMsgs_;
	};
} /* namespace rn1 */
