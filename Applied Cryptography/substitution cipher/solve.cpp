//
//  solve.cpp
//  Homework3
//
//  Created by Amin Amiripour on 2/22/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//


#include "solve.h"

void solve( char* l, char* filename )
{
    
    int max_t = atoi(l);
    int counter = 0 ;
    unsigned char *ReadBuffer = (unsigned char *)malloc(257);
    
    
    FILE* inputfile;
    inputfile = fopen(filename, "rb");
    if( inputfile == NULL )
    {
        std::cerr << "Cannot open inputfile or does not exist" << std::endl;
        exit(1);
    }
    


    while( !feof(inputfile) )
    {
        int bytes_read = fread(&ReadBuffer[counter], 1, 256, inputfile) ;
        
        if ( bytes_read )
        {
            counter = counter + bytes_read ;
            if (ReadBuffer[counter-1] == '\n')
            {
                ReadBuffer[counter-1] = '\0' ;
                break ;
            }
            else{
                ReadBuffer = (unsigned char *)realloc(ReadBuffer, 257 + counter ) ;
            }
        }
        
    }
    ReadBuffer[counter] = '\0' ;
    

    
    std::cout << "Kasiski Method" << std::endl;
    std::cout << "==============" << std::endl;
    
    
    int len;
    len = 4;
    int size = counter / 2;
    char string1[size];
    char string2[size];

    while( len < counter/2 )
    {
        int end = 0 ;
        int i = 0;
        while( i < counter - 2*len )
        {
            strncpy(string1, (char *)&ReadBuffer[i], len);
            string1[len] = '\0' ;
            
            
            bool flag = false;
            for( int m = 0; string1[m]!='\0'; m++ )
                if( string1[m] < 0x61 || string1[m] > 0x7a )
                {
                    flag = true;
                    break;
                }
            
            if( flag == true )
            {
                i = i + 1;
                continue;
            }
            
            int j = i + len;
            while( j < counter - len )
            {
                strncpy(string2, (char *)&ReadBuffer[j], len);
                string2[len] = '\0' ;
                
                bool flag = false;
                for( int m = 0; string2[m]!='\0'; m++ )
                    if( string2[m] < 0x61 || string2[m] > 0x7a )
                    {
                        flag = true;
                        break;
                    }
                
                if( flag == true )
                {
                    j = j + 1;
                    continue;
                }
                
                
                if( strcmp(string1, string2) == 0 )
                {
                    end = 1 ;
                    std::cout << "len=" << len;
                    std::cout << ", i=" << i;
                    std::cout << ", j=" << j;
                    std::cout << ", j-i=" << j-i;
                    std::cout << ", " << string1;
                    std::cout << std::endl;
                }
                
                j = j + 1;
            }
            
            i = i + 1;
        }
        
        if( end == 0 )
        {
            std::cout << "len=" << len;
            std::cout << ", no more matches";
            std::cout << std::endl;
            std::cout << std::endl;
            break ;
        }
        
        len = len + 1;
    }
    
    
    
    std::cout << "Average Index of Coincidence";
    std::cout << std::endl;
    std::cout << "============================";
    std::cout << std::endl;
    
    double length = 0 ;
    
    int* frequency = (int *)malloc(26 * sizeof(int));
    memset( frequency, 0, 26 * sizeof(int) );
    
    int i = 0;
    while( i < counter )
    {
        if( ReadBuffer[i] >= 'a' && ReadBuffer[i] <= 'z' )
        {
            length = length + 1;
            ++frequency[ReadBuffer[i] - 97] ;
        }else{
            i = i + 1;
            continue;
        }
        
        i = i + 1;
    }
    
    std::cout << "L=";
    std::cout << (int)length;
    std::cout << std::endl;
    
    i = 0;
    long double ic = 0 ;
    while( i < 26 )
    {
        std::cout << "f('";
        std::cout << (char)( i + 'a' );
        std::cout << "')=";
        std::cout << frequency[i];
        std::cout << std::endl;
        ic = ic + ( frequency[i] * ( frequency[i] - 1 ) );
        i = i + 1;
    }

    
    std::cout << "IC=";
    std::cout << std::setprecision(9) << std::fixed << ic / ( length * ( length - 1 ) );
    std::cout << std::endl;
   
    
    double n = 1;
    int m = 1;
    while ( n <= max_t )
    {
        std::cout << "t=";
        std::cout << std::setprecision( 0 ) << m;
        std::cout << ", E(IC)=";
        std::cout << std::setprecision( 9 ) << ( 0.0658/n *( ( length-n )/( length-1 ) ) + (n-1)/n *( 1.0/26 )* ( length / ( length-1 ) ) );
        std::cout << std::endl;
        
        n = n + 1;
        m = m + 1;
    }
    
    std::cout << std::endl;
    std::cout << "Auto-correlation Method";
    std::cout << std::endl;
    std::cout << "=======================";
    std::cout << std::endl;
    i = 1;
    while( i <= max_t )
    {
        int count = 0, j = 0;
        while( j < counter - i )
        {
            if( ReadBuffer[j] < 'a' || ReadBuffer[j] > 'z' )
            {
                j = j + 1;
                continue;
                
            }else if ( ReadBuffer[j] == ReadBuffer[j+i] )
                    count = count + 1 ;
            
            j = j + 1;
        }
        
        std::cout << "t=" << i;
        std::cout << ", count=" << count;
        std::cout << std::endl;
        
        i = i + 1;
    }
    

    
    std::cout << std::endl;
    
    
    
}





