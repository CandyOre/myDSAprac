#ifndef _QUEUE_H
#define _QUEUE_H

#include "../General/general.h"
#include "../List/list.h"

namespace mySTL {

    template <typename T>
    class Queue: public List<T> {

    public:
        void enqueue ( T const& e ) { this->insertAsLast ( e ); }
        T dequeue() { return this->remove ( this->first() ); }
        T& front() { return this->first()->data; }
    };
}

#endif