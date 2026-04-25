#include <stdio.h>
#include <unistd.h>
#include "file.h"

//functions to save all contacts into csv file.
void saveContactsToFile(AddressBook *addressBook) 
{
  FILE *fptr; 
  //open file in write mode and checking file.
  if((fptr=fopen("contact.csv", "w"))==NULL)
  {
    fprintf(stderr, "File not found\n");
    return;
  }

  for(int i=0; i<addressBook->contactCount; i++)
  {
    //write name, phone number, email in csv format.
    fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
  }

  
  for(int i=0; i<=100; i++)
  {
    printf("Saving---->%d\r", i);
    fflush(stdout);
    usleep(5000);
  }
  printf("Contact saved successfully\n");
  
  fclose(fptr);
}

//function to load contacts from csv file
void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fptr;
    //opening file in read mode and checking file.
    if((fptr=fopen("contact.csv", "r"))==NULL)
    {
        fprintf(stderr, "File not found\n");
        return;
    }
    
    //read each contact until end of file.
    while((fscanf(fptr,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[addressBook->contactCount].name,addressBook->contacts[addressBook->contactCount].phone,addressBook->contacts[addressBook->contactCount].email))==3)
    {
        addressBook->contactCount++;//increase contactcount after reading
    }

    fclose(fptr);
}
