//
//  keygen.cpp
//  Homework3
//
//  Created by Amin Amiripour on 2/20/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//


#include "keygen.h"

void keygen( char* phrase, char* t)
{
    if (  phrase == NULL || t == NULL )
    {
        std::cerr << "**************** Error: Wrong command ****************\n";
        std::cerr << "Valid commands are:\n./hw3 keygen -p=pphrase -t=period\n./hw3 crypt -k=keyfile [file]\n./hw3 invkey keyfile\n./hw3 histo -t=period -i=which [file]\n./hw3 solve -l=max_t file\n";
        exit(1);
    }
    
    int period = atoi(t);
    if( period <= 0 ){
        std::cerr << "**************** Error: Period should be greater that zero ****************\n";
        exit(1);
    }
    
    
    /*
     following codes obtained from Homework2 specification page :
     http://merlot.usc.edu/cs531-s16/homeworks/hw2
     */
    
    unsigned char key[period * 200];
    char md5_buf[MD5_DIGEST_LENGTH];
    int len= strlen(phrase) + 2 + MD5_DIGEST_LENGTH;
    char *s = (char*)malloc( len + 1 );
    
    MD5((unsigned char*) phrase, strlen(phrase), (unsigned char*)md5_buf);
    
    int i = 0, k = 0;
    while(1){
        if( k == period * 200 )
            break;
        else{
            sprintf(&s[MD5_DIGEST_LENGTH], "%02d%s", i, phrase);
            memcpy(s, md5_buf, MD5_DIGEST_LENGTH);
            MD5((unsigned char*)s, len, (unsigned char*)md5_buf);
            for( int j = 0; j < 8; j++ )
            {
                if ( k < period * 200 )
                {
                    key[k] = md5_buf[j];
                    k++;
                }
            }
            
            if (++i == 100)
                i = 0;
        }
        
    }//end of while
    
    /*
     following codes obtained from Homework3 specification page :
     http://merlot.usc.edu/cs531-s16/homeworks/hw3
     */
    
    unsigned int mask;
    int m = 0;
    i = 0;
    while( i < period )
    {
        std::string state = "abcdefghijklmnopqrstuvwxyz";
        for( int j = 0; j < 2; j++ )
        {
            for ( int L = 26; L > 1; L-- )
            {
                for(int k = 0; k < 4; k++ )
                {
                    mask = mask << 8;
                    mask = mask + (unsigned int) key[m];
                    m = m + 1;
                }
                
                int R = mask % L;
                if( R != L - 1 )
                {
                    char temp;
                    temp = state[R];
                    state[R] = state[L - 1];
                    state[L - 1] = temp;
                }
            }
        }//end of outer for
        
        std::cout << state << "\n";
        i = i + 1;
        
    }//end of while
        
        
}
    

