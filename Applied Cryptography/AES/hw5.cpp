//
//  hw5.cpp
//  Homework5
//
//  Created by Amin Amiripour on 3/17/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include "tablecheck.h"
#include "modprod.h"
#include "keyexpand.h"
#include "encrypt.h"
#include "decrypt.h"
#include "inverse.h"

using namespace std;

int main(int argc, char** argv) {
    
    if ( argc <= 2 || argc >= 6 ){
        cerr << "**************** Error: Wrong command ****************\n";
        cerr << "Valid commands are:\n./hw5 tablechek -t=tablefile\n./hw5 modprod -p1=poly1 -p2=poly2\n./hw5 keyexpand -k=key -t=tablefile\n./hw5 encrypt -k=key -t=tablefile [file]\n./hw5 decrypt -k=key -t=tablefile [file]\n./hw5 inverse -p=poly\n";
        
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
            cerr << "Valid commands are:\n./hw5 tablechek -t=tablefile\n./hw5 modprod -p1=poly1 -p2=poly2\n./hw5 keyexpand -k=key -t=tablefile\n./hw5 encrypt -k=key -t=tablefile [file]\n./hw5 decrypt -k=key -t=tablefile [file]\n./hw5 inverse -p=poly\n";
            
            return 0;
        }else tablecheck( t );
        
        
    }else if ( strcmp( argv[1], "modprod" ) == 0 ){
        
        char *p1 = NULL;
        char *p2 = NULL;
        int i = 2;
        while( i < argc )
        {
            if( argv[i][0] == '-' && argv[i][1] == 'p' && argv[i][2] == '1' && argv[i][3] == '=')
                p1 = argv[i] + 4;
            
            if( argv[i][0] == '-' && argv[i][1] == 'p' && argv[i][2] == '2' && argv[i][3] == '=')
                p2 = argv[i] + 4;
            
            i++;
        }
        
        if( argc > 4 || p1 == NULL || p2 == NULL || strlen(argv[2]) == 4 || strlen(argv[3]) == 4 )
        {
            cerr << "**************** Error: Wrong command ****************\n";
            cerr << "Valid commands are:\n./hw5 tablechek -t=tablefile\n./hw5 modprod -p1=poly1 -p2=poly2\n./hw5 keyexpand -k=key -t=tablefile\n./hw5 encrypt -k=key -t=tablefile [file]\n./hw5 decrypt -k=key -t=tablefile [file]\n./hw5 inverse -p=poly\n";
            
            return 0;
        }else modprod( p1, p2 );
        
        
        
    }else if ( strcmp( argv[1], "keyexpand" ) == 0 ){
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
        
        if( argc > 4 || k == NULL || t == NULL || strlen(argv[2]) == 3 || strlen(argv[3]) == 3 )
        {
            cerr << "**************** Error: Wrong command ****************\n";
            cerr << "Valid commands are:\n./hw5 tablechek -t=tablefile\n./hw5 modprod -p1=poly1 -p2=poly2\n./hw5 keyexpand -k=key -t=tablefile\n./hw5 encrypt -k=key -t=tablefile [file]\n./hw5 decrypt -k=key -t=tablefile [file]\n./hw5 inverse -p=poly\n";
            
            return 0;
        }else keyexpand( k, t );
        
    }else if ( strcmp( argv[1], "encrypt" ) == 0 ){
        
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
            cerr << "Valid commands are:\n./hw5 tablechek -t=tablefile\n./hw5 modprod -p1=poly1 -p2=poly2\n./hw5 keyexpand -k=key -t=tablefile\n./hw5 encrypt -k=key -t=tablefile [file]\n./hw5 decrypt -k=key -t=tablefile [file]\n./hw5 inverse -p=poly\n";
            
            return 0;
        }else encrypt( k, t, argv[4] );
        
    }else if ( strcmp( argv[1], "decrypt" ) == 0 )
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
            cerr << "Valid commands are:\n./hw5 tablechek -t=tablefile\n./hw5 modprod -p1=poly1 -p2=poly2\n./hw5 keyexpand -k=key -t=tablefile\n./hw5 encrypt -k=key -t=tablefile [file]\n./hw5 decrypt -k=key -t=tablefile [file]\n./hw5 inverse -p=poly\n";
            
            return 0;
        }else decrypt( k, t, argv[4] );
        
    }else if ( strcmp( argv[1], "inverse" ) == 0 ){
        char *p = NULL;
        
        int i = 2;
        while ( i < argc ){
            
            if( argv[i][0] == '-' && argv[i][1] == 'p' && argv[i][2] == '=' )
                p = argv[i] + 3;
            
            i++;
        }
        
        if ( argc > 3 || p == NULL || strlen(argv[2]) == 3 )
        {
            cerr << "**************** Error: Wrong command ****************\n";
            cerr << "Valid commands are:\n./hw5 tablechek -t=tablefile\n./hw5 modprod -p1=poly1 -p2=poly2\n./hw5 keyexpand -k=key -t=tablefile\n./hw5 encrypt -k=key -t=tablefile [file]\n./hw5 decrypt -k=key -t=tablefile [file]\n./hw5 inverse -p=poly\n";
            
            return 0;
        }else inverse( p );
        
    }else{
        cerr << "**************** Error: Wrong command ****************\n";
        cerr << "Valid commands are:\n./hw5 tablechek -t=tablefile\n./hw5 modprod -p1=poly1 -p2=poly2\n./hw5 keyexpand -k=key -t=tablefile\n./hw5 encrypt -k=key -t=tablefile [file]\n./hw5 decrypt -k=key -t=tablefile [file]\n./hw5 inverse -p=poly\n";
        
        return 0;
    }
    
    
    
    return 0;
}//end of main



