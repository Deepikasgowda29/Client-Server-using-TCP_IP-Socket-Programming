#include "header.h"

char* replaceWord(char* str,char* oldWord, char* newWord) 
{ 
	char* result; 
   	int i=0;
    	int newLen = strlen(newWord); 
    	int oldLen = strlen(oldWord); 
 
    	while (*str) 
    	{ 
 
        	if (strstr(str, oldWord) == str) 
        	{ 
            		strcpy(&result[i], newWord); 
            		i += newLen; 
            		str += oldLen; 
        	} 
        	else
        	{
            		result[i++] = *str++;
            	} 
    	} 
    	result[i] = '\0'; 
    	return result; 
} 
