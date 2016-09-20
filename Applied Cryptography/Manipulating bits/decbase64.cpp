//
//  decbase64.cpp
//  Test
//
//  Created by Amin Amiripour on 1/23/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//
#include "decbase64.h"


void DecBase64(char* filename)
{
    FILE* inputFile;
    inputFile = fopen(filename, "rb");
    
    if (!filename) {
        //cout << "Please enter your data to decode from base64:\n";
        
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
        DecBase64(tempFileName);
        remove(tempFileName);
        
        
    }else{
        
        //cout << "DecBase64 with " << filename << endl;
        
        
        char buffer[1];
        
        unsigned char input[4];
        unsigned char output[3];
        
        int NoofBytes = 0;
        bool end = false;
        
        
        
        if ( inputFile == NULL )
            cerr << "Cannot open " << filename << " or does not exist"<< endl;
        else
        {
            
            while( fread(buffer, 1, 1, inputFile) > 0 ) {
                
                if(buffer[0] == '\n')
                    continue;
                else if(buffer[0] >= 'A' && buffer[0] <= 'Z')
                    input[NoofBytes] = buffer[0] - 'A';
                else if(buffer[0] >= 'a' && buffer[0] <= 'z')
                    input[NoofBytes] = buffer[0] - 'a' + 0x1a;
                else if(buffer[0] >= '0' && buffer[0] <= '9')
                    input[NoofBytes] = buffer[0] - '0' + 0x34;
                else if(buffer[0] == '+')
                    input[NoofBytes] = 0x3e;
                else if(buffer[0] == '/')
                    input[NoofBytes] = 0x3f;
                else if(buffer[0] == '=') {
                    input[NoofBytes] = 0;
                    end = true;
                } else {
                    //fprintf(stderr, "ERROR: input stream contained invalid Base64 characters (%c).\n", buffer[0]);
                    cerr << "**************** Error ****************" << endl << "Input contains invalid character in base 64" << endl;
                    return;
                }
                if( !end )
                    NoofBytes++;
                
                if( NoofBytes == 4 || end ) {
                    output[0] = (input[0] << 2) | ((input[1] & 0x30) >> 4);
                    if(NoofBytes >= 3)
                        output[1] = ((input[1] & 0x0f) << 4) | ((input[2] & 0x3c) >> 2);
                    if(NoofBytes == 4)
                        output[2] = ((input[2] & 0x03) << 6) | (input[3] & 0x3f);
                    
                    for( int i=0 ; i < (NoofBytes-1); i++ ) {
                        cout << static_cast<char>(output[i]);
                    }
                    
                    if( end )
                        break;
                    else {
                        for( int i = 0; i <= 3; i++ )
                            input [i] = 0;
                        NoofBytes = 0;
                    }
                }
                
                
            }//end of while(fread(buf, 1, 1, in) > 0)
            
        }

        
    }
    fclose(inputFile);
}

