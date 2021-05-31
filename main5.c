#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct request
{
int floorno;
int priority;
int flag_serviced;
struct request *next;
};

typedef struct request Req;
void add_inorder(Req**,int );
void print(Req*);
void divide_queue(Req**,int);
void call_lift1(int,Req**);
void call_lift2(int,Req**);
//static num;
//void sortByPrio(Req**,int count);
main()
{
char ch;
int num=0;
int count;
Req *headptr=0;
do
{
num=num+1;
add_inorder(&headptr,num);
printf("Y/y for more request");
scanf(" %c",&ch);
}while((ch=='y')||(ch=='Y'));
print(headptr);
count=num;
//printf("%d\n", count);
divide_queue(&headptr,count);
}

void add_inorder(Req **ptr,int num)
{
Req *temp;
static Req *temp1;

temp=malloc(sizeof(Req));
printf("Enter floor no\n");
scanf("%d",&temp->floorno);
temp->priority=num;
temp->flag_serviced=0;
/*if its the first entry or its value is less than the first entry*/
if(*ptr==0||temp->floorno<(*ptr)->floorno)
{
temp->next=*ptr;
*ptr=temp;
}

/*if its at the middle and end*/
else
{
temp1=*ptr;
while(temp1)
{
if(temp1->next==0)
{
temp1->next=temp;
temp->next=0;
break;
}
if(temp1->next->floorno>temp->floorno)
{
temp->next=temp1->next;
temp1->next=temp;
break;
}
temp1=temp1->next;
}
}
}

void print(Req *ptr)
{
while(ptr)
{
printf("Floor=%d\t",ptr->floorno);
printf("priority=%d\t",ptr->priority);
printf("Flag=%d\n",ptr->flag_serviced);
ptr=ptr->next;
}
}

void divide_queue(Req **ptr, int count)
{
int c=1;
int pos1, pos2, off1, off2,off3,off4;
Req *temp,*headptr1,*temp1,*headptr2;
temp=malloc(sizeof(Req));
temp1=malloc(sizeof(Req));
temp=*ptr;
headptr1=temp;
printf("count= %d\n",count);//Check the total no of requests received
while(c<count/2)// Upto half the floors, move the ptr
{
printf("c= %d\n",c);
temp=temp->next;
c++;
}
temp1=temp->next;//Save the floor next to exact half count into temp1. This is gonna be the head ptr for the next queue.
headptr2=temp1;//Next headptr
printf("Headptr for the 2nd queue=%d\n",headptr2->floorno);
printf("Headptr for the 1st queue=%d\n",headptr1->floorno);
temp->next=0;//Divided 1st and 2nd queue
while(temp1->next)//Now move the 2nd queue till it reaches null
temp1=temp1->next;
printf("last floor of 2nd queue=%d\n",temp1->floorno);
printf("last floor of 1st queue=%d\n",temp->floorno);
temp1->next=0;//2nd queue ends

printf("Printing 2nd queue...\n");
print(headptr2);//print whole of 2nd queue
printf("Printing first queue....\n");
print(headptr1);//print whole of first queue
/*Where are the lifts now?*/
printf("Enter lift 1 location..\n");
scanf("%d",&pos1);
printf("Enter lift 2 location...\n");
scanf("%d",&pos2);
/* calculate position of the two lifts from any one of the queue. We chose 2nd queue*/
off1=abs(headptr2->floorno-pos1);/*position of 1st lift with respect to 2nd queue*/
off2=abs(headptr2->floorno-pos2);/*position of 2nd lift with respect to 2nd queue*/
off3=abs(headptr1->floorno-pos1);/*position of 1st lift with respect to 1st queue*/
off4=abs(headptr1->floorno-pos2);/*position of 2nd lift with respect to 1st queue*/
/*if lift1 is at a greater distance from 2nd queue compared to 1st queue,and lift2 is also at a greater distance from 2nd queue compared to first queue, check which lift is at a smaller distance  call lift 2 for running 2nd queue and call lift 1 for running 1st queue*/
if(off1>off2)
{
call_lift1(pos1,&headptr1);//calling lift 1 for running 1st queue
call_lift2(pos2,&headptr2);//calling lift 2 for running 2nd queue
}
/* if lift2 is at a greater distance from 2nd queue compared to 1st queue, call lift1 for running 2nd queue and call lift 2 for running 1st queue....*/
else
{
call_lift1(pos1,&headptr2);
//print(headptr2);
call_lift2(pos2,&headptr1);
}
}


/*void sortByPrio( Req**ptr,int c)
{
int i,j;
Req *temp;
temp=malloc(sizeof(Req));
//temp=*ptr;
//ptr=(*ptr)->next
//temp1=
for(i=0;i<c-1;i++)
for(j=0;j<c-i-1;j++)
if((*ptr)->priority>(*ptr)->next->priority)
{
temp=*ptr;
*ptr=(*ptr)->next;
(*ptr)->next=temp;
} 
}*/

void call_lift1(int pos1,Req** headptr)
{
int time=0;
Req *temp;
temp=*headptr;
printf("I am in floor no %d, lift is in posn %d\n",(*headptr)->floorno,pos1);
while((*headptr)!=0)
{
if(pos1>(*headptr)->floorno)
{
while(pos1!=(*headptr)->floorno)
{
pos1--;
printf("Lift is moving down to get me... Its posn now is %d\n",pos1);
time=time+5;
printf("Time taken to move to %d floor is %d\n",pos1,time);
}
}

else
{
while(pos1!=(*headptr)->floorno)
{
pos1++;
printf("Lift is moving up to get me... Its posn now is %d\n",pos1);
time=time+5;
printf("Time taken to move to %d floor is %d\n",pos1,time);
}
(*headptr)->flag_serviced=1;
}

//delete_entry(())
//temp->next=(*headptr)->next;
if((*headptr)->flag_serviced==1)
{
(*headptr)=temp->next;
free(temp);
temp=(*headptr);
}
printf("Time=%d\n",time);
printf("Now the sequence is....\n");
print(*headptr);
}
}

void call_lift2(int pos1,Req** headptr)
{
int time=0;
Req *temp;
temp=*headptr;
printf("I am in floor no %d, lift is in posn %d\n",(*headptr)->floorno,pos1);
while((*headptr)!=0)
{
if(pos1>(*headptr)->floorno)
{
while(pos1!=(*headptr)->floorno)
{
pos1--;
printf("Lift is moving down to get me... Its posn now is %d\n",pos1);
time=time+5;
printf("Time taken to move to %d floor is %d\n",pos1,time);
}
}

else
{
while(pos1!=(*headptr)->floorno)
{
pos1++;
printf("Lift is moving up to get me... Its posn now is %d\n",pos1);
time=time+5;
printf("Time taken to move to %d floor is %d\n",pos1,time);
}
(*headptr)->flag_serviced=1;
}

//delete_entry(())
//temp->next=(*headptr)->next;
if((*headptr)->flag_serviced==1)
{
(*headptr)=temp->next;
free(temp);
temp=(*headptr);
}
printf("Time=%d\n",time);
printf("Now the sequence is....\n");
print(*headptr);
}
}



