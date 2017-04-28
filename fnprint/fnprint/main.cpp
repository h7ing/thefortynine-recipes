//
//  main.cpp
//  fnprint
//
//  Created by h7ing on 28/April/2017.
//  Copyright © 2017 TheFortyNine. All rights reserved.
//

#include <iostream>
#include "fnprint.h"

int main(int argc, const char * argv[]) {
    fn::print("hello fnprint!");
    fn::print("print string:", "this is string");
    fn::print("print number:", "int:", (int)123, ",float", (float)123.5f, ",double", (double)123.6);
    return 0;
}
