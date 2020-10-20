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
 * sac_queue.h
 *
 * Creation Date: 20/10/2020
 *
 * Authors:
 * Leonardo Vencovsky (https://github.com/LeoVen)
 *
 */

/**
 * Queue
 *
 * A Queue that is stored in a fixed sized array. It works very much like a
 * queue but it is not resizeable and doesn't make use of dynamic memory
 * allocation internally.
 */

#ifndef CMC_SAC_QUEUE_H
#define CMC_SAC_QUEUE_H

/* -------------------------------------------------------------------------
 * Core functionalities of the C Macro Collections Library
 * ------------------------------------------------------------------------- */
#include "cor_core.h"

/**
 * Core Queue implementation
 *
 * \param ACCESS Either PUBLIC or PRIVATE
 * \param FILE   Either HEADER or SOURCE
 * \param PARAMS A tuple of form (PFX, SNAME, SIZE, K, V)
 */
#define CMC_SAC_QUEUE_CORE(ACCESS, FILE, PARAMS) CMC_(CMC_(CMC_SAC_QUEUE_CORE_, ACCESS), CMC_(_, FILE))(PARAMS)

/* PRIVATE or PUBLIC solver */
#define CMC_SAC_QUEUE_CORE_PUBLIC_HEADER(PARAMS) \
    CMC_SAC_QUEUE_CORE_STRUCT(PARAMS) \
    CMC_SAC_QUEUE_CORE_HEADER(PARAMS)

#define CMC_SAC_QUEUE_CORE_PUBLIC_SOURCE(PARAMS) CMC_SAC_QUEUE_CORE_SOURCE(PARAMS)

#define CMC_SAC_QUEUE_CORE_PRIVATE_HEADER(PARAMS) \
    struct CMC_PARAM_SNAME(PARAMS); \
    CMC_SAC_QUEUE_CORE_HEADER(PARAMS)

#define CMC_SAC_QUEUE_CORE_PRIVATE_SOURCE(PARAMS) \
    CMC_SAC_QUEUE_CORE_STRUCT(PARAMS) \
    CMC_SAC_QUEUE_CORE_SOURCE(PARAMS)

/* Lowest level API */
#define CMC_SAC_QUEUE_CORE_STRUCT(PARAMS) \
    CMC_SAC_QUEUE_CORE_STRUCT_(CMC_PARAM_PFX(PARAMS), CMC_PARAM_SIZE(PARAMS), CMC_PARAM_SNAME(PARAMS), CMC_PARAM_V(PARAMS))

#define CMC_SAC_QUEUE_CORE_HEADER(PARAMS) \
    CMC_SAC_QUEUE_CORE_HEADER_(CMC_PARAM_PFX(PARAMS), CMC_PARAM_SIZE(PARAMS), CMC_PARAM_SNAME(PARAMS), CMC_PARAM_V(PARAMS))

#define CMC_SAC_QUEUE_CORE_SOURCE(PARAMS) \
    CMC_SAC_QUEUE_CORE_SOURCE_(CMC_PARAM_PFX(PARAMS), CMC_PARAM_SIZE(PARAMS), CMC_PARAM_SNAME(PARAMS), CMC_PARAM_V(PARAMS))

/* -------------------------------------------------------------------------
 * Struct
 * ------------------------------------------------------------------------- */
#define CMC_SAC_QUEUE_CORE_STRUCT_(PFX, SIZE, SNAME, V) \
\
    /* Queue Structure */ \
    struct SNAME \
    { \
        /* Dynamic circular array of elements */ \
        V buffer[SIZE]; \
\
        /* Current circular array capacity */ \
        size_t capacity; \
\
        /* Current amount of elements */ \
        size_t count; \
\
        /* Index representing the front of the queue */ \
        size_t front; \
\
        /* Index representing the back of the queue */ \
        size_t back; \
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
#define CMC_SAC_QUEUE_CORE_HEADER_(PFX, SIZE, SNAME, V) \
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
    struct SNAME CMC_(PFX, _new)(struct CMC_DEF_FVAL(SNAME) * f_val); \
    struct SNAME CMC_(PFX, _new_custom)(struct CMC_DEF_FVAL(SNAME) * f_val, \
                                         struct CMC_CALLBACKS_NAME * callbacks); \
    void CMC_(PFX, _free)(struct SNAME * _queue_); \
    /* Customization of Allocation and Callbacks */ \
    void CMC_(PFX, _customize)(struct SNAME * _queue_, \
                               struct CMC_CALLBACKS_NAME * callbacks); \
    /* Collection Input and Output */ \
    bool CMC_(PFX, _enqueue)(struct SNAME * _queue_, V value); \
    bool CMC_(PFX, _dequeue)(struct SNAME * _queue_); \
    /* Element Access */ \
    V CMC_(PFX, _peek)(struct SNAME * _queue_); \
    /* Collection State */ \
    bool CMC_(PFX, _contains)(struct SNAME * _queue_, V value); \
    bool CMC_(PFX, _empty)(struct SNAME * _queue_); \
    bool CMC_(PFX, _full)(struct SNAME * _queue_); \
    size_t CMC_(PFX, _count)(struct SNAME * _queue_); \
    size_t CMC_(PFX, _capacity)(struct SNAME * _queue_); \
    int CMC_(PFX, _flag)(struct SNAME * _queue_); \
    /* Collection Utility */ \
    struct SNAME CMC_(PFX, _copy_of)(struct SNAME * _queue_); \
    bool CMC_(PFX, _equals)(struct SNAME * _queue1_, struct SNAME * _queue2_);

/* -------------------------------------------------------------------------
 * Source
 * ------------------------------------------------------------------------- */
#define CMC_SAC_QUEUE_CORE_SOURCE_(PFX, SIZE, SNAME, V) \
\
    /* Implementation Detail Functions */ \
    /* None */ \
\
    struct SNAME CMC_(PFX, _new)(struct CMC_DEF_FVAL(SNAME) * f_val) \
    { \
        return CMC_(PFX, _new_custom)(f_val, NULL); \
    } \
\
    struct SNAME CMC_(PFX, _new_custom)(struct CMC_DEF_FVAL(SNAME) * f_val, \
                                         struct CMC_CALLBACKS_NAME * callbacks) \
    { \
        CMC_CALLBACKS_MAYBE_UNUSED(callbacks); \
\
        if (!f_val) \
            return (struct SNAME){ .flag = CMC_FLAG_ERROR, 0 }; \
\
        struct SNAME _queue_ = { 0 }; \
\
        _queue_.f_val = f_val; \
        CMC_CALLBACKS_ASSIGN(&_queue_, callbacks); \
\
        return _queue_; \
    } \
\
    void CMC_(PFX, _free)(struct SNAME * _queue_) \
    { \
        if (_queue_->f_val->free) \
        { \
            for (size_t i = _queue_->front, j = 0; j < _queue_->count; j++) \
            { \
                _queue_->f_val->free(_queue_->buffer[i]); \
\
                i = (i + 1) % SIZE; \
            } \
        } \
\
        memset(_queue_, 0, sizeof(struct SNAME)); \
    } \
\
    void CMC_(PFX, _customize)(struct SNAME * _queue_, \
                               struct CMC_CALLBACKS_NAME * callbacks) \
    { \
        CMC_CALLBACKS_MAYBE_UNUSED(callbacks); \
\
        CMC_CALLBACKS_ASSIGN(_queue_, callbacks); \
\
        _queue_->flag = CMC_FLAG_OK; \
    } \
\
    bool CMC_(PFX, _enqueue)(struct SNAME * _queue_, V value) \
    { \
        if (CMC_(PFX, _full)(_queue_)) \
        { \
            _queue_->flag = CMC_FLAG_FULL; \
            return false; \
        } \
\
        _queue_->buffer[_queue_->back] = value; \
\
        _queue_->back = (_queue_->back == SIZE - 1) ? 0 : _queue_->back + 1; \
        _queue_->count++; \
        _queue_->flag = CMC_FLAG_OK; \
\
        CMC_CALLBACKS_CALL(_queue_, create); \
\
        return true; \
    } \
\
    bool CMC_(PFX, _dequeue)(struct SNAME * _queue_) \
    { \
        if (CMC_(PFX, _empty)(_queue_)) \
        { \
            _queue_->flag = CMC_FLAG_EMPTY; \
            return false; \
        } \
\
        _queue_->buffer[_queue_->front] = (V){ 0 }; \
\
        _queue_->front = (_queue_->front == SIZE - 1) ? 0 : _queue_->front + 1; \
        _queue_->count--; \
        _queue_->flag = CMC_FLAG_OK; \
\
        CMC_CALLBACKS_CALL(_queue_, delete); \
\
        return true; \
    } \
\
    V CMC_(PFX, _peek)(struct SNAME * _queue_) \
    { \
        if (CMC_(PFX, _empty)(_queue_)) \
        { \
            _queue_->flag = CMC_FLAG_EMPTY; \
            return (V){ 0 }; \
        } \
\
        _queue_->flag = CMC_FLAG_OK; \
\
        CMC_CALLBACKS_CALL(_queue_, read); \
\
        return _queue_->buffer[_queue_->front]; \
    } \
\
    bool CMC_(PFX, _contains)(struct SNAME * _queue_, V value) \
    { \
        _queue_->flag = CMC_FLAG_OK; \
\
        bool result = false; \
\
        for (size_t i = _queue_->front, j = 0; j < _queue_->count; j++) \
        { \
            if (_queue_->f_val->cmp(_queue_->buffer[i], value) == 0) \
            { \
                result = true; \
                break; \
            } \
\
            i = (i + 1) % SIZE; \
        } \
\
        CMC_CALLBACKS_CALL(_queue_, read); \
\
        return result; \
    } \
\
    bool CMC_(PFX, _empty)(struct SNAME * _queue_) \
    { \
        return _queue_->count == 0; \
    } \
\
    bool CMC_(PFX, _full)(struct SNAME * _queue_) \
    { \
        return _queue_->count >= SIZE; \
    } \
\
    size_t CMC_(PFX, _count)(struct SNAME * _queue_) \
    { \
        return _queue_->count; \
    } \
\
    size_t CMC_(PFX, _capacity)(struct SNAME * _queue_) \
    { \
        return SIZE; \
    } \
\
    int CMC_(PFX, _flag)(struct SNAME * _queue_) \
    { \
        return _queue_->flag; \
    } \
\
    struct SNAME CMC_(PFX, _copy_of)(struct SNAME * _queue_) \
    { \
        struct SNAME result = CMC_(PFX, _new_custom)(_queue_->f_val, NULL); \
\
        CMC_CALLBACKS_ASSIGN(&result, _queue_->callbacks); \
\
        if (_queue_->f_val->cpy) \
        { \
            for (size_t i = _queue_->front, j = 0; j < _queue_->count; j++) \
            { \
                result.buffer[j] = _queue_->f_val->cpy(_queue_->buffer[i]); \
\
                i = (i + 1) % SIZE; \
            } \
        } \
        else \
        { \
            for (size_t i = _queue_->front, j = 0; j < _queue_->count; j++) \
            { \
                result.buffer[j] = _queue_->buffer[i]; \
\
                i = (i + 1) % SIZE; \
            } \
        } \
\
        result.count = _queue_->count; \
        result.front = 0; \
        result.back = _queue_->count; \
\
        _queue_->flag = CMC_FLAG_OK; \
\
        return result; \
    } \
\
    bool CMC_(PFX, _equals)(struct SNAME * _queue1_, struct SNAME * _queue2_) \
    { \
        _queue1_->flag = CMC_FLAG_OK; \
        _queue2_->flag = CMC_FLAG_OK; \
\
        if (_queue1_->count != _queue2_->count) \
            return false; \
\
        size_t i, j, k; \
        for (i = _queue1_->front, j = _queue2_->front, k = 0; k < _queue1_->count; k++) \
        { \
            if (_queue1_->f_val->cmp(_queue1_->buffer[i], _queue2_->buffer[j]) != 0) \
                return false; \
\
            i = (i + 1) % SIZE; \
            j = (j + 1) % SIZE; \
        } \
\
        return true; \
    }

#endif /* CMC_SAC_QUEUE_H */
