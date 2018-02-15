#include <stdio.h>
#include <stdlib.h>

struct student
{
	long long roll;
	int day,month,year;
	char *attendance;
};
typedef struct student student;
long long converttoint(char  buff[100])
{
	int i=0;
	long long roll=buff[i]-48;
	i++;
	while(buff[i]!=',')
	{
		roll*=10;
		roll+=buff[i]-48;
		i++;
	}
	return roll;
}
 int  give_date(char* buff,int type)
 {
 	int date=0;
 	int i=0;
 	if(type==1)
 	{
 		for(int i=0;i<4;i++)
 		{
	 		date*=10;
	 		date+=buff[i]-48;
	 	}
	 	return date;
 	}
 	else if(type==2)
 	{
 		for(int i=5;i<7;i++)
 		{
 			date*=10;
 			date+=buff[i]-48;
 		}
 		return date;
 	}
 	else 
 	{
 		for(int i=8;i<10;i++)
 		{
 			date*=10;
 			date+=buff[i]-48;
 		}
 		return date;
 	}
 	return 0;
 }
void print(int data_set[],int strength)
{

	for(int i=0;i<strength;i++)
		printf("%d ",data_set[i]);
}
void print_struct(student * student_database,int rows)
{
	for(int i=0;i<rows;i++)
	{
		printf("%lld , %d/%d/%d, %s\n",student_database[i].roll,student_database[i].year,student_database[i].month,student_database[i].day,student_database[i].attendance);
	}
}
int main()
{
	FILE*fp,*fp2;
	char buff[20],temp[20];
	int rows=0,strength=0,index,classes=0;
	float class_threshold;
	long long current_roll_min=999999999,current_roll_max=0,roll_no,offset;
	fp=fopen("database_12jan2017.csv","r");
	while(!feof(fp))
	{
		fscanf(fp,"%s",buff);
		if(buff[0]!='P'&&buff[0]!='A')		
		{
			roll_no=converttoint(buff);
			rows++;
			if(roll_no>current_roll_max)current_roll_max=roll_no;
			else if(roll_no<current_roll_min)current_roll_min=roll_no;
		}
		fscanf(fp,"%s",buff);
		fscanf(fp,"%s",buff);
	}
	offset=current_roll_min;
	// printf("%lld %lld %d",current_roll_min,current_roll_max,rows);
	strength=current_roll_max-offset+1;
	classes=rows/strength;
	class_threshold=((float)classes/4)*3;
	// printf(" %d %lld %d %f",strength,offset,classes,class_threshold);
	int *data_set=(int*)malloc(sizeof(long long int)*(strength));
	student * student_database=(student*)malloc(sizeof(student)*rows);
    rewind(fp);
    int i=0;
	while(!feof(fp))
	{
		fscanf(fp,"%s",buff);
		if(buff[0]!='P'&&buff[0]!='A')		
		{
			roll_no=converttoint(buff);
			student_database[i].roll=roll_no;
			fscanf(fp,"%s",buff);
			student_database[i].day=give_date(buff,3);
			student_database[i].month=give_date(buff,2);
			student_database[i].year=give_date(buff,1);
			fscanf(fp,"%s",buff);
			if(buff[0]=='P')
				student_database[i].attendance="Present";
			else
				student_database[i].attendance="Absent";	
			index=roll_no-offset;
			if(buff[0]=='P')data_set[index]++;
			i++;
		}
	}
	fclose(fp);
	print(data_set,strength);
	fp=fopen("L75.csv","w");
	fp2=fopen("G75.csv","w");
	for(int i=0;i<strength;i++)
	{
		if(data_set[i]<class_threshold)
			fprintf(fp,"%lld , %d , %f\n",i+offset,data_set[i],((float)data_set[i]/(float)classes)*100);
		else
			fprintf(fp2,"%lld , %d , %f\n",i+offset,data_set[i],((float)data_set[i]/(float)classes)*100);
	}
	fclose(fp);
	fclose(fp2);
	printf("\n\n");
	print_struct(student_database,rows);
}