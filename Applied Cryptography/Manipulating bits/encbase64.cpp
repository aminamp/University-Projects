//
//  encbase64.cpp
//  Test
//
//  Created by Amin Amiripour on 1/23/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//
#include "encbase64.h"


void EncBase64(char* filename)
{
    FILE* inputFile;
    inputFile = fopen(filename, "rb");
    
    if (!filename) {
        //cout << "Please enter your data to encode in Base64:\n";
        
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
        EncBase64(tempFileName);
        remove(tempFileName);
        
        
    }else{
        
        
        char valid[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        
        char *buffer = new char[3];
        
        unsigned char writebuffer[4];
        unsigned char readbuffer[3];
        
        int end;
        int NumberOfColumn = 0;
        
        
        
        if ( inputFile == NULL ) {
            cerr << "Cannot open " << filename << " or does not exist"<< endl;
        }else
        {
        
        end = fread(buffer, sizeof(char), 3, inputFile);
            
        while( end > 0 ) {
            for( int i = 0; i <= 2 ; i++ )
                readbuffer[i] = buffer[i];
            
            
            // transform 3 byte of data to 4 in base64
            writebuffer[0] = valid[ readbuffer[0] >> 2 ];
            writebuffer[1] = valid[ ( ( (readbuffer[1] & 0xf0) >> 4 ) | (readbuffer[0] & 0x03) << 4 )  ];
            
            
            if(end > 1)
                writebuffer[2] = valid[ ( (readbuffer[2] & 0xc0) >> 6 ) | ( (readbuffer[1] & 0x0f) << 2)  ];
            else
                writebuffer[2] = '=';
        
            
            
            if(end > 2)
                writebuffer[3] = valid[ readbuffer[2] & 0x3f ];
            else
                writebuffer[3] = '=';   //add = at the end in the case there is not enough bytes in data to be convert
            
            
            
            for( int i = 0; i <= 3 ; i++ )
            {
    
                cout << static_cast<char>(writebuffer[i]);
                NumberOfColumn++;
                if( NumberOfColumn >= (4 * 16) ) //go to next line after output 4-byte output for 16th time
                {
                    cout << endl;
                    NumberOfColumn = 0;
                }
            }
            
            
            for( int i = 0; i <= 2; i++ )
                buffer[i] = 0;            //clear buffer - set the 3 byte to 0
            
            
            if(end > 0)
                end = fread(buffer, sizeof(char), 3, inputFile);
            
            
        }//end of while(bytes_read > 0)
        
        if( NumberOfColumn != 0 )
            cout << endl;
        
        }
        
    }
    
    
    fclose(inputFile);
}

