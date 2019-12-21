#pragma once
#include <thread> // std::thread
#include <vector> // std::vector
#include <functional> // std::function
#include "../include/ThreadSafeQueue.h"
#include "../include/Output.h"
#include "../include/AliveState.h"
#include "../include/PauseStatus.h"

namespace rn1 {
    class ThreadContainer final {
    public:
        using this_type = ThreadContainer;
        using value_type = std::thread;
        using container_type = std::vector<value_type>;
        using size_type = container_type::size_type;
        using prod_func_type = std::function<void (ThreadSafeQueue &, AliveState &, PauseStatus &)>;
        using cons_func_type = std::function<void (ThreadSafeQueue &, AliveState &, Output &)>;

        ThreadContainer(size_type producerCount, prod_func_type producerFunction,
                        cons_func_type consumerFunction,
                        Output &consOutP);

        void joinAll();

        ThreadSafeQueue &getQueue() noexcept;
        AliveState &getAliveState() noexcept;
        PauseStatus &getPauseStatus() noexcept;
    private:
        prod_func_type producerFunction_;
        cons_func_type consumerFunction_;
        container_type threads_;
        ThreadSafeQueue q_;
        AliveState aliveState_;
        PauseStatus pauseStatus_;
    };

} /* namespace rn1 */
