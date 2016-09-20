//
//  inverse.cpp
//  Homework5
//
//  Created by Amin Amiripour on 3/17/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//

#include <stdio.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include "inverse.h"
#include "modprod.h"

using namespace std;

unsigned long long hexTolong( char *hex )
{
    unsigned long long result = 0, mask = 0;
    
    int i = (int)strlen(hex)-1;
    while ( i > -1 ) {
        char temp = hex[i];
        result = result ^ ( (unsigned long long)strtol(&temp, NULL, 16) << mask);
        mask = mask + 4;
        i = i - 1;
    }
    return result;
}



unsigned int circular(unsigned int a, unsigned int b)
{
    
    unsigned char res0 = 0;
    unsigned char res1 = 0;
    unsigned char res2 = 0;
    unsigned char res3 = 0;
    
    res0 = prod((a & 0x000000ff), (b & 0x000000ff)) ^ prod((a & 0xff000000) >> 24, (b & 0x0000ff00) >> 8) ^ prod((a & 0x00ff0000) >> 16, (b & 0x00ff0000) >> 16) ^ prod((a & 0x0000ff00) >> 8, (b & 0xff000000) >> 24);
    res1 = prod((a & 0x0000ff00) >> 8, (b & 0x000000ff)) ^ prod((a & 0x000000ff), (b & 0x0000ff00) >> 8) ^ prod((a & 0xff000000) >> 24, (b & 0x00ff0000) >> 16) ^ prod((a & 0x00ff0000) >> 16, (b & 0xff000000) >> 24);
    res2 = prod((a & 0x00ff0000) >> 16, (b & 0x000000ff)) ^ prod((a & 0x0000ff00) >> 8, (b & 0x0000ff00) >> 8) ^ prod((a & 0x000000ff), (b & 0x00ff0000) >> 16) ^ prod((a & 0xff000000) >> 24, (b & 0xff000000) >> 24);
    res3 = prod((a & 0xff000000) >> 24, (b & 0x000000ff)) ^ prod((a & 0x00ff0000) >> 16, (b & 0x0000ff00) >> 8) ^ prod((a & 0x0000ff00) >> 8, (b & 0x00ff0000) >> 16) ^ prod((a & 0x000000ff), (b & 0xff000000) >> 24);
    
    int result = (res3 << 24) | (res2 << 16) | (res1 << 8) | res0 ;
    return result;
}



int degree( unsigned long long poly )
{
    int d = 0;
    unsigned long long mask;
    mask = (unsigned long long)0xFF << ((sizeof(unsigned long long) - 1)*8);
    
    unsigned long long shift = poly & mask;
    while( shift == 0 )
    {
        mask >>= 8;
        shift = poly & mask;
        if(mask == 0)
            break;
    }
    
    if(mask != 0)
    {
        while(mask != 0)
        {
            d += 1;
            mask >>=  8;
        }
        return d-1;
        
    }
    else
        return 0;
    
}

unsigned char inverseFunction(unsigned char byte)
{
    
    if( byte != 0 )
    {
        int j=0;
        for(j=0; j<256; j++){
            
            unsigned char res0 = 0;
            unsigned char res1 = 0;
            unsigned char res2 = 0;
            unsigned char res3 = 0;
            unsigned char i = (unsigned char)j;
            
            res0 = prod((byte & 0x000000ff), (i & 0x000000ff)) ^ prod((byte & 0xff000000) >> 24, (i & 0x0000ff00) >> 8) ^ prod((byte & 0x00ff0000) >> 16, (i & 0x00ff0000) >> 16) ^ prod((byte & 0x0000ff00) >> 8, (i & 0xff000000) >> 24);
            res1 = prod((byte & 0x0000ff00) >> 8, (i & 0x000000ff)) ^ prod((byte & 0x000000ff), (i & 0x0000ff00) >> 8) ^ prod((byte & 0xff000000) >> 24, (i & 0x00ff0000) >> 16) ^ prod((byte & 0x00ff0000) >> 16, (i & 0xff000000) >> 24);
            res2 = prod((byte & 0x00ff0000) >> 16, (i & 0x000000ff)) ^ prod((byte & 0x0000ff00) >> 8, (i & 0x0000ff00) >> 8) ^ prod((byte & 0x000000ff), (i & 0x00ff0000) >> 16) ^ prod((byte & 0xff000000) >> 24, (i & 0xff000000) >> 24);
            res3 = prod((byte & 0xff000000) >> 24, (i & 0x000000ff)) ^ prod((byte & 0x00ff0000) >> 16, (i & 0x0000ff00) >> 8) ^ prod((byte & 0x0000ff00) >> 8, (i & 0x00ff0000) >> 16) ^ prod((byte & 0x000000ff), (i & 0xff000000) >> 24);
            
            int result = (res3 << 24) | (res2 << 16) | (res1 << 8) | res0 ;
            if( result == 1 )
                return j;
            
        }
    }
    
    return 0;
}



/*
 
 Got some help from one of my friend for function division 
 
 */

void division(unsigned long long b, unsigned long long a, unsigned long long* quotient, unsigned long long* reminder, bool last)
{
    unsigned long long divide, mask_a , mask_dividend, temp = 0;
    unsigned char firstByte_a = 0 , nextbyte = 0 , tempquotient = 0;
    int degreea = 0, i=0;
    degreea = degree(a);
    int degreeb = 0;
    degreeb = degree(b);
    divide = b;
    mask_a = (unsigned long long)0xFF << (degreea*8);
    mask_dividend = (unsigned long long)0xFF << (degreeb*8);
    firstByte_a = ((mask_a) & a) >> (degreea*8);
 
    while ( i < (degreeb - degreea + 1) )
    {
        nextbyte = ((mask_dividend) & divide) >> ((degreeb - i)*8);
        if( last != true || i != degreeb-degreea)
            tempquotient = ( prod(inverseFunction(firstByte_a), nextbyte) );
        else
            tempquotient = ( prod(inverseFunction(firstByte_a), nextbyte^1) );
        
        *quotient <<= 8;
        *quotient |= tempquotient;
        temp = (unsigned long long)(circular(tempquotient, (unsigned int)a));
        temp <<= ( (degreeb - degreea - i) * 8 );
        
        divide ^= temp;
        mask_dividend >>=  8;
        
        i = i + 1;
    }
    
    *reminder = divide;
    
}

void inverse( char* poly )
{
    
    if( strlen(poly) != 8 )
    {
        cerr << "Bad poly, Length is not 8" << endl;
        exit(1);
    }
    
    int j = 0;
    for( j = 0; j <= 7; j++ )
    {
        
        if( poly[j] >= '0' && poly[j] <= '9' )
            continue;
        
        if( poly[j] >= 'a' && poly[j] <= 'f' )
            continue;
        
        cerr << "invalid poly, contain invalid character" << endl;
        exit(1);
        
    }
    

    unsigned long long reminder[7];
    unsigned long long quotient[7];
    unsigned long long x[7];
    char *initial = (char *)"0100000001";
    bool special = false;
    
    int i = 0;
    while( i <=6 )
    {
        reminder[i] = ~(unsigned long long)0;
        quotient[i] = x[i] = 0;
        i = i + 1;
    }
    
    reminder[1] = hexTolong(initial);
    x[1] = 0;
    reminder[2] = hexTolong(poly);
    x[2] = 1;
    
    i = 3;
    for(i=3; reminder[i]>1; i++)
    {
        
        special = false;
        
        if( i - 3 == degree( reminder[2] ) )
            special = true;
        
        if( i >= 4)
            if( (degree(reminder[i-2]) - degree(reminder[i-1]) >= 2) )
                special = true;
        
        division( reminder[i-2], reminder[i-1], &quotient[i], &reminder[i], special );
        
        unsigned char res0 = 0;
        unsigned char res1 = 0;
        unsigned char res2 = 0;
        unsigned char res3 = 0;
        
        res0 = prod((quotient[i] & 0x000000ff), (x[i-1] & 0x000000ff)) ^ prod((quotient[i] & 0xff000000) >> 24, (x[i-1] & 0x0000ff00) >> 8) ^ prod((quotient[i] & 0x00ff0000) >> 16, (x[i-1] & 0x00ff0000) >> 16) ^ prod((quotient[i] & 0x0000ff00) >> 8, (x[i-1] & 0xff000000) >> 24);
        res1 = prod((quotient[i] & 0x0000ff00) >> 8, (x[i-1] & 0x000000ff)) ^ prod((quotient[i] & 0x000000ff), (x[i-1] & 0x0000ff00) >> 8) ^ prod((quotient[i] & 0xff000000) >> 24, (x[i-1] & 0x00ff0000) >> 16) ^ prod((quotient[i] & 0x00ff0000) >> 16, (x[i-1] & 0xff000000) >> 24);
        res2 = prod((quotient[i] & 0x00ff0000) >> 16, (x[i-1] & 0x000000ff)) ^ prod((quotient[i] & 0x0000ff00) >> 8, (x[i-1] & 0x0000ff00) >> 8) ^ prod((quotient[i] & 0x000000ff), (x[i-1] & 0x00ff0000) >> 16) ^ prod((quotient[i] & 0xff000000) >> 24, (x[i-1] & 0xff000000) >> 24);
        res3 = prod((quotient[i] & 0xff000000) >> 24, (x[i-1] & 0x000000ff)) ^ prod((quotient[i] & 0x00ff0000) >> 16, (x[i-1] & 0x0000ff00) >> 8) ^ prod((quotient[i] & 0x0000ff00) >> 8, (x[i-1] & 0x00ff0000) >> 16) ^ prod((quotient[i] & 0x000000ff), (x[i-1] & 0xff000000) >> 24);
        
        int result = (res3 << 24) | (res2 << 16) | (res1 << 8) | res0 ;
        x[i] = result ^ x[i-2];
        
        if( reminder[i] == 0 )
            break;
    }
    
    i = 1;
    for(i=1; i<=6; i++)
    {
        cout << "i=" << i << ", ";
        cout << "rem[i]=";
        
        unsigned int mask;
        mask = 0xFF << 24;
        int j = 3;
        while ( j > -1 ) {
            cout << "{";
            cout << setfill('0') << setw(2) << hex << (int)((reminder[i]&mask)>>(j*8));
            cout << "}";
            mask >>= 8;
            j = j - 1;
        }
        
        
        cout << ", quo[i]=";
        mask = 0xFF << 24;
        j = 3;
        while ( j > -1 ) {
            cout << "{";
            cout << setfill('0') << setw(2) << hex << (int)(( quotient[i] & mask ) >> ( j * 8 ));
            cout << "}";
            mask >>= 8;
            j = j - 1;
        }
        
        
        cout << ", aux[i]=";
        mask = 0xFF << 24;
        j = 3;
        while ( j > -1 ) {
            cout << "{";
            cout << setfill('0') << setw(2) << hex << (int)(( x[i] & mask ) >> ( j * 8 ));
            cout << "}";
            mask >>= 8;
            j = j - 1;
        }
        cout << "\n";
        
        
        if(reminder[i] == 1)
        {
            cout << "Multiplicative inverse of ";
            mask = 0xFF << 24;
            j = 3;
            while ( j > -1 ) {
                cout << "{";
                cout << setfill('0') << setw(2) << hex << (int)(( reminder[2] & mask ) >> ( j * 8 ));
                cout << "}";
                mask >>= 8;
                j = j - 1;
            }
            cout << " is ";
            mask = 0xFF << 24;
            j = 3;
            while ( j > -1 ) {
                cout << "{";
                cout << setfill('0') << setw(2) << hex << (int)(( x[i] & mask ) >> ( j * 8 ));
                cout << "}";
                mask >>= 8;
                j = j - 1;
            }
            cout << "\n";
            break;
        }
        
        if(reminder[i] == 0)
        {
            mask = 0xFF << 24;
            j = 3;
            while ( j > -1 ) {
                cout << "{";
                cout << setfill('0') << setw(2) << hex << (int)(( reminder[2] & mask ) >> ( j * 8 ));
                cout << "}";
                mask >>= 8;
                j = j - 1;
            }
            cout << " does not have a multiplicative inverse.\n";
            break;
        }
    }
}

