//
//  maurer.cpp
//  homework6
//
//  Created by Amin Amiripour on 4/5/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//

# include <stdio.h>
# include <netinet/in.h>
# include <cstdlib>
# include <stdlib.h>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <math.h>
# include <sstream>
# include <openssl/crypto.h>
# include <openssl/bn.h>
# include "trialdiv.h"
# include "maurer.h"


#define round(X) (((X) >= 0) ? (int)((X)+0.5) : (int)((X)-0.5))

unsigned char RandomByte( FILE* rndFile )
{
    unsigned char byte;
    fread ( &byte, 1, 1, rndFile );
    return byte;
}


void RndOddNum( int k, BIGNUM *bn, FILE* rndFile )
{
    
    unsigned char* readBuffer;
    readBuffer = (unsigned char*)malloc( ceil(k/8.0)*sizeof(char*));
    int size = fread(readBuffer, 1, ceil(k/8.0), rndFile);
    if( size == 0 )
    {
        std::cerr << "Error: ";
        std::cerr << std::endl;
        std::cerr << "Ran out random bits in rndfile";
        std::cerr << std::endl;
        exit(1);
    }
    
    BN_bin2bn(readBuffer, ceil(k/8.0), bn);
    BN_set_bit(bn, 0);
    BN_set_bit(bn, k - 1);
    int i = k;
    while( i < ceil(k/8.0) * 8 )
    {
        BN_clear_bit(bn, i);
        i = i + 1;
    }

}



/*
 
 Idea of following function came from : http://merlot.usc.edu/cs531-s16/homeworks/hw6/#maurer

*/
BIGNUM* maurerAlgorithm(int k, char* primefile, FILE* rndFile , int level)
{
    BIGNUM* n = BN_new();
    BN_zero(n);
    BIGNUM* q = BN_new();
    BN_zero(q);
    BIGNUM* R = BN_new();
    BN_zero(R);
    BIGNUM* a = BN_new();
    BN_zero(a);
    BIGNUM* b = BN_new();
    BN_zero(b);
    BIGNUM* d = BN_new();
    BN_zero(d);
    BIGNUM* I = BN_new();
    BN_zero(I);
    BIGNUM* Number2 = BN_new();
    BN_zero(Number2);
    BIGNUM* n_1 = BN_new();
    BN_zero(n_1);
    BIGNUM* k_2 = BN_new();
    BN_zero(k_2);
    BN_CTX* ctx = BN_CTX_new();
    int rndByte, i = 1;
    double r;

    std::cout << "Maurer: level ";
    std::cout << level;
    std::cout << ", k=";
    std::cout << k;
    std::cout << std::endl;
    
    while ( k <= 20 ) {

        //RndOddNum(k)
        unsigned char* readBuffer;
        readBuffer = (unsigned char*)malloc( ceil(k/8.0)*sizeof(char*));
        int size = fread(readBuffer, 1, ceil(k/8.0), rndFile);
        if( size == 0 )
        {
            std::cerr << "Error: ";
            std::cerr << std::endl;
            std::cerr << "Ran out random bits in rndfile";
            std::cerr << std::endl;
            exit(1);
        }
        
        BN_bin2bn(readBuffer, ceil(k/8.0), n);
        BN_set_bit(n, 0);
        BN_set_bit(n, k - 1);
        int i = k;
        while( i < ceil(k/8.0) * 8 )
        {
            BN_clear_bit(n, i);
            i = i + 1;
        }
        
        
        std::cout << "  step 1.1, n = ";
        std::cout << BN_bn2dec ( n );
        std::cout << std::endl;
        std::cout << "    ";
        

        if ( trialdiv( BN_bn2dec ( n ), primefile ) == "passes" )
            return n;
    }


    int m = 20;
    if ( k < (2 * m) + 1  )
    {
        r = 0.5;
        std::cout << "  step 4, r = 50%";
        std::cout << std::endl;

    }
    
    if( k > (2 * m) )
    {
        while ( k > 2 * m )
        {
            
            rndByte = RandomByte( rndFile );
            r = 0.5 + (rndByte / 255.0) / 2.0;
            if ( k * ( 1 - r ) > m )
            {
                std::cout << "  step 4: random byte = ";
                std::cout << rndByte;
                std::cout << ", r = ";
                std::cout << round ( r * 100 );
                std::cout << "%";
                std::cout << std::endl;
                break;
            }
        }
        
    }
    

    int new_k = floor(k*r) + 1;
    q = maurerAlgorithm( new_k, primefile, rndFile, level + 1 );
    std::cout << "Maurer: back to level ";
    std::cout << level;
    std::cout << ", k=";
    std::cout << k;
    std::cout << ", q=";
    std::cout << BN_bn2dec( q );
    std::cout << std::endl;
    
    BN_set_word( k_2, ( k - 2 ) );                  //I = floor(2^(k-2) / q)
    BN_set_word( Number2, 2 );
    BN_exp( Number2, Number2, k_2, ctx );
    BN_div( I, NULL, Number2, q, ctx );
    
    while( 1 )
    {

        new_k = k + 1 - BN_num_bits( q );
        RndOddNum( new_k, R, rndFile );
        BN_mod( R, R, I, ctx );                    //R = (R mod I) + I + 1
        BN_add( R, R, I );
        BN_add( R, R, BN_value_one() );
        BN_mul( n, R, q, ctx );                   //n = 2Rq+1
        BN_set_word( Number2, 2 );                //set bn_2 back to two
        BN_mul( n, n, Number2, ctx );
        BN_add( n, n, BN_value_one() );
        BN_sub( n_1, n, BN_value_one());

        std::cout << "  step 7, itr ";
        std::cout << i;
        std::cout << ": R = ";
        std::cout << BN_bn2dec( R );
        std::cout << ", n = ";
        std::cout << BN_bn2dec ( n );
        std::cout << std::endl;
        std::cout << "    ";
        
        if ( trialdiv(BN_bn2dec(n), primefile) == "passes" )
        {
            
            while (1) {
                RndOddNum ( BN_num_bits( n ), a, rndFile );
                
                if(BN_cmp(a, BN_value_one()) == 1 && BN_cmp(a, n_1) == -1)
                    break;
            }
            std::cout << "  step 7.2.1, itr ";
            std::cout << i;
            std::cout << ": a = ";
            std::cout << BN_bn2dec(a);
            std::cout << std::endl;
            
            BN_mod_exp ( b, a, n_1, n, ctx );                   // b = (a ^ (n-1)) mod n

            if ( BN_cmp(b, BN_value_one()) != 1 )
                if ( BN_cmp(b, BN_value_one()) != -1 )
                    {
                        BN_mul( R, R, Number2, ctx );            //b = (a ^ 2R) mod n
                        BN_mod_exp( b, a, R, n, ctx );
                        BN_sub( b, b, BN_value_one() );
                        BN_gcd( d, b, n, ctx );

                        if ( BN_cmp( d, BN_value_one()) != 1 )
                            if ( BN_cmp( d, BN_value_one()) != -1 )
                                return n;
            
                    }
        }//end of if ( traildiv ( BN_bn2dec ( bn_n ), primefile ) == 1 )
        
        i = i + 1;
    }
}


void maurer( char* n, char* p, char * r )
{
    int level = 0;
    FILE *rndfile;
    rndfile = fopen( r, "rb" );
    BIGNUM * number = BN_new();
    if( rndfile == NULL )
    {
        std::cerr << "Cannot open rndfile or it may not exists" << std::endl;
        exit(1);
    }
    
    number = maurerAlgorithm( atoi(n), p, rndfile , level );
    
    std::cout << std::endl;
    std::cout << "Maurer's Algorithm found an ";
    std::cout << BN_num_bits(number);
    std::cout << "-bit prime:";
    std::cout << std::endl;
    std::cout << "  n = ";
    std::cout << BN_bn2dec(number);
    std::cout << std::endl;
    
}


