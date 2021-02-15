#include<stdio.h>
#include<math.h>
#include <dos.h>
int a[13],b[13],c[13];
static int atop,btop,ctop,false_move=3,move=0,disks;
void play();
void display();
char pop();

int main()
{
	int return_val,i;
	return_val=intro();
	if(return_val==0)
	{
	for(i=0;i<2;i++)
	{
		Beep(2000,60);
		Beep(200,30);	
	}
	Beep(3000,200);	
	
	return 0;
	}
}

int intro() //function for main menu
{
	int choice,i,j;
	char enter,key;
				Beep(900,100);	
				Beep(1000,50);
				Beep(1100,50);
	system("cls");
	printf("\n***WELCOME TO TOWER OF HANOI***\n\nPress 1 to start the game\n\nPress 2 to display the rules\n\nPress 3 to exit\n\n");
	btop=-1;
	ctop=-1;
	atop=0;
	b[btop]=0;
	c[ctop]=0;
	for(j=0;j<13;j++)
	{
		a[j]=0;
		b[j]=0;
		c[j]=0;
	}
	do{
	scanf("\n%d",&choice);
	scanf("%c",&enter);
	Beep(600, 90);
	}while((choice<1)||(choice>3));

	switch(choice)
	{
		case 1: //case for play
			{	
			system("cls");
			play();
			break;	
			}
			
		case 2: //case for rules
			{
			system("cls");
			printf("\n\t\t\t  ***RULES***\n\nTower of Hanoi is a mathematical puzzle, where we have three rods and n disks. On the leftmost rod, disks are arranged largest on the bottom to smallest on top placed on the rod. The Game is to transfer the disks to the rightmost rod, while only one disk can be moved at a time and a larger disk should not be kept above a smaller disk.\n");
			printf("Disks of different sizes are represented using numbers. Higher the value of the number, larger the size of the disk.\n\n");
			for(i=1;i<=3;i++)
			{
				printf("\t%d\n",i);
			}
			printf("      *****   *****   *****\n");
			printf("\tA\tB\tC");
			printf("\n\nYou can specify FROM-ROD and TO-ROD but it should obey the rules.\n\n  1. THE LARGER NUMBER SHOULD NOT COME ABOVE THE SMALLER NUMBER.");
			printf("\n\n  2. YOU HAVE ONLY 3 LIFE, INVALID MOVES WILL REDUCE YOUR LIFE.");
			printf("\n\nYou can choose the level from 1 to 10, Higher the levels number of disks is will be more.");
			printf("\n\n \"One who transfers all the disks from rod A to rod B with minimum moves will get the highest score.\"");
			printf("\n\nPress Any Key To Return To Main Menu");
			scanf("%c",&key);
			Beep(600, 90);
			intro();
			break;
			}
				
		case 3: //case for exit
			{
				system("cls");
				printf("\n!!! EXITED FROM THE GAME !!!");
				return 0;
				break;
			}
		
		default: //default case
			{
				printf("\nERROR...Invalid choice!!!");
				intro();
				break;
			}
	}
	
	return 1;
}

void play() //function for playing game
{
	int i,j,score,level;
	char ch,enter,key;
	false_move=3;
	printf("\n\t\t     !!! LET'S PLAY !!!\n");
				Beep(900,100);	
				Beep(1200,50);
				Beep(1000,100);
	do
	{
	printf("\nEnter The Level You Want To Play (choose from 1-10):");
	scanf("%d",&level);
	scanf("%c",&enter);
	Beep(600, 90);
	}while((level<1)||(level>10));
	
	disks=level+2;
	j=disks;
	for(i=0;i<disks;i++)
	{
		a[i]=j;
		j--;
	}
	atop=i-1;

	do
	{
		display();
		ch=pop();
		move++;
	}while(ch=='R'&&false_move>0);
	
	system("cls");
	
	if(ch=='E')
	{
		printf("EXITING THE GAME...");
	}
	else if(ch=='W')
	{
		display();
		printf("\n\n\n\n\t\t\tYOU WON THE GAME!!!\n\n");
		score=100-(move-(pow(2,disks)-1))*3+(-3+false_move)*5; /*finding out the score*/
		printf("\t\t\t YOUR SCORE IS %d\n\n",score);
		for(i=0;i<2;i++)
		{
		Beep(400,60);
		Beep(800,100);	
		Beep(700,100);
		}
	}
	
	if(false_move==0)
	{
		printf("\nSORRY YOU FAILED...NO LIFE LEFT!!!");
		for(i=0;i<2;i++)
		{
		Beep(700,100);
		Beep(1000,100);
		Beep(1400,60);	
		}
	}
	
	printf("\n\nPress Any Key To Return To Main Menu");
	scanf("%c",&key);
	Beep(600, 90);
	intro();
}

void display() //function for displaying stack of disks
{
	int i;
	system("cls");
	printf("\nLIFE:");
	for(i=1;i<=false_move;i++)
	{
		printf(" I");
	}
	printf("\n");
	for(i=disks;i>=0;i--) //reverse printing
	{
		if(a[i]!=0)
			printf("\t%d",a[i]); /*only want to print non zero values*/
		else
			printf("\t ");
				
		if(b[i]!=0)
			printf("\t%d",b[i]);
		else
			printf("\t ");
			
		if(c[i]!=0) 
			printf("\t%d",c[i]); 
		else
			printf("\t ");
			
		printf("\n");
	}
	printf("      *****   *****   *****\n");
	printf("\tA\tB\tC");
	return;
}

char pop() /*function to pop a disk from a rod and to push it to the specified rod*/
{
	char from,to,arr[2];
	int i;
	printf("\n\nENTER FROM-ROD AND TO-ROD:");
	gets(arr);
	Beep(900, 40);
	from=arr[0];
	to=arr[1];
	
	if(from=='E'||to=='E'||from=='e'||to=='e') /*to check return condition*/
	{
		return 'E';
	}

	if(from=='A' && to=='B')	   //case1: A->B
	{
		/*condition that to be statisfied inorder for pop and push operation*/
		if( (a[atop]!=0) && (b[btop]>a[atop] || b[btop]==0) ) 
		{
	 		b[++btop]=a[atop];
			a[atop]=0;
			atop--;
		}
		else 
		{
			false_move--; /*otherwise considered as false move*/
			for(i=0;i<3;i++)
			{
			Beep(1000,100);	
			}
		}
	}
	else if(from=='B' && to=='C')  //case2: B->C
	{
		if((b[btop]!=0) && (c[ctop]>b[btop] || c[ctop]==0))
		{
	 		c[++ctop]=b[btop];
			b[btop]=0;
			--btop;
		}
		else
		{
			false_move--;
			for(i=0;i<3;i++)
			{
			Beep(1000,100);	
			}
		}
	}
	else if(from=='C' && to=='A')  //case3: C->A
	{
		if(c[ctop]!=0 && (a[atop]>c[ctop] || a[atop]==0))
		{
	 		a[++atop]=c[ctop];
			c[ctop]=0;
			--ctop;
		}
		else
		{
			false_move--;
			for(i=0;i<3;i++)
			{
			Beep(1000,100);	
			}
		}
	}
	else if(from=='B' && to=='A')  //case4: B->A
	{
		if(b[btop]!=0 && (a[atop]>b[btop] || a[atop]==0))
		{
	 		a[++atop]=b[btop];
			b[btop]=0;
			--btop;
		}
		else
		{
			false_move--;
			for(i=0;i<3;i++)
			{
			Beep(1000,100);	
			}
		}
	}
	else if(from=='C' && to=='B')  //case5: C->B
	{
		if(c[ctop]!=0 && (b[btop]>c[ctop] || b[btop]==0))
		{
	 		b[++btop]=c[ctop];
			c[ctop]=0;
			--ctop;
		}
		else
		{
			false_move--;
			for(i=0;i<3;i++)
			{
			Beep(1000,100);	
			}
		}
	}
	else if(from=='A' && to=='C') //case6: A->C
	{
		if(a[atop]!=0 && (c[ctop]>a[atop] || c[ctop]==0))
		{
	 		c[++ctop]=a[atop];
			a[atop]=0;
			--atop;
		}
		else
		{
			false_move--;
			for(i=0;i<3;i++)
			{
			Beep(1000,100);	
			}
		}
	}
	else
	{
		false_move--;
		for(i=0;i<3;i++)
		{
		Beep(1000,100);	
		}
	}

	if(ctop==disks-1) /*Winning condition*/
	{
	 return 'W';
	}
	
	return 'R';
}
