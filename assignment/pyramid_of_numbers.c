/*----------------------------------------------------------
 *				HTBLA-Leonding / Class: 2DHIF
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			Pyramid of Numbers
 * Author:			Patrick Huemer
 * ----------------------------------------------------------
 * Description:
 * Calculates a pyramid of numbers, i.e., it multiplies a big
 * integer by the number 2, its result by 3, etc. and then
 * returns to the original value by subsequently dividing,
 * again starting by 2, 3, etc.
 * ----------------------------------------------------------
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#define MAX_DIGITS 80


struct BigInt {

	int digits_count;


	unsigned int the_int[MAX_DIGITS];
};


int strtobig_int(const char *str, int len, struct BigInt *big_int){
	int convertedNumbers = 0;
	for (int i = 0; i < len; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			(*big_int).the_int[convertedNumbers] = str[len - i - 1] - 48;
			convertedNumbers++;
		}
	}
	big_int->digits_count = convertedNumbers;
	return convertedNumbers;
}


void print_big_int(const struct BigInt *big_int){
	char BigIntString[big_int->digits_count];
	for (int i = 0; i < big_int->digits_count; i++){
		BigIntString[big_int->digits_count - i - 1] = ('0' + big_int->the_int[i]);
	}
	BigIntString[big_int->digits_count] = 0;
	printf("%s", BigIntString);
}
void multiply(const struct BigInt *big_int, int factor, struct BigInt *big_result)
{
	int overflow = 0;
	big_result->digits_count = big_int->digits_count;

	for (int i = big_int->digits_count - 1; i >= 0 && i < big_result->digits_count; i--)
	{
		int result = big_int->the_int[i] * factor + overflow;

		if (result > 9)
		{
			int temp = result / 10;
			if (i == 0)
			{
				big_result->the_int[i] = result % 10;
				big_result->digits_count++;

				for (int i = big_result->digits_count - 1 ; i > 0; i--) {
					big_result->the_int[i] = big_result->the_int[i - 1];
				}

				big_result->the_int[i] = temp;
			}
			else
			{
				big_result->the_int[i] = result % 10;
			}
			overflow = temp;
		}
		else
		{
			big_result->the_int[i] = result % 10;
			overflow = 0;
		}
	}
}


void divide(const struct BigInt *big_int, int divisor, struct BigInt *big_result){
	bool isNumberSet = false;
	int numbers = 0;
	int modulo = 0;

	for(int i = 0; i < big_int->digits_count; i++)
	{
		int result = (big_int->the_int[i] + modulo) / divisor;

		if (result == 0 && isNumberSet)
		{
			big_result->the_int[numbers] = result;
			numbers++;
		}
		else if (result != 0)
		{
			isNumberSet = true;
			big_result->the_int[numbers] = result;
			numbers++;
		}

		modulo = (big_int->the_int[i] + modulo) % divisor;
		modulo *= 10;
	}

	big_result->digits_count = numbers;
	void copy_big_int(const struct BigInt *from, struct BigInt *to){

		*to=*from;
	}
}


void inverted_big_int(struct BigInt *big_int){
	for (int i = 0; i < big_int->digits_count - 1; i++){
		int temp1 = big_int->the_int[big_int->digits_count - i - 1];
		int temp2 = big_int->the_int[i];
		big_int->the_int[i] = temp1;
		big_int->the_int[big_int->digits_count - i - 1] = temp2;
	}
}

int main(int argc, char *argv[])
{
	struct BigInt number;
	char userInput[MAX_DIGITS];

	printf("Pyramid of numbers\n");
	printf("\n");
	printf("Please enter a number: ");
	scanf("%s", userInput);
	strtobig_int(userInput, strlen(userInput), &number);
	struct BigInt result;
	int multiplyFactor = 2;
	for (int i = 0; i < 8; i++){
		print_big_int(&number);
		printf(" * %d = ", multiplyFactor);
		multiply(&number, multiplyFactor, &result);
		print_big_int(&result);
		printf("\n");
		number = result;
		multiplyFactor++;}

	int divideFactor = 2;
	for (int i = 0; i < 8; i++){
		divide(&number, divideFactor, &result);
		print_big_int(&number);
		printf(" / %d = ", divideFactor);
		print_big_int(&result);
		printf("\n");
		number = result;
		divideFactor++;}
	return 0;
}
