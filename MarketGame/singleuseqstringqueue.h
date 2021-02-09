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

    void enqueueMove(const QString&& item) noexcept;
    const QString dequeue() noexcept;

private:
    inline bool isDoneOrReady() const noexcept
    {
        //quick check to see if we are trailing the enqueuing thread
        if(this->dequeueIndex.load() < this->enqueueIndex.load()){
           return true;
         }

         //check if the enqueuing is done
         else if(this->enqueueIndex.load() >= this->size){
             return true;
         }
         return false;
    }

private:
    std::mutex mDequeue;
    std::condition_variable cv_Dequeue;
    QString *pQueue;
    const uint32_t size;
    std::atomic_uint32_t dequeueIndex;
    std::atomic_uint32_t enqueueIndex;
};

#endif // SINGLEUSEQSTRINGQUEUE_H
