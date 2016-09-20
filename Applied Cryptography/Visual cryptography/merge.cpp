//
//  merge.cpp
//  HomeWork2
//
//  Created by Amin Amiripour on 2/11/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "merge.h"

void merge( char *file1, char *file2 )
{
    int width1 = 0, height1 = 0;
    int width2 = 0, height2 = 0;
    
    //check the format of pbm1
    FILE *photo1 = fopen(file1, "rb");                
    if( photo1 == NULL )
    {
        cerr << "Cannot open " << file1 << endl;
        exit(1);
    }else{
        char *magic = (char *)malloc(4);
        fgets(magic, 4, photo1);                    // check MagicNumber (P4)
        if( magic[0] != 'P' || magic[1] != '4' || magic[2] != '\n' ) {
            cerr << file1 << "is a Malformed PBM file"<< endl;
            exit(1);
        }else{
        
            char *temp = (char *)malloc(10);
        
            fgets(temp, 10, photo1);
            if ( temp[0] == '#' )               //this is a comment line
                fgets(temp, 10, photo1);
        
            sscanf(temp, "%d%d", &width1, &height1);
        
            if (height1 <= 0 || width1 <= 0)
            {
                cerr << file1 << "is a Malformed PBM file"<< endl;
                exit(1);
            }
          }
        }
    
    
    
    //check the format of pbm2
    FILE *photo2 = fopen(file2, "rb");
    if( photo2 == NULL )
    {
        cerr << "Cannot open " << file2 << endl;
        exit(1);
    }else{
        char *magic = (char *)malloc(4);
        fgets(magic, 4, photo2);                    // check MagicNumber (P4)
        if( magic[0] != 'P' || magic[1] != '4' || magic[2] != '\n' ) {
            cerr << file2 << "is a Malformed PBM file"<< endl;
            exit(1);
        }else{
            
            char *temp = (char *)malloc(10);
            
            fgets(temp, 10, photo2);
            if ( temp[0] == '#' )               //this is a comment line
                fgets(temp, 10, photo2);
            
            sscanf(temp, "%d%d", &width2, &height2);
            
            if (height2 <= 0 || width2 <= 0)
            {
                cerr << file2 << "is a Malformed PBM file"<< endl;
                exit(1);
            }
         }
      }
    
    
    if( width1 != width2 || height1 != height2 )
    {
        cerr << file1 << " and " << file2 << "have diffent dimension, so it is not possible to be merged"<< endl;
        exit(1);
    }
    
    
    
    cout << "P4" << endl;
    cout << width1 << " " << height1 << endl;
    
    
    unsigned char readbuffer1;
    unsigned char readbuffer2;
    
    //read data of two pbm file one by one
    int i = 0;
    while( i < height1 )
    {
        int j = 0;
        while( j < ( width1 + 7 ) / 8 )
        {
            fread( &readbuffer1, 1, 1, photo1 );
            fread( &readbuffer2, 1, 1, photo2 );
            printf("%c", (readbuffer1 | readbuffer2) );  //compare two char data
            j++;
        }
        
        i++;
    }
    
}

