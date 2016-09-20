//
//  enc.cpp
//  Homework4
//
//  Created by Amin Amiripour on 3/7/16.
//  Copyright © 2016 Amin Amiripour. All rights reserved.
//

#include "enc.h"


using namespace std;


void encryptfunction(unsigned char* buffer, unsigned char keys[][6], int S[][64], int *P, int *IP, int *invIP, int *E, unsigned char* result, int done, int mode)
{
    
    unsigned char* message = (unsigned char*) malloc(8 * sizeof(unsigned char*));
    
    int i = 0;
    while( i < 64 )
    {
        int index = i / 8;
        message[index] = message[index] << 1;
        unsigned char shift = buffer[(IP[i]-1)/8] >> ( 7-((IP[i]-1)%8 ) );
        int result = shift & 1;
        message[index] = message[index] + result;
        i = i + 1;
    }
    

    
    i = 0;
    while ( i < 16 )
    {
        if( mode == 1 ) //encrypt
        {
            if(done == 0)
            {
                int j = 0;
                cerr << "(L";
                cerr << i;
                cerr << ",R";
                cerr << i;
                cerr << ")=";
                
                while( j < 8 )
                {
                    fprintf(stderr, "%02x", message[j]);
                    j = j + 1;
                }
                cerr << endl;
            }
        }
        

        
        unsigned char* Eoutput = (unsigned char*) malloc(6*sizeof(unsigned char*));
        int j = 0;
        while( j < 48 )
        {
            int index = j/8;
            unsigned char shift = message[4+(E[j]-1)/8] >> (7-((E[j]-1)%8));
            int result = shift & 1;
            if( (j % 8 ) == 0 )
                Eoutput[index] = result;
            else
                Eoutput[index] = (Eoutput[index] << 1) + result;

            j = j + 1;
        }
        
        unsigned char *Toutput = (unsigned char*) malloc(8* sizeof(unsigned char*));
        j = 0;
        while( j < 48 )
        {
            int index = j/6;
            unsigned char shift = Eoutput[j/8] >> (7-(j%8));
            unsigned char shift2 = keys[i][j/8] >> (7-(j%8));
            int result = shift & 1;
            int result2 = shift2 & 1;
            result = result ^ result2;
            if(j % 6 == 0)
                Toutput[index] = result;
            else
                Toutput[index] = (Toutput[index] << 1) + result;

            j = j + 1;
        }
        
        unsigned char *Toutput2 = (unsigned char*) malloc( 8 * sizeof(unsigned char*));
        j = 0;
        while( j < 8 )
        {
            int c = 0, k = 0;
            unsigned char shift = ( Toutput[j] >> 5 );
            int result = 2 * (shift & 1);
            result = result + (Toutput[j] & 1);
            while ( k < 4 )
            {
                unsigned char shift = ( Toutput[j] >> (4-k) );
                int result = shift & 1;
                c = (c << 1) + result;
                k = k + 1;
            }
            Toutput2[j] = S[j][result*16+c];
            j = j + 1;
        }
        
        unsigned char *Toutput3 = (unsigned char*) malloc(4*sizeof(unsigned char*));;
        j = 0;
        while( j < 32 )
        {
            int index = j/8;
            unsigned char shift = Toutput2[(P[j]-1)/4] >> (3-((P[j]-1)%4));
            int result = shift & 1;
            Toutput3[index] = (Toutput3[index] << 1) + result;
            j = j + 1;
            
        }
        
        unsigned char* newm = (unsigned char*) malloc(8 * sizeof(unsigned char*));
        j = 0;
        while( j < 4 )
        {
            newm[j] = message[j+4];
            newm[j+4] = message[j] ^ Toutput3[j];
            j = j + 1;
        }
        
        j = 0;
        while( j < 8 )
        {
            message[j] = newm[j];
            j = j + 1;
        }
        
        i = i + 1;
    }
    

    
    if( mode == 1 )
    {
        if(done == 0)
        {
            cerr << "(L";
            cerr << i;
            cerr << ",R";
            cerr << i;
            cerr << ")=";
            int j = 0;
            while( j < 8 )
            {
                fprintf(stderr, "%02x", message[j]);
                j = j + 1;
            }
            cerr << endl;
        }
        
    }
    



    unsigned char* result0 = (unsigned char *) malloc(8*sizeof(unsigned char*));
    int j = 0;
    while( j < 4 )
    {
        result0[j] = message[ j + 4 ]; //right
        result0[ j + 4 ] = message[j]; //left
        j = j + 1;
    }

    j = 0;
    while ( j < 64 )
    {
        int index = j/8;
        unsigned char shift = (result0[(invIP[j]-1)/8]) >> (7-((invIP[j]-1)%8));
        int temp = shift & 1;
        result[index] = (result[index] << 1) + temp;
        j = j + 1;
    }
    
}



void keyGenerator(char* key,unsigned char keys[][6], int *PC1, int *V, int *PC2)
{
    
    int i = 0;
    unsigned char *tohex;
    tohex = (unsigned char*) malloc(8 * sizeof(char*));

    while( i < 8 )
    {
        char temp[3] = {'\0'};
        temp[0] = key[ i * 2 ];
        temp[1] = key[ i * 2 + 1 ];
        tohex[i] = strtol(temp, NULL, 16);
        i = i + 1;
    }

    unsigned char *keygen;
    keygen = (unsigned char*) malloc(7*sizeof(char*));
    
  
    i = 0;
    while ( i <= 55 )
    {
        int index = i / 8;
        unsigned char shift = tohex[ PC1[i] / 8 ] >> ( 8 - PC1[i]%8 );
        int result = shift & 1;
        keygen[index] = (keygen[index] << 1) + result ;
        i = i + 1;
    }
    
    cerr << "(C0,D0)=";
    i = 0;
    while ( i <= 6 )
    {
        fprintf(stderr, "%02x", keygen[i]);
        i = i + 1;
    }
    cerr << endl;
    
    
    int k = 0;
    for(k = 0; k < 16; k++)
    {
        unsigned char *keygen_new = (unsigned char *) malloc(7*sizeof(char*));
        unsigned int bits = 0;
        int i = 0;
        while ( i < 3 )
        {
            int m = 0 ;
            while ( m < V[k] )
            {
                bits = keygen[i+1] >> ( 7 - m );
                m = m + 1;
            }
            keygen_new[i] = ( keygen[i] << V[k] ) + bits;
            
            i = i + 1;
        }
        
        bits = 0;
        int j = V[k];
        while( j < 4 )
        {
            bits = bits << 1;
            unsigned char shift = keygen[i] >> ( 7 - j );
            int result = shift & 1;
            bits = bits + result;
            j = j + 1;
        }
    
        j = 0;
        while( j < V[k] )
        {
            bits = bits << 1;
            unsigned char shift = keygen[0] >> ( 7 - j );
            int result = shift & 1;
            bits = bits + result;
            j = j + 1;
        }
        
        j = 3 - V[k];
        while( j > -1 )
        {
            bits = bits << 1;
            unsigned char shift = keygen[i] >> j;
            int result = shift & 1;
            bits = bits + result;
            j = j - 1;
        }
        
        j = 0;
        while( j < V[k] )
        {
            bits = bits << 1;
            unsigned char shift = keygen[i+1] >> ( 7 - j );
            int result = shift & 1;
            bits = bits + result;
            j = j + 1;
        }
        
        keygen_new[i] = bits;
        i = 4;
        while( i <= 5 )
        {
            unsigned char shift = keygen[i] << V[k];
            keygen_new[i] = shift;
            int m = 0;
            while( m < V[k] )
            {
                shift = keygen[ i+1 ] >> ( 7 - m );
                bits = shift;
                m = m + 1;
            }
             keygen_new[i] = keygen_new[i] + bits;
            i = i + 1;
        }
        
        bits = 0;
        j = V[k];
        while( j < 8 )
        {
            bits = bits << 1;
            unsigned char shift = keygen[i] >> ( 7 - j );
            int result = shift & 1;
            bits = bits + result;
            j = j + 1;
        }
        
        j = 0;
        while( j < V[k] )
        {
            bits = bits << 1;
            unsigned char shift = keygen[3] >> (3-j);
            int result = shift & 1;
            bits = bits + result;
            j = j + 1;
        }
        
        keygen_new[i] = bits;
        cerr << "(C" << k+1;
        cerr << ",D" << k+1;
        cerr << ")=";
        
        j = 0;
        while( j < 7 )
        {
            fprintf(stderr, "%02x", keygen_new[j]);
            j = j + 1;
        }
        cerr << endl;
        
        j = 0;
        while ( j < 7 )
        {
            keygen[j] = keygen_new[j];
            j = j + 1;

        }
        
        j = 0;
        while( j < 48 )
        {
            keys[k][j/8] = keys[k][j/8] << 1;
            unsigned char shift = keygen[(PC2[j]-1)/8] >> (7-((PC2[j]-1)%8));
            int result = shift & 1;
            keys[k][j/8] = keys[k][j/8] + result;
            j = j + 1;
        }
        
        j = 0;
        cerr << "k" << k+1 << "=";
        while( j < 6 )
        {
            fprintf(stderr, "%02x", keys[k][j]);
            j = j + 1;
        }
        
        cerr << endl;
    }
    
}



void encrypt(char *key, char *tablefilename, char *filename)
{
    if( strlen(key) != 16 )
    {
        cerr << "Malformed Key"<< endl;
        exit(1);
    }
    
    for( int i = 0; i < 16; i++ )
    {
        if( key[i] >= '0' && key[i] <= '9' )
            continue;
        
        if( key[i] >= 'a' && key[i] <= 'f' )
            continue;
        
        cerr << "Malformed Key"<< endl;
        exit(1);
        
    }
    
    tablecheck(tablefilename);

    
    if( !filename )
    {
        
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
        encrypt( key, tablefilename, tempFileName);
        remove(tempFileName);
        
    }else{
        
        int IP[64]={0}, invIP[64]={0}, PC1[56]={0}, PC2[48]={0}, E[48]={0}, V[16]={0}, P[32]={0}, S[8][64]={0};
        FILE *inputFile = NULL;
        inputFile = fopen(filename, "rb");
        
        if( inputFile == NULL )
        {
            cerr << "Cannot open " << filename << " or does not exist"<< endl;
            exit(1);
        }else{
            unsigned char keys[16][6];
            unsigned char* inputbuffer = (unsigned char *)malloc(8 * sizeof(unsigned char));
            unsigned char* result = (unsigned char *)malloc(8 * sizeof(unsigned char));
            int end = 0;
            FILE *tableFile = NULL;
            tableFile = fopen(tablefilename, "rb");
            if(tableFile == NULL)
            {
                cerr << "Cannot open " << tablefilename << " or does not exist"<< endl;
                exit(1);
            }
            
            int i = 0;
            char* readbuffer = (char *)malloc(256 * sizeof(char));
            char *title, *read;
            while( i <= 13 )
            {
                int k = 0;
                fgets(readbuffer, 256, tableFile);
                title = strtok(readbuffer, "=");
                int values[64] = {-1};
                
                do{
                    read = strtok(NULL, ",");
                    if( read == NULL )
                        break;
                    values[k] = atoi(read);
                    k = k + 1;
                }while( read != NULL );
                
                if( strcmp(title, "IP") == 0 )
                    for( int j = 0; j < 64; j++ )
                        IP[j] = values[j];
                
                if( strcmp(title, "E") == 0 )
                    for(int j = 0; j < 48; j++)
                        E[j] = values[j];
                
                if( strcmp(title, "V") == 0 )
                    for(int j = 0; j < 16; j++)
                        V[j] = values[j];
                
                if( strcmp(title, "P") == 0 )
                    for(int j = 0; j < 32; j++)
                        P[j] = values[j];
                
                if( strncmp(title, "S",1) == 0 )
                {
                    char *pointer = title+1;
                    int s = atoi(pointer);
                    for(int j = 0; j < 64; j++)
                        S[s-1][j] = values[j];
                }
                
                if( strcmp(title, "PC1") == 0 )
                    for(int j = 0; j < 56; j++)
                        PC1[j] = values[j];
                
                if( strcmp(title, "PC2") == 0 )
                    for(int j = 0; j < 48; j++)
                        PC2[j] = values[j];
                
                i = i + 1;
            }
            
            
            //IP-inverse
            int m = 0;
            while( m < 64 )
            {
                invIP[ IP[m] - 1 ] = m + 1;
                m = m + 1;
            }

            
            keyGenerator(key, keys, PC1, V, PC2);
            
            
            while(1)
            {
                int counter = fread(inputbuffer,1,8,inputFile);
                if ( counter <= 0 )
                    break;
                else{
                    if( counter != 8 )
                        while ( counter < 8 )
                        {
                            inputbuffer[counter] = '\0';
                            counter = counter + 1;
                        }
                    
                    
                    encryptfunction(inputbuffer, keys, S, P, IP, invIP, E, result, end, 1);
                    
                    
                    int i = 0;
                    while ( i < 8 )
                    {
                        cout << result[i];
                        i = i + 1;
                    }
                    
                    end = end + 1;
                }

            }
            
            fclose(tableFile);
            fclose(inputFile);
        }
    }

}

