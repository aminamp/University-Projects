CSCI531 - Homework 3
Author : Amin Amiripour

#############################################

Enter following command in terminal to compile the source code : 

$ make

Note : it may take some moment to execute “solve” section

#############################################

to delete all binary files created during compilation, enter following command : 
$ make clean

#############################################

Detect Period:

Mystery 1 :
using Auto-correlation method, we see an increase in values in t = 5, 10, 15, 20, 25, 30, 35, 40, 45, 50 , so in this case I guess T = 5  (greatest common factor of these numbers), now using Kasiski method, we can confirm our guess that matchings happen mostly at multiplication of 5 positions.


Mystery 2 : 
using Auto-correlation method, we see an increase in values in t = 11, 22, 33, 44 , so in this case I guess T = 11  (greatest common factor of these numbers), now using Kasiski method, we can confirm our guess that matchings happen mostly at multiplication of 11 positions.

 
