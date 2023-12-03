#include "header.h"

char* replaceWord(char* str, char* oldW,char* newW) 
{ 
    	char* result; 
    	int i,cnt=0; 
    	int newWlen = strlen(newW); 
    	int oldWlen = strlen(oldW); 
 
    // Counting the number of times old word occur in the string 
    	for (i = 0; str[i] != '\0'; i++) 
    	{ 
        	if (strstr(&str[i], oldW) == &str[i]) 
        	{ 
            		cnt++; 
  			i += oldWlen - 1;   // Jumping to index after the old word.
        	} 
    	} 
 
    // Making new string of enough length 
    	result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1);
 	i=0;
    	while (*str) 
    	{ 
        // compare the substring with the result 
        if (strstr(str, oldW) == str) 
        { 
        	strcpy(&result[i], newW); 
            	i += newWlen; 
            	str += oldWlen; 
        } 
        else
            	result[i++] = *str++; 
    	} 
 
    	result[i] = '\0'; 
    	return result; 
}  
