#include <utility> // std::move
#include <algorithm> // std::all_of
#include <stdexcept> // std::runtime_error
#include <functional> // std::ref
#include "../include/ThreadContainer.h"

namespace rn1 {
    ThreadContainer::ThreadContainer(size_type producerCount, prod_func_type producerFunction,
                                     cons_func_type consumerFunction, Output &consOutP)
        : producerFunction_{ std::move(producerFunction) }, consumerFunction_{ std::move(consumerFunction) }, aliveState_{ q_, pauseStatus_ } {
        threads_.reserve(producerCount + static_cast<size_type>(1U));
        for (auto i = static_cast<size_type>(0U); // add the producers
             i < producerCount;
             ++i) {
            threads_.emplace_back(producerFunction_,
                                  std::ref(getQueue()),
                                  std::ref(aliveState_),
                                  std::ref(pauseStatus_));
        }
        threads_.emplace_back(consumerFunction_, // add the consumer
                              std::ref(getQueue()),
                              std::ref(aliveState_),
                              std::ref(consOutP));
        auto allJoinable = std::all_of(std::begin(threads_), std::end(threads_),
                                       [](auto &&e) {
                                           return e.joinable();
                                       });
        if (!allJoinable) {
            throw std::runtime_error{ "At least one of the threads in ThreadContainer was not joinable" };
        }
    }

    void ThreadContainer::joinAll() {
        for (auto &e : threads_) {
            e.join();
        }
    }

    ThreadSafeQueue &ThreadContainer::getQueue() noexcept {
        return q_;
    }

    AliveState &ThreadContainer::getAliveState() noexcept {
        return aliveState_;
    }

    PauseStatus &ThreadContainer::getPauseStatus() noexcept {
        return pauseStatus_;
    }
} /* namespace rn1 */
