//
//  decrypt.cpp
//  HomeWork2
//
//  Created by Amin Amiripour on 2/11/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//

#include <stdio.h>
#include "decrypt.h"

void decrypt( char *filename )
{
    FILE* inputFile = NULL;
    inputFile = fopen(filename, "rb");
    int width = 0, height = 0;
    
    if (!filename)  //read from input when file is not exist
    {
        //cout << "Please enter your data to be decrypt:\n";
        //string input;
        char tempFileName[]="tempp.txt";
        ofstream tempFile;
        
        tempFile.open(tempFileName, ios_base::binary);
        
        char c;
        while( cin.get(c) )
        {
            tempFile << c;
            if(cin.peek() == EOF)
                break;
        }
        
        tempFile.close();
        decrypt(tempFileName);
        remove(tempFileName);
        
        
    }else    //read data from file
    {
        if ( inputFile == NULL ) {
            cerr << "Cannot open " << filename << " or does not exist"<< endl;
            exit(1);
        }else{
            
            char *magic = (char *)malloc(4);
            fgets(magic, 4, inputFile);                    // check MagicNumber (P4)
            if( magic[0] != 'P' || magic[1] != '4' || magic[2] != '\n' ) {
                cerr << filename << "is a Malformed PBM file"<< endl;
                exit(1);
            }else{
                
                char *temp = (char *)malloc(10);
                
                fgets(temp, 10, inputFile);
                if ( temp[0] == '#' )               //this is a comment line
                    fgets(temp, 10, inputFile);
                
                sscanf(temp, "%d%d", &width, &height);
                
                if (height <= 0 || width <= 0)
                {
                    cerr << filename << "is a Malformed PBM file"<< endl;
                    exit(1);
                }
            }
        }
        
        
        cout << "P4" << endl;
        cout << width/2 << " " << height/2 << endl;

        unsigned char *row1;
        row1 = (unsigned char*)malloc((width+7)/8);
        unsigned char *row2;
        row2 = (unsigned char*)malloc((width+7)/8);
        unsigned char *outpixel;
        outpixel = (unsigned char*)malloc(1);
        unsigned char *blackpixel;
        blackpixel = (unsigned char*)malloc(1);
        unsigned char *whitepixel;
        whitepixel = (unsigned char*)malloc(1);
        *blackpixel = 0xff;
        *whitepixel = 0x00;
        *outpixel = *whitepixel;
        int widthbytes = ( width + 7 ) / 8;
        int i = 0;
        while( i < height )
        {
            fread(row1, 1, widthbytes, inputFile);  //read whole bytes in row 1
            fread(row2, 1, widthbytes, inputFile);  //read whole bytes in row 2
            
            int j = 0;
            while( j < widthbytes )
            {
                
                bool row1IsBlack = false;
                bool row2IsBlack = false;
                
                
                // Checks if both pixel in two lines are black or now
                for( int k = 0; k < 4; k++ )
                {
                    row1IsBlack = ( ( row1[j] & (0xc0 >> 2 * k) ) == ( 0xc0 >> 2 * k ));
                    row2IsBlack = ( ( row2[j] & (0xc0 >> 2 * k) ) == ( 0xc0 >> 2 * k ));
                    if( row1IsBlack )
                        if( row2IsBlack )
                            {
                                if( j % 2 == 0 )
                                    *outpixel = *outpixel | (0x80 >> k);  //0x80 == 10000000
                                else
                                    *outpixel = *outpixel | (0x08 >> k);  //0x08 == 00001000
                                
                            }
                }
                
                
                if( j%2 == 1 || ((j+1)*8 + 4 >= width) )
                {
                    printf("%c", *outpixel);
                    *outpixel = *whitepixel;
                }
                
                j = j + 1;
            }
 
            i = i + 2;
        }
  
        
    }// end of else read data from file
}


