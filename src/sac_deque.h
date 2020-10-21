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
 * sac_deque.h
 *
 * Creation Date: 08/10/2020
 *
 * Authors:
 * Leonardo Vencovsky (https://github.com/LeoVen)
 *
 */

/**
 * Deque
 *
 * A Deque that is stored in a fixed sized array. It works very much like a
 * deque but it is not resizeable and doesn't make use of dynamic memory
 * allocation internally.
 */

#ifndef CMC_SAC_DEQUE_H
#define CMC_SAC_DEQUE_H

/* -------------------------------------------------------------------------
 * Core functionalities of the C Macro Collections Library
 * ------------------------------------------------------------------------- */
#include "cor_core.h"

/**
 * Core Deque implementation
 *
 * \param ACCESS Either PUBLIC or PRIVATE
 * \param FILE   Either HEADER or SOURCE
 * \param PARAMS A tuple of form (PFX, SNAME, SIZE, K, V)
 */
#define CMC_SAC_DEQUE_CORE(ACCESS, FILE, PARAMS) CMC_(CMC_(CMC_SAC_DEQUE_CORE_, ACCESS), CMC_(_, FILE))(PARAMS)

/* PRIVATE or PUBLIC solver */
#define CMC_SAC_DEQUE_CORE_PUBLIC_HEADER(PARAMS) \
    CMC_SAC_DEQUE_CORE_STRUCT(PARAMS) \
    CMC_SAC_DEQUE_CORE_HEADER(PARAMS)

#define CMC_SAC_DEQUE_CORE_PUBLIC_SOURCE(PARAMS) CMC_SAC_DEQUE_CORE_SOURCE(PARAMS)

#define CMC_SAC_DEQUE_CORE_PRIVATE_HEADER(PARAMS) \
    struct CMC_PARAM_SNAME(PARAMS); \
    CMC_SAC_DEQUE_CORE_HEADER(PARAMS)

#define CMC_SAC_DEQUE_CORE_PRIVATE_SOURCE(PARAMS) \
    CMC_SAC_DEQUE_CORE_STRUCT(PARAMS) \
    CMC_SAC_DEQUE_CORE_SOURCE(PARAMS)

/* Lowest level API */
#define CMC_SAC_DEQUE_CORE_STRUCT(PARAMS) \
    CMC_SAC_DEQUE_CORE_STRUCT_(CMC_PARAM_PFX(PARAMS), CMC_PARAM_SIZE(PARAMS), CMC_PARAM_SNAME(PARAMS), \
                               CMC_PARAM_V(PARAMS))

#define CMC_SAC_DEQUE_CORE_HEADER(PARAMS) \
    CMC_SAC_DEQUE_CORE_HEADER_(CMC_PARAM_PFX(PARAMS), CMC_PARAM_SIZE(PARAMS), CMC_PARAM_SNAME(PARAMS), \
                               CMC_PARAM_V(PARAMS))

#define CMC_SAC_DEQUE_CORE_SOURCE(PARAMS) \
    CMC_SAC_DEQUE_CORE_SOURCE_(CMC_PARAM_PFX(PARAMS), CMC_PARAM_SIZE(PARAMS), CMC_PARAM_SNAME(PARAMS), \
                               CMC_PARAM_V(PARAMS))

/* -------------------------------------------------------------------------
 * Struct
 * ------------------------------------------------------------------------- */
#define CMC_SAC_DEQUE_CORE_STRUCT_(PFX, SIZE, SNAME, V) \
\
    /* Deque Structure */ \
    struct SNAME \
    { \
        /* Circular array of elements */ \
        V buffer[SIZE]; \
\
        /* Current amount of elements */ \
        size_t count; \
\
        /* Index representing the front of the deque */ \
        size_t front; \
\
        /* Index representing the back of the deque */ \
        size_t back; \
\
        /* Flags indicating errors or success */ \
        int flag; \
\
        struct CMC_DEF_FVAL(SNAME) * f_val; \
\
        /* Custom callback functions */ \
        CMC_CALLBACKS_DECL; \
    };

/* -------------------------------------------------------------------------
 * Header
 * ------------------------------------------------------------------------- */
#define CMC_SAC_DEQUE_CORE_HEADER_(PFX, SIZE, SNAME, V) \
\
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
    struct SNAME CMC_(PFX, _new)(struct CMC_DEF_FVAL(SNAME) * f_val); \
    struct SNAME CMC_(PFX, _new_custom)(struct CMC_DEF_FVAL(SNAME) * f_val, struct CMC_CALLBACKS_NAME * callbacks); \
    void CMC_(PFX, _clear)(struct SNAME * _deque_); \
    void CMC_(PFX, _free)(struct SNAME * _deque_); \
    /* Customization of Allocation and Callbacks */ \
    void CMC_(PFX, _customize)(struct SNAME * _deque_, struct CMC_CALLBACKS_NAME * callbacks); \
    /* Collection Input and Output */ \
    bool CMC_(PFX, _push_front)(struct SNAME * _deque_, V value); \
    bool CMC_(PFX, _push_back)(struct SNAME * _deque_, V value); \
    bool CMC_(PFX, _pop_front)(struct SNAME * _deque_); \
    bool CMC_(PFX, _pop_back)(struct SNAME * _deque_); \
    /* Element Access */ \
    V CMC_(PFX, _front)(struct SNAME * _deque_); \
    V CMC_(PFX, _back)(struct SNAME * _deque_); \
    /* Collection State */ \
    bool CMC_(PFX, _contains)(struct SNAME * _deque_, V value); \
    bool CMC_(PFX, _empty)(struct SNAME * _deque_); \
    bool CMC_(PFX, _full)(struct SNAME * _deque_); \
    size_t CMC_(PFX, _count)(struct SNAME * _deque_); \
    size_t CMC_(PFX, _capacity)(struct SNAME * _deque_); \
    int CMC_(PFX, _flag)(struct SNAME * _deque_); \
    /* Collection Utility */ \
    struct SNAME CMC_(PFX, _copy_of)(struct SNAME * _deque_); \
    bool CMC_(PFX, _equals)(struct SNAME * _deque1_, struct SNAME * _deque2_);

/* -------------------------------------------------------------------------
 * Source
 * ------------------------------------------------------------------------- */
#define CMC_SAC_DEQUE_CORE_SOURCE_(PFX, SIZE, SNAME, V) \
\
    /* Implementation Detail Functions */ \
    /* None */ \
\
    struct SNAME CMC_(PFX, _new)(struct CMC_DEF_FVAL(SNAME) * f_val) \
    { \
        return CMC_(PFX, _new_custom)(f_val, NULL); \
    } \
\
    struct SNAME CMC_(PFX, _new_custom)(struct CMC_DEF_FVAL(SNAME) * f_val, struct CMC_CALLBACKS_NAME * callbacks) \
    { \
        CMC_CALLBACKS_MAYBE_UNUSED(callbacks); \
\
        if (!f_val) \
            return (struct SNAME){ .flag = CMC_FLAG_ERROR, 0 }; \
\
        struct SNAME _deque_ = { 0 }; \
\
        _deque_.f_val = f_val; \
        CMC_CALLBACKS_ASSIGN(&_deque_, callbacks); \
\
        return _deque_; \
    } \
\
    void CMC_(PFX, _free)(struct SNAME * _deque_) \
    { \
        if (_deque_->f_val->free) \
        { \
            for (size_t i = _deque_->front, j = 0; j < _deque_->count; j++) \
            { \
                _deque_->f_val->free(_deque_->buffer[i]); \
\
                i = (i + 1) % SIZE; \
            } \
        } \
\
        memset(_deque_, 0, sizeof(struct SNAME)); \
    } \
\
    void CMC_(PFX, _customize)(struct SNAME * _deque_, struct CMC_CALLBACKS_NAME * callbacks) \
    { \
        CMC_CALLBACKS_MAYBE_UNUSED(callbacks); \
\
        CMC_CALLBACKS_ASSIGN(_deque_, callbacks); \
\
        _deque_->flag = CMC_FLAG_OK; \
    } \
\
    bool CMC_(PFX, _push_front)(struct SNAME * _deque_, V value) \
    { \
        if (CMC_(PFX, _full)(_deque_)) \
        { \
            _deque_->flag = CMC_FLAG_FULL; \
            return false; \
        } \
\
        _deque_->front = (_deque_->front == 0) ? SIZE - 1 : _deque_->front - 1; \
\
        _deque_->buffer[_deque_->front] = value; \
\
        _deque_->count++; \
        _deque_->flag = CMC_FLAG_OK; \
\
        CMC_CALLBACKS_CALL(_deque_, create); \
\
        return true; \
    } \
\
    bool CMC_(PFX, _push_back)(struct SNAME * _deque_, V value) \
    { \
        if (CMC_(PFX, _full)(_deque_)) \
        { \
            _deque_->flag = CMC_FLAG_FULL; \
            return false; \
        } \
\
        _deque_->buffer[_deque_->back] = value; \
\
        _deque_->back = (_deque_->back == SIZE - 1) ? 0 : _deque_->back + 1; \
\
        _deque_->count++; \
        _deque_->flag = CMC_FLAG_OK; \
\
        CMC_CALLBACKS_CALL(_deque_, create); \
\
        return true; \
    } \
\
    bool CMC_(PFX, _pop_front)(struct SNAME * _deque_) \
    { \
        if (CMC_(PFX, _empty)(_deque_)) \
        { \
            _deque_->flag = CMC_FLAG_EMPTY; \
            return false; \
        } \
\
        _deque_->buffer[_deque_->front] = (V){ 0 }; \
\
        _deque_->front = (_deque_->front == SIZE - 1) ? 0 : _deque_->front + 1; \
\
        _deque_->count--; \
        _deque_->flag = CMC_FLAG_OK; \
\
        CMC_CALLBACKS_CALL(_deque_, delete); \
\
        return true; \
    } \
\
    bool CMC_(PFX, _pop_back)(struct SNAME * _deque_) \
    { \
        if (CMC_(PFX, _empty)(_deque_)) \
        { \
            _deque_->flag = CMC_FLAG_EMPTY; \
            return false; \
        } \
\
        _deque_->back = (_deque_->back == 0) ? SIZE - 1 : _deque_->back - 1; \
\
        _deque_->buffer[_deque_->back] = (V){ 0 }; \
\
        _deque_->count--; \
        _deque_->flag = CMC_FLAG_OK; \
\
        CMC_CALLBACKS_CALL(_deque_, delete); \
\
        return true; \
    } \
\
    V CMC_(PFX, _front)(struct SNAME * _deque_) \
    { \
        if (CMC_(PFX, _empty)(_deque_)) \
        { \
            _deque_->flag = CMC_FLAG_EMPTY; \
            return (V){ 0 }; \
        } \
\
        _deque_->flag = CMC_FLAG_OK; \
\
        CMC_CALLBACKS_CALL(_deque_, read); \
\
        return _deque_->buffer[_deque_->front]; \
    } \
\
    V CMC_(PFX, _back)(struct SNAME * _deque_) \
    { \
        if (CMC_(PFX, _empty)(_deque_)) \
        { \
            _deque_->flag = CMC_FLAG_EMPTY; \
            return (V){ 0 }; \
        } \
\
        _deque_->flag = CMC_FLAG_OK; \
\
        CMC_CALLBACKS_CALL(_deque_, read); \
\
        return _deque_->buffer[(_deque_->back == 0) ? SIZE - 1 : _deque_->back - 1]; \
    } \
\
    bool CMC_(PFX, _contains)(struct SNAME * _deque_, V value) \
    { \
        _deque_->flag = CMC_FLAG_OK; \
\
        bool result = false; \
\
        for (size_t i = _deque_->front, j = 0; j < _deque_->count; j++) \
        { \
            if (_deque_->f_val->cmp(_deque_->buffer[i], value) == 0) \
            { \
                result = true; \
                break; \
            } \
\
            i = (i + 1) % SIZE; \
        } \
\
        CMC_CALLBACKS_CALL(_deque_, read); \
\
        return result; \
    } \
\
    bool CMC_(PFX, _empty)(struct SNAME * _deque_) \
    { \
        return _deque_->count == 0; \
    } \
\
    bool CMC_(PFX, _full)(struct SNAME * _deque_) \
    { \
        return _deque_->count >= SIZE; \
    } \
\
    size_t CMC_(PFX, _count)(struct SNAME * _deque_) \
    { \
        return _deque_->count; \
    } \
\
    size_t CMC_(PFX, _capacity)(struct SNAME * _deque_) \
    { \
        return SIZE; \
    } \
\
    int CMC_(PFX, _flag)(struct SNAME * _deque_) \
    { \
        return _deque_->flag; \
    } \
\
    struct SNAME CMC_(PFX, _copy_of)(struct SNAME * _deque_) \
    { \
        struct SNAME result = CMC_(PFX, _new_custom)(_deque_->f_val, NULL); \
\
        if (result.flag == CMC_FLAG_ERROR) \
            return result; \
\
        CMC_CALLBACKS_ASSIGN(&result, _deque_->callbacks); \
\
        if (_deque_->f_val->cpy) \
        { \
            for (size_t i = _deque_->front, j = 0; j < _deque_->count; j++) \
            { \
                result.buffer[j] = _deque_->f_val->cpy(_deque_->buffer[i]); \
\
                i = (i + 1) % SIZE; \
            } \
        } \
        else \
        { \
            for (size_t i = _deque_->front, j = 0; j < _deque_->count; j++) \
            { \
                result.buffer[j] = _deque_->buffer[i]; \
\
                i = (i + 1) % SIZE; \
            } \
        } \
\
        result.count = _deque_->count; \
        result.front = 0; \
        result.back = _deque_->count; \
\
        _deque_->flag = CMC_FLAG_OK; \
\
        return result; \
    } \
\
    bool CMC_(PFX, _equals)(struct SNAME * _deque1_, struct SNAME * _deque2_) \
    { \
        _deque1_->flag = CMC_FLAG_OK; \
        _deque2_->flag = CMC_FLAG_OK; \
\
        if (_deque1_->count != _deque2_->count) \
            return false; \
\
        size_t i, j, k; \
        for (i = _deque1_->front, j = _deque2_->front, k = 0; k < _deque1_->count; k++) \
        { \
            if (_deque1_->f_val->cmp(_deque1_->buffer[i], _deque2_->buffer[j]) != 0) \
                return false; \
\
            i = (i + 1) % SIZE; \
            j = (j + 1) % SIZE; \
        } \
\
        return true; \
    }

#endif /* CMC_SAC_DEQUE_H */
