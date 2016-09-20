//
//  histo.cpp
//  Homework3
//
//  Created by Amin Amiripour on 2/22/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//


#include "histo.h"

void histo( char* t, char* i, char* filename )
{
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
        histo(t, i, tempFileName);
        remove(tempFileName);
        
        
    }else{
        
        FILE * inputfile;
        inputfile = fopen(filename, "r");
        if( inputfile == NULL )
        {
            std::cerr << "Cannot open inputfile" << std::endl;
            exit(1);
        }
        
        int period = atoi(t);   //convert to int
        if( period <= 0 ){
            std::cerr << "t should be integer\n";
            exit(1);
        }
        
        int which = atoi(i);    //convert to int
        if( which <= 0 ){
            std::cerr << "i should be integer\n";
            exit(1);
        }
        if( period < which ){
            std::cerr << "t should be bigger than i\n";
            exit(1);
        }
        
        int counter = 0;
        int* readBuffer = (int *)malloc(26 * sizeof(int));
        memset(readBuffer, 0, 26 * sizeof(int));
        
        char inputBuffer[period];
        memset(inputBuffer, '\0', period);
        fread(inputBuffer, 1, which-1, inputfile);
        
        
        while( fread(inputBuffer, 1, period, inputfile) )
        {
            
            if( *inputBuffer < 'a' || *inputBuffer > 'z' )      //invalid alphabet
                continue;
            else{
                counter = counter + 1;
                readBuffer[*inputBuffer - 'a']++;
            }
        }
        
        
        std::cout << "L=" << counter;
        std::cout << std::endl;
        
        int i = 0;
        while( i < 26 ){
            
            int j = 0, temp = -1, maximum = -1;
            while( j < 26 )
            {
                if( readBuffer[j] <= temp )
                {
                    j = j + 1;
                    continue;
                }else{
                    maximum = j;
                    temp = readBuffer[j];
                }
                
                j = j + 1;
            }
            
            std::cout << (char)('a' + maximum);
            std::cout << ": " << temp;
            std::cout << " (";
            std::cout << std::setprecision(2) << std::fixed << ((double)(temp * 100) / (double)counter);
            std::cout << "%)";
            std::cout << std::endl;
            
            readBuffer[maximum] = -1;
            i = i + 1;
            
        }
        
        
        free(inputBuffer);
        
        
    }
    
  
    
}



