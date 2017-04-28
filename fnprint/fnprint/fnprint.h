//
//  FNPrint
//  FortyNine Print
//
//  Created by h7ing on Sept/09/2015.
//  Copyright © 2017 TheFortyNine. All rights reserved.
//


#ifndef __FNPRINT_H__
#define __FNPRINT_H__

#include <iostream>

namespace fn {
    
    inline void print() {
        std::cout << std::endl;
    }
    
    template<typename _T>
    void print(const _T &log) {
        std::cout << log << std::endl;
    }
    
    template<typename Head, typename... Tail>
    void print(const Head& h, const Tail&... tail) {
        std::cout << h;
        print(tail...);
    }
    
    inline void printerr() {
        std::cerr << std::endl;
    }
    
    template<typename _T>
    void printerr(const _T &err) {
        std::cerr << err << std::endl;
    }
    
    template<typename Head, typename... Tail>
    void printerr(const Head &h, const Tail&... tail) {
        std::cerr << h;
        printerr(tail...);
    }
    
} // namespace fn

#endif
