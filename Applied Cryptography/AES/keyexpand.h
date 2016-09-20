//
//  keyexpand.h
//  Homework5
//
//  Created by Amin Amiripour on 3/17/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//

#ifndef keyexpand_h
#define keyexpand_h

void keyexpand( char* k, char* t );
void exapndfunction(unsigned char init_key[16], unsigned char round_key[44][4], FILE* table);

#endif /* keyexpand_h */
