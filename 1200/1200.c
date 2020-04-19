
// Problem acm.timus.ru
// 1200. Horns and Hoofs
// Difficulty: 250
// WA (Respuesta Incorrecta) BAD

// Method: Brute force
#include <stdio.h>
#include <math.h>

long calcMax (int horn_n , int hoof_n,  float horn_b, float  hoof_b ) {

	long max =  (long) horn_b * horn_n + (long) hoof_b * hoof_n - (long) 100 * ( (long) horn_n * horn_n +  (long) hoof_n * hoof_n); 
	return max;
}

/**
	Pasa un número en texto de precisión 2 a entero y lo multiplica por 100 para que sea totalmente entero
*/
int passtoInt( char *number) {
	int num = 0, signo = 1, begin = 0;
	char decimal_flag = 'N';
	int dec_ndig = 0;
	
	if( number[0] == '-')  {
		signo = -1;
		begin = 1;
	}
	for(int i=begin; number[i] != 0; i++) {
		if(number[i] == '.')  {
			decimal_flag = 'Y' ;
			continue;
		}
		if(decimal_flag == 'Y') dec_ndig++;
		if(dec_ndig > 2) break;

		num = num * 10  + (number[i] - '0');
	
	}
	for(int i = dec_ndig; i < 2; i++) num = num*10;

	return num * signo;
}

/** 
	Toma un número num y lo divide entre 100 devolviendo en cociente en *ent y el residuo en *dec
*/
void getPartEntAndDec(long num, long *ent, unsigned *dec )  {
	*ent = num / 100;
	*dec = num % 100;

} 


int main(void) {
	char horn_s[14],  hoof_s[14]; 
	int  horn_n= 0, hoof_n = 0, horn = 0, hoof = 0;
	
	int horn_b, hoof_b; 
	long max = 0, max1, max_ent; 
	unsigned max_dec;
	int maxmount;

	scanf("%s%s%d", horn_s, hoof_s, &maxmount);
	horn_b = passtoInt( horn_s); 
	hoof_b = passtoInt( hoof_s); 	
	
	//printf("horn_b:  %d hoof_b: %d\n",  horn_b, hoof_b );

	for(int horn_n = 0; horn_n <= maxmount; horn_n++) {
		for(int hoof_n = 0; hoof_n <= maxmount -  horn_n;  hoof_n++) {	
			max1 = calcMax (horn_n , hoof_n,  horn_b,  hoof_b );
			if(max1 > max) {
				horn = horn_n;
				hoof = hoof_n;
				max = max1;

			}

		}

	}
	getPartEntAndDec(max, &max_ent, &max_dec );
	printf("%ld.%02u\n", max_ent, max_dec);
	printf("%d %d\n", horn,  hoof);

	return 0;	

}

