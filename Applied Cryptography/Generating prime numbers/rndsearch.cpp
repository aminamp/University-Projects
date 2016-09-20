//
//  rndsearch.cpp
//  homework6
//
//  Created by Amin Amiripour on 4/5/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <openssl/crypto.h>
#include <openssl/bn.h>
#include "trialdiv.h"
#include "millerrabin.h"
#include "rndsearch.h"

using namespace std;


void rndsearch( char* k, char* t, char* p, char* r )
{

    FILE* rndfile = fopen(r,"rb");
    unsigned char* readBuffer;
    readBuffer = (unsigned char*)malloc( ceil(atoi(k)/8.0)*sizeof(char*));
    BIGNUM* number = BN_new();
    int count = 0;
    
    
    int i = 0;
    while ( i < strlen(t) )
    {
        if( t[i] >= '0' )
            if( t[i] <= '9')
            {
                i = i + 1;
                continue;
            }
        
        cerr << "maxitr should be contains digits only" << endl;
        exit(1);
    }
    
    i = 0;
    while ( i < strlen(k) )
    {
        if( k[i] >= '0' )
            if( k[i] <= '9')
            {
                i = i + 1;
                continue;
            }
        
        cerr << "numbit should be contains digits only" << endl;
        exit(1);
    }
    
    
    if( rndfile == NULL )
    {
        std::cerr << "Cannot open rndfile or it may not exists" << std::endl;
        exit(1);
    }
    
    while(1)
    {
        
        std::cout << "RANDOM-SEARCH: iteration ";
        std::cout << count + 1;
        std::cout << std::endl;

        int size = fread(readBuffer, 1, ceil(atoi(k)/8.0), rndfile);
        if( size == 0 )
        {
            std::cerr << "Error: ";
            std::cerr << std::endl;
            std::cerr << "Ran out random bits in rndfile";
            std::cerr << std::endl;
            exit(1);
        }
        
        BN_bin2bn(readBuffer, ceil(atoi(k)/8.0), number);
        BN_set_bit(number, 0);
        BN_set_bit(number, atoi(k)-1);
        int i = atoi(k);
        while( i < ceil(atoi(k)/8.0)*8 ){
            BN_clear_bit(number, i);
            i = i + 1;
        }

        
        std::cout << "  n = ";
        std::cout << BN_bn2dec(number);
        std::cout << std::endl;
        std::cout << "  ";

        string space = "  ";
        
        if( trialdiv( BN_bn2dec(number), p ) == "passes" )
            if( millerrabin( BN_bn2dec(number), t, p, space ) == "prime" )
                break;
            
        
        count = count + 1;
    }
    
}


