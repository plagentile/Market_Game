#include "singleuseqstringqueue.h"

SingleUseQStringQueue::SingleUseQStringQueue(const uint32_t size)
    :pQueue(new QString[size]), size(size), dequeueIndex(0),enqueueIndex(0)
{
}

SingleUseQStringQueue::~SingleUseQStringQueue(){
    delete[] pQueue;
}

void SingleUseQStringQueue::enqueueMove(const QString&& item){
    if(this->enqueueIndex.load() == this->size) return;
    this->pQueue[this->enqueueIndex++] = item;
    this->cv_Dequeue.notify_one();
}

const QString SingleUseQStringQueue::dequeue(){
    std::unique_lock<std::mutex> lock(this->mutex);
    if(this->dequeueIndex.load() >= this->size) return "";

    if(!this->isDoneOrReady()){
        cv_Dequeue.wait(lock, [&]{return isDoneOrReady();});
    }
    return this->pQueue[dequeueIndex++];
}


