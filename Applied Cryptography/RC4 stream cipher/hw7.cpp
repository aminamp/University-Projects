//
//  hw7.cpp
//  homework7
//
//  Created by Amin Amiripour on 4/18/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include "rc4.h"
#include "x1.h"
#include "x2.h"
#include "x3.h"
#include "x4.h"
#include "x5.h"

using namespace std;

int main(int argc, char** argv) {
    
    if ( argc < 2 || argc >= 5 ){
        cerr << "**************** Error: Wrong command ****************\n";
        cerr << "Valid commands are:\n./hw7 rc4 -p=pphrase [-l=len]\n./hw7 x1 [file]\n./hw7 x2 [file]\n./hw7 x3 [file]\n./hw7 x4 [file]\n./hw7 x5 -d=dval [file]\n";
        
        return 0;
    }
    else if ( strcmp( argv[1], "rc4" ) == 0 )
    {
        
        char *p = NULL;
        char *l = NULL;
        bool flag = false;
        bool flag2 = true;
        int i = 2;
        
        while( i < argc )
        {
            if( argv[i][0] == '-' && argv[i][1] == 'l' && argv[i][2] == '=')
                l = argv[i] + 3;
            
            if( argv[i][0] == '-' && argv[i][1] == 'p' && argv[i][2] == '=')
            {
                p = argv[i] + 3;
                flag = true;
            }
            
            if (argv[i][0] == '-' && argv[i][1] == 'x' && argv[i][2] == '=') {
                flag2 = false;
            }

            
            i++;
        }
        
        if ( argc > 4 || p == NULL || flag == false || flag2 == false )
        {
            cerr << "**************** Error: Wrong command ****************\n";
            cerr << "Valid commands are:\n./hw7 rc4 -p=pphrase [-l=len]\n./hw7 x1 [file]\n./hw7 x2 [file]\n./hw7 x3 [file]\n./hw7 x4 [file]\n./hw7 x5 -d=dval [file]\n";
            
            return 0;
        }else rc4( p, l );
        
        
    }else if ( strcmp( argv[1], "x1" ) == 0 ){
        
        if ( argc > 3 )
        {
            cerr << "**************** Error: Wrong command ****************\n";
            cerr << "Valid commands are:\n./hw7 rc4 -p=pphrase [-l=len]\n./hw7 x1 [file]\n./hw7 x2 [file]\n./hw7 x3 [file]\n./hw7 x4 [file]\n./hw7 x5 -d=dval [file]\n";
            
            return 0;
        }else x1( argv[2] );
        
        
    }else if ( strcmp( argv[1], "x2" ) == 0 ){
        if ( argc > 3 )
        {
            cerr << "**************** Error: Wrong command ****************\n";
            cerr << "Valid commands are:\n./hw7 rc4 -p=pphrase [-l=len]\n./hw7 x1 [file]\n./hw7 x2 [file]\n./hw7 x3 [file]\n./hw7 x4 [file]\n./hw7 x5 -d=dval [file]\n";
            
            return 0;
        }else x2( argv[2] );
        
    }else if ( strcmp( argv[1], "x3" ) == 0 ){
        
        if ( argc > 3 )
        {
            cerr << "**************** Error: Wrong command ****************\n";
            cerr << "Valid commands are:\n./hw7 rc4 -p=pphrase [-l=len]\n./hw7 x1 [file]\n./hw7 x2 [file]\n./hw7 x3 [file]\n./hw7 x4 [file]\n./hw7 x5 -d=dval [file]\n";
            
            return 0;
        }else x3( argv[2] );
        
    }else if ( strcmp( argv[1], "x4" ) == 0 )
    {
        
        if ( argc > 3 )
        {
            cerr << "**************** Error: Wrong command ****************\n";
            cerr << "Valid commands are:\n./hw7 rc4 -p=pphrase [-l=len]\n./hw7 x1 [file]\n./hw7 x2 [file]\n./hw7 x3 [file]\n./hw7 x4 [file]\n./hw7 x5 -d=dval [file]\n";
            
            return 0;
        }else x4( argv[2] );
        
    }else if ( strcmp( argv[1], "x5" ) == 0 )
    {
        char *d = NULL;
        bool flag = false;

        if( argc >= 3 )
        {
            if( argv[2][0] == '-' && argv[2][1] == 'd' && argv[2][2] == '=' ){
                d = argv[2] + 3;
                flag = true;
            }
        }


        if ( flag == false || argc > 4 )
        {
            cerr << "**************** Error: Wrong command ****************\n";
            cerr << "Valid commands are:\n./hw7 rc4 -p=pphrase [-l=len]\n./hw7 x1 [file]\n./hw7 x2 [file]\n./hw7 x3 [file]\n./hw7 x4 [file]\n./hw7 x5 -d=dval [file]\n";
            
            return 0;
        }else x5( d, argv[3] );
        
    }else{
        cerr << "**************** Error: Wrong command ****************\n";
        cerr << "Valid commands are:\n./hw7 rc4 -p=pphrase [-l=len]\n./hw7 x1 [file]\n./hw7 x2 [file]\n./hw7 x3 [file]\n./hw7 x4 [file]\n./hw7 x5 -d=dval [file]\n";
        
        return 0;
    }
    
    
    return 0;
}//end of main


