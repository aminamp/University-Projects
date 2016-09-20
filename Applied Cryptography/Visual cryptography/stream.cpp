//
//  stream.cpp
//  HomeWork2
//
//  Created by Amin Amiripour on 2/6/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//
#include "stream.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#include <openssl/md5.h>

using namespace std;

void stream( char *p, char *length )
{
    
    /*
     following codes obtained from from Homework2 specification page : 
     http://merlot.usc.edu/cs531-s16/homeworks/hw2
     */
    int l = atoi(length);
    char md5_buf[MD5_DIGEST_LENGTH];               //MD5_DIGEST_LENGTH default value is 16
    int len = strlen(p) + 2 + MD5_DIGEST_LENGTH;
    char *s = (char *)malloc( len + 1 );         
    int i = 0;
    

    MD5((unsigned char *)p, strlen(p), (unsigned char *)md5_buf);
    for ( int j = 0 ; j < (l / 8); j++ ){             //process the data until they are multiple of 8
        sprintf(&s[MD5_DIGEST_LENGTH], "%02d%s", i, p);
        memcpy(s, md5_buf, MD5_DIGEST_LENGTH);
        MD5((unsigned char *)s, len, (unsigned char *)md5_buf);
        fwrite(md5_buf, 1, sizeof(md5_buf)>>1, stdout);
        if ( ++i == 100 )
            i = 0;
    }
    if( (l % 8) != 0 ){     //change to >0              //process the remaining bytes that is not multiple of 8
        sprintf(&s[MD5_DIGEST_LENGTH], "%02d%s", i, p);
        memcpy(s, md5_buf, MD5_DIGEST_LENGTH);
        MD5((unsigned char *)s, len, (unsigned char *)md5_buf);
        fwrite(md5_buf, 1, (l % 8), stdout);
        // if (++i == 100)
          //  i = 0;
    }
    
    
    free(s);
}

