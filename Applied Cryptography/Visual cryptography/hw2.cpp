//
//  hw2.cpp
//  HomeWork2
//
//  Created by Amin Amiripour on 2/6/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include "stream.h"
#include "encrypt.h"
#include "merge.h"
#include "decrypt.h"
using namespace std;

int main(int argc, char** argv) {
    
    if ( argc <= 1 || argc >= 6 ){
        cerr << "**************** Error: Wrong command ****************\n";
        cerr << "Valid commands are:\n./hw2 stream -p=pphrase -l=len\n./hw2 encrypt -p=pphrase -out=name [pbmfile]\n./hw2 merge pbmfile1 pbmfile2\n./hw2 decrypt [pbmfile]\n";

        return 0;
    }
    else if ( strcmp( argv[1], "stream" ) == 0 )
        {
        
        char *p = NULL;
        char *l = NULL;
        int i = 2;
        while ( i < argc ){
            
            //search for -l=lenght
            if( argv[i][0] == '-' && argv[i][1] == 'l' && argv[i][2] == '=' )
                l = argv[i] + 3 ;
            
            //search for -p=phrase
            if( argv[i][0] == '-' && argv[i][1] == 'p' && argv[i][2] == '=' )
                p = argv[i] + 3;

            i++;
        }//end of while
        
        if ( argc > 4 || p == NULL || l == 0)
        {
            cerr << "**************** Error: Wrong command ****************\n";
            cerr << "Valid commands are:\n./hw2 stream -p=pphrase -l=len\n./hw2 encrypt -p=pphrase -out=name [pbmfile]\n./hw2 merge pbmfile1 pbmfile2\n./hw2 decrypt [pbmfile]\n";
            return 0;
        }else stream( p, l );

    
        
    }else if ( strcmp( argv[1], "encrypt" ) == 0 ){
        
        char *p = NULL;
        char *out = NULL;
        int i = 2;
        
        while( i < 4 )
        {
            if( argv[i][0] == '-' && argv[i][1] == 'p' && argv[i][2] == '=' )
                p = argv[i] + 3;
            
            if( argv[i][0] == '-' && argv[i][1] == 'o' && argv[i][2] == 'u' && argv[i][3] == 't' && argv[i][4] == '=')
                out = argv[i] + 5;
            
            i++;
        }
        
        if( argc > 5 || p == NULL || out == NULL )
        {
            cerr << "**************** Error: Wrong command ****************\n";
            cerr << "Valid commands are:\n./hw2 stream -p=pphrase -l=len\n./hw2 encrypt -p=pphrase -out=name [pbmfile]\n./hw2 merge pbmfile1 pbmfile2\n./hw2 decrypt [pbmfile]\n";
            return 0;
            
        }else encrypt( p, out, argv[4] );
        
         
       
    }else if ( strcmp( argv[1], "merge" ) == 0 ){
        if( argc != 4 )
        {
            cerr << "**************** Error: Wrong command ****************\n";
            cerr << "Valid commands are:\n./hw2 stream -p=pphrase -l=len\n./hw2 encrypt -p=pphrase -out=name [pbmfile]\n./hw2 merge pbmfile1 pbmfile2\n./hw2 decrypt [pbmfile]\n";
            return 0;
        } else merge( argv[2], argv[3] );
        
    }else if ( strcmp( argv[1], "decrypt" ) == 0 ){
        if( argc > 3)
        {
            cerr << "**************** Error: Wrong command ****************\n";
            cerr << "Valid commands are:\n./hw2 stream -p=pphrase -l=len\n./hw2 encrypt -p=pphrase -out=name [pbmfile]\n./hw2 merge pbmfile1 pbmfile2\n./hw2 decrypt [pbmfile]\n";
            return 0;
        }else decrypt( argv[2] );
    }else{
        cerr << "**************** Error: Wrong command ****************\n";
        cerr << "Valid commands are:\n./hw2 stream -p=pphrase -l=len\n./hw2 encrypt -p=pphrase -out=name [pbmfile]\n./hw2 merge pbmfile1 pbmfile2\n./hw2 decrypt [pbmfile]\n";
        return 0;
    }
    
    
    
    return 0;
}//end of main


