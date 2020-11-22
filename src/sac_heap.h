/**
 * Copyright (c) 2019 Leonardo Vencovsky
 *
 * This file is part of the C Macro Collections Libray.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * sac_heap.h
 *
 * Creation Date: 21/10/2020
 *
 * Authors:
 * Leonardo Vencovsky (https://github.com/LeoVen)
 *
 */

/**
 * Heap
 *
 * A Heap that is stored in a fixed sized array. It works very much like a heap
 * but it is not resizeable and doesn't make use of dynamic memory allocation
 * internally.
 */

#ifndef CMC_SAC_HEAP_H
#define CMC_SAC_HEAP_H

/* -------------------------------------------------------------------------
 * Core functionalities of the C Macro Collections Library
 * ------------------------------------------------------------------------- */
#include "cor_core.h"

/* -------------------------------------------------------------------------
 * Heap Implementation
 * ------------------------------------------------------------------------- */
#include "cor_heap.h"

/**
 * Core Heap implementation
 *
 * \param ACCESS Either PUBLIC or PRIVATE
 * \param FILE   Either HEADER or SOURCE
 * \param PARAMS A tuple of form (PFX, SNAME, SIZE, K, V)
 */
#define CMC_SAC_HEAP_CORE(ACCESS, FILE, PARAMS) CMC_(CMC_(CMC_SAC_HEAP_CORE_, ACCESS), CMC_(_, FILE))(PARAMS)

/* PRIVATE or PUBLIC solver */
#define CMC_SAC_HEAP_CORE_PUBLIC_HEADER(PARAMS) \
    CMC_SAC_HEAP_CORE_STRUCT(PARAMS) \
    CMC_SAC_HEAP_CORE_HEADER(PARAMS)

#define CMC_SAC_HEAP_CORE_PUBLIC_SOURCE(PARAMS) CMC_SAC_HEAP_CORE_SOURCE(PARAMS)

#define CMC_SAC_HEAP_CORE_PRIVATE_HEADER(PARAMS) \
    struct CMC_PARAM_SNAME(PARAMS); \
    CMC_SAC_HEAP_CORE_HEADER(PARAMS)

#define CMC_SAC_HEAP_CORE_PRIVATE_SOURCE(PARAMS) \
    CMC_SAC_HEAP_CORE_STRUCT(PARAMS) \
    CMC_SAC_HEAP_CORE_SOURCE(PARAMS)

/* Lowest level API */
#define CMC_SAC_HEAP_CORE_STRUCT(PARAMS) \
    CMC_SAC_HEAP_CORE_STRUCT_(CMC_PARAM_PFX(PARAMS), CMC_PARAM_SIZE(PARAMS), CMC_PARAM_SNAME(PARAMS), CMC_PARAM_V(PARAMS))

#define CMC_SAC_HEAP_CORE_HEADER(PARAMS) \
    CMC_SAC_HEAP_CORE_HEADER_(CMC_PARAM_PFX(PARAMS), CMC_PARAM_SIZE(PARAMS), CMC_PARAM_SNAME(PARAMS), CMC_PARAM_V(PARAMS))

#define CMC_SAC_HEAP_CORE_SOURCE(PARAMS) \
    CMC_SAC_HEAP_CORE_SOURCE_(CMC_PARAM_PFX(PARAMS), CMC_PARAM_SIZE(PARAMS), CMC_PARAM_SNAME(PARAMS), CMC_PARAM_V(PARAMS))

/* -------------------------------------------------------------------------
 * Struct
 * ------------------------------------------------------------------------- */
#define CMC_SAC_HEAP_CORE_STRUCT_(PFX, SIZE, SNAME, V) \
\
    /* Heap Structure */ \
    struct SNAME \
    { \
        /* Array of elements */ \
        V buffer[SIZE]; \
\
        /* Current amount of elements in the heap */ \
        size_t count; \
\
        /* Heap order (MaxHeap or MinHeap) */ \
        enum cmc_heap_order HO; \
\
        /* Flags indicating errors or success */ \
        int flag; \
\
        /* Value function table */ \
        struct CMC_DEF_FVAL(SNAME) * f_val; \
\
        /* Custom callback functions */ \
        CMC_CALLBACKS_DECL; \
    };

/* -------------------------------------------------------------------------
 * Header
 * ------------------------------------------------------------------------- */
#define CMC_SAC_HEAP_CORE_HEADER_(PFX, SIZE, SNAME, V) \
\
    /* Value struct function table */ \
    struct CMC_DEF_FVAL(SNAME) \
    { \
        /* Comparator function */ \
        CMC_DEF_FTAB_CMP(V); \
\
        /* Copy function */ \
        CMC_DEF_FTAB_CPY(V); \
\
        /* To string function */ \
        CMC_DEF_FTAB_STR(V); \
\
        /* Free from memory function */ \
        CMC_DEF_FTAB_FREE(V); \
\
        /* Hash function */ \
        CMC_DEF_FTAB_HASH(V); \
\
        /* Priority function */ \
        CMC_DEF_FTAB_PRI(V); \
    }; \
\
    /* Collection Functions */ \
    /* Collection Allocation and Deallocation */ \
    struct SNAME CMC_(PFX, _new)(enum cmc_heap_order HO, struct CMC_DEF_FVAL(SNAME) * f_val); \
    struct SNAME CMC_(PFX, _new_custom)(enum cmc_heap_order HO, struct CMC_DEF_FVAL(SNAME) * f_val, \
                                         struct CMC_CALLBACKS_NAME * callbacks); \
    void CMC_(PFX, _free)(struct SNAME * _heap_); \
    /* Customization of Allocation and Callbacks */ \
    void CMC_(PFX, _customize)(struct SNAME * _heap_, \
                               struct CMC_CALLBACKS_NAME * callbacks); \
    /* Collection Input and Output */ \
    bool CMC_(PFX, _insert)(struct SNAME * _heap_, V value); \
    bool CMC_(PFX, _remove)(struct SNAME * _heap_); \
    /* Element Access */ \
    V CMC_(PFX, _peek)(struct SNAME * _heap_); \
    /* Collection State */ \
    bool CMC_(PFX, _contains)(struct SNAME * _heap_, V value); \
    bool CMC_(PFX, _empty)(struct SNAME * _heap_); \
    bool CMC_(PFX, _full)(struct SNAME * _heap_); \
    size_t CMC_(PFX, _count)(struct SNAME * _heap_); \
    size_t CMC_(PFX, _capacity)(struct SNAME * _heap_); \
    int CMC_(PFX, _flag)(struct SNAME * _heap_); \
    /* Collection Utility */ \
    struct SNAME CMC_(PFX, _copy_of)(struct SNAME * _heap_); \
    bool CMC_(PFX, _equals)(struct SNAME * _heap1_, struct SNAME * _heap2_);

/* -------------------------------------------------------------------------
 * Source
 * ------------------------------------------------------------------------- */
#define CMC_SAC_HEAP_CORE_SOURCE_(PFX, SIZE, SNAME, V) \
\
    /* Implementation Detail Functions */ \
    static void CMC_(PFX, _impl_float_up)(struct SNAME * _heap_, size_t index); \
    static void CMC_(PFX, _impl_float_down)(struct SNAME * _heap_, size_t index); \
\
    struct SNAME CMC_(PFX, _new)(enum cmc_heap_order HO, struct CMC_DEF_FVAL(SNAME) * f_val) \
    { \
        return CMC_(PFX, _new_custom)(HO, f_val, NULL); \
    } \
\
    struct SNAME CMC_(PFX, _new_custom)(enum cmc_heap_order HO, struct CMC_DEF_FVAL(SNAME) * f_val, \
                                         struct CMC_CALLBACKS_NAME * callbacks) \
    { \
        CMC_CALLBACKS_MAYBE_UNUSED(callbacks); \
\
        if (HO != CMC_MIN_HEAP && HO != CMC_MAX_HEAP) \
            return (struct SNAME){ .flag = CMC_FLAG_ERROR, 0 }; \
\
        if (!f_val) \
            return (struct SNAME){ .flag = CMC_FLAG_ERROR, 0 }; \
\
        struct SNAME _heap_ = { 0 }; \
\
        _heap_.HO = HO; \
        _heap_.f_val = f_val; \
        CMC_CALLBACKS_ASSIGN(&_heap_, callbacks); \
\
        return _heap_; \
    } \
\
    void CMC_(PFX, _free)(struct SNAME * _heap_) \
    { \
        if (_heap_->f_val->free) \
        { \
            for (size_t i = 0; i < _heap_->count; i++) \
            { \
                _heap_->f_val->free(_heap_->buffer[i]); \
            } \
        } \
\
        memset(_heap_, 0, sizeof(struct SNAME)); \
    } \
\
    void CMC_(PFX, _customize)(struct SNAME * _heap_, \
                               struct CMC_CALLBACKS_NAME * callbacks) \
    { \
        CMC_CALLBACKS_MAYBE_UNUSED(callbacks); \
\
        CMC_CALLBACKS_ASSIGN(_heap_, callbacks); \
\
        _heap_->flag = CMC_FLAG_OK; \
    } \
\
    bool CMC_(PFX, _insert)(struct SNAME * _heap_, V value) \
    { \
        if (CMC_(PFX, _full)(_heap_)) \
        { \
            _heap_->flag = CMC_FLAG_FULL; \
            return false; \
        } \
\
        _heap_->buffer[_heap_->count++] = value; \
\
        if (_heap_->count > 1) \
        { \
            CMC_(PFX, _impl_float_up)(_heap_, _heap_->count - 1); \
        } \
\
        _heap_->flag = CMC_FLAG_OK; \
\
        CMC_CALLBACKS_CALL(_heap_, create); \
\
        return true; \
    } \
\
    bool CMC_(PFX, _remove)(struct SNAME * _heap_) \
    { \
        if (CMC_(PFX, _empty)(_heap_)) \
        { \
            _heap_->flag = CMC_FLAG_EMPTY; \
            return false; \
        } \
\
        _heap_->buffer[0] = _heap_->buffer[_heap_->count - 1]; \
        _heap_->buffer[_heap_->count - 1] = (V){ 0 }; \
\
        _heap_->count--; \
\
        CMC_(PFX, _impl_float_down)(_heap_, 0); \
\
        _heap_->flag = CMC_FLAG_OK; \
\
        CMC_CALLBACKS_CALL(_heap_, delete); \
\
        return true; \
    } \
\
    V CMC_(PFX, _peek)(struct SNAME * _heap_) \
    { \
        if (CMC_(PFX, _empty)(_heap_)) \
        { \
            _heap_->flag = CMC_FLAG_EMPTY; \
            return (V){ 0 }; \
        } \
\
        _heap_->flag = CMC_FLAG_OK; \
\
        CMC_CALLBACKS_CALL(_heap_, read); \
\
        return _heap_->buffer[0]; \
    } \
\
    bool CMC_(PFX, _contains)(struct SNAME * _heap_, V value) \
    { \
        _heap_->flag = CMC_FLAG_OK; \
\
        bool result = false; \
\
        for (size_t i = 0; i < _heap_->count; i++) \
        { \
            if (_heap_->f_val->cmp(_heap_->buffer[i], value) == 0) \
            { \
                result = true; \
                break; \
            } \
        } \
\
        CMC_CALLBACKS_CALL(_heap_, read); \
\
        return result; \
    } \
\
    bool CMC_(PFX, _empty)(struct SNAME * _heap_) \
    { \
        return _heap_->count == 0; \
    } \
\
    bool CMC_(PFX, _full)(struct SNAME * _heap_) \
    { \
        return _heap_->count >= SIZE; \
    } \
\
    size_t CMC_(PFX, _count)(struct SNAME * _heap_) \
    { \
        return _heap_->count; \
    } \
\
    size_t CMC_(PFX, _capacity)(struct SNAME * _heap_) \
    { \
        return SIZE; \
    } \
\
    int CMC_(PFX, _flag)(struct SNAME * _heap_) \
    { \
        return _heap_->flag; \
    } \
\
    struct SNAME CMC_(PFX, _copy_of)(struct SNAME * _heap_) \
    { \
        struct SNAME result = \
            CMC_(PFX, _new_custom)(_heap_->HO, _heap_->f_val, NULL); \
\
        CMC_CALLBACKS_ASSIGN(&result, _heap_->callbacks); \
\
        if (_heap_->f_val->cpy) \
        { \
            for (size_t i = 0; i < _heap_->count; i++) \
                result.buffer[i] = _heap_->f_val->cpy(_heap_->buffer[i]); \
        } \
        else \
            memcpy(result.buffer, _heap_->buffer, sizeof(V) * _heap_->count); \
\
        result.count = _heap_->count; \
        _heap_->flag = CMC_FLAG_OK; \
\
        return result; \
    } \
\
    bool CMC_(PFX, _equals)(struct SNAME * _heap1_, struct SNAME * _heap2_) \
    { \
        _heap1_->flag = CMC_FLAG_OK; \
        _heap2_->flag = CMC_FLAG_OK; \
\
        if (_heap1_->count != _heap2_->count) \
            return false; \
\
        for (size_t i = 0; i < _heap1_->count; i++) \
        { \
            if (_heap1_->f_val->cmp(_heap1_->buffer[i], _heap2_->buffer[i]) != 0) \
                return false; \
        } \
\
        return true; \
    } \
\
    static void CMC_(PFX, _impl_float_up)(struct SNAME * _heap_, size_t index) \
    { \
        /* Current index */ \
        size_t C = index; \
        V child = _heap_->buffer[C]; \
        V parent = _heap_->buffer[(index - 1) / 2]; \
\
        int mod = _heap_->HO; \
\
        while (C > 0 && _heap_->f_val->cmp(child, parent) * mod > 0) \
        { \
            /* Swap between C (current element) and its parent */ \
            V tmp = _heap_->buffer[C]; \
            _heap_->buffer[C] = _heap_->buffer[(C - 1) / 2]; \
            _heap_->buffer[(C - 1) / 2] = tmp; \
\
            /* Go to parent */ \
            C = (C - 1) / 2; \
\
            /* Prevent the two lines below from accessing a negative index */ \
            if (C == 0) \
                break; \
\
            child = _heap_->buffer[C]; \
            parent = _heap_->buffer[(C - 1) / 2]; \
        } \
    } \
\
    static void CMC_(PFX, _impl_float_down)(struct SNAME * _heap_, size_t index) \
    { \
        int mod = _heap_->HO; \
\
        while (index < _heap_->count) \
        { \
            size_t L = 2 * index + 1; \
            size_t R = 2 * index + 2; \
            size_t C = index; \
\
            /* Determine if we swap with the left or right element */ \
            if (L < _heap_->count && _heap_->f_val->cmp(_heap_->buffer[L], _heap_->buffer[C]) * mod > 0) \
            { \
                C = L; \
            } \
\
            if (R < _heap_->count && _heap_->f_val->cmp(_heap_->buffer[R], _heap_->buffer[C]) * mod > 0) \
            { \
                C = R; \
            } \
\
            /* Swap only if either left or right was picked, otherwise done */ \
            if (C != index) \
            { \
                V tmp = _heap_->buffer[index]; \
                _heap_->buffer[index] = _heap_->buffer[C]; \
                _heap_->buffer[C] = tmp; \
\
                index = C; \
            } \
            else \
                break; \
        } \
    }

#endif /* CMC_SAC_HEAP_H */
