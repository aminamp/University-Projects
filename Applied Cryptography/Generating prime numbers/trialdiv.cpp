//
//  trialdiv.cpp
//  homework6
//
//  Created by Amin Amiripour on 4/5/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <openssl/crypto.h>
#include <openssl/bn.h>
#include <netinet/in.h>
#include "trialdiv.h"

using namespace std;

string trialdiv( char* n, char *p ) {
    
    BIGNUM *number = BN_new();
    BIGNUM *maximum = BN_new();
    BIGNUM *prime = BN_new();
    BIGNUM *reminder = BN_new();
    BN_CTX *ctx = BN_CTX_new();

    BN_dec2bn(&number, n);

    FILE* primesfile = fopen( p, "rb" );
    if( primesfile == NULL )
    {
        std::cerr << "Cannot open primesfile or it may not exists" << std::endl;
        exit(1);
    }
    
    int i = 0;
    while ( i < strlen(n) )
    {
        if( n[i] >= '0' )
            if( n[i] <= '9')
            {
                i = i + 1;
                continue;
            }
        
        cerr << "number value should be contains digits only" << endl;
        exit(1);
    }
    
    unsigned int* readBuffer;
    readBuffer = (unsigned int*)malloc(1 * sizeof(unsigned int *));
    
    fread(readBuffer, sizeof(unsigned int *), 1, primesfile);
    BN_bin2bn((unsigned char *)readBuffer, sizeof(unsigned int), maximum);
    
    int size = 0;
    size = fread(readBuffer, sizeof(unsigned int), 1, primesfile);
    while ( size )
    {
        
        BN_bin2bn((unsigned char *)readBuffer, sizeof(unsigned int), prime);
        BN_mod(reminder, number, prime, ctx);
        
        if ( BN_is_zero( reminder ) != 0 )
            if( BN_cmp( number, prime ) != 0 )
                {
                    std::cout << "n is composite by trial division (mod ";
                    std::cout << BN_bn2dec( prime );
                    std::cout << " = 0)";
                    std::cout << std::endl;
                    return "composite";

                }
        
        size = fread(readBuffer, sizeof(unsigned int), 1, primesfile );
    }
    
    BN_sqr(maximum, maximum, ctx);
    if( BN_cmp(maximum, number) == 1 )
    {
        std::cout << "n passes trial division test";
        std::cout << std::endl;
    }
    
    if( BN_cmp(maximum, number) == 0 )
    {
        std::cout << "n passes trial division test (not enough primes)";
        std::cout << std::endl;
    }
    
    if( BN_cmp(maximum, number) == -1 )
    {
        std::cout << "n passes trial division test (not enough primes)";
        std::cout << std::endl;
    }
    
    return "passes";
}

