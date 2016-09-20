//
//  hw4.cpp
//  Homework4
//
//  Created by Amin Amiripour on 3/7/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include "tablecheck.h"
#include "enc.h"
#include "dec.h"
#include "enc3.h"
#include "dec3.h"

using namespace std;

int main(int argc, char** argv) {
    
    if ( argc <= 2 || argc >= 6 ){
        cerr << "**************** Error: Wrong command ****************\n";
        cerr << "Valid commands are:\n./hw4 tablechek -t=tablefile\n./hw4 encrypt -k=key -t=tablefile [file]\n./hw4 decrypt -k=key -t=tablefile [file]\n./hw4 encrypt3 -k=key3 -t=tablefile [file]\n./hw4 decrypt3 -k=key3 -t=tablefile [file]\n";
        
        return 0;
    }
    else if ( strcmp( argv[1], "tablecheck" ) == 0 )
    {
        
        char *t = NULL;
        int i = 2;
        while ( i < argc ){
            
            if( argv[i][0] == '-' && argv[i][1] == 't' && argv[i][2] == '=' )
                t = argv[i] + 3 ;
            
            i++;
        }//end of while
        
        if ( argc > 3 || t == NULL || strlen(argv[2]) == 3)
        {
            cerr << "**************** Error: Wrong command ****************\n";
            cerr << "Valid commands are:\n./hw4 tablechek -t=tablefile\n./hw4 encrypt -k=key -t=tablefile [file]\n./hw4 decrypt -k=key -t=tablefile [file]\n./hw4 encrypt3 -k=key3 -t=tablefile [file]\n./hw4 decrypt3 -k=key3 -t=tablefile [file]\n";
            
            return 0;
        }else tablecheck( t );
        
        
    }else if ( strcmp( argv[1], "encrypt" ) == 0 ){
        
        char *k = NULL;
        char *t = NULL;
        int i = 2;
        while( i < argc )
        {
            if( argv[i][0] == '-' && argv[i][1] == 'k' && argv[i][2] == '=' )
                k = argv[i] + 3;
            
            if( argv[i][0] == '-' && argv[i][1] == 't' && argv[i][2] == '=' )
                t = argv[i] + 3;
            
            i++;
        }
        
        if( argc > 5 || k == NULL || t == NULL || strlen(argv[2]) == 3 || strlen(argv[3]) == 3 )
        {
            cerr << "**************** Error: Wrong command ****************\n";
            cerr << "Valid commands are:\n./hw4 tablechek -t=tablefile\n./hw4 encrypt -k=key -t=tablefile [file]\n./hw4 decrypt -k=key -t=tablefile [file]\n./hw4 encrypt3 -k=key3 -t=tablefile [file]\n./hw4 decrypt3 -k=key3 -t=tablefile [file]\n";
            
            return 0;
        }else encrypt( k, t, argv[4] );
        
        
        
    }else if ( strcmp( argv[1], "decrypt" ) == 0 ){
        char *k = NULL;
        char *t = NULL;
        int i = 2;
        while( i < argc )
        {
            if( argv[i][0] == '-' && argv[i][1] == 'k' && argv[i][2] == '=' )
                k = argv[i] + 3;
            
            if( argv[i][0] == '-' && argv[i][1] == 't' && argv[i][2] == '=' )
                t = argv[i] + 3;
            
            i++;
        }
        
        if( argc > 5 || k == NULL || t == NULL || strlen(argv[2]) == 3 || strlen(argv[3]) == 3 )
        {
            cerr << "**************** Error: Wrong command ****************\n";
            cerr << "Valid commands are:\n./hw4 tablechek -t=tablefile\n./hw4 encrypt -k=key -t=tablefile [file]\n./hw4 decrypt -k=key -t=tablefile [file]\n./hw4 encrypt3 -k=key3 -t=tablefile [file]\n./hw4 decrypt3 -k=key3 -t=tablefile [file]\n";
            
            return 0;
        }else decrypt( k, t, argv[4] );
        
    }else if ( strcmp( argv[1], "encrypt3" ) == 0 ){
        
        char *t = NULL;
        char *k = NULL;
        int j = 2;
        while ( j < argc ){
            
            if( argv[j][0] == '-' && argv[j][1] == 't' && argv[j][2] == '=' )
                t = argv[j] + 3 ;
            
            if( argv[j][0] == '-' && argv[j][1] == 'k' && argv[j][2] == '=' )
                k = argv[j] + 3;
            
            j++;
            
        }//end of while
        
        if ( argc > 5 || t == NULL || k == NULL || strlen(argv[2]) == 3 || strlen(argv[3]) == 3 )
        {
            cerr << "**************** Error: Wrong command ****************\n";
            cerr << "Valid commands are:\n./hw4 tablechek -t=tablefile\n./hw4 encrypt -k=key -t=tablefile [file]\n./hw4 decrypt -k=key -t=tablefile [file]\n./hw4 encrypt3 -k=key3 -t=tablefile [file]\n./hw4 decrypt3 -k=key3 -t=tablefile [file]\n";
            
            return 0;
        }else encrypt3( k, t, argv[4] );
        
    }else if ( strcmp( argv[1], "decrypt3" ) == 0 )
    {
        char *t = NULL;
        char *k = NULL;
        int i = 2;
        while ( i < argc ){
            
            if( argv[i][0] == '-' && argv[i][1] == 'k' && argv[i][2] == '=' )
                k = argv[i] + 3;
            
            if( argv[i][0] == '-' && argv[i][1] == 't' && argv[i][2] == '=' )
                t = argv[i] + 3;
            
            i++;
        }
        
        if ( argc > 5 || t == NULL || k == NULL || strlen(argv[2]) == 3 || strlen(argv[3]) == 3 )
        {
            cerr << "**************** Error: Wrong command ****************\n";
            cerr << "Valid commands are:\n./hw4 tablechek -t=tablefile\n./hw4 encrypt -k=key -t=tablefile [file]\n./hw4 decrypt -k=key -t=tablefile [file]\n./hw4 encrypt3 -k=key3 -t=tablefile [file]\n./hw4 decrypt3 -k=key3 -t=tablefile [file]\n";
            
            return 0;
        }else decrypt3( k, t, argv[4] );
        
        
    }else{
        cerr << "**************** Error: Wrong command ****************\n";
        cerr << "Valid commands are:\n./hw4 tablechek -t=tablefile\n./hw4 encrypt -k=key -t=tablefile [file]\n./hw4 decrypt -k=key -t=tablefile [file]\n./hw4 encrypt3 -k=key3 -t=tablefile [file]\n./hw4 decrypt3 -k=key3 -t=tablefile [file]\n";
        
        return 0;
    }
    
    
    
    return 0;
}//end of main


