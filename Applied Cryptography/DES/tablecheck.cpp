//
//  tablecheck.cpp
//  Homework4
//
//  Created by Amin Amiripour on 3/7/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tablecheck.h"

using namespace std;

void tablecheck( char* filename )
{
    FILE *table = fopen(filename, "rb");
    char *key;
    char *read;
    
    if( table == NULL )
    {
        std::cerr << "Cannot open inputfile" << std::endl;
        exit(1);
    }
    
    char* readbuffer = (char *)malloc(256 * sizeof(char));

    
    for( int j = 0; j <= 13; j++ )
    {
        int i=0;
        fgets(readbuffer, 256, table);
        key = strtok(readbuffer, "=");
        int values[64] = {-1};
    
        do{
            read = strtok(NULL, ",");
            if( read == NULL )
                break;
            values[i] = atoi(read);
            i = i + 1;
        }while( read != NULL );
        

        
        if( strcmp(key, "P") == 0 )
            if( i != 32 )
            {
                std::cerr << "P should contain 32 values, now contains " << i << " values" << std::endl;
                exit(1);
            }
        
            else{
                int counter[33] = {0};
                int j = 0;
                while( j < 32 )
                {
                    if( values[j] <= 0 || values[j] > 32 )
                    {
                        std::cerr << "P contains invalid values" << std::endl;
                        exit(1);
                    }
                    else{
                        counter[ values[j] ] = 1;
                        j = j + 1;
                    }
                }
                
                for(int j = 0; j <= 31; j++ )
                    if( counter[ ( j + 1 ) ] == 0 )
                    {
                        std::cerr << "P is not a permutation" << std::endl;
                        exit(1);
                    }
            }
            else if( strcmp(key, "E") == 0 )
                if(i != 48 )
                {
                    std::cerr << "E should contain 48 values" << std::endl;
                    exit(1);
                }
                else{
                    int counter[33] = {0};
                    int j=0;
                    
                    while( j <= 47 )
                    {
                        if( values[j] <= 0 || values[j] > 32 )
                        {
                            std::cerr << "E contains invalid values" << std::endl;
                            exit(1);
                        }
                        else {
                            counter[ values[j] ] = counter[ values[j] ] + 1;
                            j = j + 1;
                        }
  
                    }
                    
                    j = 1;
                    while ( j <= 32 )
                    {
                        if( counter[j] <= 0 )
                        {
                            std::cerr << "E doen not contains " << j << std::endl;
                            exit(1);
                        }
                        else if( counter[j] > 2)
                        {
                            std::cerr << "E contains value " << j << " for " << counter[j] << " times"<< std::endl;
                            exit(1);
                        }
                        
                        j = j + 1;
                        
                    }
                
                }
        else if( strcmp(key, "IP") == 0 )
            if( i != 64 )
            {
                std::cerr << "IP should contain 64 values, now contains " << i << " values" << std::endl;
                exit(1);
            }
            else{
            int counter[65] = {0};
                
                int j = 0;
                while( j < 64 )
                {
                    if( values[j] <= 0 || values[j] > 64 )
                    {
                        std::cerr << "IP contains invalid values" << std::endl;
                        exit(1);
                    }else{
                         counter[ values[j] ] = counter[ values[j] ] + 1;
                        j = j + 1;
                    }
                }
                

                j = 1;
                while ( j <= 64 )
                {
                    if( counter[j]==0 )
                    {
                        std::cerr << "IP is not a permutation" << std::endl;
                        exit(1);
                    }
                    j = j + 1;
                }

                
            }
            else if( strcmp(key, "PC1") == 0 )
                if( i != 56 )
                {
                    std::cerr << "PC1 should contain 56 values, now contains " << i << " values" << std::endl;
                    exit(1);
                }
                else{
                    int counter[65] = {0};
                    
                    int j = 0;
                    while ( j < 56 )
                    {
                        if( values[j] <= 0 || values[j] > 64 )
                        {
                            std::cerr << "PC1 is not a permutation" << std::endl;
                            exit(1);
                        }else if( values[j]%8 == 0 ){
                            std::cerr << "PC1 is not a permutation, some values did not occur" << std::endl;
                            exit(1);
                        }
                        else{
                            counter[values[j]] = counter[values[j]] + 1;
                            j = j + 1;
                        }
                        
                    }

                    j = 1;
                    while( ( j <= 64 ) && ( j % 8 != 0 ) )
                    {
                        if( counter[j] == 0 )
                        {
                            std::cerr << "PC1 is not a permutation, value " << j << " is missing" << std::endl;
                            exit(1);
                        }else
                            j = j + 1;
                    }

                }
        else if( strcmp(key, "V") == 0 )
            if( i != 16 )
            {
                std::cerr << "V should contain 16 values, now contains " << i << " values" << std::endl;
                exit(1);
            }
            else{
            int one = 0, two = 0, j = 0;

            while ( j < 16 )
            {
                if( values[j] == 1 )
                    one = one + 1;
                
                if ( values[j] == 2 )
                    two = two + 1;
                
                j = j + 1;
            }
   
            if( one != 4 )
            {
                std::cerr << "V should contain 4 ones, now contains " << one << " ones" << std::endl;
                exit(1);
                
            }else if( two != 12 )
            {
                std::cerr << "V should contain 12 two, now contains " << two << " two" << std::endl;
                exit(1);
                    
            }
                
        }
        else if( strcmp(key, "PC2") == 0 )
            if( i != 48 )
            {
                std::cerr << "PC2 should contain 48 values, now contains " << i << " values" << std::endl;
                exit(1);
            }
            else
            {
            int counter[57] = {0};
            int j = 0, count = 0;
                
                while( j < 48 )
                {
                    if( values[j] <= 0 || values[j] > 56 )
                    {
                        std::cerr << "PC2 contains invalid values" << std::endl;
                        exit(1);
                    }
                    else {
                        counter[ values[j] ] = counter[ values[j] ] + 1;
                        j = j + 1;
                    }
                }
                

            j = 1;
                while ( j <= 56 )
                {
                    if( counter[j] == 0 )
                        count = count + 1;
                    j = j + 1;
                }

            if( count >= 9 )
            {
                std::cerr << "PC2 is not a permutation, some values in PC2 table occur too many times" << std::endl;
                exit(1);

            }
        }
        else if( strncmp(key, "S",1) == 0 )
            if( i != 64 )
            {
                char *pointer = key + 1;
                int n = atoi(pointer);
                std::cerr << key[0] << n << " should contain 64 values, now contains " << i << " values" << std::endl;
                exit(1);
            }
        else{

            int counter[16] = {0};
            int j=0;
            for( int j = 0 ; j < 64; j++ )
                counter[values[j]] = counter[values[j]] + 1;

            while( j < 16)
            {
                if( counter[j] !=4 )
                {
                    char *pointer = key + 1;
                    int n = atoi(pointer);
                    std::cerr << key[0] << n << " value " << j << " did not occure 4 times in it"<< std::endl;
                    exit(1);
                }
                
                j = j + 1;
                
            }

        }else{
                std::cerr << "malformed tablefile"<< std::endl;
                exit(1);
            }
    }
    

}


