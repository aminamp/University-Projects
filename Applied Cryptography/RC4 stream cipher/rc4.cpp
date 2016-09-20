//
//  rc4.cpp
//  homework7
//
//  Created by Amin Amiripour on 4/18/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <openssl/md5.h>

using namespace std;

void rc4( char* p, char* len )
{
    int l;
    if (len == NULL)
        l = 256;
    else l = atoi(len);
    
    
    unsigned char md5_buf[MD5_DIGEST_LENGTH];       //16
    char string[strlen(p)+3];
    unsigned char key[256];
    int k = 0;
    for ( int j = 0; j < 16; j++ ) {
        sprintf(string, "%02d%s", j, p);
        MD5((unsigned char*)&string, strlen(string), (unsigned char*)&md5_buf);
        
        for(int i = 0; i < 16; i++){
            key[(16*k) + i] = md5_buf[i];
        }
        k = k + 1;
        
    }
    
//    
//    char mmdString[512];
//    for ( unsigned int i = 0; i <= 255; i++ )
//        sprintf(&mmdString[i*2], "%02x", (unsigned int)key[i]);
//    
//    printf("%s\n", mmdString);
//    
    
    
    
    unsigned char s[256];
    for ( unsigned int i = 0; i <= 255; i++ )
        s[i] = (char)i;
    
    unsigned int j = 0;
    for (unsigned int i = 0; i <= 255; i++ ){
        j = ( j + s[i] + key[i%256]) % 256;
        char temp;
        temp = s[j];
        s[j] = s[i];
        s[i] = temp;
    }
    
    
    if (len == NULL) {
        for (unsigned int i = 0; i <= 255; i++ )
            cout << s[i];
        
        exit(1);
    }
    
    
    int i = 0, n = 0;
    int length = 0;

    while( length < l )
    {
        i = ( i + 1 )%256;
        n = (n + s[i])%256;
        unsigned char temp;
        temp = s[i];
        s[i] = s[n];
        s[n] = temp;

        cout << s[ ( s[i] + s[n] ) % 256 ];


        length = length + 1;
    }


}

