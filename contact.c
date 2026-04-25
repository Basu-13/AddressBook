#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria

    //sorted contacts using bubble sort.
    for(int i=0; i<addressBook->contactCount-1; i++)
    {
        for(int j=0; j<addressBook->contactCount-1-i; j++)
        {
            if(strcmp(addressBook->contacts[j].name, addressBook->contacts[j+1].name)>0)
            {
                //swapping of contacts 
                Contact temp=addressBook->contacts[j];
                addressBook->contacts[j]=addressBook->contacts[j+1];
                addressBook->contacts[j+1]=temp;
            }
        }
    }

    printf("<------------------------------------------------------------------------->\n");
    printf("                           Contact details                                 \n");
    printf("<------------------------------------------------------------------------->\n");
    printf("%-4s %-15s %-15s %-30s\n", "S.no", "Name", "P.no", "Email");
    printf("<------------------------------------------------------------------------->\n");
    for(int i=0; i<addressBook->contactCount; i++)
    {
        //printing the contact list using loop.
        printf("%-4d %-15s %-15s %-30s\n", i+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    printf("<-------------------------------------------------------------------------->\n");   
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program

}

void validName(AddressBook *addressBook, char *newName)
{
    //name validation
    char Name[50]; 
    int flag;

    while(1)
    {
        printf("Enter the name: ");
        scanf(" %[^\n]", Name);

        flag=1;
        //validating name only alphabates, space and dot allowed.
        for(int i=0; Name[i] != '\0'; i++)
        {
            if(Name[i] >= 'a' && Name[i] <='z' || Name[i] >= 'A' && Name[i] <= 'Z')
            {
                continue;
            }
            else if(Name[i] == ' ' || Name[i] == '.') 
            {
                continue;
            }
            else
            {
                flag=0;
                break;
            }
        }
        if(flag==0)
        {
            printf("Invalid name\n");
            printf("\n");
            continue;
        }

        flag=1;
        //check for duplicate name in addressbook
        for(int i=0; i<addressBook->contactCount; i++)
        {
            if(strcmp(Name, addressBook->contacts[i].name)==0)
            {
                flag=0;
                break;
            }
        }
        
        if(flag == 0)
        {
            printf("<------------------------------------------------------------------------->\n");
            printf("            Name is already exists in the addressBook              \n");
            printf("<------------------------------------------------------------------------->\n");
            continue;
        }
        
        //copy validated name to newName.
        strcpy(newName, Name);
        printf("Name is valid\n");
        printf("\n");
        return;
    }
}

void validPhone(AddressBook *addressBook, char *newPhone)
{
    //phone number validation
    char Phone[50];
    int flag;

    while(1)
    {
        printf("Enter the phone number: ");
        scanf(" %[^\n]", Phone);

        flag=1;
        //checking the length of the phone number.
        if(strlen(Phone) != 10)
        {
            printf("Length should be 10\n");
            printf("\n");
            continue;
        }
        
        flag=1;
        //check phone number should have only digits.
        
        for(int i=0; Phone[i] != '\0'; i++)
        {
            if(!(Phone[i] >= '0' && Phone[i] <= '9'))
            {
                flag=0;
                printf("phone number should contain numbers only\n");
                printf("\n");
                break;
            }
            
        }
        
        if(flag == 0)
        {
            printf("Invalid contact\n");
            printf("\n");
            continue;
        }

        flag=1;
        //check for duplicate phone number in the addresssbook.
        for(int i=0; i<addressBook->contactCount; i++)
        {
            if(strcmp(Phone, addressBook->contacts[i].phone)==0)
            {
                flag=0;
                break;
            }
        }
        if(flag == 0)
        {
            printf("<------------------------------------------------------------------------->\n");
            printf("             phone number is already exists in the addressBook             \n");
            printf("<------------------------------------------------------------------------->\n");
            continue;
        }

        //copy validates phone number to newPhone.
        strcpy(newPhone, Phone);
        printf("Phone number is valid\n");
        printf("\n");
        return;
    }
}

void validEmail(AddressBook *addressBook, char *newEmail)
{
    //email validation
    char Email[50];
    int flag;

    while(1)
    {
        printf("Enter the email: ");
        scanf(" %[^\n]", Email);

        flag=1;
        int len=strlen(Email);

        //check for spaces in email.
        for(int i=0; i<len; i++)
        {
            if(Email[i] == ' ')
            {
                flag=0;
                break;
            }
        }
        if(flag == 0)
        {
            printf("Invalid Email no space allowed\n");
            printf("\n");
            continue;
        }


        int atIndex=0;
        int atFound=0;
        //check for exactly one @ symbol.
        for(int i=0; i<len; i++)
        {
            if(Email[i] == '@')
            {
                atFound++;
                atIndex=i;
            }
        }

        if(atFound != 1 || atIndex == 0 || atIndex == len - 1)
        {
            printf("Invalid Email\n");
            printf("\n");
            continue;
        }

        //validate characters before @.
        if(Email[atIndex-1] == '.' || Email[0] == '.' || Email[0] == '_' || Email[atIndex-1] == '_')
        {
            printf("cannot start with or end with dot\n");
            printf("\n");
            continue;
        }

        //validate domain and extension afetr @.
        for(int i=0; i<atIndex; i++)
        {
            if(!((Email[i] >= 'a' && Email[i] <= 'z') ||
                 (Email[i] >= '0' && Email[i] <= '9') ||
                  Email[i] == '.' || Email[i] == '_'))
            {
                flag=0;
                break;
            }
        }
        if(flag == 0)
        {
            printf("Invalid characters before @\n");
            printf("\n");
            continue;
        }

        

        int dotFound=0; 
        int dotIndex=0;

        //check dot afetr domain.
        for(int i=atIndex+1; i<len; i++)
        {
            if(Email[i] == '.')
            {
                dotFound=1;
                dotIndex=i;
                break;
            }
        }

        if(dotIndex == 0 || dotIndex == atIndex+1 || dotIndex == len - 1)
        {
            printf("Invalid Email\n");
            printf("\n");
            continue;
        }

        //checking only alphabates between @ and dot.
        for(int i=atIndex+1; i<dotIndex; i++)
        {
            if(!(Email[i] >= 'a' && Email[i] <= 'z'))
            {
                flag=0;
                break;
            }
        }
        if(flag == 0)
        {
            printf("Invalid Email\n");
            printf("\n");
            continue;
        }

        flag=1;
        //check alphabates after dot.
        for(int i=dotIndex+1; i<len; i++)
        {
            if(!(Email[i] >= 'a' && Email[i] <= 'z'))
            {
                flag=0;
                break;
            }
        }
        if(flag == 0)
        {
            printf("Invalid Email\n");
            continue;
        }

        flag=1;
        //validate duplicate email in the addressbook.
        for(int i=0; i<addressBook->contactCount; i++)
        {
            if(strcmp(Email, addressBook->contacts[i].email)==0)
            {
                flag=0;
                break;
            }
        }
        if(flag == 0)
        {
            printf("<------------------------------------------------------------------------->\n");
            printf("                Email is already existed in the addressBook                \n");
            printf("<------------------------------------------------------------------------->\n");
            continue;
        }

        //copy validate email to newEmail.
        strcpy(newEmail, Email);
        printf("Email is valid\n");
        printf("\n");
        return;
    }
}

void createContact(AddressBook *addressBook)
{

	/* Define the logic to create a Contacts */
    printf("<------------------------------------------------------->\n");
    printf("                     CREATE CONTACT                      \n");
    printf("<------------------------------------------------------->\n");

    char Name[100], Phone[100], Email[100];

    //validate for name, phone number nad email.
    validName(addressBook, Name);

    validPhone(addressBook, Phone);
    
    validEmail(addressBook, Email);

    //store name, phone number and email in the addressBook.

    strcpy(addressBook->contacts[addressBook->contactCount].name, Name);
    

    strcpy(addressBook->contacts[addressBook->contactCount].phone, Phone);
    

    strcpy(addressBook->contacts[addressBook->contactCount].email, Email);

    printf("<------------------------------------------------------->\n");
    printf("             Contact stored successfully                 \n");
    printf("<------------------------------------------------------->\n");

    //increment contactCount to store new contact.
    addressBook->contactCount++;
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int choice;
    char str[100];

    printf("<------------------------------------------------------->\n");
    printf("                      Search Contact                     \n");
    printf("<------------------------------------------------------->\n");
    printf("1. search by name\n");
    printf("2. search by mobile number\n");
    printf("3. search by email\n");
    printf("enter your choice");
    scanf("%d", &choice);

    int dup_index[100];
    int dup_count=0;

    //search contact by name, phone number and email.
    switch(choice)
    {
        case 1:
            printf("Enter the name: ");
            scanf(" %[^\n]", str);
        
            //to search name
            for(int i=0; i<addressBook->contactCount; i++)
            {
                char* res=strstr(addressBook->contacts[i].name, str);
                if(res != NULL)
                {
                    dup_index[dup_count]=i;
                    dup_count++;
                }
            }
        break;

        case 2:
            printf("Enter the phone number: ");
            scanf(" %[^\n]", str);

            //to search phone number.
            for(int i=0; i<addressBook->contactCount; i++)
            {
                int res=strcmp(addressBook->contacts[i].phone, str);
                if(res==0)
                {
                    dup_index[dup_count]=i;
                    dup_count++;
                }
            }
        break;

        case 3:
            printf("Enter the email: ");
            scanf(" %[^\n]", str);

            //to search email.
            for(int i=0; i<addressBook->contactCount; i++)
            {
                int res=strcmp(addressBook->contacts[i].email, str);
                if(res==0)
                {
                    dup_index[dup_count]=i;
                    dup_count++;
                }
            }
        break;

        default:
            printf("Invalid input\n");
            return;
    }

    if(dup_count == 0)
    {
        printf("Contact not found\n");
        return;
    }

    //store matching contacts indices and print them.
    printf("<------------------------------------------------------->\n");
    printf("%-4s  %-15s %-15s %-30s\n", "S.No", "Name", "P.no", "Email");
    printf("<------------------------------------------------------->\n");
    for(int i=0; i<dup_count; i++)
    {
        int idx=dup_index[i];
        printf("%-4d  %-15s %-15s %-30s\n", i+1, addressBook->contacts[idx].name, addressBook->contacts[idx].phone, addressBook->contacts[idx].email);
    }
    printf("<------------------------------------------------------->\n");

    return;
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int choice;
    char str[100];

    while(1)
    {
        printf("<------------------------------------------------------->\n");
        printf("                       Edit Contact                      \n");
        printf("<------------------------------------------------------->\n");
        printf("1. search by name\n");
        printf("2. search by number\n");
        printf("3. search by email\n");
        printf("Enetr the choice: ");
        scanf("%d", &choice);

        int dup_index[100];
        int dup_count=0;

        //search contacts by name, phone number and email to edit.
        switch(choice)
        {
            case 1:
                printf("Enter the name to edit: ");
                scanf(" %[^\n]", str);

                //search by name.
                for(int i=0; i<addressBook->contactCount; i++)
                {
                    char* res=strstr(addressBook->contacts[i].name, str);
                    if(res != NULL)
                    {
                        dup_index[dup_count]=i;
                        dup_count++;
                    }
                }
            break;

            case 2:
                printf("Enter the number to edit: ");
                scanf(" %[^\n]", str);

                //search by phone number.
                for(int i=0; i<addressBook->contactCount; i++)
                {
                    int res=strcmp(addressBook->contacts[i].phone, str);
                    if(res == 0)
                    {
                        dup_index[dup_count]=i;
                        dup_count++;
                    }
                }
            break;

            case 3:
                printf("Enter the email to edit: ");
                scanf(" %[^\n]", str);

                //search by email.
                for(int i=0; i<addressBook->contactCount; i++)
                {
                    int res=strcmp(addressBook->contacts[i].email, str);
                    if(res == 0)
                    {
                        dup_index[dup_count]=i;
                        dup_count++;
                    }
                }
            break;

            default:
                printf("Invalid input\n");
                continue;
        }

        if(dup_count == 0)
        {
            printf("Contact not found\n");
            printf("\n");
            continue;
        }

        int index;
        //handle multiple selection and print multiple contacts based on indexes.
        if(dup_count >= 1)
        {
            printf("<------------------------------------------------------->\n");
            printf("%-4s  %-15s %-15s %-30s\n", "S.No", "Name", "P.no", "Email");
            printf("<------------------------------------------------------->\n");
            for(int i=0; i<dup_count; i++)
            {
                int idx=dup_index[i];
                printf("%-4d  %-15s %-15s %-30s\n", i+1, addressBook->contacts[idx].name, addressBook->contacts[idx].phone, addressBook->contacts[idx].email);
            }
            printf("<------------------------------------------------------->\n");

            //choosing contacts by user.
            int choose;
            printf("Enter which one do you want to edit (1 to %d): ", dup_count);
            scanf("%d", &choose);

            if(choose < 1 || choose > dup_count)
            {
                printf("Invalid selection\n");
                continue;
            }

            index=dup_index[choose - 1];
        }
        else
        {
            index=dup_index[0];
        }

        int editchoice;
        printf("Enter what do you to edit\n");
        printf("1. Edit by name\n");
        printf("2. Edit by phone number\n");
        printf("3. Edit by email\n");
        printf("Enter the editchoice: ");
        scanf("%d", &editchoice);

        char newname[100];
        char newphone[100];
        char newemail[100];

        //edit by name, phone number and email.
        switch(editchoice)
        {
            case 1:

                //check valid name and update contact.
                validName(addressBook, newname);
                strcpy(addressBook->contacts[index].name, newname);
            break;

            case 2:

                //check valid phone number and update contact.
                validPhone(addressBook, newphone);
                strcpy(addressBook->contacts[index].phone, newphone);
            break;

            case 3:

                //check valid email and update contact.
                validEmail(addressBook, newemail);
                strcpy(addressBook->contacts[index].email, newemail);
            break;

            default:
                printf("Invalid input\n");
        }
        //updated contact list.
        printf("<------------------------------------------------------->\n");
        printf("            Contact updated successfully                 \n");
        printf("<------------------------------------------------------->\n");

        printf("<------------------------------------------------------->\n");
        printf("%-15s %-15s %-30s\n", addressBook->contacts[index].name, addressBook->contacts[index].phone, addressBook->contacts[index].email);
        printf("<------------------------------------------------------->\n");
        return;

    }
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int choice;
    char str[100];

    printf("<------------------------------------------------------->\n");
    printf("                      Delete Contact                     \n");
    printf("<------------------------------------------------------->\n");
    printf("1. search by name\n");
    printf("2. search by number\n");
    printf("3. search by email\n");
    printf("Enetr the choice: ");
    scanf("%d", &choice);

    int dup_index[100];
    int dup_count=0;

    //search by name, phone number and email to delete.
    switch(choice)
    {
        case 1:
            printf("Enter the name to delete: ");
            scanf(" %[^\n]", str);

            //search by name.
            for(int i=0; i<addressBook->contactCount; i++)
            {
                char* res=strstr(addressBook->contacts[i].name, str);
                if(res != NULL)
                {
                    dup_index[dup_count]=i;
                    dup_count++;
                }
            }
        break;

        case 2:
            printf("Enter the number to delete: ");
            scanf(" %[^\n]", str);

            //search by phone number.
            for(int i=0; i<addressBook->contactCount; i++)
            {
                int res=strcmp(addressBook->contacts[i].phone, str);
                if(res == 0)
                {
                    dup_index[dup_count]=i;
                    dup_count++;
                }
            }
        break;

        case 3:
            printf("Enter the email to delete: ");
            scanf(" %[^\n]", str);

            //search by email.
            for(int i=0; i<addressBook->contactCount; i++)
            {
                int res=strcmp(addressBook->contacts[i].email, str);
                if(res == 0)
                {
                    dup_index[dup_count]=i;
                    dup_count++;
                }
            }
        break;

        default:
            printf("Invalid input\n");
            return;
    }

    if(dup_count == 0)
    {
        printf("Contact not found\n");
        return;
    }

    int pos;
    //find matching duplicate contacts and printing them.
    if(dup_count >= 1)
    {
        printf("<------------------------------------------------------->\n");
        printf("%-1s    %-15s %-15s %-30s\n", "S.No", "Name", "P.no", "Email");
        printf("<------------------------------------------------------->\n");

        for(int i=0; i<dup_count; i++)
        {
            int idx=dup_index[i];
            printf("%-1d -> %-15s %-15s %-30s\n", i+1, addressBook->contacts[idx].name, addressBook->contacts[idx].phone, addressBook->contacts[idx].email);
        }
        printf("<------------------------------------------------------->\n");

        //ask user to select contacts for delete.
        int choose;
        printf("Enter which one you want to  delete (1 to %d): ", dup_count);
        scanf("%d", &choose);

        if(choose < 1 || choose > dup_count)
        {
            printf("Invalid selection\n");
            return;
        }

        pos=dup_index[choose - 1];
    }
    else
    {
        pos=dup_index[0];
    }

    char ch;
    printf("Which contact do you want to delete (y/Y): ");
    scanf(" %c", &ch);

    //shift contacts to remove selected contacts.
    if(ch == 'y' || ch == 'Y')
    {
        for(int i=pos; i<addressBook->contactCount-1; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }
        addressBook->contactCount--;

        printf("<------------------------------------------------------->\n");
        printf("               Contact deleted successfully               \n");
        printf("<------------------------------------------------------->\n");
    }
    else
    {
        printf("<------------------------------------------------------->\n");
        printf("                   Delete cancelled                      \n");
        printf("<------------------------------------------------------->\n");
    }
    return;
}