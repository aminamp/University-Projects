//
//  encrypt.h
//  HomeWork2
//
//  Created by Amin Amiripour on 2/8/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//

#ifndef encrypt_h
#define encrypt_h


#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <openssl/md5.h>
using namespace std;

void encrypt( char *p, char *o, char *file );


#endif /* encrypt_h */
