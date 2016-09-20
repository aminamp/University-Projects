//
//  x2.cpp
//  homework7
//
//  Created by Amin Amiripour on 4/18/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//

#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <fstream>
#include <stdlib.h>
#include <istream>
#include <string>
#include <string.h>
#include "x2.h"


using namespace std;

void x2( char* filename ){
    
    if ( !filename )  //read from input when file is not exist
    {
        //cout << "Please enter your data:\n";
        char tempFileName[]="tempp.txt";
        std::ofstream tempFile;
        
        tempFile.open(tempFileName, std::ios_base::binary);
        
        char c;
        while( std::cin.get(c) )
        {
            tempFile << c;
            if(std::cin.peek() == EOF)
                break;
        }
        
        tempFile.close();
        x2(tempFileName);
        remove(tempFileName);
        
        
    }else{
        
        FILE* inputfile;
        inputfile = fopen(filename, "rb");
        if( inputfile == NULL )
        {
            std::cerr << "Cannot open inputfile or does not exist" << std::endl;
            exit(1);
        }
        
        fseek(inputfile, 0, SEEK_END);
        long fsize = ftell(inputfile);
        fseek(inputfile, 0, SEEK_SET);
        
        unsigned char *ReadBuffer = (unsigned char *)malloc(fsize);
        fread(ReadBuffer, fsize, 1, inputfile);
        fclose(inputfile);
        
        //ReadBuffer[fsize]= '\0';
        
        
        int k = 1;
        for( int i = 0; (i < fsize && i < 256); i++ )
        {
            if( i == 16 * k )
            {
                printf("\n");
                k = k + 1;
                
            }
            
            printf("%02x", (unsigned char)ReadBuffer[i]);
            
            
        }
        
        printf("\n");
        
        int ones = 0;
        int zeroes = 0;
        int oneone = 0;
        int onezero = 0;
        int zeroone = 0;
        int zerozero = 0;
        
        int bits[ fsize * 8 ];
        
        
        for(int i = 0; i < fsize ; i++)
            for(int j = 0; j < 8; j++)
            {
                int d = (ReadBuffer[i] >> j)&1 ;
                bits[ 8*(i+1) - j - 1 ] = d;
                if( d == 1)
                    ones = ones + 1;
                else
                    zeroes = zeroes + 1;
                
            }
        
        
        
        for( int i = 0; i < (8*fsize)-1; i++ )
        {
            if( bits[i] == 0 && bits[i+1] == 0)
                zerozero = zerozero + 1;
            
            if( bits[i] == 0 && bits[i+1] == 1)
                zeroone = zeroone + 1;
            
            if( bits[i] == 1 && bits[i+1] == 0)
                onezero = onezero + 1;
            
            if( bits[i] == 1 && bits[i+1] == 1)
                oneone = oneone + 1;
            
        }
        
        if ( (ones + zeroes) < 21 )
        {
            cerr << "n = " << ones + zeroes;
            cerr << endl;
            cerr << "x2: insufficient data";
            cerr << endl;
            exit(1);
        }
        
        cout << "n = " << ones + zeroes;
        cout << endl;
        cout << "n0 = " << zeroes;
        cout << endl;
        cout << "n1 = " << ones;
        cout << endl;
        cout << "n00 = " << zerozero;
        cout << endl;
        cout << "n01 = " << zeroone;
        cout << endl;
        cout << "n10 = " << onezero;
        cout << endl;
        cout << "n11 = " << oneone;
        cout << endl;
        
        
    
        double x2 =  ( 4 * ( ( pow(zerozero, 2.0) + pow(zeroone, 2.0) + pow(onezero, 2.0) + pow(oneone, 2.0) ) / (double)(ones + zeroes - 1) ) ) - ( 2 * ( ( pow(zeroes, 2.0) + pow(ones, 2.0) ) )/(zeroes+ones) ) + 1 ;
        cout << "x2 = " << setprecision(6) << fixed << x2 ;
        cout << endl;
        cout << "pass/fail = ";
        if( x2 > 5.9915 )
            cout << "fail";
        else
            cout << "pass";
        
        cout << endl;
        
        
    }
    
    
    
    
    
}


