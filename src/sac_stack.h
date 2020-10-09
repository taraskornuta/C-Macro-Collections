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
 * sac_stack.h
 *
 * Creation Date: 09/10/2020
 *
 * Authors:
 * Leonardo Vencovsky (https://github.com/LeoVen)
 *
 */

/**
 * Stack
 *
 * A Stack that is stored in a fixed sized array. It works very much like a
 * stack but it is not resizeable and doesn't make use of dynamic memory
 * allocation internally.
 */

#ifndef CMC_SAC_STACK_H
#define CMC_SAC_STACK_H

/* -------------------------------------------------------------------------
 * Core functionalities of the C Macro Collections Library
 * ------------------------------------------------------------------------- */
#include "cor_core.h"

/**
 * Core Stack implementation
 *
 * \param ACCESS Either PUBLIC or PRIVATE
 * \param FILE   Either HEADER or SOURCE
 * \param PARAMS A tuple of form (PFX, SNAME, SIZE, K, V)
 */
#define CMC_SAC_STACK_CORE(ACCESS, FILE, PARAMS) CMC_(CMC_(CMC_SAC_STACK_CORE_, ACCESS), CMC_(_, FILE))(PARAMS)

/* PRIVATE or PUBLIC solver */
#define CMC_SAC_STACK_CORE_PUBLIC_HEADER(PARAMS) \
    CMC_SAC_STACK_CORE_STRUCT(PARAMS) \
    CMC_SAC_STACK_CORE_HEADER(PARAMS)

#define CMC_SAC_STACK_CORE_PUBLIC_SOURCE(PARAMS) CMC_SAC_STACK_CORE_SOURCE(PARAMS)

#define CMC_SAC_STACK_CORE_PRIVATE_HEADER(PARAMS) \
    struct CMC_PARAM_SNAME(PARAMS); \
    CMC_SAC_STACK_CORE_HEADER(PARAMS)

#define CMC_SAC_STACK_CORE_PRIVATE_SOURCE(PARAMS) \
    CMC_SAC_STACK_CORE_STRUCT(PARAMS) \
    CMC_SAC_STACK_CORE_SOURCE(PARAMS)

/* Lowest level API */
#define CMC_SAC_STACK_CORE_STRUCT(PARAMS) \
    CMC_SAC_STACK_CORE_STRUCT_(CMC_PARAM_PFX(PARAMS), CMC_PARAM_SIZE(PARAMS), CMC_PARAM_SNAME(PARAMS), CMC_PARAM_V(PARAMS))

#define CMC_SAC_STACK_CORE_HEADER(PARAMS) \
    CMC_SAC_STACK_CORE_HEADER_(CMC_PARAM_PFX(PARAMS), CMC_PARAM_SIZE(PARAMS), CMC_PARAM_SNAME(PARAMS), CMC_PARAM_V(PARAMS))

#define CMC_SAC_STACK_CORE_SOURCE(PARAMS) \
    CMC_SAC_STACK_CORE_SOURCE_(CMC_PARAM_PFX(PARAMS), CMC_PARAM_SIZE(PARAMS), CMC_PARAM_SNAME(PARAMS), CMC_PARAM_V(PARAMS))

/* -------------------------------------------------------------------------
 * Struct
 * ------------------------------------------------------------------------- */
#define CMC_SAC_STACK_CORE_STRUCT_(PFX, SIZE, SNAME, V) \
\
    /* Stack Structure */ \
    struct SNAME \
    { \
        /* Dynamic array of elements */ \
        V buffer[SIZE]; \
\
        /* Current amount of elements */ \
        size_t count; \
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
#define CMC_SAC_STACK_CORE_HEADER_(PFX, SIZE, SNAME, V) \
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
    struct SNAME CMC_(PFX, _new_custom)(struct CMC_DEF_FVAL(SNAME) * f_val, struct CMC_CALLBACKS_NAME * callbacks); \
    void CMC_(PFX, _clear)(struct SNAME * _stack_); \
    void CMC_(PFX, _free)(struct SNAME * _stack_); \
    /* Customization of Allocation and Callbacks */ \
    void CMC_(PFX, _customize)(struct SNAME * _stack_, \
                               struct CMC_CALLBACKS_NAME * callbacks); \
    /* Collection Input and Output */ \
    bool CMC_(PFX, _push)(struct SNAME * _stack_, V value); \
    bool CMC_(PFX, _pop)(struct SNAME * _stack_); \
    /* Element Access */ \
    V CMC_(PFX, _top)(struct SNAME * _stack_); \
    /* Collection State */ \
    bool CMC_(PFX, _contains)(struct SNAME * _stack_, V value); \
    bool CMC_(PFX, _empty)(struct SNAME * _stack_); \
    bool CMC_(PFX, _full)(struct SNAME * _stack_); \
    size_t CMC_(PFX, _count)(struct SNAME * _stack_); \
    size_t CMC_(PFX, _capacity)(struct SNAME * _stack_); \
    int CMC_(PFX, _flag)(struct SNAME * _stack_); \
    /* Collection Utility */ \
    struct SNAME CMC_(PFX, _copy_of)(struct SNAME * _stack_); \
    bool CMC_(PFX, _equals)(struct SNAME * _stack1_, struct SNAME * _stack2_);

/* -------------------------------------------------------------------------
 * Source
 * ------------------------------------------------------------------------- */
#define CMC_SAC_STACK_CORE_SOURCE_(PFX, SIZE, SNAME, V) \
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
            return (struct SNAME) { .flag = CMC_FLAG_ERROR, 0 }; \
\
        struct SNAME _stack_ = { 0 }; \
\
        _stack_.f_val = f_val; \
        CMC_CALLBACKS_ASSIGN(&_stack_, callbacks); \
\
        return _stack_; \
    } \
\
    void CMC_(PFX, _clear)(struct SNAME * _stack_) \
    { \
        if (_stack_->f_val->free) \
        { \
            for (size_t i = 0; i < _stack_->count; i++) \
                _stack_->f_val->free(_stack_->buffer[i]); \
        } \
\
        memset(_stack_->buffer, 0, sizeof(V) * SIZE); \
\
        _stack_->count = 0; \
        _stack_->flag = CMC_FLAG_OK; \
    } \
\
    void CMC_(PFX, _free)(struct SNAME * _stack_) \
    { \
        if (_stack_->f_val->free) \
        { \
            for (size_t i = 0; i < _stack_->count; i++) \
                _stack_->f_val->free(_stack_->buffer[i]); \
        } \
\
        memset(_stack_, 0, sizeof(struct SNAME)); \
    } \
\
    void CMC_(PFX, _customize)(struct SNAME * _stack_, \
                               struct CMC_CALLBACKS_NAME * callbacks) \
    { \
        CMC_CALLBACKS_MAYBE_UNUSED(callbacks); \
\
        CMC_CALLBACKS_ASSIGN(_stack_, callbacks); \
\
        _stack_->flag = CMC_FLAG_OK; \
    } \
\
    bool CMC_(PFX, _push)(struct SNAME * _stack_, V value) \
    { \
        if (CMC_(PFX, _full)(_stack_)) \
        { \
            _stack_->flag = CMC_FLAG_FULL; \
            return false; \
        } \
\
        _stack_->buffer[_stack_->count++] = value; \
\
        _stack_->flag = CMC_FLAG_OK; \
\
        CMC_CALLBACKS_CALL(_stack_, create); \
\
        return true; \
    } \
\
    bool CMC_(PFX, _pop)(struct SNAME * _stack_) \
    { \
        if (CMC_(PFX, _empty)(_stack_)) \
        { \
            _stack_->flag = CMC_FLAG_EMPTY; \
            return false; \
        } \
\
        _stack_->buffer[--_stack_->count] = (V){ 0 }; \
\
        _stack_->flag = CMC_FLAG_OK; \
\
        CMC_CALLBACKS_CALL(_stack_, delete); \
\
        return true; \
    } \
\
    V CMC_(PFX, _top)(struct SNAME * _stack_) \
    { \
        if (CMC_(PFX, _empty)(_stack_)) \
        { \
            _stack_->flag = CMC_FLAG_EMPTY; \
            return (V){ 0 }; \
        } \
\
        _stack_->flag = CMC_FLAG_OK; \
\
        CMC_CALLBACKS_CALL(_stack_, read); \
\
        return _stack_->buffer[_stack_->count - 1]; \
    } \
\
    bool CMC_(PFX, _contains)(struct SNAME * _stack_, V value) \
    { \
        _stack_->flag = CMC_FLAG_OK; \
\
        bool result = false; \
\
        for (size_t i = 0; i < _stack_->count; i++) \
        { \
            if (_stack_->f_val->cmp(_stack_->buffer[i], value) == 0) \
            { \
                result = true; \
                break; \
            } \
        } \
\
        CMC_CALLBACKS_CALL(_stack_, read); \
\
        return result; \
    } \
\
    bool CMC_(PFX, _empty)(struct SNAME * _stack_) \
    { \
        return _stack_->count == 0; \
    } \
\
    bool CMC_(PFX, _full)(struct SNAME * _stack_) \
    { \
        return _stack_->count >= SIZE; \
    } \
\
    size_t CMC_(PFX, _count)(struct SNAME * _stack_) \
    { \
        return _stack_->count; \
    } \
\
    size_t CMC_(PFX, _capacity)(struct SNAME * _stack_) \
    { \
        return SIZE; \
    } \
\
    int CMC_(PFX, _flag)(struct SNAME * _stack_) \
    { \
        return _stack_->flag; \
    } \
\
    struct SNAME CMC_(PFX, _copy_of)(struct SNAME * _stack_) \
    { \
        struct SNAME result = CMC_(PFX, _new_custom)(_stack_->f_val, NULL); \
\
        if (result.flag == CMC_FLAG_ERROR) \
            return result; \
\
        CMC_CALLBACKS_ASSIGN(&result, _stack_->callbacks); \
\
        if (_stack_->f_val->cpy) \
        { \
            for (size_t i = 0; i < _stack_->count; i++) \
                result.buffer[i] = _stack_->f_val->cpy(_stack_->buffer[i]); \
        } \
        else \
            memcpy(result.buffer, _stack_->buffer, sizeof(V) * _stack_->count); \
\
        result.count = _stack_->count; \
        _stack_->flag = CMC_FLAG_OK; \
\
        return result; \
    } \
\
    bool CMC_(PFX, _equals)(struct SNAME * _stack1_, struct SNAME * _stack2_) \
    { \
        _stack1_->flag = CMC_FLAG_OK; \
        _stack2_->flag = CMC_FLAG_OK; \
\
        if (_stack1_->count != _stack2_->count) \
            return false; \
\
        for (size_t i = 0; i < _stack1_->count; i++) \
        { \
            if (_stack1_->f_val->cmp(_stack1_->buffer[i], _stack2_->buffer[i]) != 0) \
                return false; \
        } \
\
        return true; \
    }

#endif /* CMC_SAC_STACK_H */
