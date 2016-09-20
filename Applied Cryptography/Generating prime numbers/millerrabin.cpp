//
//  millerrabin.cpp
//  homework6
//
//  Created by Amin Amiripour on 4/5/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//

# include <stdio.h>
# include <netinet/in.h>
# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <sstream>
# include <string>
# include <math.h>
# include <openssl/bn.h>
#include <openssl/crypto.h>
#include "millerrabin.h"

using namespace std;

string millerrabin(char* n, char* t, char* p, string space){
    
    BIGNUM* number = BN_new();
    BIGNUM* a = BN_new();
    BN_zero(a);
    BIGNUM* y = BN_new();
    BN_zero(y);
    BIGNUM* r = BN_new();
    BN_zero(r);
    BIGNUM* s = BN_new();
    BN_zero(s);
    BIGNUM* n_one = BN_new();
    BN_zero(n_one);
    BIGNUM* numberTwo = BN_new();
    BN_zero(numberTwo);
    BN_CTX* ctx = BN_CTX_new();
    BN_dec2bn(&number, n);
    BN_dec2bn(&numberTwo, "2");
    BN_sub(n_one, number, BN_value_one());                  // n - 1
    
    
    FILE* primesfile = fopen(p,"rb");
    if( primesfile == NULL )
    {
        std::cerr << "Cannot open primesfile or it may not exists" << std::endl;
        exit(1);
    }
    
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

    
    BN_copy(r, n_one);
    while( 1 )
    {
        if( BN_is_odd(r) )
            break;
        BN_add( s, s, BN_value_one() );                   // ( 2 ^ s ) * r = n - 1 ==> s=? r=?
        BN_div( r, NULL, r, numberTwo, ctx );
    }
    

    if( space.length() == 0 ){
        cout << space;
        cout << "n = ";
        cout << BN_bn2dec(number);
        cout << endl;
    }
    
    
    cout << space;
    cout << "  n-1 = ";
    cout << BN_bn2dec(n_one);
    cout << endl;
    cout << space;
    cout << "  s = ";
    cout << BN_bn2dec(s);
    cout << endl;
    cout << space;
    cout << "  r = ";
    cout << BN_bn2dec(r);
    cout << endl;
    
    unsigned int* readBuffer;
    readBuffer = (unsigned int*)malloc(1* sizeof(unsigned int*));
    fseek(primesfile, sizeof(unsigned int), SEEK_SET);
    i = 1;
    while ( i < atoi(t)+1 ) {
        
        int size = 0;
        size = fread(readBuffer, sizeof(unsigned int), 1, primesfile);
        if( size == 0 )
        {
            cerr <<  "ERROR: not enough primes in primesfile.";
            cerr << endl;
            exit(1);
        }
        
        
        BN_set_word(a, ntohl(*readBuffer));
        BN_mod_exp(y, a, r, number, ctx);      // y = a ^ r mod n
        
        if( BN_cmp(y, n_one) == 1 || BN_cmp(y, n_one) == -1 )
        {
            cout << space;
            cout << "  Itr ";
            cout << i;
            cout << " of ";
            cout << atoi(t);
            cout << ", a = ";
            cout << BN_bn2dec(a);
            cout << ", y = ";
            cout << BN_bn2dec(y);
            cout << endl;
            
        }else{
            
            cout << space;
            cout << "  Itr ";
            cout << i;
            cout << " of ";
            cout << atoi(t);
            cout << ", a = ";
            cout << BN_bn2dec(a);
            cout << ", y = ";
            cout << BN_bn2dec(y);
            cout << " (which is n-1)";
            cout << endl;
        }
        
        
        if( BN_cmp(y, BN_value_one()) == 1 || BN_cmp(y, BN_value_one()) == -1 )
            if( BN_cmp(y, n_one) == 1 || BN_cmp(y, n_one) == -1 )
            {
                
                for(int j=1; (j<=atoi( BN_bn2dec(s) )-1) && (BN_cmp(y, n_one) != 0); j++)
                {
                    
                    BN_mod_sqr(y, y, number, ctx);     // y = y ^ (1/2) mod n
                    
                    if( BN_cmp(y, n_one) == 1 || BN_cmp(y, n_one) == -1 )
                    {
                        cout << space;
                        cout << "    ";
                        cout << "j = ";
                        cout << j;
                        cout << " of ";
                        cout << atoi(BN_bn2dec(s)) - 1;
                        cout << ", y = ";
                        cout << BN_bn2dec(y);
                        cout << endl;
                        
                    }else{
                        
                        cout << space;
                        cout << "    ";
                        cout << "j = ";
                        cout << j;
                        cout << " of ";
                        cout << atoi(BN_bn2dec(s)) - 1;
                        cout << ", y = ";
                        cout << BN_bn2dec(y);
                        cout << " (which is n-1)";
                        cout << endl;
                    }
                    
                    
                }
                
                
                if( BN_cmp(y, n_one) == 1 || BN_cmp(y, n_one) == -1 )
                {
                    cout << space;
                    cout << "Miller-Rabin found a strong witness ";
                    cout << BN_bn2dec(a);
                    cout << endl;
                    return "composite";
                }
            }
        
        i = i + 1;
        
    }

    cout << space;
    cout << "Miller-Rabin declares n to be a prime number";
    cout << endl;
    
    return "prime";
    
}

