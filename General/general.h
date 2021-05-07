#ifndef _GENERAL_H
#define _GENERAL_H

namespace mySTL {
    
    template <typename T>
    static bool lt ( T* a, T* b ) { return lt ( *a, *b ); }

    template <typename T>
    static bool lt ( T& a, T& b ) { return a < b; }

    template <typename T>
    static bool eq ( T* a, T* b ) { return eq ( *a, *b ); }

    template <typename T>
    static bool eq ( T& a, T& b ) { return a == b; }
}

#endif