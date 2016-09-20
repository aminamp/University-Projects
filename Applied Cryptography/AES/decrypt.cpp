//
//  decrypt.cpp
//  Homework5
//
//  Created by Amin Amiripour on 3/17/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "encrypt.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include "tablecheck.h"
#include "modprod.h"
#include "keyexpand.h"
#include "decrypt.h"

using namespace std;


void print2(unsigned char state[4][4], int round) {
    
    if(round <= 9)
        cout << "round[ " << dec << round << "].ik_sch   ";
    if(round == 10)
        cout << "round[" << dec << round << "].ik_sch   ";
    
    for(int i=0; i<16; i++)
        cout << setfill('0') << setw(2) << hex << (int)state[i/4][i%4];
    
    cout << "\n";
}





void decryptFunction(unsigned char input[16], unsigned char output[16], unsigned char rKey[44][4], FILE* table) {
    
    unsigned char state[4][4];
    for( int i = 0; i <= 3 ; i++)
        for( int j = 0; j <= 3 ; j++)
            state[i][j] = 0;
    

    unsigned char invertPoly[4], sBox[256], invertSbox[256];
    
    char *ReadBuffer = (char *)malloc(520 * sizeof(char *));
    fseek(table, 0, SEEK_SET);
    
    while( strncmp(ReadBuffer, "S=", 2) != 0 )
        if(!fgets(ReadBuffer, 640, table))
        {
            cerr << "S-box not found in Table";
            exit(1);
        }
    
    ReadBuffer = ReadBuffer + 2;
    
    int *temp11 = (int *)malloc(256 * sizeof(int *));
    memset(temp11, 0, 256);
    
    int j=0;
    while( j <= 510 )
    {
        char *tempp = (char *)malloc( 3 * sizeof(char *));
        memset(tempp, '\0', 3);
        tempp[0] = ReadBuffer[j];
        tempp[1] = ReadBuffer[j+1];
        tempp[2] = '\0';
        if ( tempp[0] >= '0' && tempp[0] <='9' )
            if( (tempp[1] >= '0' && tempp[1] <='9') || (tempp[1] >= 'a' && tempp[1] <= 'f') )
            {
                temp11[ strtoul(tempp, NULL, 16) ] = temp11[ strtoul(tempp, NULL, 16) ] + 1;
                sBox[j/2] = strtoul(tempp, NULL, 16);
                j = j + 2;
                continue;
            }
        
        if ( tempp[0] >= 'a' && tempp[0] <= 'f' )
            if( (tempp[1] >= '0' && tempp[1] <='9') || (tempp[1] >= 'a' && tempp[1] <= 'f') )
            {
                temp11[ strtoul(tempp, NULL, 16) ] = temp11[ strtoul(tempp, NULL, 16) ] + 1;
                sBox[j/2] = strtoul(tempp, NULL, 16);
                j = j + 2;
                continue;
            }
        
        cerr << "S contains invalid characters" << endl;
        exit(1);
        
    }
    
    
    int k = 0;
    while( k <= 255 )
    {
        invertSbox[ sBox[k] ] = k;
        k = k + 1;
    }

    
    char* readBuffer = (char*)malloc( 32 * sizeof( char* ));
    fseek(table, 0, SEEK_SET);
    while(strncmp(readBuffer, "INVP=", strlen("INVP=")) != 0) {
        if(!fgets(readBuffer, 32, table)) {
            cerr << "P not found in Table";
            exit(1);
        }
    }
    readBuffer = readBuffer + 5;
    
    int *temp22 = (int *)malloc(10 * sizeof(int *));
    memset(temp22, 0, 10);
    
    j=0;
    while( j <= 6 )
    {
        char *tempp = (char *)malloc( 3 * sizeof(char *));
        memset(tempp, '\0', 3);
        tempp[0] = readBuffer[j];
        tempp[1] = readBuffer[j+1];
        tempp[2] = '\0';
        if ( tempp[0] >= '0' && tempp[0] <='9' )
            if( (tempp[1] >= '0' && tempp[1] <='9') || (tempp[1] >= 'a' && tempp[1] <= 'f') )
            {
                temp22[ strtoul(tempp, NULL, 16) ] = temp22[ strtoul(tempp, NULL, 16) ] + 1;
                invertPoly[j/2] = strtoul(tempp, NULL, 16);
                j = j + 2;
                continue;
            }
        
        if ( tempp[0] >= 'a' && tempp[0] <= 'f' )
            if( (tempp[1] >= '0' && tempp[1] <='9') || (tempp[1] >= 'a' && tempp[1] <= 'f') )
            {
                temp22[ strtoul(tempp, NULL, 16) ] = temp22[ strtoul(tempp, NULL, 16) ] + 1;
                invertPoly[j/2] = strtoul(tempp, NULL, 16);
                j = j + 2;
                continue;
            }
        
        cerr << "INVP contains invalid characters" << endl;
        exit(1);
        
    }

    int i = 0;
    while( i <= 15 ){
        state[i%4][i/4] = input[i];
        i = i + 1;
    }
    
    cout << "round[ "<< dec << 0 << "].iinput   ";
    for(int i=0; i<16; i++)
        cout << setfill('0') << setw(2) << hex << (int)state[i%4][i/4];
    
    cout << "\n";
    
    print2(&(rKey[4*10]), 0);
    
    i = 0;
    while ( i <= 3 ) {
        
        for(int j=0; j<=3; j++)
            state[i][j] = state[i][j] ^ rKey[ 40 + j ][i];
        
        i = i + 1;
    }
    

    j = 9;
    while( j > 0 )
    {
        
        cout << "round[ "<< dec << 10-j << "].istart   ";
        for(int i=0; i<16; i++)
            cout << setfill('0') << setw(2) << hex << (int)state[i%4][i/4];
        
        cout << "\n";
        
        unsigned char* tempRC = (unsigned char*)malloc(3 * sizeof(unsigned char*));
        int r = 1;
        while ( r <= 3) {
            for(int i=3; i>3-r; i--)
                tempRC[i+r-4] = state[r][i];
            
            for(int c=3; c>-1; c--)
            {
                if( (c-r) > -1 )
                    state[r][c] = state[r][c-r];
                
                if((c-r) < 0)
                    state[r][c] = tempRC[c];
            }
            r = r + 1;
        }

        
        
        cout << "round[ "<< dec << 10-j << "].is_row   ";
        for(int i=0; i<16; i++)
            cout << setfill('0') << setw(2) << hex << (int)state[i%4][i/4];
        
        cout << "\n";
        
        
        int i = 0;
        while ( i <= 3 ) {
            for(int j=0; j <= 3; j++)
                state[i][j] = invertSbox[ state[i][j] ];
            i = i + 1;
        }

        
        
        cout << "round[ "<< dec << 10-j << "].is_box   ";
        for(int i=0; i<16; i++)
            cout << setfill('0') << setw(2) << hex << (int)state[i%4][i/4];
        
        cout << "\n";
        
        print2(&(rKey[4*j]), 10-j);
        
        i = 0;
        while ( i <= 3 ) {
            
            for(int m=0; m<=3; m++)
                state[i][m] = state[i][m] ^ rKey[ 4*j + m ][i];
            
            i = i + 1;
        }
        cout << "round[ "<< dec << 10-j << "].ik_add   ";
        for(int i=0; i<16; i++)
            cout << setfill('0') << setw(2) << hex << (int)state[i%4][i/4];
        
        cout << "\n";
        
        unsigned char temppppppp[4];
        i =0;
        while( i <= 3)
        {
            for( int k = 0; k <= 3; k++)
                temppppppp[k] = 0x00;
            
            for(int j=0; j<= 3; j++)
            {
                int k = 0;
                while ( k <= 3) {
                    temppppppp[j] = temppppppp[j] ^ prod(state[k][i], invertPoly[ (k-j+3)%4 ]);
                    k = k + 1;
                }
            }
            
            int j = 0;
            while( j <=3 )
            {
                state[j][i] = temppppppp[j];
                j = j + 1;
            }
            
            i = i + 1;
        }
        
        j = j - 1;
    }

    
    cout << "round[10].istart   ";
    for(int i=0; i<16; i++)
        cout << setfill('0') << setw(2) << hex << (int)state[i%4][i/4];
    
    cout << "\n";
    
    unsigned char* tempRC = (unsigned char*)malloc(3 * sizeof(unsigned char*));
    int r = 1;
    while ( r <= 3) {
        for(int i=3; i>3-r; i--)
            tempRC[i+r-4] = state[r][i];
        
        for(int c=3; c>-1; c--)
        {
            if( (c-r) > -1 )
                state[r][c] = state[r][c-r];
            
            if((c-r) < 0)
                state[r][c] = tempRC[c];
        }
        r = r + 1;
    }

    cout << "round[10].is_row   ";
    for(int i=0; i<16; i++)
        cout << setfill('0') << setw(2) << hex << (int)state[i%4][i/4];
    
    cout << "\n";
    

    i = 0;
    while ( i <= 3 ) {
        for(int j=0; j <= 3; j++)
            state[i][j] = invertSbox[ state[i][j] ];
        i = i + 1;
    }

    cout << "round[10].is_box   ";
    for(int i=0; i<16; i++)
        cout << setfill('0') << setw(2) << hex << (int)state[i%4][i/4];
    
    cout << "\n";
    
    i = 0;
    while ( i <= 3 ) {
        
        for(int m=0; m<=3; m++)
            state[i][m] = state[i][m] ^ rKey[ m ][i];
        
        i = i + 1;
    }
    
    
    print2(&(rKey[4*0]), 10);
    
    i = 0;
    while ( i <= 15 ) {
        output[i] = state[i%4][i/4];
        i = i + 1;
    }
    
    cout << "round[10].ioutput  ";
    for(int i=0; i<16; i++)
        cout << setfill('0') << setw(2) << hex << (int)state[i%4][i/4];
    
    cout << "\n";
    
}






void decrypt(char* key, char* tablefileName, char* inputfileName) {
    
    if( strlen(key) != 32 ) {
        
        cerr << "Key is not in length 32";
        cerr << endl;
        exit(1);
    }
    
    if( tablefileName[1] == 'e' )
    {
        cerr << "malformed table file" << endl;
        exit(1);
    }
    
    tablecheck(tablefileName);
    
    if( !inputfileName )
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
        decrypt( key, tablefileName, tempFileName);
        remove(tempFileName);
        
    }else{
    
       unsigned char rKey[44][4], initialKey[16] , cipherBuffer[16] ,  textBuffer[16];
        for( int i = 0; i <= 43 ; i++)
            for( int j = 0; j <= 3 ; j++)
                rKey[i][j] = 0;
        
        FILE *tablefile = fopen(tablefileName, "rb");
        if( tablefile == NULL )
        {
            cerr << "cannot open table file or it may not exists" << endl;
            exit(1);
        }
        
        FILE *inputfile = fopen(inputfileName, "rb");
        if( inputfile == NULL )
        {
            cerr << "cannot open input file or it may not exists" << endl;
            exit(1);
        }
        
        char temp[3];
        int i = 0;
        while ( i < 16 )
        {
            if( key[i*2] >= '0' && key[i*2] <= '9' )
                if( (key[i*2+1] >= '0' && key[i*2+1] <= '9') ||  (key[i*2+1] >= 'a' && key[i*2+1] <= 'f') )
                {
                    for( int j = 0; j < 2; j++ )
                    {
                        temp[j] = key[ i*2 + j ];
                    }
                    temp[2] = '\0';
                    unsigned char temp2 = strtol(temp, NULL, 16);
                    initialKey[i] = temp2 ;
                    i = i + 1;
                    continue;
                }
            
            if( key[i*2] >= 'a' && key[i*2] <= 'f' )
                if( (key[i*2+1] >= '0' && key[i*2+1] <= '9') ||  (key[i*2+1] >= 'a' && key[i*2+1] <= 'f') )
                {
                    for( int j = 0; j < 2; j++ )
                    {
                        temp[j] = key[ i*2 + j ];
                    }
                    temp[2] = '\0';
                    unsigned char temp2 = strtol(temp, NULL, 16);
                    initialKey[i] = temp2 ;
                    i = i + 1;
                    continue;
                }
            
            cerr << "key contains invalid characters" << endl;
            exit(1);
            
            
        }
    
    exapndfunction(initialKey, rKey, tablefile);
    while( fread(cipherBuffer, 1, 16, inputfile) )
        decryptFunction(cipherBuffer, textBuffer, rKey, tablefile);
        
    
    }

}


