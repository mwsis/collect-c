/* /////////////////////////////////////////////////////////////////////////
 * File:    src/stock_cmp_fns.c
 *
 * Purpose: Stock comparison functions.
 *
 * Created: 19th February 2025
 * Updated: 19th February 2025
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

 #include <collect-c/common.h>

#include <assert.h>
#include <stdint.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * internal functions & macros
 */

typedef int (*pfn_cmp_t)(
    void const* _lhs
,   void const* _rhs
);

extern
int
collect_c_fn_cmp_undiscriminated_(
    void const* _lhs
,   void const* _rhs
);

static
int
collect_c_fn_cmp_int16_(
    int16_t const*  pe_lhs
,   int16_t const*  pe_rhs
)
{
    int16_t const   lhs =   *pe_lhs;
    int16_t const   rhs =   *pe_rhs;

    if (lhs < rhs)
    {
        return -1;
    }

    if (lhs > rhs)
    {
        return +1;
    }

    return 0;
}

static
int
collect_c_fn_cmp_int32_(
    int32_t const*  pe_lhs
,   int32_t const*  pe_rhs
)
{
    int32_t const   lhs =   *pe_lhs;
    int32_t const   rhs =   *pe_rhs;

    if (lhs < rhs)
    {
        return -1;
    }

    if (lhs > rhs)
    {
        return +1;
    }

    return 0;
}

static
int
collect_c_fn_cmp_int64_(
    int64_t const*  pe_lhs
,   int64_t const*  pe_rhs
)
{
    int64_t const   lhs =   *pe_lhs;
    int64_t const   rhs =   *pe_rhs;

    if (lhs < rhs)
    {
        return -1;
    }

    if (lhs > rhs)
    {
        return +1;
    }

    return 0;
}

static
int
collect_c_fn_cmp_uint16_(
    uint16_t const* pe_lhs
,   uint16_t const* pe_rhs
)
{
    uint16_t const  lhs =   *pe_lhs;
    uint16_t const  rhs =   *pe_rhs;

    if (lhs < rhs)
    {
        return -1;
    }

    if (lhs > rhs)
    {
        return +1;
    }

    return 0;
}

static
int
collect_c_fn_cmp_uint32_(
    uint32_t const* pe_lhs
,   uint32_t const* pe_rhs
)
{
    uint32_t const  lhs =   *pe_lhs;
    uint32_t const  rhs =   *pe_rhs;

    if (lhs < rhs)
    {
        return -1;
    }

    if (lhs > rhs)
    {
        return +1;
    }

    return 0;
}

static
int
collect_c_fn_cmp_uint64_(
    uint64_t const*  pe_lhs
,   uint64_t const*  pe_rhs
)
{
    uint64_t const  lhs =   *pe_lhs;
    uint64_t const  rhs =   *pe_rhs;

    if (lhs < rhs)
    {
        return -1;
    }

    if (lhs > rhs)
    {
        return +1;
    }

    return 0;
}


#define CLC_INTERNAL_SIGNED_SELECT_(n)                      (8 == (n)) ? (pfn_cmp_t)collect_c_fn_cmp_int64_ : (4 == (n)) ? (pfn_cmp_t)collect_c_fn_cmp_int32_ : (pfn_cmp_t)collect_c_fn_cmp_int16_
#define CLC_INTERNAL_UNSIGNED_SELECT_(n)                    (8 == (n)) ? (pfn_cmp_t)collect_c_fn_cmp_uint64_ : (4 == (n)) ? (pfn_cmp_t)collect_c_fn_cmp_uint32_ : (pfn_cmp_t)collect_c_fn_cmp_uint16_

#define CLC_INTERNAL_SELECT_CMPFN_FOR_SIZED_T_(t_int)  _Generic(((t_int)0), \
                                                                            \
     int64_t : collect_c_fn_cmp_int64_,                                     \
     int32_t : collect_c_fn_cmp_int32_,                                     \
     int16_t : collect_c_fn_cmp_int16_,                                     \
    uint64_t : collect_c_fn_cmp_uint64_,                                    \
    uint32_t : collect_c_fn_cmp_uint32_,                                    \
    uint16_t : collect_c_fn_cmp_uint16_,                                    \
     default : collect_c_fn_cmp_undiscriminated_                            \
)

#define CLC_INTERNAL_SELECT_CMPFN_FOR_BUILT_IN_T_(t_int)   _Generic(((t_int)0), \
                                                                                \
                  short : CLC_INTERNAL_SIGNED_SELECT_(sizeof(t_int)),           \
                    int : CLC_INTERNAL_SIGNED_SELECT_(sizeof(t_int)),           \
                   long : CLC_INTERNAL_SIGNED_SELECT_(sizeof(t_int)),           \
              long long : CLC_INTERNAL_SIGNED_SELECT_(sizeof(t_int)),           \
         unsigned short : CLC_INTERNAL_SIGNED_SELECT_(sizeof(t_int)),           \
           unsigned int : CLC_INTERNAL_SIGNED_SELECT_(sizeof(t_int)),           \
          unsigned long : CLC_INTERNAL_SIGNED_SELECT_(sizeof(t_int)),           \
     unsigned long long : CLC_INTERNAL_SIGNED_SELECT_(sizeof(t_int)),           \
                default : collect_c_fn_cmp_undiscriminated_                     \
)


/* /////////////////////////////////////////////////////////////////////////
 * API functions
 */

int
collect_c_fn_cmp_int16(
    void const*     pe_lhs
,   void const*     pe_rhs
,   size_t          el_size
)
{
    typedef int16_t                                         int_t;

    assert(NULL != pe_lhs);
    assert(NULL != pe_rhs);
    assert(0 != el_size);
    assert(sizeof(int_t) == el_size);

    ((void)&el_size);

    return CLC_INTERNAL_SELECT_CMPFN_FOR_SIZED_T_(int_t)(pe_lhs, pe_rhs);
}

int
collect_c_fn_cmp_int32(
    void const*     pe_lhs
,   void const*     pe_rhs
,   size_t          el_size
)
{
    typedef int32_t                                         int_t;

    assert(NULL != pe_lhs);
    assert(NULL != pe_rhs);
    assert(0 != el_size);
    assert(sizeof(int_t) == el_size);

    ((void)&el_size);

    return CLC_INTERNAL_SELECT_CMPFN_FOR_SIZED_T_(int_t)(pe_lhs, pe_rhs);
}

int
collect_c_fn_cmp_int64(
    void const*     pe_lhs
,   void const*     pe_rhs
,   size_t          el_size
)
{
    typedef int64_t                                         int_t;

    assert(NULL != pe_lhs);
    assert(NULL != pe_rhs);
    assert(0 != el_size);
    assert(sizeof(int_t) == el_size);

    ((void)&el_size);

    return CLC_INTERNAL_SELECT_CMPFN_FOR_SIZED_T_(int_t)(pe_lhs, pe_rhs);
}

int
collect_c_fn_cmp_uint16(
    void const*     pe_lhs
,   void const*     pe_rhs
,   size_t          el_size
)
{
    typedef uint16_t                                        int_t;

    assert(NULL != pe_lhs);
    assert(NULL != pe_rhs);
    assert(0 != el_size);
    assert(sizeof(int_t) == el_size);

    ((void)&el_size);

    return CLC_INTERNAL_SELECT_CMPFN_FOR_SIZED_T_(int_t)(pe_lhs, pe_rhs);
}

int
collect_c_fn_cmp_uint32(
    void const*     pe_lhs
,   void const*     pe_rhs
,   size_t          el_size
)
{
    typedef uint32_t                                        int_t;

    assert(NULL != pe_lhs);
    assert(NULL != pe_rhs);
    assert(0 != el_size);
    assert(sizeof(int_t) == el_size);

    ((void)&el_size);

    return CLC_INTERNAL_SELECT_CMPFN_FOR_SIZED_T_(int_t)(pe_lhs, pe_rhs);
}

int
collect_c_fn_cmp_uint64(
    void const*     pe_lhs
,   void const*     pe_rhs
,   size_t          el_size
)
{
    typedef uint64_t                                        int_t;

    assert(NULL != pe_lhs);
    assert(NULL != pe_rhs);
    assert(0 != el_size);
    assert(sizeof(int_t) == el_size);

    ((void)&el_size);

    return CLC_INTERNAL_SELECT_CMPFN_FOR_SIZED_T_(int_t)(pe_lhs, pe_rhs);
}


int
collect_c_fn_cmp_short(
    void const*     pe_lhs
,   void const*     pe_rhs
,   size_t          el_size
)
{
    typedef short                                           int_t;

    assert(NULL != pe_lhs);
    assert(NULL != pe_rhs);
    assert(0 != el_size);
    assert(sizeof(int_t) == el_size);

    ((void)&el_size);

    return CLC_INTERNAL_SELECT_CMPFN_FOR_BUILT_IN_T_(int_t)(pe_lhs, pe_rhs);
}

int
collect_c_fn_cmp_int(
    void const*     pe_lhs
,   void const*     pe_rhs
,   size_t          el_size
)
{
    typedef int                                             int_t;

    assert(NULL != pe_lhs);
    assert(NULL != pe_rhs);
    assert(0 != el_size);
    assert(sizeof(int_t) == el_size);

    ((void)&el_size);

    return CLC_INTERNAL_SELECT_CMPFN_FOR_BUILT_IN_T_(int_t)(pe_lhs, pe_rhs);
}

int
collect_c_fn_cmp_long(
    void const*     pe_lhs
,   void const*     pe_rhs
,   size_t          el_size
)
{
    typedef long                                            int_t;

    assert(NULL != pe_lhs);
    assert(NULL != pe_rhs);
    assert(0 != el_size);
    assert(sizeof(int_t) == el_size);

    ((void)&el_size);

    return CLC_INTERNAL_SELECT_CMPFN_FOR_BUILT_IN_T_(int_t)(pe_lhs, pe_rhs);
}

int
collect_c_fn_cmp_llong(
    void const*     pe_lhs
,   void const*     pe_rhs
,   size_t          el_size
)
{
    typedef long long                                       int_t;

    assert(NULL != pe_lhs);
    assert(NULL != pe_rhs);
    assert(0 != el_size);
    assert(sizeof(int_t) == el_size);

    ((void)&el_size);

    return CLC_INTERNAL_SELECT_CMPFN_FOR_BUILT_IN_T_(int_t)(pe_lhs, pe_rhs);
}

int
collect_c_fn_cmp_ushort(
    void const*     pe_lhs
,   void const*     pe_rhs
,   size_t          el_size
)
{
    typedef unsigned short                                  int_t;

    assert(NULL != pe_lhs);
    assert(NULL != pe_rhs);
    assert(0 != el_size);
    assert(sizeof(int_t) == el_size);

    ((void)&el_size);

    return CLC_INTERNAL_SELECT_CMPFN_FOR_BUILT_IN_T_(int_t)(pe_lhs, pe_rhs);
}

int
collect_c_fn_cmp_uint(
    void const*     pe_lhs
,   void const*     pe_rhs
,   size_t          el_size
)
{
    typedef unsigned int                                    int_t;

    assert(NULL != pe_lhs);
    assert(NULL != pe_rhs);
    assert(0 != el_size);
    assert(sizeof(int_t) == el_size);

    ((void)&el_size);

    return CLC_INTERNAL_SELECT_CMPFN_FOR_BUILT_IN_T_(int_t)(pe_lhs, pe_rhs);
}

int
collect_c_fn_cmp_ulong(
    void const*     pe_lhs
,   void const*     pe_rhs
,   size_t          el_size
)
{
    typedef unsigned long                                   int_t;

    assert(NULL != pe_lhs);
    assert(NULL != pe_rhs);
    assert(0 != el_size);
    assert(sizeof(int_t) == el_size);

    ((void)&el_size);

    return CLC_INTERNAL_SELECT_CMPFN_FOR_BUILT_IN_T_(int_t)(pe_lhs, pe_rhs);
}

int
collect_c_fn_cmp_ullong(
    void const*     pe_lhs
,   void const*     pe_rhs
,   size_t          el_size
)
{
    typedef unsigned long long                              int_t;

    assert(NULL != pe_lhs);
    assert(NULL != pe_rhs);
    assert(0 != el_size);
    assert(sizeof(int_t) == el_size);

    ((void)&el_size);

    return CLC_INTERNAL_SELECT_CMPFN_FOR_BUILT_IN_T_(int_t)(pe_lhs, pe_rhs);
}


/* ///////////////////////////// end of file //////////////////////////// */

