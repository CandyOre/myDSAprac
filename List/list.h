#include "listNode.h"

template <typename T>
class List {

private:
    int _size;
    ListNodePosi(T) header, trailer;

protected:
    void init();
    int clear();

    void copyNodes ( ListNodePosi(T), int );

    void merge ( ListNodePosi(T)&, int, List<T>&, ListNodePosi(T)&, int );
    void mergeSort ( ListNodePosi(T)&, int );
    void selectionSort ( ListNodePosi(T), int );
    void insertionSort ( ListNodePosi(T), int );

public:
    List() { init(); }
    List ( List<T> const& L );
    List ( List<T> const& L, RANK r, int n );
    List ( ListNodePosi(T) p, int n );

    ~List();

    RANK size() const { return _size; }
    bool empty() const { return _size <= 0; }

    T& operator[] ( RANK r ) const;
    ListNodePosi(T) first() const { return header->suc; }
    ListNodePosi(T) last() const { return trailer->pre; }

    bool valid ( ListNodePosi(T) p ) { return p && ( trailer != p ) && ( header != p ); }

    int disordered() const;

    ListNodePosi(T) find ( T const& e ) const { return find ( e, _size, trailer ); }
    ListNodePosi(T) find ( T const& e, int n, ListNodePosi(T) p ) const;

    ListNodePosi(T) search ( T const& e ) const { return search ( e, _size, trailer ); }
    ListNodePosi(T) search ( T const& e, int n, ListNodePosi(T) p ) const; //不大于e的最后者
    ListNodePosi(T) selectMax () const { return selectMax ( header->suc, _size ); }
    ListNodePosi(T) selectMax ( ListNodePosi(T) p, int n ) const;

    ListNodePosi(T) insertAsFirst ( T const& e );
    ListNodePosi(T) insertAsLast ( T const& e );
    ListNodePosi(T) insertA ( ListNodePosi(T) p, T const& e );
    ListNodePosi(T) insertB ( ListNodePosi(T) p, T const& e );

    void merge ( List<T>& L ) { merge ( first(), size(), L, L.first(), L.size() ) }
    void sort ( ListNodePosi(T) p, int n );
    void sort () { sort( first(), _size ); }

    T remove ( ListNodePosi(T) p );

    int deduplicate ();
    int uniquify ();

    void traverse ( void (* ) ( T& ) );
    template <typename VST> void traverse ( VST& );
};

template <typename T>
void List<T>::init () {
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->suc = trailer; header->pre = NULL:
    trailer->pred = header; trailer->suc = NULL;
    _size = 0;
}

template <typename T>
int List<T>::clear () {
    int oldSize = _size;
    while ( 0 < _size-- ) remove ( header->suc );
    return oldSize;
}

template <typename T>
void List<T>::copyNodes ( ListNodePosi(T) p, int n ) {
    init();
    while ( n-- ) { insertAsLast ( p->data ); p = p->suc; }
}

template <typename T>
void List<T>::insertionSort ( ListNodePosi(T) p, int n ) {
    for( int r = 0; r < n; r++ ) {
        insertA ( search ( p->data, r, p ), p->data );
        p = p->suc; remove ( p->pre );
    }
}

template <typename T>
void List<T>::selectionSort ( ListNodePosi(T) p, int n ) {
    ListNodePosi(T) head = p->pre, tail = p;
    for ( int i = 0; i < n; i++ ) tail = tail->suc;
    while ( 1 < n ) {
        ListNodePosi(T) max = selectMax ( head->suc, n );
        insertB( tail, remove ( max ) );
        tail = tail->pre;
        n--;
    }
}

template <typename T>
List<T>::List ( List<T> const& L ) { copyNodes ( L.first(), L._size ); }

template <typename T>
List<T>::List ( List<T> const& L, RANK r, int n ) { copyNodes ( L[r], n ); }

template <typename T>
List<T>::List ( ListNodePosi(T) p, int n ) { copyNodes ( p, n ) }

template <typename T>
List<T>::~List () { clear(); delete header, trailer; }

template <typename T>
T& List<T>::operator[] ( RANK r ) const {
    ListNodePosi(T) p = first();
    while( 0 < r-- ) p = p->suc;
    return p->data;
}

template <typename T>
ListNodePosi(T) List<T>::find ( T const& e, int n, ListNodePosi(T) p ) const {
    while ( 0 < n-- )
        if ( e == ( p = p->pre )-> data ) return p;
    return NULL;
}

template <typename T>
ListNodePosi(T) List<T>::search ( T const& e, int n, ListNodePosi(T) p ) const {
    while ( 0 <= n-- )
        if( ( p = p->pre )->data <= e ) break;
    return p;
}

template <typename T>
ListNodePosi(T) List<T>::selectMax ( ListNodePosi(T) p, int n ) const {
    ListNodePosi(T) max = p;
    for ( ListNodePosi(T) cur = p; 1 < n; n-- )
        if ( ( cur = cur->suc )->data > max->data )
            max = cur;
    return max;
}

template <typename T>
ListNodePosi(T) List<T>::insertAsFirst ( T const& e )
{ _size++; return header->insertAsSuc ( e ); }

template <typename T>
ListNodePosi(T) List<T>::insertAsLast ( T const& e )
{ _size++; return trailer->insertAsPre ( e ); }

template <typename T>
ListNodePosi(T) List<T>::insertA ( ListNodePosi(T) p, T const& e )
{ _size++; return p->insertAsSuc ( e ); }

template <typename T>
ListNodePosi(T) List<T>::insertB ( ListNodePosi(T) p, T const& e )
{ _size++; return p->insertAsPre ( e ); }

template <typename T>
T List<T>::remove ( ListNodePosi(T) p ) {
    T e = p->data;
    p->pre->suc = p->suc; p->suc->pre = p->pre;
    delete p; _size--;
    return e;
}

template <typename T>
void List<T>::sort ( ListNodePosi(T) p, int n ) {
    switch( rand() % 3 ) {
        case 1: insertionSort ( p, n ); break;
        case 2: selectionSort ( p, n ); break;
        default: mergeSort ( p, n ); break;
    }
}

template <typename T>
int List<T>::deduplicate () {
    if ( _size < 2 ) return 0;
    int oldSize = _size;
    ListNodePosi(T) p = header; RANK r = 0;
    while ( trailer != ( p = p->suc ) ) {
        ListNode q = find ( p->data, r, p );
        q ? remove ( q ) : r++;
    }
    return oldSize - _size;
}

template <typename T>
int List<T>::uniquify () {
    if ( _size < 2 ) return 0;
    int oldSize = _size;
    ListNodePosi(T) p = first(), q;
    while( trailer != ( q = p->suc ) )
        if ( p->data != q->data ) p = q;
        else remove ( q );
    return oldSize - _size;
}

template <typename T>
void List<T>::traverse ( void ( *visit ) ( T& ) ) 
{ for( ListNodePosi(T) p = header->suc; p != trailer; p = p->suc ) visit( p->data ); }

template <typename T> template <typename VST>
void List<T>::traverse ( VST& visit ) 
{ for( ListNodePosi(T) p = header->suc; p != trailer; p = p->suc ) visit( p->data ); }
