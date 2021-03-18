typedef int RANK;
#define ListNodePosi(T) ListNode<T>*

template <typename T>
struct ListNode {

    T data;
    ListNodePosi(T) pre, suc;

    ListNode() {}
    ListNode ( T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL )
        : data( e ), pre( p ), suc( s ) {}
    
    ListNodePosi(T) insertAsPre ( T const& e );
    ListNodePosi(T) insertAsSuc ( T const& e );
};

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPre ( T const& e ) {
    ListNodePosi(T) x = new ListNode( e, pre, this );
    pre->suc = x; pre = x;
    return x;
}

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSuc ( T const& e ) {
    ListNodePosi(T) x = new ListNode( e, this, suc );
    suc->pre = x; suc = x;
    return x;
}

