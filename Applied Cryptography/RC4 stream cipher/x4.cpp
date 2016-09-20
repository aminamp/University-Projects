//
//  x4.cpp
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

void x4( char* filename ){
    
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
        x4(tempFileName);
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
        
        
        
        if ( (ones + zeroes) < 79 )
        {
            cerr << "n = " << ones + zeroes;
            cerr << endl;
            cerr << "x4: insufficient data";
            cerr << endl;
            exit(1);
        }
        
        if ( k >= 12 )
        {
            cerr << "n = " << ones + zeroes;
            cerr << endl;
            cerr << "k = " << k;
            cerr << endl;
            cerr << "x4: k is too large";
            cerr << endl;
            exit(1);
        }
        
        cout << "n = " << ones + zeroes;
        cout << endl;
        cout << "k = " << k;
        cout << endl;
        

        
        
        int *blocks = (int *)malloc(sizeof(int) * k);
        for ( int i = 1; i<= k ; i++) {
            int finish = 0;
            int start = 0;
            int j = 0;
            int counter = 0;
            
            while ( j < fsize * 8 ) {
                
                if (bits[j] == 1) {
                    start = j;
                    
                    while ( (j+1)<(fsize * 8) && bits[j+1] == 1)
                        j = j + 1;
                    
                    finish = j;
                    
                    if( (finish - start + 1) == i )
                        counter = counter + 1;
                    
                    
                }
                
                j = j + 1;
            }
            
            blocks[i-1] = counter;
            //cout << "B" << i << " = " << blocks[i-1] << endl;
        }
        
        
        int *gaps = (int *)malloc(sizeof(int) * k);
        for ( int i = 1; i<= k ; i++) {
            int finish = 0;
            int start = 0;
            int j = 0;
            int counter = 0;
            
            while ( j < fsize * 8 ) {
                
                if (bits[j] == 0) {
                    start = j;
                    
                    while ( (j+1)<(fsize * 8) && bits[j+1] == 0)
                        j = j + 1;
                    
                    finish = j;
                    
                    if( (finish - start + 1) == i )
                        counter = counter + 1;
                    
                    
                }
                
                j = j + 1;
            }
            
            gaps[i-1] = counter;
            //cout << "G" << i << " = " << gaps[i-1] << endl;
        }
        
        
        double *e = (double *)malloc(sizeof(double) * k);
        for (int i = 1; i <= k; i++) {
            
            e[i-1] = ( ((ones + zeroes) - i + 3) / pow(2, i+2));
            cout << "e" << i << " = " << setprecision(6) << fixed << e[i-1] ;
            cout << endl;
            
            cout << "B" << i << " = " << blocks[i-1] << endl;
            cout << "G" << i << " = " << gaps[i-1] << endl;
        }
        
        
        
        double sum = 0;
        for (int i = 1; i <= k; i++)
        {
            sum += ( (pow(blocks[i-1]-e[i-1], 2) + pow(gaps[i-1]-e[i-1], 2)) / e[i-1] );
        }
        double x4;
        x4 = sum;
        cout << "x4 = " << setprecision(6) << fixed << x4 << endl ;
        
        double threshold;
        
        if(k == 2)
            threshold = 5.9915;
        if(k == 3)
            threshold = 9.4877;
        if(k == 4)
            threshold = 12.5916;
        if(k == 5)
            threshold = 15.5073;
        if(k == 6)
            threshold = 18.3070;
        if(k == 7)
            threshold = 21.0261;
        if(k == 8)
            threshold = 23.6848;
        if(k == 9)
            threshold = 26.2962;
        if(k == 10)
            threshold = 28.8693;
        if(k == 11)
            threshold = 31.4104;
        
        cout << "pass/fail = ";
        if( x4 > threshold )
            cout << "fail";
        else
            cout << "pass";
        
        cout << endl;
        
        
    }
    
    
    
    
    
}


