/* Written by Will Tremml
 * 4/29/15
 */

#include <stdio.h>
#include <math.h>
#define SHIFT_AMT 20; /* this was the shift used for pad6.txt */

/* function prototypes */
char XOR(int a, int b);
int decrypt (void);
int encrypt (void);

/* main function */
int main (void)
{
	/* variables that store user input and error code */
	int ans,placeholder;
	
	/* user interface */
	printf("\n ___________________________________ \n");
	printf("|                                   |\n");		
	printf("| Would you like to:                |\n");	
	printf("|   Encrypt \"quote.txt\"         (1) |\n");	
	printf("|   Decrypt \"WhatIsThis.Vern\"   (2) |\n");	
	printf("|   Perform both                (3) |\n");	
	printf("|___________________________________|\n\n");	
	
	/* scanning user input */
	scanf("%d",&ans);
	
	/* checking to make sure input is logical */
	while (ans<1 || ans>3){
		printf("Please enter integer 1-3\n");
		scanf("%d",&ans);
		}
	
	/* placeholder holds error codes from padcheck. The function shifts pad6.txt to pad.txt */
	placeholder = padcheck();
	
	/* response based of user input */	
	if (ans==1) encrypt();
	else if (ans==2) decrypt();
	else{
		encrypt();
		decrypt();
	}
	
	/* end of main function returns 0 */
	return(0);
	
}


/* decryption function */
int decrypt (void)
{
	/* variables for two file inputs and a final output */
	char thing1, thing2, final;
	
	/* defining file locations */
	FILE *rfile, *wfile, *pfile;
	rfile=fopen("whatIsThis.vern","r");
	wfile=fopen("whatIsThis.txt","w");
	pfile=fopen("pad.txt","r");
	
	/* checking if files exist */
	if (rfile==NULL){
		 printf("whatIsThis.vern DNE \n");
	 	 return(-1);
	}
	if (wfile==NULL){
		 printf("whatIsThis.txt DNE \n");
	 	 return(-2);
	}
	if (pfile==NULL){
		 printf("pad.txt DNE\n");
	 	 return(-3);
	}
	
	/* XORing each file letter by letter (until EOF) and saving to the wfile */
	while((fscanf(rfile,"%c",&thing1)!=EOF) && (fscanf(pfile,"%c",&thing2)!=EOF)){

		final= XOR(thing1,thing2);
		fprintf(wfile,"%c",final);
	} 
	
	/* checking if the pad was long enough */
	if (fscanf(pfile,"%c",&thing2)==EOF) printf("The pad was not long enough, please provide more secure pad. Your decryption is partial.");
	
	/* closing files */
	fclose(rfile);
	fclose(wfile);
	fclose(pfile);
	
	/* output to user */
	printf("\nDecrypted\n\n");

	/* end of function */
	return(0);
}


/* the same as decrypt but with different files. .vern and .txt are switched as well */
/* refer to decrypt for further explaination */
int encrypt (void)
{
	char thing1, thing2, final, test;
	
	
	FILE *rfile, *wfile, *pfile;
	rfile=fopen("quote.txt","r");
	wfile=fopen("quote.vern","w");
	pfile=fopen("pad.txt","r");
	
	
	if (rfile==NULL){
		 printf("quote.txt DNE \n");
	 	 return(-1);
	}
	if (wfile==NULL){
		 printf("quote.vern DNE \n");
	 	 return(-2);
	}
	if (pfile==NULL){
		 printf("pad.txt DNE\n");
	 	 return(-3);
	}
	
	while((fscanf(rfile,"%c",&thing1)!=EOF) && (fscanf(pfile,"%c",&thing2)!=EOF)) {
		final= XOR(thing1,thing2);
		fprintf(wfile,"%c",final);
	}
	
	if (fscanf(rfile,"%c",&thing1)==EOF) printf("The pad was long enough:");
	else if (fscanf(pfile,"%c",&thing2)==EOF) printf("The pad was not long enough, please provide more secure pad. Your encryption is partial.");

	fclose(rfile);
	fclose(wfile);
	fclose(pfile);
	
	printf("\nEncrypted\n\n");

	return(0);
}


/* manual XOR function has two parameters and one output */
char XOR(int a, int b)
{
	/* creating variables */
	int var1, var2;
	int x=0;
	int i=0;
	
	/* counting for the 8 bits in ASCII Code */
	for(i;i<8;i++)
	{
		/* takes modulo of each variable with respect to 2 to get the (i+1) bit */
		var1=a%2;
		var2=b%2;
		
		/* actual operation on the bit comparison, adds the integer of the bit after XOR to the result */
		/* pow(2,i) is the value of the bit (ie the 3rd bit (i=2) has value 4) */
		if (var1!=var2) x=x +pow(2,i)*1;
		else x=x;
		
		/* divides by two to move onto the next bit. Repeat for all 8 bits. */
		a=a/2;
		b=b/2;
	}
	
	return(x);
}

/* this shifts pad6.txt to pad.txt for use in the main function */
int padcheck (void)
{
	/* Variables */
	FILE *pfile,*tfile;
	char thing1,thing2,final;
	
	/* establishing file locations */
	pfile=fopen("pad6.txt","r");
	tfile=fopen("pad.txt","w");
	
	/* checking that files exist */
	/* notice the returns for different errors */
	if (pfile==NULL){
		printf("pad6.txt DNE. Aborting");
		return(-1);
	}
	if (tfile==NULL){
		printf("pad.txt DNE. Aborting");
		return(-2);
	}
	
	/* scans each character, subtracts 20, converts values <32 to values <=126 */
	while( fscanf(pfile,"%c",&thing2)!=EOF  )
	{
		thing2=thing2-20;
		if (thing2 <32) thing2+=95;
		fprintf(tfile,"%c",thing2);
	}
	
	/* report to user */
	printf("\nThe pad file has been successfully shifted.\n\n");
	
	/* close files */
	fclose(pfile);
	fclose(tfile);
	
	/* end function */
	return(0);
	
}
 
