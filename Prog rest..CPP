#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<dos.h>
#include<iomanip.h>
#include<process.h>
#include<ctype.h>

class MyFood
{
  int FCODE;
  char FOOD[100];
  char type[100];
  char catg[100];
  int PRICE;
public:
  void editcode();
  void Getdata()
  {
    cout<<"FCODE     : ";
    cin>>FCODE;
    cout<<"TYPE	     : ";
    gets(type);
    cout<<"Category  : ";
    gets(catg);
    cout<<"Food Name : ";
    gets(FOOD);
    cout<<"Price     : ";
    cin>>PRICE;
  }
  void Showdata()
  {
    cout<<FCODE<<setw(18)<<type<<setw(14)<<catg
    <<setw(26)<<FOOD<<setw(12)<<"Rs."<<PRICE<<endl;
  }
  int retFCODE()
  {return FCODE;}
  char *rettype()
  {return type;}
  char *retcatg()
  {return catg;}
  char *retFOOD()
  {return FOOD;}
  int retPRICE()
  { return PRICE;}
};

void MyFood::editcode()
{
  cout<<"Code           :"<<FCODE<<endl;
  cout<<"Type	        :"<<type<<endl;
  cout<<"Category       :"<<catg<<endl;
  cout<<"Food name      :"<<FOOD<<endl;
  cout<<"Existing Price :"<<PRICE<<endl;
  cout<<"Revised Price  :";
  cin>>PRICE;
}

void ADD()
{
  textcolor(2);
  textbackground(14);
  fstream fil1;
  fil1.open("Food.dat",ios::binary|ios::app);
  MyFood B;
  char ch;
  do
  {
    B.Getdata();
    fil1.write((char*)&B,sizeof(B));
    cout<<"Want to add more...(y/n):";cin>>ch;
    ch=toupper(ch);
  }
  while(ch=='Y');
  fil1.close();
}

void DISPLAY()
{
  textcolor(5);
  textbackground(0);
  fstream fil;
  fil.open("Food.dat", ios::binary|ios::in);
  MyFood B;
  int trec=0;
  cout<<"FCODE"<<setw(14)<<"TYPE"<<setw(13)<<"CATEGORY"<<setw(20)
  <<"FOOD"<<setw(21)<<"PRICE"<<endl;
  while (fil.read((char*)&B, sizeof(B)))
  {
    B.Showdata();
    trec++;
  }
  fil.close();
  cout<<endl<<endl<<endl;
  cout<<"Total records:"<<trec;
  cout<<endl;
}
void searchcode()
{
  textcolor(4);
  textbackground(14);
  fstream fil;
  fil.open("Food.dat",ios::binary|ios::in);
  int inp;
  MyFood B;
  int found=0;
  cout<<"Enter FCODE  : ";cin>>inp;
  cout<<"Processing";
  while(!found && fil.read((char*)&B,sizeof(B)))
  {
    cout<<".";delay(50);
    if(B.retFCODE()==inp)
    {
      cout<<endl;
      B.Showdata();
      found++;
    }
  }
  fil.close();
  if(found==0)
  {
    cout<<endl;
    cout<<"[FCODE NOT FOUND!!!]"<<endl;
    }
  gotoxy(45,40);
  cout<<"Press Any Key To Continue..."<<endl;
  getch();
}

void modification()
{
  fstream fil;
  fil.open("Food.dat",ios::binary|ios::in|ios::out);
  MyFood P;int mcode;int found=0;
  cout<<"enter code you wish to modify:"<<endl;cin>>mcode;
  while(!found && fil.read((char*)&P,sizeof(P)))
    if(P.retFCODE()==mcode)
      found++;
  if(found)
  {
    P.editcode();
    int POS=fil.tellg()-sizeof(P);
    fil.seekp(POS);
    fil.write((char*)&P,sizeof(MyFood));
  }
  else
    cout<<"[No Record Matching for editing...]"<<endl;
  fil.close();
  gotoxy(45,40);
  cout<<"Press Any Key To Continue..."<<endl;
  getch();
}

void DEL()
{
  textcolor(4);
  textbackground(0);
  fstream fil,fil1;
  fil.open("Food.dat",ios::binary|ios::in);
  fil1.open("temp.dat",ios::binary|ios::out);
  int cd1;
  int del= 0;
  MyFood W ;
  cout<<"Enter the food code to be deleted:";cin>>cd1;
  cout<<"Processing";
  while(fil.read((char*)&W,sizeof(W)))
  {
    cout<<".";delay(100);
    if (W.retFCODE()!=cd1)
      fil1.write((char*)&W,sizeof(W));
    else
    {
      del++;
    }
  }
  fil.close();
  fil1.close();
  if(!del)
   {
    cout<<endl;
    cout<<"No record available for deletion"<<endl;
    }
  else
  {
    remove("Food.DAT");
    rename("Temp.DAT","Food.DAT");
  }
  cout<<endl;
  gotoxy(45,40);
  cout<<"Press Any Key To Continue..."<<endl;
  getch();
}

void transaction()
{
  textcolor(0);
  textbackground(15);
  int billno,r;
  char ch;
  double sum=0;
  double totalbill,vat,st;
  MyFood Z;
  do
	{
		fstream fil;
		fil.open("Food.dat",ios::binary|ios::in);
		cout<<"Enter the fcode to be added to the bill:"<<endl;
		cin>>billno;cout<<endl;
		cout<<"Enter the quantity: ";
		cin>>r;
		cout<<endl;
		while(fil.read((char*)&Z,sizeof(Z)))
		{
			if(Z.retFCODE()==billno)
			{
				sum=sum+(Z.retPRICE()*r);
			}
		}
		cout<<"Want to add  more to the bill...(y/n):"<<endl;
		cin>>ch;
	}while((ch=='y')|(ch=='Y'));
	vat=sum*(0.125);
	st=sum*(0.04);
	totalbill=sum+vat+st;
	cout<<"Bill Amount                  : Rs."<<sum<<"/-"<<endl<<endl;
	cout<<"VAT (12.5% of the bill)      : Rs."<<vat<<"/-"<<endl<<endl;
	cout<<"Service tax (4% of the bill) : Rs."<<st<<"/-"<<endl<<endl;
	cout<<"The total billed amount is   : Rs."<<totalbill<<"/-"<<endl;
	gotoxy(45,40);
  cout<<"Press Any Key To Continue..."<<endl;
  getch();
}

void main()
{
clrscr();
	{
			textcolor(15);
			textbackground(4);
	}
	char Z[45]="THE GRAND TAJ INDIAN CUISINE WELCOMES YOU";
	gotoxy(15,15);
	for(int j=0;j<45;j++)
	{
	sound(2200);
	cout<<Z[j];
	delay(125);
	}
	cout<<endl;
	delay(150);
	cout<<endl;
	cout<<endl;
	cout<<"                         ";
	cout<<"Press Any Letter To Continue..."<<endl;
	getch();
	clrscr();
	sound(880);
	cout<<"T";
	delay(250);
	cout<<"I";
	delay(250);
	cout<<"M";
	delay(250);
	cout<<"E";
	delay(250);
	cout<<":";
	nosound();

	{
		struct dostime_t t;
		 _dos_gettime(&t);
		printf(" %2d:%02d:%02d\n", t.hour, t.minute,
		t.second);

	}

	char q,w,ck;
	cout<<"Press any Letter to continue......."<<endl;
	getch();
	sound(880);
	    cout<<"_______________________________________________"<<endl;
	    cout<<"| Enter your choice:                            |"<<endl;
	    cout<<"| A for input:                                  |"<<endl;
	    cout<<"| D for display:                                |"<<endl;
	    cout<<"| S for search:                                 |"<<endl;
	    cout<<"| L for delete:                                 |"<<endl;
	    cout<<"| E for modification:                           |"<<endl;
	    cout<<"| B for generating bill:                        |"<<endl;
	    cout<<"-----------------------------------------------"<<endl;
	    do
	    {
		cout<<"Enter the operation:"<<endl;
		cin>>w;
		switch(w)
		{
			case 'A':
			case 'a':clrscr();
				 ADD();break;
			case 'D':
			case 'd':clrscr();
				 DISPLAY(); break;
			case 'S':
			case 's':clrscr();
				 searchcode(); break;
			case 'L':
			case 'l':clrscr();
				 DISPLAY();
				 DEL();break;
			case 'B':
			case 'b':clrscr();
				 DISPLAY();
				 transaction(); break;
			case 'E':
			case 'e':clrscr();
				 DISPLAY();
				 modification();break;
			default:cout<<"Enter the correct input"<<endl;
		}
		delay(100);
		gotoxy(45,35);
		cout<<"continue...(y/n):";
		cin>>ck;
		clrscr();
		sound(1320);
		delay(100);
		cout<<"_______________________________________________"<<endl;
	    cout<<"| Enter your choice:                            |"<<endl;
	    cout<<"| A for input:                                  |"<<endl;
	    cout<<"| D for display:                                |"<<endl;
	    cout<<"| S for search:                                 |"<<endl;
	    cout<<"| L for delete:                                 |"<<endl;
	    cout<<"| E for modification:                           |"<<endl;
	    cout<<"| B for generating bill:                        |"<<endl;
	    cout<<"-----------------------------------------------"<<endl;
		cout<<endl;
	    }while((ck=='y')|(ck=='Y'));

	clrscr();
	char ty[33]="THANK YOU PLEASE VISIT AGAIN";
	gotoxy(15,15);
	for(int k=0;k<33;k++)
	{
	cout<<ty[k];
	delay(100);
	}

	delay(500);
	clrscr();
	char top[32]="THIS PROGRAM WAS MADE BY -----";
	gotoxy(10,10);
	for(k=0;k<32;k++)
	{
	sound(440);
	cout<<top[k];
	delay(100);
	}
	char top1[45]="HARSHVARDHAN AGARWAL";
	gotoxy(15,15);
	for(k=0;k<45;k++)
	{
	sound(1760);
	cout<<top1[k];
	delay(100);
	}
	delay(500);
	exit(0);
	getch();
}







































































































































































































































































