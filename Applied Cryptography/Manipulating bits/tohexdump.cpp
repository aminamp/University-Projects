//
//  tohexdump.cpp
//  Test
//
//  Created by Amin Amiripour on 1/23/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//
#include "tohexdump.h"
#include <iomanip>
#include <istream>
#include <string>
#include <string.h>


void ToHexdump(char* filename)
{
    //ifstream inputFile;
    
    char *buffer = new char[17];
    int end;
    int address = 0;

    FILE* inputFile = NULL;
    inputFile = fopen(filename, "rb");

    
    
    if (!filename)  //read from input when file is not exist
    {
        //cout << "Please enter your data to be convert to HexDump:\n";
        
        //string input;
        char tempFileName[]="tempppp.txt";
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
        
        ToHexdump(tempFileName);
        
        remove(tempFileName);
        
        
    }else    //read data from file
    {
        
        
        if ( inputFile == NULL ) {
            cerr << "Cannot open " << filename << " or does not exist"<< endl;
        }else{
            while(1)
            {
                end = fread(buffer, sizeof(char), 16, inputFile);
                if( end == 0) //reach end of file
                    break;
                
                if( end != 16 ) //read less than 16 byte
                {
                    
                    cout << hex << setfill('0') << setw(6) << address << ": ";
                    for( int i = 0; i < end; i++ )
                    {
                        printf("%02x ", (unsigned char)buffer[i]);
                        if( i == 7 )
                            printf(" "); //two space
                    }
                    
                    for( int i = end; i <= 15; i++ )
                    {
                        printf("-- ");  //pritn -- to fill non-existant bytes
                        if ( i == 7 )
                            printf(" "); //two space
                    }
                    
                    printf(" "); //two space
                    
                    for( int i = 0 ; i < end; i++ )
                    {
                        //convert to hexDump
                        if( (unsigned char)buffer[i] <= 0x7e && (unsigned char)buffer[i] >= 0x20 )
                            printf("%c", (unsigned char)buffer[i]);
                        if( (unsigned char)buffer[i] == 0x7f || (unsigned char)buffer[i] <= 0x1f )
                            printf(".");
                        if( (unsigned char)buffer[i] >= 0x80 )
                            printf("~");
                    }
                    for( int i = end; i <= 15 ; i++ )
                        printf(" ");    //space characters in the right column in the case of non-existant bytes
                    
                    printf("\n");
                    break;
                    
                }//end of if( end != 16)
                
                
                if( end == 16 ) //one full line of data
                {
                    cout << hex << setfill('0') << setw(6) << address << ": ";
                    for( int i = 0; i <= 15; i++ )
                    {
                        printf("%02x ", (unsigned char)buffer[i]);  //print the address
                        if( i == 7 )
                            printf(" "); //two space
                    }
                    printf(" ");
                    for( int i = 0; i <= 15; i++)
                    {
                        //convert to hexDump
                        if((unsigned char)buffer[i] >= 0x20 && (unsigned char)buffer[i] <= 0x7e)
                            printf("%c", (unsigned char)buffer[i]);
                        if((unsigned char)buffer[i] <= 0x1f || (unsigned char)buffer[i] == 0x7f)
                            printf(".");
                        if((unsigned char)buffer[i] >= 0x80)
                            printf("~");
                    }
                    
                    printf("\n");
                    address = address + 16; //because we read 16 byte at each time to form a line
                    
                }//end of if( end == 16 )
                

            }//end of while(1)
            
        }
        
    }
    
    fclose(inputFile);
    
}

