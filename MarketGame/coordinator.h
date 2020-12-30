#ifndef COORDINATOR_H
#define COORDINATOR_H


/**
 * @brief The Coordinator class
 * Coordinates the switching of contexts between windows
 */
class Coordinator
{
    public:
       Coordinator();
       Coordinator(const Coordinator & assignThis) =delete;
       Coordinator & operator =(const Coordinator &assignThis)=delete;
       ~Coordinator() = default;

      void run();


    private:

};

#endif // COORDINATOR_H
