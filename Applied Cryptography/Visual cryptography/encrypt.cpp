//
//  encrypt.cpp
//  HomeWork2
//
//  Created by Amin Amiripour on 2/8/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//

#include "encrypt.h"
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>


void encrypt( char *p, char *o, char *filename )
{
    
    FILE* inputFile = NULL;
    inputFile = fopen(filename, "rb");
    
    if (!filename)  //read from input when file is not exist
    {
        //cout << "Please enter your data to be encrypt:\n";
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
        encrypt( p, o, tempFileName);
        remove(tempFileName);
        
        
    }else    //read data from file
    {
        if ( inputFile == NULL ) {
            cerr << "Cannot open " << filename << " or does not exist"<< endl;
        }else{
            
            char *magic = (char *)malloc(4);
            fgets(magic, 4, inputFile);       // check MagicNumber (P4)
            if( magic[0] != 'P' || magic[1] != '4' || magic[2] != '\n' ) {
                cerr << "Malformed PBM file"<< endl;
                exit(1);    
            }else{
                
                //free( magic );
                char *temp = (char *)malloc(10);
                int width = 0, height = 0;
                fgets(temp, 10, inputFile);
                
                if ( temp[0] == '#' )               //this is a comment line
                    fgets(temp, 10, inputFile);
                
                sscanf(temp, "%d%d", &width, &height);

                
                if (height <= 0 || width <= 0)
                {
                    cerr << "Malformed PBM file "<< endl;
                    exit(1);
                }
                
                
                int size = (int)strlen(o);
                
                FILE* photo1;
                char photo1name [size + 7];
                strcpy(photo1name,o);
                photo1 = fopen( strcat( photo1name, ".1.pbm" ), "w");
                if( photo1 == NULL ){
                    cerr << "Cannot open " << photo1name << endl;
                    exit(1);
                }else
                {
                    fprintf ( photo1, "P4\n" );
                    fprintf ( photo1, "%d %d\n", width*2, height*2 );
                }
                
                FILE* photo2;
                char photo2name [size + 7];
                strcpy(photo2name,o);
                photo2 = fopen( strcat( photo2name, ".2.pbm" ), "w");
                if( photo2 == NULL ){
                    cerr << "Cannot open " << photo2name << endl;
                    exit(1);
                }else
                {
                    fprintf ( photo2, "P4\n" );
                    fprintf ( photo2, "%d %d\n", width*2, height*2 );
                }
                
                
                


                
                //generate key
                /*
                 following codes obtained from from Homework2 specification page :
                 http://merlot.usc.edu/cs531-s16/homeworks/hw2
                 */
                
                unsigned char md5_buf[MD5_DIGEST_LENGTH];
                int len = strlen(p) + 2 + MD5_DIGEST_LENGTH;
                char *s = (char *)malloc( len + 1 );
                unsigned char Key[ height * (width/8 + 1) ];
                MD5((unsigned char *)p, strlen(p), (unsigned char *)md5_buf);
                int i = 0, k = 0;
                
                while( k != height * ( width/8 + 1 ) )
                {
                    sprintf((char *)&s[MD5_DIGEST_LENGTH], "%02d%s", i, p);
                    memcpy(s, md5_buf, MD5_DIGEST_LENGTH);
                    MD5((unsigned char *)s, len, md5_buf);
                    
                    for( int j = 0; j < 8; j++ )
                    {
                        if( k < ( height * ( width/8 + 1 ) ) )
                        {
                            Key[k] = md5_buf[j];
                            k = k + 1;
                        }
                    }
                    
                    if ( ++i == 100 )
                        i = 0;
                }
                
                free(s);
                //end of generate key
                
                
                //read inputFile
                unsigned char *ReadBuffer;
                if( width % 8 == 0 ){
                    ReadBuffer = (unsigned char*)malloc(height * width/8);
                    fread(ReadBuffer, 1, (height * width/8), inputFile);
                }
                
                if( width % 8 > 0 ) {
                    ReadBuffer = (unsigned char*)malloc(height * (width/8 + 1));
                    fread(ReadBuffer, 1, (height * (width/8 + 1)), inputFile);
                }
                
                
                
                
                unsigned char *KeyBuffer;
                KeyBuffer = (unsigned char*)Key;
                unsigned short outrow1[2];
                unsigned char row_out1[(2*width+7)/8][2];
                unsigned short outrow2[2];
                unsigned char row_out2[(2*width+7)/8][2];
                unsigned char tempinut = 0x80;
                unsigned char tempkey = 0x80;
                
                
                
                
                /*
                 ##########################
                 
                 following algorithm idea obtainet from this paper : 
                 http://www.slideshare.net/ieeexploreprojects/k-n-secret-sharing-visual-cryptography-scheme-for-color-image-using-random-numberbak
                 
                 ##########################
                 */
                
                i = 0;
                while( i < height )
                {
                    
                    int j=0;
                    while ( j < (width+7) / 8 )
                    {
                        
                        outrow1[0] = 0x0000;
                        outrow1[1] = 0x0000;
                        outrow2[0] = 0x0000;
                        outrow2[1] = 0x0000;
                        
                        int k = 0;
                        while ( k < 8 )
                        {
                            if( ( j * 8 + k ) < width ) {
                                
                                if( *ReadBuffer & tempinut )
                                {
                                    if( *KeyBuffer & tempkey ) {                            // pixel = black, key = 1
                                        outrow1[0] = outrow1[0] | ( 0x4000 >> ( 2 * k ) );
                                        outrow1[1] = outrow1[1] | ( 0x8000 >> ( 2 * k ) );
                                        outrow2[0] = outrow2[0] | ( 0x8000 >> ( 2 * k ) );
                                        outrow2[1] = outrow2[1] | ( 0x4000 >> ( 2 * k ) );
                                    }else
                                    {                                                       // pixel = black, key = 0
                                        outrow1[0] = outrow1[0] | ( 0x8000 >> ( 2 * k ) );
                                        outrow1[1] = outrow1[1] | ( 0x4000 >> ( 2 * k ) );
                                        outrow2[0] = outrow2[0] | ( 0x4000 >> ( 2 * k ) );
                                        outrow2[1] = outrow2[1] | ( 0x8000 >> ( 2 * k ) );
                                    }
                                }else
                                {
                                    if( *KeyBuffer & tempkey )
                                    {                                                       // pixel = white, key = 1
                                        outrow1[0] = outrow1[0] | ( 0x4000 >> ( 2 * k ) );
                                        outrow1[1] = outrow1[1] | ( 0x8000 >> ( 2 * k ) );
                                        outrow2[0] = outrow2[0] | ( 0x4000 >> ( 2 * k ) );
                                        outrow2[1] = outrow2[1] | ( 0x8000 >> ( 2 * k ) );
                                    }else
                                    {
                                        outrow1[0] = outrow1[0] | ( 0x8000 >> ( 2 * k ) );  //// pixel = white, key = 1
                                        outrow1[1] = outrow1[1] | ( 0x4000 >> ( 2 * k ) );
                                        outrow2[0] = outrow2[0] | ( 0x8000 >> ( 2 * k ) );
                                        outrow2[1] = outrow2[1] | ( 0x4000 >> ( 2 * k ) );
                                    }
                                }
                                
                                
                                tempkey = tempkey >> 1;
                                if(tempkey == 0) {
                                    KeyBuffer++;
                                    tempkey = 0x80;
                                }

                            }
                            
                            
                            if( ( j * 8 + k ) >= width )
                                if( k == 4 )
                                {
                                    ReadBuffer++;
                                    tempinut = 0x80;
                                    break;
                                }

                            
                            tempinut = tempinut >> 1;
                            if( tempinut == 0 ) {
                                ReadBuffer++;
                                tempinut = 0x80;
                            }
                            
                            k++;
                        }
                        
                        
                        
                        
                        
                        /* 
                         following idea obtained from
                         http://vijayinterviewquestions.blogspot.com/2007/07/what-little-endian-and-big-endian-how.html
                         */
                        int num = 1;
                        if( *(char *) & num == 1) {
                            row_out1[j*2][0] = *(((unsigned char*)&outrow1[0])+1);
                            row_out1[j*2+1][0] = *(unsigned char*)&outrow1[0];
                            row_out1[j*2][1] = *(((unsigned char*)&outrow1[1])+1);
                            row_out1[j*2+1][1] = *(unsigned char*)&outrow1[1];
                            
                            row_out2[j*2][0] = *(((unsigned char*)&outrow2[0])+1);
                            row_out2[j*2+1][0] = *(unsigned char*)&outrow2[0];
                            row_out2[j*2][1] = *(((unsigned char*)&outrow2[1])+1);
                            row_out2[j*2+1][1] = *(unsigned char*)&outrow2[1];
                        }
                        
                        if( *(char *) & num != 1)
                        {
                            row_out1[j*2][0] = *(unsigned char*)&outrow1[0];
                            row_out1[j*2+1][0] = *(((unsigned char*)&outrow1[0])+1);
                            row_out1[j*2][1] = *(unsigned char*)&outrow1[1];
                            row_out1[j*2+1][1] = *(((unsigned char*)&outrow1[1])+1);
                            
                            row_out2[j*2][0] = *(unsigned char*)&outrow2[0];
                            row_out2[j*2+1][0] = *(((unsigned char*)&outrow2[0])+1);
                            row_out2[j*2][1] = *(unsigned char*)&outrow2[1];
                            row_out2[j*2+1][1] = *(((unsigned char*)&outrow2[1])+1);
                        }
                        
                        
                        j++;
                    }
                    
                    
                    
                    //start to write encrypted data in photo1 and photo2
                    int l = 0;
                    while( l < 2)
                    {
                        for( int j = 0; j < ( 2 * width + 7 ) / 8; j++ )
                        {
                            fprintf(photo1, "%c", row_out1[j][l]);
                            fprintf(photo2, "%c", row_out2[j][l]);
                        }
                        
                        l++;
                    }
                    
                

                
                    i++;
                }
                
                fclose(photo1);
                fclose(photo2);
                
            }
            
            
        }
        
    }


    fclose(inputFile);
    
}


