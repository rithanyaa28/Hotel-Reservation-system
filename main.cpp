#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<stdio.h>
#include<dos.h>
#include<string.h>
#include<iomanip.h>

class hotel
{
	int room_no;
	char date_in[10];
	char date_out[10];
	char name[30];
	char address[50];
	char phone[10];

	public:
	void main_menu();	//to dispay the main menu
	void add();		//to book a room
	void display();	//to display the customer record
	void rooms();	//to display alloted rooms
	void edit();	//to edit the customer record
	int check(int);	//to check room status
	void modify(int);	//to modify the record
	void delete_rec(int);   //to delete the record
	void roomservice();

}h;
struct food
{
 char title[20];
 char dish[10][30];
 char type[7];
 float price;
 int titleno;
 int dishno;
}a;
struct order
{
 char name[30];
 char type[10];
 float price;
}o[10];
void foodenter();
void foodmenu();

void hotel::main_menu()
{
	int choice;

	while(choice!=7)
	{
		clrscr();
		cout<<"\n\t\t\t\t*************";
		cout<<"\n\t\t\t\t* MAIN MENU *";
		cout<<"\n\t\t\t\t*************";
		cout<<"\n\n\n\t\t\t1.Book A Room";
		cout<<"\n\t\t\t2.Customer Record";
		cout<<"\n\t\t\t3.Rooms Allotted";
		cout<<"\n\t\t\t4.Edit Record";
		cout<<"\n\t\t\t5.Enter menu";
		cout<<"\n\t\t\t6.Room service";
		cout<<"\n\t\t\t7.Exit";
		cout<<"\n\n\t\t\tEnter Your Choice: ";
		cin>>choice;

		switch(choice)
		{
			case 1: add();
					break;
			case 2: display();
					break;
			case 3: rooms();
					break;
			case 4: edit();
					break;
			case 5: foodenter();
					break;
			case 6: foodmenu();
					break;
			case 7:break;
			default:
					{
						cout<<"\n\n\t\t\tWrong choice!!!";
						cout<<"\n\t\t\tPress any key to continue!!";
						getch();
					}
		}
	}
}

void hotel::add()
{
	clrscr();
	int r,flag,qty;char c;
	ofstream fout("Record.dat",ios::app|ios::binary);

	cout<<"\n Enter Customer Detalis";
	cout<<"\n **********************";
	cout<<"\n\n Room no: ";
	cin>>r;
	flag=check(r);

	if(flag)
		cout<<"\n Sorry..!!!Room is already booked";
	else
	{
		room_no=r;
		cout<<" Name: ";
		gets(name);
		cout<<" Address: ";
		gets(address);
		cout<<" Phone No: ";
		gets(phone);
		cout<<"date of check in:";
		gets(date_in);
		cout<<"date of check out:";
		gets(date_out);
		fout.write((char*)this,sizeof(hotel));
		cout<<"\n Room is booked!!!";
	}

	cout<<"\n Press any key to continue!!";
	getch();
	fout.close();
}

void hotel::display()
{
	clrscr();
	ifstream fin("Record.dat",ios::in|ios::binary);
	int r,flag;
	cout<<"\n Enter room no: ";
	cin>>r;

	while(!fin.eof())

	{
		fin.read((char*)this,sizeof(hotel));
		if(room_no==r)
		{
			clrscr();
			cout<<"\n Customer Details";
			cout<<"\n ****************";
			cout<<"\n\n Room no: "<<room_no;
			cout<<"\n Name: "<<name;
			cout<<"\n Address: "<<address;
			cout<<"\n Phone no: "<<phone;
			cout<<"\n date of check in: "<<date_in;
			cout<<"\n date of check out:"<<date_out;
			flag=1;
			break;
		}
	}

	if(flag==0)
		cout<<"\n Sorry Room no. not found or vacant!!";

	cout<<"\n\n Press any key to continue!!";
	getch();
	fin.close();
}

void hotel::rooms()
{
	clrscr();
	ifstream fin("Record.dat",ios::in|ios::binary);
	cout<<"\n\t\t\tList Of Rooms Allotted";
	cout<<"\n\t\t\t*********************";
	cout<<"\n\n Room No.\t Name\t Address\t\t Phone no.\n";

	while(fin.read((char*)this,sizeof(hotel)))
	{

		cout<<"\n\n "<<room_no<<setw(2)<<"\t\t"<<name;
		cout<<"\t\t"<<address<<setw(2)<<"\t\t"<<phone;

	}

	cout<<"\n\n\n\t\t\tPress any key to continue!!";
	getch();
	fin.close();
}


void hotel::edit()
{
	clrscr();
	int choice,r;

	cout<<"\n EDIT MENU";
	cout<<"\n *********";
	cout<<"\n\n 1.Modify Customer Record";
	cout<<"\n 2.Delete Customer Record";

	cout<<"\n Enter your choice: ";
	cin>>choice;

	clrscr();
	cout<<"\n Enter room no: ";
	cin>>r;

	switch(choice)
	{
		case 1: modify(r);
				break;
		case 2: delete_rec(r);
				break;
		default: cout<<"\n Wrong Choice!!";
			       break;
	}

	cout<<"\n Press any key to continue!!!";
	getch();
}

int hotel::check(int r)
{
	int flag=0;
	ifstream fin("Record.dat",ios::in|ios::binary);
	while(!fin.eof())
	{
		fin.read((char*)this,sizeof(hotel));
		if(room_no==r)
		{
			flag=1;
				break;
		}
	}

	fin.close();
	return(flag);
}

void hotel::modify(int r)
{
	long pos,flag=0;
	fstream file("Record.dat",ios::in|ios::out|ios::binary);

	while(!file.eof())
	{
		pos=file.tellg();
		file.read((char*)this,sizeof(hotel));
		if(room_no==r)
		{
			cout<<"\n Enter New Details";
			cout<<"\n *****************";
			cout<<"\n Name: ";
			gets(name);
			cout<<" Address: ";
			gets(address);
			cout<<" Phone no: ";
			gets(phone);
			cout<<"date of check in:";
			gets(date_in);
			cout<<"date of check out:";
			gets(date_out);
			file.seekg(pos);
			file.write((char*)this,sizeof(hotel));
			cout<<"\n Record is modified!!";
			flag=1;
			break;
		}
	}

	if(flag==0)
		cout<<"\n Sorry Room no. not found or vacant!!";

	file.close();
}

void hotel::delete_rec(int r)
{
	int flag=0;
	char ch;
	ifstream fin("Record.dat",ios::in|ios::binary);
	ofstream fout("temp.dat",ios::out|ios::binary);

	while(fin.read((char*)this,sizeof(hotel)))
	{

		if(room_no==r)
		{
			cout<<"\n Name: "<<name;
			cout<<"\n Address: "<<address;
			cout<<"\n Phone No: "<<phone;
			cout<<"\n  date of check in:"<<date_in;
			cout<<"\n date of check out:"<<date_out;
			cout<<"\n\n Do you want to delete this record(y/n): ";
			cin>>ch;

			if(ch=='n')
			fout.write((char*)this,sizeof(hotel));

			flag=1;
		}
		else
			fout.write((char*)this,sizeof(hotel));
	}

	fin.close();
	fout.close();

	if(flag==0)
		cout<<"\n Sorry room no. not found or vacant!!";
	else
	{
		remove("Record.dat");
		rename("temp.dat","Record.dat");
	}
}

void foodenter()
{
 clrscr();
 ofstream f("food.dat",ios::binary);
 char b[100];
 int n,c;
 float p;
 cout<<"enter no of titles: ";
 cin>>c;
 for(int i=1;i<=c;i++)
 {
  clrscr();
  cout<<"\nenter title: ";
  gets(b);
  strcpy(a.title,b);
  a.titleno=i;
  cout<<"\nenter no of dishes: \n";
  cin>>a.dishno;
  for (int j=1;j<=a.dishno;j++)
  {

   cout<<"\nenter dish number "<<j<<":";
   gets(b);
   strcpy(a.dish[j],b);
   cout<<"\nenter type of this dish veg / nonveg: ";
   gets(b);
   strcpy(a.type,b);
   cout<<"\nenter price: ";
   cin>>p;
   a.price=p;
  }
  f.write((char*)&a,sizeof(a));
 }
 f.close();
}

void order()
{
 int u=0,flag=0;
 float amt=0;
 char d='n';
 ifstream g("food.dat",ios::binary);
 while(1)
 {  int c,b;
  cout<<"enter your order";
  cout<<"\ntitleno: ";
  cin>>c;
  cout<<"\ndishno: ";
  cin>>b;
  g.seekg(0,ios::beg);
  while(g.read((char*)&a,sizeof(a)))
  {

   if(a.titleno==c)
   {
    flag=1;
    goto bag;
   }

  }
   if(flag==0)
   {
    cout<<"\nwrong title no";
    continue;
   }
   bag:
    if(b>a.dishno)
    {
     cout<<"\nwrong dish no";
     continue;
    }
    strcpy(o[u].name,a.dish[b]);
    strcpy(o[u].type,a.type);
    o[u].price=a.price;
    u++;
    cout<<"\nmore dishes needed? if yes enter y ";
    cin>>d;
    if(d!='y')
     break;

  }


 cout<<"\nyour order is: ";
 cout<<"\norderno\t\tdish name\t\tprice\t\ttype \n";
 cout<<"--------------------------------------------\n";
 for(int i=0;i<u;i++)
 {
  cout<<i+1<<"\t\t"<<o[i].name<<"\t\t";
  cout<<o[i].price<<"\t\t"<<o[i].type<<"\n";
  amt+=o[i].price;
 }
 cout<<"\n\n\n\t\t\ttotal price is "<<amt<<"\n";
 getch();
 g.close();
}

void foodmenu()
{
  clrscr();
  ifstream g("food.dat",ios::binary);
  cout<<"\t\t\t\t ********************* \n";
  cout<<"\t\t\t\t      FOOD MENU        \n";
  cout<<"\t\t\t\t ********************* \n";
  while(g.read((char*)&a,sizeof(a)))
  {

  cout<<a.titleno<<"\t"<<a.title<<"\n***************************";
  cout<<"\ndish no\t\tdish\t\tprice\t\tveg/nonveg \n";
  cout<<"------------------------------------------------------------\n";
  for(int i=1;i<=a.dishno;i++)
   {
   cout<<i<<"\t\t"<<a.dish[i]<<"\t\t"<<a.price<<"\t\t"<<a.type<<"\n";
   }
  }
 order();
 g.close();
}
void main()
{
	textmode(C80);
	textbackground(WHITE);
	textcolor(BLACK);

	clrscr();
	cout<<"\n\t\t\t****************************";
	cout<<"\n\t\t\t* HOTEL MANAGEMENT PROJECT *";
	cout<<"\n\t\t\t****************************";
	sleep(2);

	cout<<"\n\n\n\n\t\tMade By:";
	sleep(2);
	cout<<" Manasa , Akshitaa , Hari Rithanyaa ";
	sleep(2);
	cout<<"\n\n\n\n\n\t\t\t\tPress any key to continue!!";
	getch();
	h.main_menu();
}


















