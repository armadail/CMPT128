#include <stdio.h>

int main()
{
	float week;
	float day;
	float hour;
	float min;

	printf("Please enter the number of weeks:");
	scanf_s("%f", & week);
	printf("THE INPUT NUMBER OF WEEKS IS %.3f", week);

	day = week * 7;
	hour = week * 7 * 24;
	min = week * 7 * 24 * 60;

	printf("\n the equivalent number of days is %.2f\n\n ", day);

	printf("the equivalent number of hours is %.2f\n\n ", hour);

	printf("the equivalent number of minuites is %.2f\n\n ", min);

	printf("%f weeks is \n", week);

	int day2;
	int hour2;
	float min2;
	
	//23.65432

	day2 = week * 7;
	hour2 = ( week * 7 * 24 ) - (day2 * 24);
	min2 = (week * 7 * 24 * 60) - (hour2 * 60) - (day2 * 24 * 60);
	

	

	printf("DAYS        ");
	printf("%d\n", day2);

	printf("HOURS       ");
	printf("%d\n", hour2);

	printf("MINUITES    ");
	printf("%.4f\n", min2);
	
	return 0;
}
