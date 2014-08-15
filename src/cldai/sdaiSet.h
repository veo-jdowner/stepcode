#ifndef SDAISET_H
#define SDAISET_H 1

#include <sc_export.h>

typedef void * SDAI_ptr;

class SC_DAI_EXPORT SDAI__set {
    public:
        SDAI__set( int = 16 );
        ~SDAI__set();

        SDAI_ptr retrieve( int index );
        int is_empty();

        SDAI_ptr & operator[]( int index );

        void Insert( SDAI_ptr, int index );
        void Append( SDAI_ptr );
        void Remove( int index );

        int Index( SDAI_ptr );

        void Clear();
        int Count();

    private:
        void Check( int index );
    private:
        SDAI_ptr * _buf;
        int _bufsize;
        int _count;

    public:

};

#endif