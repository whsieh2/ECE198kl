#include<stdio.h>
#include<string.h>
void redact(char *inputFile, char *outputFile, char *word);
int main(int argc, char *argv[])
{
    redact(argv[1],argv[2],argv[3]);
}

void redact(char *inputFile, char *outputFile, char *word)
{
    File *input = (inputFile,"r");
	File *output = (outputFile,"w+");
//	int stringLength = strlen(const char * 
	char string[10000];
	int letter;
	int i;
	for(i=0; i<10000;i++)
	{
		fscanf(input,"%1s", string);
		letter = string[i]-' ';
		if !((letter>=65&&letter<=90)||(letter>=97&&letter<=122||(letter>=48&&letter<=57) //make 			sure the char is alphanumeric;
		{
			int x=0;
			int y=0; //counter
			if (string[i]==word[x]
			{
				for(x=0;x<strlen(const char word);i++)
				{	
					if (string[i+x]==word[x])
					{
						y++;
					}
				}
				if (y = strlen(const char word))
				{
					for (x=0;x<y;x++)
					{
						fprintf(output,"%c", 'x');
						i++;
					}

				}
			}
			else
				fprintf(output,"%c", string[i]);
		}	
	}

}
