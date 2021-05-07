#ifndef _STACK_H
#define _STACK_H

#include "../General/general.h"
#include "../Vector/vector.h"

namespace mySTL {

    template <typename T>
    class Stack: public Vector<T> {
    
    public:
        void push ( T const& e ) { this->insert ( this->size(), e ); }
        T pop() { return this->remove ( this->size() - 1 ); }
        T& top() { return ( *this ) [this->size() - 1]; } 
    };
}

#endif