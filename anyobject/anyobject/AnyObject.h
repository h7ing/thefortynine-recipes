//
//  AnyObject.h
//  FortyNine-AnyObject
//
//  Created by h7ing on Aug/14/2014.
//  Copyright (c) h7ing Inc. All rights reserved.
//

#ifndef __AnyObject__
#define __AnyObject__

#include <iostream>
#include <string>
#include <vector>
#include <functional>

namespace fn {
    
    class AnyTranslater {
    public:
        virtual ~AnyTranslater() {}
    };
    
    template <typename _T>
    class Translator : public AnyTranslater {
    public:
        //std::function<void(_T &)> func_;
        
        _T *value;
    };
    
    // User SHOULD NOT use the base class, it's for internal use only.
    class AnyObjectBase {
    public:
        virtual ~AnyObjectBase() {}
        virtual AnyObjectBase *copySelf() = 0;
        virtual void exposeToVisitor(AnyTranslater &vis) = 0;
    };
    
    template <typename _T>
    class AnyObjectReal : public AnyObjectBase {
    public:
        typedef _T RealType;
        RealType value;
        
    public:
        AnyObjectReal(const _T &another_value) : value(another_value) {}
        virtual ~AnyObjectReal() {}
        
        AnyObjectBase *copySelf() override {
            return new AnyObjectReal<RealType>(value);
        }
        
        void exposeToVisitor(AnyTranslater &vis) override {
            typedef Translator<_T> TForT;
            TForT *tr = dynamic_cast< TForT * >(&vis);
            if (tr) { tr->value = &value; }
        }
    };
    
    class AnyObject {
    public:
        virtual ~AnyObject() {
            if (_any_value) {
                delete _any_value;
            }
        }
        
        AnyObject() : _any_value(nullptr) {}
        
        AnyObject(const AnyObject &other) {
            _any_value = nullptr;
            if (other._any_value) {
                _any_value = other._any_value->copySelf();
            }
        }
        
        template <typename _T>
        void setValue(const _T &data) {
            if (_any_value) {
                delete _any_value;
            }
            AnyObjectBase *realValue = new AnyObjectReal<_T>(data);
            _any_value = realValue;
        }
        
        template <typename _T>
        AnyObject(const _T &data) {
            setValue(data);
        }
        
        void handleVisitor(AnyTranslater &vis) {
            if (_any_value)
                _any_value->exposeToVisitor(vis);
        }
        
        template <typename _T>
        _T* any_cast() {
            
            AnyObjectReal<_T>* F = dynamic_cast< AnyObjectReal<_T>* >(_any_value);
            if (F) {
                return &F->value;
            }
            
            return nullptr;
        }
        
    private:
        AnyObjectBase *_any_value;
    };
} // namespace fn

#endif /* defined(__AnyObject__) */
