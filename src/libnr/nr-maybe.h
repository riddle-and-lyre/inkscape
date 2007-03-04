#ifndef __NR_MAYBE_H__
#define __NR_MAYBE_H__

/*
 * Nullable values for C++
 *
 * Copyright 2004, 2006  MenTaLguY <mental@rydia.net>
 *
 * This code is licensed under the GNU GPL; see COPYING for more information.
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdexcept>
#include <string>

namespace NR {

class IsNothing : public std::domain_error {
public:
    IsNothing() : domain_error(std::string("Is nothing")) {}
};

struct Nothing {};

template <typename T>
class Maybe {
public:
    Maybe(Nothing) : _is_nothing(true), _t() {}
    Maybe(T const &t) : _is_nothing(false), _t(t) {}
    Maybe(Maybe const &m) : _is_nothing(m._is_nothing), _t(m._t) {}

    template <typename T2> Maybe(Maybe<T2> const &m)
    : _is_nothing(m._is_nothing), _t(m._t) {}

    template <typename T2> Maybe(T2 const &t)
    : _is_nothing(false), _t(t) {};

    operator bool() const { return !_is_nothing; }

    T const &operator*() const throw(IsNothing) {
        if (_is_nothing) {
            throw IsNothing();
        } else {
            return _t;
        }
    }
    T &operator*() throw(IsNothing) {
        if (_is_nothing) {
            throw IsNothing();
        } else {
            return _t;
        }
    }

    T const *operator->() const throw(IsNothing) {
        if (_is_nothing) {
            throw IsNothing();
        } else {
            return &_t;
        }
    }
    T *operator->() throw(IsNothing) {
        if (_is_nothing) {
            throw IsNothing();
        } else {
            return &_t;
        }
    }

private:
    bool _is_nothing;
    T _t;
};

template <typename T>
class Maybe<T const> {
public:
    Maybe(Nothing) : _is_nothing(true), _t() {}
    Maybe(T const &t) : _is_nothing(false), _t(t) {}
    Maybe(Maybe const &m) : _is_nothing(m._is_nothing), _t(m._t) {}

    template <typename T2> Maybe(Maybe<T2> const &m)
    : _is_nothing(m._is_nothing), _t(m._t) {}

    template <typename T2> Maybe(T2 const &t)
    : _is_nothing(false), _t(t) {};

    operator bool() const { return !_is_nothing; }

    T const &operator*() const throw(IsNothing) {
        if (_is_nothing) {
            throw IsNothing();
        } else {
            return _t;
        }
    }

    T const *operator->() const throw(IsNothing) {
        if (_is_nothing) {
            throw IsNothing();
        } else {
            return &_t;
        }
    }

private:
    bool _is_nothing;
    T const _t;
};

template <typename T>
class Maybe<T &> {
public:
    Maybe(Nothing) : _is_nothing(true), _t() {}
    Maybe(T &t) : _is_nothing(false), _t(t) {}
    Maybe(Maybe const &m) : _is_nothing(m._is_nothing), _t(m._t) {}

    template <typename T2> Maybe(Maybe<T2> const &m)
    : _is_nothing(m._is_nothing), _t(m._t) {}

    template <typename T2> Maybe(T2 &t)
    : _is_nothing(false), _t(t) {};

    operator bool() const { return !_is_nothing; }

    T &operator*() const throw(IsNothing) {
        if (_is_nothing) {
            throw IsNothing();
        } else {
            return _t;
        }
    }

    T *operator->() const throw(IsNothing) {
        if (_is_nothing) {
            throw IsNothing();
        } else {
            return &_t;
        }
    }

private:
    bool _is_nothing;
    T &_t;
};

} /* namespace NR */

#endif

/*
  Local Variables:
  mode:c++
  c-file-style:"stroustrup"
  c-file-offsets:((innamespace . 0)(inline-open . 0)(case-label . +))
  indent-tabs-mode:nil
  fill-column:99
  End:
*/
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4:encoding=utf-8:textwidth=99 :
