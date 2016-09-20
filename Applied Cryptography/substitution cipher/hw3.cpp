//
//  hw3.cpp
//  Homework3
//
//  Created by Amin Amiripour on 2/14/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include "keygen.h"
#include "crypt.h"
#include "invkey.h"
#include "histo.h"
#include "solve.h"

using namespace std;

int main(int argc, char** argv) {
    
    if ( argc <= 2 || argc >= 6 ){
        cerr << "**************** Error: Wrong command ****************\n";
        cerr << "Valid commands are:\n./hw3 keygen -p=pphrase -t=period\n./hw3 crypt -k=keyfile [file]\n./hw3 invkey keyfile\n./hw3 histo -t=period -i=which [file]\n./hw3 solve -l=max_t file\n";
        
        return 0;
    }
    else if ( strcmp( argv[1], "keygen" ) == 0 )
    {
        
        char *p = NULL;
        char *t = NULL;
        int i = 2;
        while ( i < argc ){
            
            //search for -t=period
            if( argv[i][0] == '-' && argv[i][1] == 't' && argv[i][2] == '=' )
                t = argv[i] + 3 ;
            
            //search for -p=phrase
            if( argv[i][0] == '-' && argv[i][1] == 'p' && argv[i][2] == '=' )
                p = argv[i] + 3;
            
            i++;
        }//end of while
        
        if ( argc > 4 || p == NULL || t == NULL || strlen(argv[2]) == 3)
        {
            cerr << "**************** Error: Wrong command ****************\n";
            cerr << "Valid commands are:\n./hw3 keygen -p=pphrase -t=period\n./hw3 crypt -k=keyfile [file]\n./hw3 invkey keyfile\n./hw3 histo -t=period -i=which [file]\n./hw3 solve -l=max_t file\n";
            return 0;
        }else keygen( p, t );
        
        
    }else if ( strcmp( argv[1], "crypt" ) == 0 ){
        
        char *k = NULL;
        int i = 2;
        while( i < argc )
        {
            if( argv[i][0] == '-' && argv[i][1] == 'k' && argv[i][2] == '=' )
                k = argv[i] + 3;
            
            i++;
        }
        
        if( argc > 4 || k == NULL || strlen(argv[2]) == 3 )
        {
            cerr << "**************** Error: Wrong command ****************\n";
            cerr << "Valid commands are:\n./hw3 keygen -p=pphrase -t=period\n./hw3 crypt -k=keyfile [file]\n./hw3 invkey keyfile\n./hw3 histo -t=period -i=which [file]\n./hw3 solve -l=max_t file\n";
            
        }else crypt( k, argv[3] );
        
        
        
    }else if ( strcmp( argv[1], "invkey" ) == 0 ){
        if( argc != 3 )
        {
            cerr << "**************** Error: Wrong command ****************\n";
            cerr << "Valid commands are:\n./hw2 stream -p=pphrase -l=len\n./hw2 encrypt -p=pphrase -out=name [pbmfile]\n./hw2 merge pbmfile1 pbmfile2\n./hw2 decrypt [pbmfile]\n";
            return 0;
        }else invkey( argv[2] );
        
    }else if ( strcmp( argv[1], "histo" ) == 0 ){
        
        char *t = NULL;
        char *i = NULL;
        int j = 2;
        while ( j < argc ){
            
            //search for -t=period
            if( argv[j][0] == '-' && argv[j][1] == 't' && argv[j][2] == '=' )
                t = argv[j] + 3 ;
            
            //search for -i=which
            if( argv[j][0] == '-' && argv[j][1] == 'i' && argv[j][2] == '=' )
                i = argv[j] + 3;
            
            j++;

        }//end of while
        
        if ( argc > 5 || t == NULL || i == NULL || strlen(argv[2]) == 3 || strlen(argv[3]) == 3 )
        {
            cerr << "**************** Error: Wrong command ****************\n";
            cerr << "Valid commands are:\n./hw3 keygen -p=pphrase -t=period\n./hw3 crypt -k=keyfile [file]\n./hw3 invkey keyfile\n./hw3 histo -t=period -i=which [file]\n./hw3 solve -l=max_t file\n";
            return 0;
        }else histo( t, i, argv[4] );
        
    }else if ( strcmp( argv[1], "solve" ) == 0 )
    {
        char *l = NULL;
        int i = 2;
        while ( i < argc ){
            
            if( argv[i][0] == '-' && argv[i][1] == 'l' && argv[i][2] == '=' )
                l = argv[i] + 3 ;
            
            i++;
        }
        
        if ( argc > 4 || l == NULL || strlen(argv[2]) == 3 )
        {
            cerr << "**************** Error: Wrong command ****************\n";
            cerr << "Valid commands are:\n./hw3 keygen -p=pphrase -t=period\n./hw3 crypt -k=keyfile [file]\n./hw3 invkey keyfile\n./hw3 histo -t=period -i=which [file]\n./hw3 solve -l=max_t file\n";
            return 0;
        }else solve( l, argv[3] );
        
        
    }else{
        cerr << "**************** Error: Wrong command ****************\n";
        cerr << "Valid commands are:\n./hw3 keygen -p=pphrase -t=period\n./hw3 crypt -k=keyfile [file]\n./hw3 invkey keyfile\n./hw3 histo -t=period -i=which [file]\n./hw3 solve -l=max_t file\n";
        return 0;
    }
    
    
    
    return 0;
}//end of main



