//
//  x3.cpp
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

void x3( char* filename ){
    
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
        x3(tempFileName);
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
        
        int m = 0;
        
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
            if( floor((zeroes + ones)/i) >= (5 * pow(2, i)) )
            {
                m = i;
                break;
            }
        }
        
        k = (int)floor((zeroes + ones)/m);
        
        
        if ( (ones + zeroes) < 10 )
        {
            cerr << "n = " << ones + zeroes;
            cerr << endl;
            cerr << "x3: insufficient data";
            cerr << endl;
            exit(1);
        }
        
        if ( m >= 11 )
        {
            cerr << "n = " << ones + zeroes;
            cerr << endl;
            cerr << "m = " << m;
            cerr << endl;
            cerr << "x3: m is too large";
            cerr << endl;
            exit(1);
        }
        
        cout << "n = " << ones + zeroes;
        cout << endl;
        cout << "m = " << m;
        cout << endl;
        cout << "k = " << k;
        cout << endl;
        
        
        int *array = (int *)malloc(sizeof(int) * m);
        int *count = (int *)malloc(sizeof(int) * (int)pow(2, m));
        
        for (int i = 0; i < m;  i++) {
            array[i] = 0;
        }
        
        for (int z = 0; z < (int)pow(2, m) ; z++) {
            
            
            int last = m - 1;
            int temp = z;
            while ( temp != 0 ) {
                if( temp%2 == 0 )
                    array[last] = 0;
                else
                    array[last] = 1;
                
                last = last - 1;
                temp = temp/2;
            }
            
            cout << "n";
            
            for (int i = 0; i < m;  i++) {
                cout << array[i];
            }
            
            cout << " = " ;
            
           
            int counter = 0;
            
            for( int i = 0; i < k; i++ )
            {
                bool flag = true;
                
                for ( int j = 0; j < m;  j++ )
                    if( bits[(m*i)+j] != array[j] )
                        flag = false;
                
                if( flag == true ){
                    counter = counter + 1;
                    
                }
                
            }
            
            cout << counter << endl;
            count[z] = counter;
            
            
        }
        

        
        int sum = 0;
        for (int z = 0; z < (int)pow(2, m) ; z++)
        {
            sum += (int)pow(count[z], 2);
        }
        
        
        
        double x3 = (double)((( pow(2, m) / (double)k ) * (sum) ) - k);
        cout << "x3 = " << setprecision(6) << fixed << x3 ;
        cout << endl;
        cout << "pass/fail = ";
        
        
        double threshold;
        
        if(m == 1)
            threshold = 3.8415;
        if(m == 2)
            threshold = 7.8147;
        if(m == 3)
            threshold = 14.0671;
        if(m == 4)
            threshold = 24.9958;
        if(m == 5)
            threshold = 44.9853;
        if(m == 6)
            threshold = 82.5287;
        if(m == 7)
            threshold = 154.3015;
        if(m == 8)
            threshold = 293.2478;
        if(m == 9)
            threshold = 564.6961;
        if(m == 10)
            threshold = 1098.5208;

        
        
        if( x3 > threshold )
            cout << "fail";
        else
            cout << "pass";
        
        cout << endl;
        
        
    }
    
    
    
    
    
}


