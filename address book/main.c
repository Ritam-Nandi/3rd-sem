
/*Purpose : To implement Address book of a phone containing the names and numbers
 *The program should be capable of performing insertion ,searching ,modifications ,deletion and display
 *
 *Author : Ritam Nandi - 2BV14CS081
 *Author : Sudeshna Chakraborty - 2BV14CS111
 *
 *Date    : 07-10-2015 */

// Preprocessor directives
#include <stdio.h>
#include <malloc.h>
#include<string.h>

// Macros
#define NULL 0
#define naSize 20
#define nuSize 11

//structure for contact list
struct node
{
    struct contact//nested structure
    {
        char name[naSize];
        char number[nuSize];
    };

    struct contact data;
    struct node *next;
};

typedef struct node node;

/*Function : Count the total number of nodes
 *Input  : The linked list whose total number of nodes are to be calculated
 *Output : The integer value of the total number of nodes*/
int count_contact(node *head)
{
    int c=0;
    node *cur;
    cur=head;

    while(cur!=NULL){

        c++;                                        //counts each node
        cur=cur->next;
    }
    return c;
}

/*Function : Sort all the names alphabetically
 *Input  : The linked list which has to be sorted
 *Output : The sorted linked list */
node *sort(node *head)
{
    int i;
    int j;
    int n=count_contact(head);
    int k=n;
    node *p,*q;
    struct contact temp;

    for(i=0;i<n-1;i++,k--){

        p=head;
        q=p->next;

        for(j=1;j<k;j++){

            if(strcmp(p->data.name,q->data.name)>0){                    //sorting condition

                temp=p->data;
                p->data=q->data;
                q->data=temp;
            }
            p=p->next;
            q=q->next;
        }
    }

    return head;
}

/*Function : To check if the name entered by the user contains only alphabets or not
 *Input  : A character array that contains the name of the contact
 *Output : Returns an integer 1 if the name is invalid and 0 if it is valid*/
int validate_name(char name[naSize])
{
    int i,c=0,n=strlen(name);

    for(i=0;name[i]!=NULL;i++)
    {
        if(!((name[i]>='A'&&name[i]<='Z')||(name[i]>='a'&&name[i]<='z')))
         {
            c++;//increments if other than alphabets are found
            break;
         }
    }

    if(c==1)
        return 1;
    else
        return 0;
}

/*Function : To check if the number entered by the user contains only 10 digits
 *Input  : A character array that contains the number of the contact
 *Output : Returns an integer 1 if the number is invalid and 0 if it is valid*/
 int validate_number(char num[20])
{
    int i,c=0;

    for(i=0;num[i]!=NULL;i++)
    {
        if(num[i]>='0'&&num[i]<='9')
           c++;
    }

    if(c==10)
        return 0;
    else
        return 1;
}

/*Function : Insert the elements in a sorted order
 *Input  : The main linked list and structure containing a name and a number
 *Output : The linked list updated with the new contact information in the sorted order*/
node *L_INSERT(node *head,struct contact x)
{
    node *newnode;
    newnode=(node*)malloc(sizeof(node));
    newnode->data=x;
    newnode->next=head;

    sort(newnode);                                 //the new name is to be sorted after entering

    return newnode;                                //sorted linked list
}

/*Function : Load the data from the file into the linked list
 *Input  : void
 *Output : The linked list that contains all the data from the file*/
node *load()
{
    FILE *fp;
    int i=0;
    int j=0;
    node *head=NULL;
    struct contact x;

    fp=fopen("contact.txt","r");                              //open the file in read mode
    char ch,wor[naSize];

    while((ch=fgetc(fp))!=EOF){                               //extract each character till end of file

        if(ch!='\n'&&j==1)                                    //formation of the number part

            wor[i++]=ch;

        if(ch=='\n')                                          //end of the number part
        {
            j=0;
            wor[i]='\0';
            strcpy(x.number,wor);
            head=L_INSERT(head,x);                            //insert name and number to linked list
            i=0;
            strcpy(wor,"");
        }

        if(j==0&&ch!=':'&&ch!='\n')                           //formation of the name part

            wor[i++]=ch;

        if(ch==':')                                           //end of the name part
        {
            j++;
            wor[i]='\0';
            strcpy(x.name,wor);
            i=0;
            strcpy(wor,"");
        }

    }

    fclose(fp);                                               //saving the file
    return head;
}

/*Function : Search a given contact information in the linked list
 *Input  :  The main linked list and the name of the person
 *Output :  The Node containing the required name if name is found else a null Node*/
 node *LSEARCH(node *head,char name[naSize])
{
    node *cur,*temp;
    cur=head;

    while(cur!=NULL)
    {
        if(strcmp(name,(cur->data).name)!=0)
        {
            temp=cur;
            cur=cur->next;
        }
        else
            break;                                              //breaks if search value is found
    }

    return cur;
}

/*Function : Delete the elements from contact list
 *Input  :  The main linked list and the name of the person
 *Output :  The linked list with the required node deleted else if not matched then the original linked list*/
node *LDELETE(node *head,char name[naSize])
{
    node *cur,*temp;

    if(head==NULL){                                      //Phone book is empty

        printf("List is empty\n");
        return head;
    }
    cur=head;

    while(cur!=NULL){

        if(strcmp(name,cur->data.name)!=0)
        {
            temp=cur;
            cur=cur->next;
        }
        else
            break;
    }

    if(cur==NULL)                                        //not found
    {
        printf(" NO SUCH NAME AVAILABLE\n");
        return head;
    }
    printf("\n %s has been deleted from your contacts\n",cur->data.name);

    if(cur==head)                                       //first case
    {
        temp=head;
        head=head->next;
        free(temp);
        return head;
    }
    temp->next=cur->next;                               //all other cases
    free(cur);

    return head;
}

/*Function : Modify the elements from contact list based on name or number
 *Input  :  The main linked list and the structure containing the name and number
 *Output :  The linked list modified with the new values*/
node *LMODIFY(node *head,struct contact x)
{
    node *cur;
    int flag=0;
    if(head==NULL)                                      //Phone book is empty
    {
        printf("Phone book is empty\n");
        return head;
    }
    cur=head;

    while(cur!=NULL){

        if(strcmp(x.name,cur->data.name)==0)
        {
            strcpy(cur->data.number,x.number);
            flag=1;
        }
        cur=cur->next;

    }

    if(flag==0)
        printf(" Name not matched\n");

    sort(head);
    return head;
}

/*Function : Replace the existing name or number
 *Input  : The linked list , structure containing the name and number, character array containing the name or number, choice to modify
 *Output : The linked list with the changed values based on the input of the integer choice*/
node *LREPLACE(node *head,struct contact x,char inp[naSize],int c)
{
    node *cur;
    int flag=0;
    cur=head;

    while(cur!=NULL){

        if(c==1)                                //condition for name to match
        {
            if(strcmp(x.name,cur->data.name)==0)
            {
                strcpy(cur->data.number,inp);
                flag=1;
            }
        }

        if(c==2)                                //condition for number to match
        {
            if(strcmp(x.name,cur->data.name)==0)
            {
                strcpy(cur->data.name,inp);
                flag=1;
            }
        }
            cur=cur->next;

    }

    if(flag==0)
        printf("Search not matched\n");

    sort(head);
    return head;
}

/*Function :  Display all the contacts in the phone book
 *Input  : The main linked list
 *Output : void */
void display(node *head)
{
    node *cur;
    cur=head;
    char ch;
    char fin;
    int flag=0;
    int tmp=0;
    printf("--------------------------------------------------------------------------------\n");
    printf("\n\t\t\t\t  Displaying %d contacts\n",count_contact(head));
    printf("--------------------------------------------------------------------------------\n");

    while(cur!=NULL){

        ch=cur->data.name[0];

        if(tmp==0)                            //for first case only
        {
            tmp++;
            fin=ch;
        }

        if(flag==1&&ch!=fin)                  //when 2 names have the same staring alphabet
        {
             flag=0;
             fin=ch;

        }

        if(flag==0)                           //when 2 names have different starting alphabet
        {
            printf("\n\t\t\t\t%c\n\n",ch);
            flag=1;
        }

        printf("\t\tName : %s\tNumber : %s\n",cur->data.name,cur->data.number);
        cur=cur->next;
    }
    printf("\n----------------------------------------------------------------------------\n");
}

/*Function : Write the data back in the file from linked list
 *Input  : The main linked list
 *Output : void */
void reload(node *head)
{
    node *cur;
    FILE *fp;
    fp=fopen("contact.txt","w");                  //open the file in write mode

    if(fp==NULL)
    {
        printf("FILE cannot be opened\n");
        return;
    }
    cur=head;

    while(cur!=NULL){

        fprintf(fp,"%s",cur->data.name);            //store the name
        fprintf(fp,"%c",':');                       //store the separator
        fprintf(fp,"%s",cur->data.number);          //store the number
        fprintf(fp,"%c",'\n');                      //change line
        cur=cur->next;
    }

    fclose(fp);
}

/*Main function- The starting of the program
 *
 *Instructions - The  switch case provides a menu for calling all cases performed by the program
 *
 *The data is written in the file at the end of the program*/
void main()
{
    int i=0,j=0,k;
    node *head=NULL,*temp,*cur;
    struct contact x;
    char ch,name1[naSize],number1[nuSize];

    head=load();
    char inp[naSize];
    int choice=0,sub_choice;

    while(choice!=6)                              //Main Menu
    {
        printf("------------------------------\n");
        printf("1.Insert New Contact\n");
        printf("2.Modify Existing Contact\n");
        printf("3.Search A Contact\n");
        printf("4.Delete Existing Contact\n");
        printf("5.Display all contacts\n");
        printf("6.Exit\n");
        printf("------------------------------\n");

        printf("Enter your choice\n");
        scanf("%d",&choice);
        printf("\n");

        switch(choice)
        {

            case 1 : b1:printf("Enter Name\n");
                        scanf("%s",x.name);
                        k=validate_name(x.name);
                        if(k==1)
                        {
                             printf("\nPlease enter a valid name containing only alphabets\n\n");
                             goto b1;
                        }

                     b2:printf("Enter Number\n");
                        scanf("%s",x.number);
                        k=validate_number(x.number);
                        if(k==1)
                        {
                             printf("\nPlease enter a valid number containing 10 digits \n\n");
                             goto b2;
                        }

                     temp=LSEARCH(head,x.name);                     //Searching if the contact exists

                     if(temp!=NULL)
                     {
                         printf("\nName already exists in phone book\n");
                         printf("1.Replace existing number\n");
                         printf("2.Replace existing name\n");

                         scanf("%d",&sub_choice);

                         switch(sub_choice)
                         {
                             case 1:printf("Enter Number\n");
                                    k:
                                    scanf("%s",inp);
                                    if(strcmp(inp,x.number)==0)     //again enters the same number
                                    {
                                        printf("Please enter a different number\n");
                                        goto k;
                                    }

                                    head=LREPLACE(head,x,inp,sub_choice);
                                    break;

                             case 2:printf("Enter Name\n");
                                    l:
                                    scanf("%s",inp);
                                    if(strcmp(inp,x.name)==0)              //again enters the same name
                                    {
                                        printf("Please enter a different name\n");
                                        goto l;
                                    }

                                    head=LREPLACE(head,x,inp,sub_choice);
                                    break;

                             default:printf("Wrong choice has been entered\n");
                         }
                     }

                     else
                        head=L_INSERT(head,x);                             //Name has not matched
                     break;

            case 2:  b3:printf("Enter Name\n");
                        scanf("%s",x.name);
                        k=validate_name(x.name);
                        if(k==1)
                        {
                             printf("\nPlease enter a valid name containing only alphabets\n\n");
                             goto b3;
                        }

                     b4:printf("Enter Number\n");
                        scanf("%s",x.number);
                        k=validate_number(x.number);
                        if(k==1)
                        {
                             printf("\nPlease enter a valid number containing 10 digits \n\n");
                             goto b4;
                        }

                     head=LMODIFY(head,x);

                     break;

            case 3:  b5:printf("Enter Name\n");
                        scanf("%s",inp);
                        k=validate_name(inp);
                        if(k==1)
                        {
                             printf("\nPlease enter a valid name containing only alphabets\n\n");
                             goto b5;
                        }

                     if(head==NULL)
                        printf("Phone book is empty\n");

                     else{

                        temp=LSEARCH(head,inp);
                        if(temp!=NULL)
                            printf("Name : %s\tNumber : %s\n",temp->data.name,temp->data.number);
                        else
                            printf("Contact not found\n");
                     }
                     break;

            case 4:  b6:printf("Enter Name\n");
                        scanf("%s",inp);
                        k=validate_name(inp);
                        if(k==1)
                        {
                             printf("\nPlease enter a valid name containing only alphabets\n\n");
                             goto b6;
                        }
                     head=LDELETE(head,inp);                              //delete given name

                     break;

            case 5: display(head);
                    printf("\n");
                    break;

            case 6: break;

            default:printf("Wrong choice has been entered\n");

        }    //end of main switch
    }        //end of while loop

    reload(head);                                                     //writing the contents of list in the file

    printf("Exiting phonebook\n\n");

}            //end of main function
