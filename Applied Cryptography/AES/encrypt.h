//
//  encrypt.h
//  Homework5
//
//  Created by Amin Amiripour on 3/17/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//

#ifndef encrypt_h
#define encrypt_h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tablecheck.h"
#include "modprod.h"
#include "keyexpand.h"

void encrypt( char* k, char* t, char*  );

#endif /* encrypt_h */
