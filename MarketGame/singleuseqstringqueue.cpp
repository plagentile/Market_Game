#include "singleuseqstringqueue.h"

SingleUseQStringQueue::SingleUseQStringQueue(uint32_t size)
    :pQueue(new QString[size]), size(size), dequeueIndex(0),enqueueIndex(0)
{
}

SingleUseQStringQueue::~SingleUseQStringQueue(){
    delete[] pQueue;
}

void SingleUseQStringQueue::enqueue(const QString item){
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


bool SingleUseQStringQueue::isDoneOrReady() {

    //quick check to see if we are trailing the enqueuing thread
    if(this->dequeueIndex.load() < this->enqueueIndex.load()){
        return true;
    }

    //check for all items to have been enqued
    else if(this->enqueueIndex.load() == this->size){
        return true;
    }

    return false;
}
