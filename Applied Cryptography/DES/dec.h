//
//  dec.h
//  Homework4
//
//  Created by Amin Amiripour on 3/7/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//

#ifndef dec_h
#define dec_h

void decrypt(char *key, char *tablefilename, char *filename);
void decryptfunction(unsigned char *buf1, unsigned char keys[][6], int S[][64], int *P, int *IP, int *inverseIP, int *E, unsigned char *result, int done);

#endif /* dec_h */


