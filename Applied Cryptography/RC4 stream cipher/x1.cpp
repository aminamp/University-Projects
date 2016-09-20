//
//  x1.cpp
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
#include "x1.h"



using namespace std;

void x1( char* filename ){
    
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
        x1(tempFileName);
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
        
       
        for(int i = 0; i < fsize ; i++)
            for(int j = 0; j < 8; j++)
            {
                int d = (ReadBuffer[i] >> j)&1 ;
                if( d == 1)
                    ones = ones + 1;
                else
                    zeroes = zeroes + 1;
                
            }
        
        if ( (ones + zeroes) < 10 )
        {
            cerr << "n = " << ones + zeroes;
            cerr << endl;
            cerr << "x1: insufficient data";
            cerr << endl;
            exit(1);
        }
        
        cout << "n = " << ones + zeroes;
        cout << endl;
        cout << "n0 = " << zeroes;
        cout << endl;
        cout << "n1 = " << ones;
        cout << endl;
        
        double x1 =  ( pow(zeroes - ones, 2.0) / (double)(ones + zeroes) );
        cout << "x1 = " << setprecision(6) << fixed << x1 ;
        cout << endl;
        cout << "pass/fail = ";
        if( x1 > 3.8415 )
            cout << "fail";
        else
            cout << "pass";
        
        cout << endl;
        

    }
    

    
    
    
}





