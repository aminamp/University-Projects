//
//  hw1.cpp
//
//  Created by Amin Amiripour on 1/18/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//
#include "tohexdump.h"
#include "encbase64.h"
#include "decbase64.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>


using namespace std;

int main(int argc, char** argv) {
    
    if ( argc <= 1 || argc >= 4 ){
        cerr << "**************** Error: Wrong command ****************\n";
        cerr << "Valid commands are:\n./hw1 hexdump [file]\n./hw1 enc-base64 [file]\n./hw1 dec-base64 [file]\n";
        return 0;
    }else if ( strcmp( argv[1], "hexdump" ) == 0 ){
        ToHexdump( argv[2] );
    }else if ( strcmp( argv[1], "enc-base64" ) == 0 ){
        EncBase64( argv[2] );
    }else if ( strcmp( argv[1], "dec-base64" ) == 0 ){
        DecBase64( argv[2] );
    }else{
        cerr << "**************** Error: Wrong command ****************\n";
        cerr << "Valid commands are:\n./hw1 hexdump [file]\n./hw1 enc-base64 [file]\n./hw1 dec-base64 [file]\n";
        return 0;
    }
    
    return 0;
}//end of main




