//Question 1 
Write a program in any language that takes two (2) command-line arguments, 
both strings, and checks to see if the second string is a substring of the
first string. Any * in the second string can match zero or more characters 
in the first string.*/
//Question 1 program is below.
#include <stdio.h>
#include<string.h>
#define MaxNumber 1000
/*
pseudocode
Match(mainString, mianSubString)
	while(mainSubString)
	{
		get substring with-out wildcard
		match with mainString else return false
		Remove until subString from mainString and mainSubString  
	}
	return true

*/
/*
//test data
program.out mahesh mah 		<Matched>
program.out mahesh mah* 	<Matched>
program.out mahesh *mah 	<Matched>
program.out mahesh ma*h 	<Matched>
program.out mahesh ? 		<Invalid input>
program.out mahesh ma**h 	<Matched>
program.out mahesh m*a*h 	<Matched>
program.out mahesh ba*shi 	<Not Matched>
program.out maheshbak m*ak*	<Matched>
program.out 				<Invalid input>
program.out mah*sh ma		<Invalid input>
*/
//extract non-wildcard substring
int extract(char * inStr, char *outSubStr)
{
	int i=0;
	while(inStr[i]=='*' && inStr[i+1]!='\0')
	{
		inStr = &inStr[i+1];
		i++;
	}
	if(inStr)
	{
		int j=0;
		while(inStr[j]!='*' && inStr[j]!='\0')
		{
			outSubStr[j]=inStr[j];
			j++;
		}
		outSubStr[j]='\0';
		return i+j;//length to keep track of wild-card 
	}
	else
		return 0;
}
//match non-wildcard substring
char* match(char *inStr, char *inSubStr)
{
	return strstr(inStr, inSubStr);
}
//Remove validated sub-string
char* removeSubStr(char *inStr, char *inRemoveSubStr, int lengthWithStar)
{
	char *retStr;
	if(lengthWithStar==0)
	 lengthWithStar = strlen(inRemoveSubStr);
	 
	retStr = &inStr[lengthWithStar];
	return retStr;
}
//validate input string 
int isValidate(char * inputString1, char * inputString2, int numArgs)
{
	if(numArgs!=3)
		return 0;
	int i=0;
	int asciiVal=0;
	while(inputString1[i]!='\0')
	{
	asciiVal=inputString1[i++];
	if(!((asciiVal>=65 && asciiVal<=90) || (asciiVal>=97 && asciiVal<=122)))
			return 0;
	}
	i=0;
	asciiVal=0;
	while(inputString2[i]!='\0')
	{
	asciiVal=inputString2[i++];
	if(!(asciiVal==42 || (asciiVal>=65 && asciiVal<=90) || (asciiVal>=97 && asciiVal<=122)))
			return 0;
	}
	return 1;
}
void main(int argc, char *argv[])
{
	char *mainStr = argv[1]; 
	char *mainSubStr = argv[2];
	  
	//Input validation
	if(isValidate(mainStr, mainSubStr, argc)==0)
	{
		printf("\n Wrong arguments or invalid character(not [a-z],*,[A,Z]). \n program.exe <string> <subString>");
		return;
	}	   
	int length=0;
	while(mainStr || mainSubStr)
	{	
	   //extract non-wild-card substring
	   char subStr[MaxNumber];
	   char *subStrPtr=subStr;
	   length = extract(mainSubStr, subStrPtr);
	   //match substring 
	   char *retStr;
	   retStr = match(mainStr, subStr);
	   if(!retStr)
	   {
			printf("\n Not Matched");
			return;
		}
	    else
		{
			//Remove validated substring
			mainStr = removeSubStr(retStr, subStr, 0);
			mainSubStr = removeSubStr(mainSubStr, subStr, length);
			if(mainSubStr)
			{
				printf("\n Matched");
				return;
			}
		}
	}
	getch();
}
