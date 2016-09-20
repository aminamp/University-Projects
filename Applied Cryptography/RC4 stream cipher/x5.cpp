//
//  x5.cpp
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
#include "x3.h"

using namespace std;

void x5( char* d, char* filename ){
    
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
        x5(d, tempFileName);
        remove(tempFileName);
        
        
    }else{
        
        int dval = atoi(d);
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
        
        
        for(int i = (zeroes + ones); i > 0; i-- )
        {
            if( ( ((zeroes + ones) - i + 3) / pow(2, (i+2)) ) >= 5 )
            {
                k = i;
                break;
            }
        }
        
        
        
        if ( (ones + zeroes) < dval + 10 )
        {
            cerr << "n = " << ones + zeroes;
            cerr << endl;
            cerr << "x5: insufficient data";
            cerr << endl;
            exit(1);
        }
        
        if ( dval < 1 || dval > (ones + zeroes) )
        {
            cerr << "n = " << ones + zeroes;
            cerr << endl;
            cerr << "x5: d should be in the range [1, n>>1]";
            cerr << endl;
            exit(1);
        }
        
        cout << "n = " << ones + zeroes;
        cout << endl;
        cout << "d = " << dval;
        cout << endl;
        
        
       ////////////////////////////////////////////////////////
        
        int sum = 0;
        for ( int i = 0; i < (ones + zeroes)-dval ; i++) {
            sum += (int)( bits[i] ^ bits[i+dval] );
        }
        
        
        cout << "A(d) = " << sum << endl;
        
     
        double x5 = 0;
        x5 = ( ( (2*sum) - (ones+zeroes-dval) ) / sqrt( (ones+zeroes)-dval) );
        cout << "x5 = " << setprecision(6) << fixed << x5 << endl ;
        

        
        cout << "pass/fail = ";
        if( x5 > 1.9600 || x5 < -1.9600 )
            cout << "fail";
        else
            cout << "pass";
        
        cout << endl;
        
        
    }
    
    
    
    
    
}

