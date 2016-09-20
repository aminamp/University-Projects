//
//  dec.cpp
//  Homework4
//
//  Created by Amin Amiripour on 3/7/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//

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
#include "tablecheck.h"
using namespace std;

void decryptfunction(unsigned char *buffer, unsigned char keys[][6], int S[][64], int *P, int *IP, int *inverseIP, int *E, unsigned char *result, int done)
{

    unsigned char* message = (unsigned char*) malloc(8 * sizeof(unsigned char*));
    
    int i = 0;
    while( i < 64 )
    {
        int index = i / 8;
        unsigned char shift = buffer[ (IP[i]-1)/8 ] >> ( 7 - ((IP[i]-1)%8) );
        int result = shift & 1;
        message[index] = ( message[index] << 1 ) + result;
        i = i + 1;
    }
    

    ////
    i = 16;
    while( i > 0 )
    {
        int j = 0;
        if(done == 0)
        {
            int j = 0;
            cerr << "(L";
            cerr << ( 16 - i )%17;
            cerr << ",R";
            cerr << ( 16 - i )%17;
            cerr << ")=";
            
            while( j < 8 )
            {
                fprintf(stderr, "%02x", message[j]);
                j = j + 1;
            }
            cerr << endl;
        }
        
        
        
        unsigned char* Eoutput = (unsigned char*) malloc( 6 * sizeof(unsigned char*) );
        j = 0;
        while( j < 48 )
        {
            int index = j/8;
            unsigned char shift = message[ 4+(E[j]-1)/8 ] >> ( 7-((E[j]-1)%8) );
            int result = shift & 1;
            if( (j % 8 ) == 0 )
                Eoutput[index] = result;
            else
                Eoutput[index] = (Eoutput[index] << 1) + result;
            j = j + 1;
        }
        
        
        
        unsigned char *Toutput = (unsigned char*) malloc( 8 * sizeof(unsigned char*) );
        j = 0;
        while( j < 48 )
        {
            int index = j/6;
            unsigned char shift = Eoutput[j/8] >> ( 7 - ( j%8 ) );
            unsigned char shift2 = keys[i-1][j/8] >> ( 7 - ( j%8 ) );
            int result = shift & 1;
            int result2 = shift2 & 1;
            result = result ^ result2;
            
            if(j % 6 == 0)
                Toutput[index] = result;
            else
                Toutput[index] = (Toutput[index] << 1) + result;
            
            j = j + 1;
        }
        
        
        unsigned char *Toutput2 = (unsigned char*) malloc( 8 * sizeof(unsigned char*));
        j = 0;
        while( j < 8 )
        {
            int c = 0, k = 0;
            unsigned char shift = ( Toutput[j] >> 5 );
            int result = (2 * (shift & 1)) + (Toutput[j] & 1);
            while ( k < 4 )
            {
                unsigned char shift = ( Toutput[j] >> (4-k) );
                int result = shift & 1;
                c = (c << 1) + result;
                k = k + 1;
            }
            Toutput2[j] = S[j][result*16+c];
            j = j + 1;
        }
        
        
        unsigned char *Toutput3 = (unsigned char*) malloc(4*sizeof(unsigned char*));;
        j = 0;
        while( j < 32 )
        {
            int index = j/8;
            unsigned char shift = Toutput2[ (P[j]-1)/4 ] >> ( 3 - ((P[j]-1)%4) );
            int result = shift & 1;
            Toutput3[index] = (Toutput3[index] << 1) + result;
            j = j + 1;
            
        }
        

        unsigned char* newm = (unsigned char*) malloc(8 * sizeof(unsigned char*));
        j = 0;
        while( j < 4 )
        {
            newm[j] = message[j+4];
            newm[j+4] = message[j] ^ Toutput3[j];
            j = j + 1;
        }
        
        j = 0;
        while( j < 8 )
        {
            message[j] = newm[j];
            j = j + 1;
        }
        
        i = i - 1;
    }
    
    int j = 0;
    if(done == 0)
    {
        cerr << "(L";
        cerr << ( 16 - i )%17;
        cerr << ",R";
        cerr << ( 16 - i )%17;
        cerr << ")=";
        int j = 0;
        while( j < 8 )
        {
            fprintf(stderr, "%02x", message[j]);
            j = j + 1;
        }
        cerr << endl;
    }
    
    unsigned char* result0 = (unsigned char *) malloc(8*sizeof(unsigned char*));
    j = 0;
    while( j < 4 )
    {
        result0[j] = message[ j + 4 ]; //right
        result0[ j + 4 ] = message[j]; //left
        j = j + 1;
    }
    
    j = 0;
    while ( j < 64 )
    {
        int index = j/8;
        unsigned char shift = ( result0[ ( inverseIP[j] - 1 ) / 8 ] ) >> ( 7 - ( ( inverseIP[j] - 1 ) % 8 ) );
        int temp = shift & 1;
        result[index] = (result[index] << 1) + temp;
        j = j + 1;
    }
    
}

void decrypt(char *key, char *tablefilename, char *filename)
{
    if( strlen(key) != 16 )
    {
        cerr << "Malformed Key"<< endl;
        exit(1);
    }
    
    for( int i = 0; i < 16; i++ )
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
        decrypt( key, tablefilename, tempFileName);
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
            unsigned char keys[16][6];
            unsigned char* inputbuffer = (unsigned char *)malloc(8 * sizeof(unsigned char));
            unsigned char* result = (unsigned char *)malloc(8 * sizeof(unsigned char));
            int end = 0;
            FILE *tableFile = NULL;
            tableFile = fopen(tablefilename, "rb");
            if(tableFile == NULL)
            {
                cerr << "Cannot open " << tablefilename << " or does not exist"<< endl;
                exit(1);
            }
            
            int i = 0;
            char* readbuffer = (char *)malloc(256 * sizeof(char));
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
            
            keyGenerator(key, keys, PC1, V, PC2);
            
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
                    
                    decryptfunction(inputbuffer, keys, S, P, IP, invIP, E, result, end);
                    
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


