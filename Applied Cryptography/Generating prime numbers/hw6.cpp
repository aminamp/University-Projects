//
//  hw6.cpp
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
#include "primes.h"
#include "trialdiv.h"
#include "millerrabin.h"
#include "rndsearch.h"
#include "maurer.h"

using namespace std;

int main(int argc, char** argv) {
    
    if ( argc <= 2 || argc >= 7 ){
        cerr << "**************** Error: Wrong command ****************\n";
        cerr << "Valid commands are:\n./hw6 primes -n=maxval\n./hw6 trialdiv -n=number -p=primesfile\n./hw6 millerrabin -n=number -t=maxitr -p=primesfile\n./hw6 rndsearch -k=numbits -t=maxitr -p=primesfile -r=rndfile\n./hw6 maurer -k=numbits -p=primesfile -r=rndfile\n";
        
        return 0;
    }
    else if ( strcmp( argv[1], "primes" ) == 0 )
    {
        
        char *n = NULL;
        if( argv[2][0] == '-' && argv[2][1] == 'n' && argv[2][2] == '=')
            n = argv[2] + 3;
        
        if ( argc > 3 || n == NULL || strlen(argv[2]) == 3 || (*n) == '\0')
        {
            cerr << "**************** Error: Wrong command ****************\n";
            cerr << "Valid commands are:\n./hw6 primes -n=maxval\n./hw6 trialdiv -n=number -p=primesfile\n./hw6 millerrabin -n=number -t=maxitr -p=primesfile\n./hw6 rndsearch -k=numbits -t=maxitr -p=primesfile -r=rndfile\n./hw6 maurer -k=numbits -p=primesfile -r=rndfile\n";
            
            return 0;
        }else primes( n );
        
        
    }else if ( strcmp( argv[1], "trialdiv" ) == 0 ){
        
        char *n = NULL;
        char *p = NULL;
        int i = 2;
        while( i < argc )
        {
            if( argv[i][0] == '-' && argv[i][1] == 'n' && argv[i][2] == '=')
                n = argv[i] + 3;
            
            if( argv[i][0] == '-' && argv[i][1] == 'p' && argv[i][2] == '=')
                p = argv[i] + 3;
            
            i++;
        }
        
        if( argc > 4 || n == NULL || p == NULL || strlen(argv[2]) == 3 || strlen(argv[3]) == 3 )
        {
            cerr << "**************** Error: Wrong command ****************\n";
            cerr << "Valid commands are:\n./hw6 primes -n=maxval\n./hw6 trialdiv -n=number -p=primesfile\n./hw6 millerrabin -n=number -t=maxitr -p=primesfile\n./hw6 rndsearch -k=numbits -t=maxitr -p=primesfile -r=rndfile\n./hw6 maurer -k=numbits -p=primesfile -r=rndfile\n";
            
            return 0;
        }else trialdiv( n, p);
        
        
        
    }else if ( strcmp( argv[1], "millerrabin" ) == 0 ){
        char *n = NULL;
        char *t = NULL;
        char *p = NULL;
        int i = 2;
        while( i < argc )
        {
            if( argv[i][0] == '-' && argv[i][1] == 'n' && argv[i][2] == '=' )
                n = argv[i] + 3;
            
            if( argv[i][0] == '-' && argv[i][1] == 't' && argv[i][2] == '=' )
                t = argv[i] + 3;
            
            if( argv[i][0] == '-' && argv[i][1] == 'p' && argv[i][2] == '=' )
                p = argv[i] + 3;
            
            i++;
        }
        
        string space = "";
        
        if( argc > 5 || n == NULL || t == NULL || p == NULL || strlen(argv[2]) == 3 || strlen(argv[3]) == 3 || strlen(argv[4]) == 3 )
        {
            cerr << "**************** Error: Wrong command ****************\n";
            cerr << "Valid commands are:\n./hw6 primes -n=maxval\n./hw6 trialdiv -n=number -p=primesfile\n./hw6 millerrabin -n=number -t=maxitr -p=primesfile\n./hw6 rndsearch -k=numbits -t=maxitr -p=primesfile -r=rndfile\n./hw6 maurer -k=numbits -p=primesfile -r=rndfile\n";
            
            return 0;
        }else millerrabin( n, t, p, space );
        
    }else if ( strcmp( argv[1], "rndsearch" ) == 0 ){
        
        
        char *k = NULL;
        char *t = NULL;
        char *p = NULL;
        char *r = NULL;
        int j = 2;
        while ( j < argc ){
            
            if( argv[j][0] == '-' && argv[j][1] == 't' && argv[j][2] == '=' )
                t = argv[j] + 3 ;
            
            if( argv[j][0] == '-' && argv[j][1] == 'k' && argv[j][2] == '=' )
                k = argv[j] + 3;
            
            if( argv[j][0] == '-' && argv[j][1] == 'p' && argv[j][2] == '=' )
                p = argv[j] + 3;
            
            if( argv[j][0] == '-' && argv[j][1] == 'r' && argv[j][2] == '=' )
                r = argv[j] + 3;
            
            j++;
            
        }//end of while
        
        if ( argc > 6 || t == NULL || k == NULL || p == NULL || r == NULL || strlen(argv[2]) == 3 || strlen(argv[3]) == 3 || strlen(argv[4]) == 3 || strlen(argv[5]) == 3 )
        {
            cerr << "**************** Error: Wrong command ****************\n";
            cerr << "Valid commands are:\n./hw6 primes -n=maxval\n./hw6 trialdiv -n=number -p=primesfile\n./hw6 millerrabin -n=number -t=maxitr -p=primesfile\n./hw6 rndsearch -k=numbits -t=maxitr -p=primesfile -r=rndfile\n./hw6 maurer -k=numbits -p=primesfile -r=rndfile\n";
            
            return 0;
        }else rndsearch( k, t, p, r );
        
    }else if ( strcmp( argv[1], "maurer" ) == 0 )
    {
        char *k = NULL;
        char *p = NULL;
        char *r = NULL;
        int i = 2;
        while ( i < argc ){
            
            if( argv[i][0] == '-' && argv[i][1] == 'k' && argv[i][2] == '=' )
                k = argv[i] + 3;
            
            if( argv[i][0] == '-' && argv[i][1] == 'p' && argv[i][2] == '=' )
                p = argv[i] + 3;
            
            if( argv[i][0] == '-' && argv[i][1] == 'r' && argv[i][2] == '=' )
                r = argv[i] + 3;
            
            i++;
        }
        
        if ( argc > 5 || k == NULL || p == NULL || r == NULL || strlen(argv[2]) == 3 || strlen(argv[3]) == 3 || strlen(argv[4]) == 3 )
        {
            cerr << "**************** Error: Wrong command ****************\n";
            cerr << "Valid commands are:\n./hw6 primes -n=maxval\n./hw6 trialdiv -n=number -p=primesfile\n./hw6 millerrabin -n=number -t=maxitr -p=primesfile\n./hw6 rndsearch -k=numbits -t=maxitr -p=primesfile -r=rndfile\n./hw6 maurer -k=numbits -p=primesfile -r=rndfile\n";
            
            return 0;
        }else maurer( k, p, r );
        
    }else{
        cerr << "**************** Error: Wrong command ****************\n";
        cerr << "Valid commands are:\n./hw6 primes -n=maxval\n./hw6 trialdiv -n=number -p=primesfile\n./hw6 millerrabin -n=number -t=maxitr -p=primesfile\n./hw6 rndsearch -k=numbits -t=maxitr -p=primesfile -r=rndfile\n./hw6 maurer -k=numbits -p=primesfile -r=rndfile\n";
        
        return 0;
    }
    
    
    return 0;
}//end of main

