/*
Name: Sumit Subhash Jadhav(U89612131)
This program sorts top 10 cars with highest city miles per gallon (fuel economy) and lists them in a separate file.
*/
#include <stdio.h>
#include <string.h> //initializing the required libraries
#define maximum_length 150 //defining macros
#define CAR_LIST 1000   //should have been 6000 but showing 'segmentation fault'
struct car  //structure
{
    char Identification[maximum_length],Classification[maximum_length],Engine_Type[maximum_length],Transmission[maximum_length],Fuel_Type[maximum_length];
    int City_MPG,Highway_mpg;
};
int find_largest(struct car list[], int n)
{
	int i, max = 0;
	for(i = 1; i < n; i++)
	{
		if(list[i].City_MPG > list[max].City_MPG)
        {
			max = i;
        }
	}
	return max;
}
void sort_city_mpg(struct car list[], int n)
{
	struct car temp;
	int largest = 0;
	largest = find_largest(list, n);
	if(largest < n - 1) //just like the swap function that you all know and love <3
	{
		temp = list[n - 1];
		list[n - 1] = list[largest];
		list[largest] = temp;
	}
	if(n > 1)
		sort_city_mpg(list, n - 1);
}


int main()
{
    char InputName[maximum_length+1],OutputPrefix[]="Top10_city_mpg.csv";
    FILE *rFile;
    FILE *wFile;
    struct car list[CAR_LIST];
    printf("Enter input file: ");   //Requesting Input filename
    scanf("%s",InputName);
    rFile=fopen(InputName,"r"); //Opening and checking Input file
    if(rFile==NULL)
    {
        printf("Error opening the input file");
        return 1;
    }
    printf("Output file is: %s",OutputPrefix);

    wFile=fopen(OutputPrefix,"w");  //creating a new file with specified output name
    int j=0;
    while(!feof(rFile)&&!ferror(rFile))
    {
        if(fscanf(rFile,"%[^,], %[^,], %[^,], %[^,], %d, %[^,], %d\n", list[j].Identification, list[j].Classification, list[j].Engine_Type, list[j].Transmission, &list[j].City_MPG, list[j].Fuel_Type, &list[j].Highway_mpg)==7)
        {
            j++;
        }
    }
    sort_city_mpg(list,j);
	int a;
	for(a = j - 1; a > j - 11; a--)
	{
        fprintf(wFile, "%s, %s, %s, %s, %d, %s, %d\n", list[a].Identification, list[a].Classification, list[a].Engine_Type, list[a].Transmission, list[a].City_MPG, list[a].Fuel_Type, list[a].Highway_mpg);
	}

    fclose(rFile);
    fclose(wFile);  //closing both input and output files
    return 0;
}
