#ifndef SINGLEUSEQSTRINGQUEUE_H
#define SINGLEUSEQSTRINGQUEUE_H

#include <QString>
#include <future>
class SingleUseQStringQueue
{
public:
    SingleUseQStringQueue(uint32_t size);
    SingleUseQStringQueue() = delete;
    SingleUseQStringQueue(const SingleUseQStringQueue & assign) = delete;
    SingleUseQStringQueue & operator = (const SingleUseQStringQueue & assign) = delete;
    ~SingleUseQStringQueue();

    void enqueueMove(const QString&& item);
    const QString dequeue();

private:
    inline bool isDoneOrReady() const
    {
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

private:
    std::mutex mutex;
    std::condition_variable cv_Dequeue;
    QString *pQueue;
    const uint32_t size;
    std::atomic_uint32_t dequeueIndex;
    std::atomic_uint32_t enqueueIndex;
};

#endif // SINGLEUSEQSTRINGQUEUE_H
