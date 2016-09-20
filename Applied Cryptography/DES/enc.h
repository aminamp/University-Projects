//
//  enc.h
//  Homework4
//
//  Created by Amin Amiripour on 3/7/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//

#ifndef enc_h
#define enc_h
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include<iomanip>
#include <string.h>
#include <stdio.h>
#include "tablecheck.h"
void encrypt(char *key, char *tablefile, char *filename);
void keyGenerator(char* key,unsigned char keys[][6], int *PC1, int *V, int *PC2);
void encryptfunction(unsigned char* buf1, unsigned char keys[][6], int S[][64], int *P, int *IP, int *invIP, int *E, unsigned char* result, int done, int mode);
#endif /* enc_h */


