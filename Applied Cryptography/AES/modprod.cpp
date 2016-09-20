//
//  modprod.cpp
//  Homework5
//
//  Created by Amin Amiripour on 3/17/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include "modprod.h"
using namespace std;


unsigned char prod(unsigned char poly1, unsigned char poly2)
{
    unsigned char tempp[8];
    int i = 1;
    tempp[0] = poly1;
    unsigned char oneinhex = 1;
    unsigned char result = 0;


    while( i < 8 )
    {
        unsigned char temp;
        temp = tempp[i-1] & (1<<7) ;
        if( temp == 0 )
        {
            tempp[i]= tempp[i-1] << 1;
            i = i + 1;
            continue;
        }
        
        tempp[i] =( tempp[i-1] << 1 ) ^ (0x1B);
        i = i + 1;
    }
    

    i = 0;
    while( i < 8 )
    {
        unsigned char temp;
        temp = poly2 & oneinhex;
        if( temp == oneinhex )
            result ^= tempp[i];
        
        oneinhex <<= 1;
        i = i + 1;
    }

    
    return result;
}


void modprod( char* p1, char* p2 ){
    if( strlen( p1 ) == 8 )
    {
        if ( strlen( p2 ) == 8 )
        {
            for( int i = 0; i < 8; i++ )
            {
                if( p1[i] >= '0' && p1[i] <= '9' )
                    continue;
                
                if( p1[i] >= 'a' && p1[i] <= 'f' )
                    continue;
                
                cerr << "poly1 contains invalid characters" << endl;
                exit(1);
            }
            
            for( int i = 0; i < 8; i++ )
            {
                if( p2[i] >= '0' && p2[i] <= '9' )
                    continue;
                
                if( p2[i] >= 'a' && p2[i] <= 'f' )
                    continue;
                
                cerr << "poly2 contains invalid characters" << endl;
                exit(1);
            }
            
            unsigned int a = strtoul(p1, NULL, 16);
            unsigned int b = strtoul(p2, NULL, 16);
            unsigned char res0 = 0;
            unsigned char res1 = 0;
            unsigned char res2 = 0;
            unsigned char res3 = 0;
            
            res0 = prod((a & 0x000000ff), (b & 0x000000ff)) ^ prod((a & 0xff000000) >> 24, (b & 0x0000ff00) >> 8) ^ prod((a & 0x00ff0000) >> 16, (b & 0x00ff0000) >> 16) ^ prod((a & 0x0000ff00) >> 8, (b & 0xff000000) >> 24);
            res1 = prod((a & 0x0000ff00) >> 8, (b & 0x000000ff)) ^ prod((a & 0x000000ff), (b & 0x0000ff00) >> 8) ^ prod((a & 0xff000000) >> 24, (b & 0x00ff0000) >> 16) ^ prod((a & 0x00ff0000) >> 16, (b & 0xff000000) >> 24);
            res2 = prod((a & 0x00ff0000) >> 16, (b & 0x000000ff)) ^ prod((a & 0x0000ff00) >> 8, (b & 0x0000ff00) >> 8) ^ prod((a & 0x000000ff), (b & 0x00ff0000) >> 16) ^ prod((a & 0xff000000) >> 24, (b & 0xff000000) >> 24);
            res3 = prod((a & 0xff000000) >> 24, (b & 0x000000ff)) ^ prod((a & 0x00ff0000) >> 16, (b & 0x0000ff00) >> 8) ^ prod((a & 0x0000ff00) >> 8, (b & 0x00ff0000) >> 16) ^ prod((a & 0x000000ff), (b & 0xff000000) >> 24);
            
            cout << "{" << p1[0] << p1[1] << "}";
            cout << "{" << p1[2] << p1[3] << "}";
            cout << "{" << p1[4] << p1[5] << "}";
            cout << "{" << p1[6] << p1[7] << "}";
            cout << " CIRCLEX ";
            cout << "{" << p2[0] << p2[1] << "}";
            cout << "{" << p2[2] << p2[3] << "}";
            cout << "{" << p2[4] << p2[5] << "}";
            cout << "{" << p2[6] << p2[7] << "}";
            cout << " = ";
            cout << "{" << setfill('0') << setw(2) << hex << (int)res3 << "}";
            cout << "{" << setfill('0') << setw(2) << hex << (int)res2 << "}";
            cout << "{" << setfill('0') << setw(2) << hex << (int)res1 << "}";
            cout << "{" << setfill('0') << setw(2) << hex << (int)res0 << "}";
            cout << endl;

        }//end if ( strlen( p2 ) == 8 )
        else{
            cerr << "poly2 is not a string of length 8" << endl;
            exit(1);
        }
    }//end if( strlen( p1 ) == 8 )
    else{
        cerr << "poly1 is not a string of length 8" << endl;
        exit(1);
    }

    
}




