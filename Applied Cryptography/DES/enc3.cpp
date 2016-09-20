//
//  enc3.cpp
//  Homework4
//
//  Created by Amin Amiripour on 3/7/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//

#include <stdio.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include<iomanip>
#include <string.h>
#include <stdio.h>
#include "enc.h"
#include "dec.h"
#include "enc3.h"
#include "tablecheck.h"

using namespace std;


void encrypt3(char *key, char *tablefilename, char *filename)
{
    
    if( strlen(key) < 24  )
    {
        cerr << "Key is too short"<< endl;
        exit(1);
    }
    
    for( std::size_t i = 0; i < strlen(key); i++ )
    {
        if( key[i] >= '0' && key[i] <= '9' )
            continue;
        
        if( key[i] >= 'a' && key[i] <= 'f' )
            continue;
        
        cerr << "Malformed Key"<< endl;
        exit(1);
        
    }
    
    tablecheck(tablefilename);
    
    
    if( !filename )
    {
        
        char tempFileName[]="tempp.txt";
        ofstream tempFile;
        
        tempFile.open(tempFileName, ios_base::binary);
        
        char c;
        while( cin.get(c) )
        {
            tempFile << c;
            if(cin.peek() == EOF)
                break;
        }
        
        tempFile.close();
        encrypt3( key, tablefilename, tempFileName);
        remove(tempFileName);
        
    }else{
        int IP[64]={0}, invIP[64]={0}, PC1[56]={0}, PC2[48]={0}, E[48]={0}, V[16]={0}, P[32]={0}, S[8][64]={0};
        
        FILE *inputFile = NULL;
        inputFile = fopen(filename, "rb");
        
        if( inputFile == NULL )
        {
            cerr << "Cannot open " << filename << " or does not exist"<< endl;
            exit(1);
        }else{
            
            
            FILE *tableFile = NULL;
            tableFile = fopen(tablefilename, "rb");
            if(tableFile == NULL)
            {
                cerr << "Cannot open " << tablefilename << " or does not exist"<< endl;
                exit(1);
            }
            

            int i = 0;
            char* readbuffer = (char *)malloc(256 * sizeof(char));
            char key1[16] = {'\0'}, key2[16] = {'\0'} , key3[16] = {'\0'};
            unsigned char keys1[16][6]= {'\0'}, keys2[16][6]= {'\0'}, keys3[16][6]= {'\0'};
            unsigned char* inputbuffer = (unsigned char *)malloc(8 * sizeof(unsigned char));
            unsigned char* result = (unsigned char *)malloc(8 * sizeof(unsigned char));
            int end = 0;
            char *title, *read;
            while( i <= 13 )
            {
                int k = 0;
                fgets(readbuffer, 256, tableFile);
                title = strtok(readbuffer, "=");
                int values[64] = {-1};
                
                do{
                    read = strtok(NULL, ",");
                    if( read == NULL )
                        break;
                    values[k] = atoi(read);
                    k = k + 1;
                }while( read != NULL );
                
                if( strcmp(title, "IP") == 0 )
                    for( int j = 0; j < 64; j++ )
                        IP[j] = values[j];
                
                if( strcmp(title, "E") == 0 )
                    for(int j = 0; j < 48; j++)
                        E[j] = values[j];
                
                if( strcmp(title, "V") == 0 )
                    for(int j = 0; j < 16; j++)
                        V[j] = values[j];
                
                if( strcmp(title, "P") == 0 )
                    for(int j = 0; j < 32; j++)
                        P[j] = values[j];
                
                if( strncmp(title, "S",1) == 0 )
                {
                    char *pointer = title+1;
                    int s = atoi(pointer);
                    for(int j = 0; j < 64; j++)
                        S[s-1][j] = values[j];
                }
                
                if( strcmp(title, "PC1") == 0 )
                    for(int j = 0; j < 56; j++)
                        PC1[j] = values[j];
                
                if( strcmp(title, "PC2") == 0 )
                    for(int j = 0; j < 48; j++)
                        PC2[j] = values[j];
                
                i = i + 1;
            }
            
            
            int m = 0;
            while( m < 64 )
            {
                invIP[ IP[m] - 1 ] = m + 1;
                m = m + 1;
            }
            
            
            i = 0;
            while( i < 48 )
            {
                if( i < 16 )
                    key1[i] = key[i];
                else if( i < 32 && i >= 16)
                    key2[i-16] = key[i];
                else if( i < 48 && i >= 32 )
                    key3[i-32] = key[i];
                
                i = i + 1;
            }

            
            keyGenerator(key1, keys1, PC1, V, PC2);
            keyGenerator(key2, keys2, PC1, V, PC2);
            keyGenerator(key3, keys3, PC1, V, PC2);
            
            
            while(1)
            {
                int counter = fread(inputbuffer,1,8,inputFile);
                if ( counter <= 0 )
                    break;
                else{
                    if( counter != 8 )
                        while ( counter < 8 )
                        {
                            inputbuffer[counter] = '\0';
                            counter = counter + 1;
                        }
                    
                    
                    encryptfunction(inputbuffer, keys1, S, P, IP, invIP, E, result, end, 1);
                    decryptfunction(result, keys2, S, P, IP, invIP, E, result, end);
                    encryptfunction(result, keys3, S, P, IP, invIP, E, result, end, 1);
                    
                    
                    int i = 0;
                    while ( i < 8 )
                    {
                        cout << result[i];
                        i = i + 1;
                    }
                    
                    end = end + 1;
                }
                
            }
            
            fclose(tableFile);
            fclose(inputFile);
            
        }
        
    }
    
   
}


