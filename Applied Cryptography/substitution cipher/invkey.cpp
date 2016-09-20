//
//  invkey.cpp
//  Homework3
//
//  Created by Amin Amiripour on 2/22/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//


#include "invkey.h"

void invkey( char* keyFilename ){
    
    FILE * keyfile;
    keyfile = fopen(keyFilename, "r");
    if( keyfile == NULL )
    {
        std::cerr << "Cannot open keyfile" << std::endl;
        exit(1);
    }
    

    unsigned char* inverse;
    inverse = (unsigned char*)malloc( 26 + 1 );
    unsigned char* input;
    input = (unsigned char*)malloc( 26 + 1 );
    int counter;
    
    while( !feof(keyfile) )
    {
        counter = fread(input,1 , 27, keyfile);
        
        if ( !(counter < 26) )
        {
            int i = 0;
            while( i < 26 )
            {
                if ( input[i] < 'a' || input[i] > 'z')
                {
                    std::cerr << "malformed keyfile\n";
                    exit(1);
                }
                
                inverse[input[i] - 'a'] = i + 'a' ;
                i = i + 1;
            }
            std::cout << inverse << std::endl;

        }
        
    }
    
    fclose(keyfile);    
    
}

