#ifndef _VECTOR_H
#define _VECTOR_H

#include "../General/general.h"
#include <stdlib.h>
#include <algorithm>

namespace mySTL {

    typedef int RANK;
    #define DEFAULT_CAPACITY 8

    template <typename T>
    class Vector {

    protected:
        RANK _size;
        int _capacity;
        T* _elem;

        void copyFrom ( T const* A, RANK lo, RANK hi );

        void expand();
        void shrink();

        bool bubble ( RANK lo, RANK hi );
        void bubbleSort ( RANK lo, RANK hi );

        RANK max ( RANK lo, RANK hi );
        void selectionSort ( RANK lo, RANK hi );

        void merge ( RANK lo, RANK mi, RANK hi );
        void mergeSort ( RANK lo, RANK hi );

        RANK partition ( RANK lo, RANK hi );
        void quickSort ( RANK lo, RANK hi );

        void heapSort ( RANK lo, RANK hi );

    public:
        Vector ( int c = DEFAULT_CAPACITY, int s = 0, T v = 0 )
        { _elem = new T[_capacity = c]; for ( _size = 0; _size < s; _elem[_size++] = v ); }
        Vector ( T const* A, RANK n ) { copyFrom ( A, 0, n ); }
        Vector ( T const* A, RANK lo, RANK hi ) { copyFrom ( A, lo, hi ); }
        Vector ( Vector<T> const& V ) { copyFrom ( V._elem, 0, V._size ); }
        Vector ( Vector<T> const& V, RANK lo, RANK hi ) { copyFrom ( V._elem, lo, hi ); }

        ~Vector() { delete [] _elem; }

        RANK size() const { return _size; }
        bool empty() const { return !_size; }
        
        int disordered() const;
        RANK find ( T const& e, RANK lo, RANK hi ) const;
        RANK find ( T const& e ) const { return find ( e, 0, _size ); }
        RANK search ( T const& e, RANK lo, RANK hi ) const;
        RANK search ( T const& e ) const
        { return ( 0 >= _size ) ? -1 : search ( e, 0, _size ); }

        T& operator[] ( RANK r ) const { return _elem[r]; }
        Vector<T>& operator= ( Vector<T> const& );

        T remove ( RANK r );
        int remove ( RANK lo, RANK hi );

        RANK insert ( RANK r, T const& e );
        RANK insert ( T const& e ) { return insert ( _size, e ); }

        void sort ( RANK lo, RANK hi );
        void sort() { sort ( 0, _size ); }

        void unsort ( RANK lo, RANK hi );
        void unsort() { unsort ( 0, _size ); }

        int deduplicate();
        int uniquify();

        void traverse ( void (* ) ( T& ) );
        template <typename VST> void traverse ( VST& );
    };

    template <typename T>
    void Vector<T>::copyFrom ( T const* A, RANK lo, RANK hi ) {
        _elem = new T[_capacity = 2 * ( hi - lo ) ]; _size = 0;
        while ( lo < hi ) _elem[_size++] = A[lo++];
    }

    template <typename T>
    void Vector<T>::expand() { 
        if ( _size < _capacity ) return;
        if ( _capacity < DEFAULT_CAPACITY ) _capacity = DEFAULT_CAPACITY;
        T* oldElem = _elem; _elem = new T[_capacity *= 2];
        for ( int i = 0; i < _size; i++ ) _elem[i] = oldElem[i];
        delete [] oldElem;
    }

    template <typename T>
    void Vector<T>::shrink() {
        if ( _capacity < DEFAULT_CAPACITY * 2 ) return;
        if ( _size > _capacity / 4 ) return;
        T* oldElem = _elem; _elem = new T[_capacity /= 2];
        for ( int i = 0; i  < _size; i++ ) _elem[i] = oldElem[i];
        delete [] oldElem;
    }

    template <typename T>
    RANK Vector<T>::find ( T const& e, RANK lo, RANK hi ) const {
        while ( ( lo < hi-- ) && ( e != _elem[hi] ) );
        return hi;
    }

    template <typename T>
    Vector<T>& Vector<T>::operator= ( Vector<T> const& V ) {
        if ( _elem ) delete [] _elem;
        copyFrom ( V._elem, 0, V.size() );
        return *this;
    }

    template <typename T>
    T Vector<T>::remove ( RANK r ) {
        T e = _elem[r];
        remove ( r, r + 1 );
        return e;
    }

    template <typename T>
    int Vector<T>::remove ( RANK lo, RANK hi ) {
        if ( lo == hi ) return 0;
        while ( hi < _size ) _elem[lo++] = _elem[hi++];
        _size = lo;
        shrink();
        return hi - lo;
    }

    template <typename T>
    RANK Vector<T>::insert ( RANK r, T const& e ) {
        expand();
        for ( int i = _size; i > r; i-- ) _elem[i] = _elem[i - 1];
        _elem[r] = e; _size++;
        return r;
    }

    template <typename T>
    void Vector<T>::unsort ( RANK lo, RANK hi ) {
        T* V = _elem + lo;
        for ( RANK i = hi - lo; i > 0; i-- ) swap ( V[i - 1], V[rand() % i] );
    }

    template <typename T>
    int Vector<T>::deduplicate() {
        int oldSize = _size;
        RANK i = 1;
        while ( i < _size ) ( find ( _elem[i], 0, i ) < 0 ) ? i++ : remove ( i );
        return oldSize - _size;
    }

    template <typename T>
    void Vector<T>::traverse ( void ( *visit ) ( T& ) ) 
    { for ( int i = 0; i < _size; i++ ) visit ( _elem[i] ); }

    template <typename T> template <typename VST>
    void Vector<T>::traverse ( VST& visit ) 
    { for ( int i = 0; i < _size; i++ ) visit ( _elem[i] ); }
}

#endif