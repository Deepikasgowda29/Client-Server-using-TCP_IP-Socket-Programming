#include "header.h"

char* replaceWord(char* str,char* oldWord, char* newWord) 
{ 
	char* result; 
   	int i, cnt = 0; 
    	int newLen = strlen(newWord); 
    	int oldLen = strlen(oldWord); 
 
    	for (i = 0; str[i] != '\0'; i++) 
    	{ 
        	if (strstr(&str[i], oldWord) == &str[i]) 
        	{ 
            		cnt++; 
            		i += oldLen - 1; 
        	} 
    	} 
 
    	i = 0; 
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

