//
//  tablecheck.cpp
//  Homework5
//
//  Created by Amin Amiripour on 3/17/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//

#include <stdio.h>
#include "tablecheck.h"
#include "modprod.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
using namespace std;



void tablecheck( char* tablefilename ){
    
    
    FILE *tableFile = fopen(tablefilename, "rb");
    
    if( tableFile != NULL )
    {
        
        char *line = (char *)malloc(520 * sizeof(char *));
        unsigned int P = 0;
        unsigned int INVP = 0;

        int i = 1;
        while( i <= 3 )
        {
            if ( fgets(line, 520, tableFile) == NULL )
            {
                cerr << "missing INVP" << endl;
                exit(1);
            }else{
                
                char * keyword = strtok(line, "=");
                char *value = strtok(NULL, "=");
                
                if( strcmp(keyword, "S") == 0 )
                {
                    
                    if( strlen(value) != (256 * 2 + 1) )
                    {
                        cerr << "length of S's value is not equal to 256 Hex number";
                        exit(1);
                    }
                    
                    int *temp = (int *)malloc(256 * sizeof(int *));
                    memset(temp, 0, 256);
                    
                    int j=0;
                    while( j <= 510 )
                    {
                        char *tempp = (char *)malloc( 3 * sizeof(char *));
                        memset(tempp, '\0', 3);
                        tempp[0] = value[j];
                        tempp[1] = value[j+1];
                        if ( tempp[0] >= '0' && tempp[0] <='9' )
                            if( (tempp[1] >= '0' && tempp[1] <='9') || (tempp[1] >= 'a' && tempp[1] <= 'f') )
                            {
                                temp[ strtoul(tempp, NULL, 16) ] = temp[ strtoul(tempp, NULL, 16) ] + 1;
                                j = j + 2;
                                continue;
                            }
                        
                        if ( tempp[0] >= 'a' && tempp[0] <= 'f' )
                            if( (tempp[1] >= '0' && tempp[1] <='9') || (tempp[1] >= 'a' && tempp[1] <= 'f') )
                            {
                                temp[ strtoul(tempp, NULL, 16) ] = temp[ strtoul(tempp, NULL, 16) ] + 1;
                                j = j + 2;
                                continue;
                            }
                        
                        cerr << "S contains invalid characters" << endl;
                        exit(1);
                        
                    }
                    
                    int k = 0;
                    while( k < 256 )
                    {
                        if( temp[k] != 0 )
                        {
                            k = k + 1;
                            continue;
                        }
                        else{
                            
                            cerr << "invalid S-box, repeated entries" << endl;
                            exit(1);
                        }
                    }
                    
                    
                }
                
                else if( strcmp(keyword, "P") == 0 )
                {
                    
                    
                    if ( strlen( value ) == 9 )
                    {
                        for( int i = 0; i < 8; i++ )
                        {
                            if( value[i] >= '0' && value[i] <= '9' )
                                continue;
                            
                            if( value[i] >= 'a' && value[i] <= 'f' )
                                continue;
                            
                            cerr << "P contains invalid characters" << endl;
                            exit(1);
                        }
                        
                        value[8] = '\0';
                        P = strtoul(value, NULL, 16);

                        
                    }else{
                         cerr << "P is not a string of length 8" << endl;
                         exit(1);
                    }

                    
                }else if( strcmp(keyword, "INVP") == 0 )
                {
                    if ( strlen( value ) == 9 )
                    {
                        for( int i = 0; i < 8; i++ )
                        {
                            if( value[i] >= '0' && value[i] <= '9' )
                                continue;
                            
                            if( value[i] >= 'a' && value[i] <= 'f' )
                                continue;
                            
                            cerr << "INVP contains invalid characters" << endl;
                            exit(1);
                        }
                        value[8] = '\0';
                        INVP = strtoul(value, NULL, 16);
                        
                    }else{
                        cerr << "INVP is not a string of length 8" << endl;
                        exit(1);
                    }
                    
                    
                }else {
                    cerr << "malformed table, contains keywords not equal to S, P and INVP";
                    cerr << endl;
                    exit(1);
                }
                
            }
            i = i + 1;
        }
        
        
        unsigned char res0 = 0;
        unsigned char res1 = 0;
        unsigned char res2 = 0;
        unsigned char res3 = 0;
        
        res0 = prod((P & 0x000000ff), (INVP & 0x000000ff)) ^ prod((P & 0xff000000) >> 24, (INVP & 0x0000ff00) >> 8) ^ prod((P & 0x00ff0000) >> 16, (INVP & 0x00ff0000) >> 16) ^ prod((P & 0x0000ff00) >> 8, (INVP & 0xff000000) >> 24);
        res1 = prod((P & 0x0000ff00) >> 8, (INVP & 0x000000ff)) ^ prod((P & 0x000000ff), (INVP & 0x0000ff00) >> 8) ^ prod((P & 0xff000000) >> 24, (INVP & 0x00ff0000) >> 16) ^ prod((P & 0x00ff0000) >> 16, (INVP & 0xff000000) >> 24);
        res2 = prod((P & 0x00ff0000) >> 16, (INVP & 0x000000ff)) ^ prod((P & 0x0000ff00) >> 8, (INVP & 0x0000ff00) >> 8) ^ prod((P & 0x000000ff), (INVP & 0x00ff0000) >> 16) ^ prod((P & 0xff000000) >> 24, (INVP & 0xff000000) >> 24);
        res3 = prod((P & 0xff000000) >> 24, (INVP & 0x000000ff)) ^ prod((P & 0x00ff0000) >> 16, (INVP & 0x0000ff00) >> 8) ^ prod((P & 0x0000ff00) >> 8, (INVP & 0x00ff0000) >> 16) ^ prod((P & 0x000000ff), (INVP & 0xff000000) >> 24);

        int result = (res3 << 24) | (res2 << 16) | (res1 << 8) | res0;
        if( result != 1)
        {
            cerr << "P and INVP are not inverses";
            exit(1);
        }
        

    }else
    {
        cerr << "cannot open table file or it may not exists" << endl;
        exit(1);
    }
    
    
}


