//
//  crypt.cpp
//  Homework3
//
//  Created by Amin Amiripour on 2/20/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//


#include "crypt.h"

void crypt(const char * keyFilename, char * inputfilename)
{
    if ( !inputfilename )  //read from input when file is not exist
    {
        //cout << "Please enter your data to be encrypt:\n";
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
        crypt( keyFilename, tempFileName);
        remove(tempFileName);
        
    }else {
        
        int keylength = 1, line = 0, counter = 0;
        
        char **key;
        key = (char **) malloc( sizeof(char**) );
        
        
        FILE * KeyFile;
        KeyFile = fopen(keyFilename, "rb");
        if( KeyFile == NULL )
        {
            std::cerr << "Key file cannot be opened";
            std::cerr << std::endl;
            exit(1);
        }
        
        
        FILE * inputFile;
        inputFile = fopen(inputfilename, "rb");
        if(inputFile == NULL)
        {
            std::cerr << "input file cannot be opened";
            std::cerr << std::endl;
            exit(1);
        }
        
        //read the key file
        key[keylength - 1] = (char *) malloc( 26 );
        while( !feof(KeyFile) )
        {
            char readbuffer;
            int bytes_read = fread(&readbuffer, 1, 1, KeyFile);
            if ( bytes_read )
            {
                if( readbuffer == '\n' )
                    continue;
                
                if( readbuffer >= 'a' && readbuffer <= 'z' )
                {
                    if( line == 26 )    //go to next line
                    {
                        keylength = keylength + 1;
                        key[keylength - 1] = (char *) malloc( 26 );
                        line = 0;
                    }
                    
                    key[keylength - 1][line] = readbuffer;
                    line = line + 1;
                    
                }else{
                    std::cerr << "malformed key file";
                    std::cerr << std::endl;
                    exit(1);
                }
                
            }
            
        }
        
        //start to encrypt/decrypt input file using the key file provided
        while( !feof(inputFile) )
        {
            char readbuffer;
            int bytes_read = fread(&readbuffer, 1, 1, inputFile);
            if ( bytes_read )
            {
                
                if( readbuffer < 'a' || readbuffer > 'z' )
                {
                    std::cout << readbuffer;
                    counter = counter + 1;
                    continue;
                }
                std::cout << (key[counter % keylength][readbuffer - 'a']);
                counter = counter + 1;
            }

        }
        
        fclose(KeyFile);
        fclose(inputFile);
        
    }
    
}


