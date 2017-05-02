//
//  main.cpp
//  cpptest
//
//  Created by h7ing on Aug/13/2014.
//  Copyright (c) 2014 h7ing Inc. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include "AnyObject.h"

struct Bar
{
    Bar() {
        std::cout << "construct bar\n";
    }
    
    Bar(const Bar &anotherBar) {
        std::cout << "copy contstruct bar\n";
    }
    
    ~Bar() {
        std::cout << "destructor of bar\n";
    }
    
    void helloBar() {
        std::cout << "wof wof\n";
    }
};

void func(int& i)
{
    std::cout<<"func: "<<i<<std::endl;
}

struct FF{
    void test(int& i)
    {
        std::cout<<"test: "<<i<<std::endl;
    }
};

template<size_t N>
struct Factorial{
    static const size_t RESULT = N*Factorial<N-1>::RESULT;
};

template<>
struct Factorial<1>{
    static const size_t RESULT = 1;
};

template<size_t N>
void testFactorial()
{
    std::clog<<"factorial<"<<N<<">: "<<Factorial<N>::RESULT<<std::endl;
}

int main(int argc, const char * argv[])
{
    Bar a;
    
    using namespace fn;
    
    std::vector<AnyObject> var;
    
    AnyObject objA;
    objA.setValue(a);
    
    AnyObject objB;
    objB.setValue(1);
    
    var.push_back(objB);
    
    Translator<Bar> barTrans;
    objA.handleVisitor(barTrans);
    
    
    if (barTrans.value)
        barTrans.value->helloBar();
    
    Translator<int> intT;
    objA.handleVisitor(intT);
    if (intT.value)
        std::cout << "int:" << *intT.value << std::endl;
    
    Bar *pb = objA.any_cast<Bar>();
    if (pb)
        pb->helloBar();
    
    int *pi = objA.any_cast<int>();
    if (pi)
        std::cout << "int:" << *intT.value << std::endl;
    
//    intT.func_ = [](int& i){
//        std::cout<<i<<std::endl;
//    };
//    intT.func_ = std::function<void(int&)>(&func);
//    FF ff;
//    intT.func_ = std::bind(std::mem_fn(&FF::test), &ff, std::placeholders::_1);
//    objB.handleVisitor(intT);
    
    return 0;
}
