#include "../General/general.h"
#include "../List/list.h"

namespace mySTL {

    template <typename T>
    class Queue: public List {

    public:
        void push ( T const& e ) { insertAsLast ( e ); }
        T pop() { return remove ( first() ); }
        T& front() { return first()->data; }
    };
}