//
//  primes.cpp
//  homework6
//
//  Created by Amin Amiripour on 4/5/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//


#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <iomanip>
#include <arpa/inet.h>
#include <cstdlib>
#include <netinet/in.h>
using namespace std;


void primes( char *n ){
    
    int i = 0;
    while ( i < strlen(n) )
    {
        if( n[i] >= '0' )
            if( n[i] <= '9')
            {
                i = i + 1;
                continue;
            }
        
        cerr << "maximul value should be a number" << endl;
        exit(1);
    }
    
    
    int maxval = atoi(n);
    if( maxval >= 2 && maxval <= pow(2,24) )
    {
        char* bytes = (char*)&maxval;
        int i = 0;
        while( i <= 3 )
        {
            cout << bytes[i];
            i = i + 1;
        }
        
        
        
        
        /*
         idea of following lines came from http://merlot.usc.edu/cs531-s16/homeworks/sieve.html
         
         */
        
        int *primes = (int *)malloc( (maxval+1) * sizeof(int) );
        primes[0] = primes[1] = 0;
        
        i = 2;
        while ( i < maxval + 1) {
            primes[i] = 1;
            i = i + 1;
        }
        
        int p = 2;
        while ( p * p <= maxval) {
            for( int j = p * p ; j <= maxval ; j = j + p)
                primes[j] = 0;
            
            p = p + 1;
        }
        
        i = 2;
        while ( i < maxval + 1 ) {
            
            
            if( primes[i] != 0 ){
                
                char* bytes = (char*)&i;
                int j = 0;
                while( j <= 3 )
                {
                    cout << bytes[j];
                    j = j + 1;
                }
            }
            
            
            i = i + 1;
        }
        
        free(primes);
        
        

    }else {
        cerr << "maxval should be between 2 and 2^24" << endl;
        exit(1);
    }
    
    
}



