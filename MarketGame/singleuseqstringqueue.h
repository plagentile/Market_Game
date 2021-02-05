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

    void enqueue(QString item);
    const QString dequeue();

private:
    bool isDoneOrReady();

private:
    std::mutex mutex;
    std::condition_variable cv_Dequeue;
    QString *pQueue;
    const uint32_t size;
    std::atomic_uint32_t dequeueIndex;
    std::atomic_uint32_t enqueueIndex;
};

#endif // SINGLEUSEQSTRINGQUEUE_H
