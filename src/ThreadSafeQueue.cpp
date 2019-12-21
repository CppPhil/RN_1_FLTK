#include <utility> // std::move
#include "../include/ThreadSafeQueue.h"
#include "../include/utils.h"

namespace rn1 {
	ThreadSafeQueue::value_type ThreadSafeQueue::pop() {
        printDebug("Consumer tries to acquire mutex");
        lock_type lock{ mu_ };
        printDebug("Consumer got mutex");
        printDebug("Consumer waits on condvar");
		cvHasMsgs_.wait(lock, [this] { return !cont_.empty(); });
        printDebug("Consumer returned from condvar");
        printDebug("Consumer taking first element");
        auto retMe = cont_.front();
        printDebug("Consumer got first element: ", retMe);
		cont_.pop();
        printDebug("Consumer removed first element");        
		return retMe;
	}

	void ThreadSafeQueue::push(value_type const &data) {
        printDebug("HEY THERE'S SOMEONE IN THE const & OVERLOAD OF", __func__);
		lock_type lock{ mu_ };
		cont_.push(data);
		cvHasMsgs_.notify_all(); // let the consumer know that the queue has at least one message now
	}

	void ThreadSafeQueue::push(value_type &&data) {    
        printDebug("Producer acquiring mutex");
		lock_type lock{ mu_ };
        printDebug("Producer got mutex");
		cont_.push(std::move(data));
		cvHasMsgs_.notify_all(); // let the consumer know that the queue has at least one message now
        printDebug("Producer sent notification");
	}

} /* namespace rn1 */
