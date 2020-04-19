#include <stdio.h>

// Fecha de Ref. Viernes 17 - 4 - 2020
const unsigned ref_wday = 4,  day_ref = 17,  month_ref = 4, year_ref = 2020;

int dayByMonths[] = {
 	//Enero 	
	31 , 
 	//Febrero 	
	28,   // or 29 en año bisiesto
 	// Marzo 	
	31, 
 	// Abril 	
	30, 
 	// Mayo 	
	31, 
	// Junio 	
	30, 
	// Julio 	
	31, 
 	// Agosto 	
	31, 
	// Septiembre 	
	30, 
	// Octubre 
	31, 
	// Noviembre 	
	30, 
	// Diciembre 	
	31
}; 

const char days[][7] = {"mon", "tue", "wed", "thu", "fri", "sat", "sun"};

/**
 *	Método que compara fechas si (day1, month1, year1) > (day2, month2, year2) devuelve 1 
 *	si (day1, month1, year1) < (day2, month2, year2) devuelve -1 si (day1, month1, year1) = (day2, month2, year2) devuelve 0
 */
int cmpdates(int day1, int month1, int year1, int day2, int month2, int year2) {
	int cmpdates_r = 1;
	if(year1 < year2) {
		cmpdates_r = -1;
		
	} else if(year1 == year2) {
		if(month1 < month2) cmpdates_r = -1;
		else if(month1 == month2) {
			if(day1 < day2) cmpdates_r = -1;
			else if(day1 == day2) cmpdates_r  = 0;
		}
		
	} 

	return cmpdates_r;
}
unsigned isBisiesto( unsigned year) {
	unsigned isBisiesto_r = 0;
	if( year % 400 == 0 ) {
		isBisiesto_r =  1;

	} else if(year % 4 == 0 && year % 100 != 0) {
		isBisiesto_r =  1;
	}
	return isBisiesto_r;
}

unsigned getDaysOfMonth (unsigned month, unsigned year ) {
	unsigned days;
	if(month != 2) {
		days = dayByMonths[month - 1];
	}
	else if( !isBisiesto( year)) {
		days = 28;
	} else days = 29;
	return days;
}

unsigned getDaysOfYear(unsigned year) {
	unsigned days;
	if( isBisiesto( year) ) {
		days = 366;
	}
	else {
		days = 365;
	}
	return days;
}


int getNumDaysinterDates (int day_x, int month_x, int year_x, int day_y, int month_y, int year_y ) {
	int cmpdates_r ;
	int getNumDaysinterDates_r = 0;
	unsigned sum_days = 0;


	cmpdates_r = cmpdates(day_x, month_x, year_x, day_y, month_y, year_y ); 

	int day1, month1, year1, day2, month2, year2;

	if(cmpdates_r > 0)  {
		day1 = day_y; month1 = month_y; year1 = year_y;
		day2 = day_x; month2 = month_x; year2 = year_x;
		
	} else if(cmpdates_r < 0) {
		day1 = day_x; month1 = month_x; year1 = year_x;		
		day2 = day_y; month2 = month_y; year2 = year_y;
	} 
	
	// printf("Fechas: %u-%u-%u < %u-%u-%u\n", day1, month1, year1, day2, month2, year2);


	if(year1 == year2) {
		// Cuenta los dias  de year1		
		if(month1 == month2) {
			sum_days = day2 - day1;		
		}
		else {

			sum_days = sum_days + getDaysOfMonth (month1, year1 ) - day1 ; // cuenta los dias del primer mes

			// Cuenta los días que están entre el primero y el ultimo mes sin incluir ninguna de los dos
			for(int month=month1 + 1; month < month2; month++) { 

				sum_days = sum_days + getDaysOfMonth (month, year1 );

			}
			// Cuenta los días del ultimo mes
			sum_days = sum_days + day2;			

		}
	}		
	else  {

		// Cuenta los dias de year1
		// Cuenta los días del primer mes

 
		sum_days = sum_days + getDaysOfMonth (month1, year1 ) - day1 ; // cuenta los dias del primer mes

		for(int month=month1 + 1; month <= 12; month++) { // cuenta los días del resto de los meses 
			sum_days = sum_days + getDaysOfMonth (month, year1 );
		}
		
		// Suma los dias que estan entre los year1 y year2 pero sin incluir ninguno de los 2
		for(int year=year1 + 1; year < year2; year++) {
			sum_days = sum_days + getDaysOfYear(year) ; 
		}

		// Cuenta los días de year2
			
		for(int month = 1; month < month2; month++) {	// Cuenta los días del primer mes al ultimo sin incluir el ultimo
			sum_days = sum_days + getDaysOfMonth (month, year2 );
	
		}
		// Cuenta los días del ultimo mes

		sum_days = sum_days + day2;		


	}
	getNumDaysinterDates_r = sum_days;
	return getNumDaysinterDates_r;
}
unsigned getDay (unsigned day, unsigned month, unsigned year ) {
	unsigned numdays;
	int cmpdates_r;
	int day_f = ref_wday;

	numdays = getNumDaysinterDates (day_ref, month_ref, year_ref, day, month, year ) ;	
	cmpdates_r = cmpdates(day_ref, month_ref, year_ref, day, month, year  );


	if(cmpdates_r > 0) {
		day_f = ((7 - (numdays  % 7)) % 7 + ref_wday) % 7;

	} else if(cmpdates_r < 0) {
		day_f = ((numdays % 7) + ref_wday) % 7;
	}
	return day_f;

}



#define FORMAT_1 1
#define FORMAT_2 2

void printCalendar( unsigned day, unsigned month, unsigned year) {
	
	unsigned days_n = getDaysOfMonth (month, year );
	unsigned day_first = 	getDay (1, month, year );
	
	//char buffer[512];

	for(int day_week=0; day_week < 7; day_week++) {
		// imprime el primer dia del mes
		printf("%s", days[day_week]);

		unsigned flag = FORMAT_1;

		for(int day_month = 1; day_month <= days_n; day_month++ )  {

			char buffer[20];
			if(getDay (day_month, month, year ) == day_week && day_week < day_first ) {

				if(flag == FORMAT_1) { 
					if( day_month != day) printf("%5s%4d ", "", day_month);
					else { 

						sprintf (buffer, "[%2d]", day);
						printf("%5s%5s", "", buffer);
					}
					flag = FORMAT_2;
				}
				else  { 
				
					if( day_month != day) printf("%4d ", day_month);
					else { 
					
						sprintf (buffer, "[%2d]", day);
						printf("%5s", buffer);
					}

				}
			} else if( getDay (day_month, month, year ) == day_week) {
					if( day_month != day) printf("%4d ", day_month);
					else { 
					
						sprintf (buffer, "[%2d]", day);
						printf("%5s", buffer);
					}
			}

		}


		printf("\n");
	}	

}

int main (void) {
	unsigned day, month, year;
	

	scanf("%u%u%u", &day, &month, &year);
	
	printCalendar(day, month, year);

	return 0;
}


