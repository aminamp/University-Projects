//
//  keyexpand.cpp
//  Homework5
//
//  Created by Amin Amiripour on 3/17/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
#include "tablecheck.h"
#include "modprod.h"
#include "keyexpand.h"


using namespace std;

void rotate(unsigned char* tempkey) {
    
    unsigned char temp;
    temp = tempkey[0];
    
    for( int i = 0; i < 3; i++ )
        tempkey[i] = tempkey[i+1];

    tempkey[3] = temp;
}

void exapndfunction(unsigned char* initialkey, unsigned char rKey[44][4], FILE* table)
{
    
    unsigned char sBox[256], rcon[256];
    unsigned char* temp = (unsigned char*)malloc( 4 * sizeof(unsigned char*) );

    
    char *line = (char *)malloc(520 * sizeof(char *));
    int i = 1;
    bool sExist = false;
    while( i <= 3 )
    {
        if ( fgets(line, 520, table) == NULL )
        {
            cerr << "missing INVP" << endl;
            exit(1);
        }else{
            
            char * keyword = strtok(line, "=");
            char *value = strtok(NULL, "=");
            
            
            if( strcmp(keyword, "S") == 0 )
            {
                sExist = true;
                if( strlen(value) != (256 * 2 + 1) )
                {
                    cerr << "length of S's value is not equal to 256 Hex number";
                    exit(1);
                }
                
                int *temp11 = (int *)malloc(256 * sizeof(int *));
                memset(temp11, 0, 256);
                
                int j=0;
                while( j <= 510 )
                {
                    char *tempp = (char *)malloc( 3 * sizeof(char *));
                    memset(tempp, '\0', 3);
                    tempp[0] = value[j];
                    tempp[1] = value[j+1];
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
                
                //cout << "my program : " << s_box << endl;
                
                int k = 0;
                while( k < 256 )
                {
                    if( temp11[k] != 0 )
                    {
                        k = k + 1;
                        continue;
                    }
                    else{
                        
                        cerr << "invalid S-box, repeated entries" << endl;
                        exit(1);
                    }
                }
                
                
            }//end of if
        }
        
        i = i + 1;
    }
    
            if( sExist == false )
            {
                cerr << "S-box not found in Table";
                exit(1);
            }
    
    unsigned char temp5 = 0x02;
    i = 0;
    while( i <= 255 )
    {
        if( i == 0 )
        {
            rcon[0] = 0x8d;
            i = i + 1;
            continue;
        }
        
        rcon[i] = prod(rcon[i-1], temp5);
        i = i + 1;
    }
    
    
    for(int i=0; i<= 3; i++)
        for(int j=0; j<= 3; j++)
            rKey[i][j] = initialkey[ 4*i + j ];

    i = 4;
    while( i <= 43 )
    {
        for(int j=0; j<= 3; j++)
            temp[j] = rKey[ i - 1 ][j];
        
        if ( i%4 == 0 )
        {
            rotate(temp);
            temp[i%4] = sBox[ temp[i%4] ] ^ rcon[ i / 4 ];
            for(int j=1; j<= 3; j++)
                temp[j] = sBox[ temp[j] ];
        }
        
        for(int j=0; j<= 3; j++)
            rKey[i][j] = rKey[ i - 4 ][j] ^ temp[j];
        
        i = i + 1;
    }

}


void keyexpand( char* key, char* tablefileName ) {
    
    FILE *table = fopen(tablefileName, "rb");
    if( table == NULL )
    {
        cerr << "cannot open table file or it may not exists" << endl;
        exit(1);
    }
    else{
        unsigned char initialKey[16], rKey[44][4];
        tablecheck(tablefileName);
        if( strlen(key) != 32 )
        {
            cerr << "Key is not a string of length 32" << endl;
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
        
        
        exapndfunction(initialKey, rKey, table);
        

        i = 0;
        while( i <= 43 )
        {
            if( i < 10)
            {
                cout << "w[ ";
                cout << i ;
                cout << "]: ";
                cout << setfill('0') << setw(2) << hex << (int)rKey[i][0];
                cout << setfill('0') << setw(2) << hex << (int)rKey[i][1];
                cout << setfill('0') << setw(2) << hex << (int)rKey[i][2];
                cout << setfill('0') << setw(2) << hex << (int)rKey[i][3];
                cout << endl;
                
            }

            if( i > 9 )
            {
                cout << "w[";
                cout << dec <<i ;
                cout << "]: ";
                cout << setfill('0') << setw(2) << hex << (int)rKey[i][0];
                cout << setfill('0') << setw(2) << hex << (int)rKey[i][1];
                cout << setfill('0') << setw(2) << hex << (int)rKey[i][2];
                cout << setfill('0') << setw(2) << hex << (int)rKey[i][3];
                cout << endl;
            }

            i = i + 1;
        }
    }
    
}

