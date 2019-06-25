//
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>

class Bakery
{
	int code;
	char desc[15];
	int price;
	int qty;
	public:
	Bakery retObject(int code, int &found);
	void genCode();
	void modifyCode();
	void addStock();
	void showItemList();
	void searchByCode();
	void updateRec(int code, int qty);
	int retCode(){return code;}
	char* retDesc(){return desc;}
	int retPrice(){return price;}
	int retQty(){return qty;}
};

class Invoice
{
	int ibno;
	int Icode;
	char Idesc[15];
	int Iprice;
	int Iqty;
	int Iamount;
	public:
	void raiseBill();
	void salesTillDate();
};

void menu(int x1, int y1, int x2, int y2, int line);
void codeGenScr();
void reportScr();
char mainFile[]="bake.dat";
char salesFile[]="sales.dat";

void main()
{
	clrscr();

//	fstream f1(mainFile, ios::binary | ios::out);
//	f1.close();
//	fstream f2(salesFile, ios::binary | ios::out);
//	f2.close();

	Bakery b;
	Invoice I;

	int ch;

	do
	{
		clrscr();
		menu(20,3,60,19,1);
		gotoxy(33,4);
		cout<<"THE ARTSY TARTSY";
		gotoxy(28,7);
		cout<<"1. Code Management";
		gotoxy(28,9);
		cout<<"2. Stock Management";
		gotoxy(28,11);
		cout<<"3. Billing";
		gotoxy(28,13);
		cout<<"4. Reports";
		gotoxy(28,15);
		cout<<"0. Exit";
		gotoxy(28,17);
		cout<<"Enter your choice :";
		cin>>ch;
		switch(ch)
		{
			case 1:	codeGenScr();
							break;

			case 2:	b.addStock();
							break;

			case 3:	I.raiseBill();
							break;

			case 4:	reportScr();
							break;
		}
	}while(ch!=0);
}

void menu(int x1, int y1, int x2, int y2, int line)
{
	char hr=205,vr=186,c1=201,c2=187,c3=204,c4=185,c5=200,c6=188;

	for(int r=x1; r<x2; r++)
	{
		gotoxy(r,y1);
		cout<<hr;
		if(line==1)
		{
			gotoxy(r,y1+2);
			cout<<hr;
		}
		gotoxy(r,y2);
		cout<<hr;
	}
	for(int c=y1; c<y2; c++)
	{
		gotoxy(x1,c);
		cout<<vr;
		gotoxy(x2,c);
		cout<<vr;
	}
	gotoxy(x1,y1);
	cout<<c1;
	gotoxy(x2,y1);
	cout<<c2;
	if(line==1)
	{
		gotoxy(x1,y1+2);
		cout<<c3;
		gotoxy(x2,y1+2);
		cout<<c4;
	}
	gotoxy(x1,y2);
	cout<<c5;
	gotoxy(x2,y2);
	cout<<c6;
}

void Bakery::genCode()
{
	int ch, CD=0;
	char ans, more;
	Bakery b,bb;
	fstream f1;
	f1.open(mainFile, ios::binary | ios::in);

	if(!f1)
		CD=0;
	else
	{
		while(f1.read((char*)&b, sizeof(b)))
			CD=b.code;
	}
	f1.close();

	do
	{
		clrscr();
		menu(20,3,60,12,1);
		gotoxy(28,4);
		cout<<"New Code Generation";

		gotoxy(28,7);
		cout<<"New code is :"<<CD+1;

		gotoxy(28,8);
		cout<<"Enter Desc. :";
		gets(bb.desc);

		gotoxy(28,9);
		cout<<"Enter Price :";
		cin>>bb.price;

		bb.qty=0;

		gotoxy(25,14);
		cout<<"Do you want to Save it (y/n)?:";
		cin>>ans;

		if(ans=='Y'||ans=='y')
		{
			CD++;
			bb.code=CD;
			fstream f2;
			f2.open("bake.dat", ios::binary | ios::app);
			f2.write((char*)&bb, sizeof(bb));
			f2.close();
		}
		gotoxy(22,15);
		cout<<"Do you want to Save More Records (y/n)?:";
		cin>>more;

	}while(more=='y' || more=='Y');
}

void Bakery::modifyCode()
{
	clrscr();
	int CODE,found=0;
	Bakery b;
	fstream f1;
	f1.open("bake.dat", ios::binary | ios::in | ios::out);

	menu(20,3,60,15,1);
	gotoxy(31,4);
	cout<<"Code Modification";

	gotoxy(25,7);
	cout<<"Enter Code to be modified :";
	cin>>CODE;

	while(f1.read((char*)&b, sizeof(b)))
	{
		if(CODE==b.code)
		{
			found=1;
			gotoxy(30,9);
			cout<<"Desc : "<<b.desc;
			gotoxy(30,10);
			cout<<"Price: "<<b.price;

			gotoxy(30,12);
			cout<<"Enter Desc. : ";
			cin>>b.desc;
			gotoxy(30,13);
			cout<<"Enter Price : ";
			cin>>b.price;
			int n=-sizeof(b);
			f1.seekp(n, ios::cur);
			f1.write((char*)&b, sizeof(b));
		}
	}

	f1.close();

	if(found==0)
	{
		gotoxy(30,16);
		cout<<"No such Record!!!";
	}
}

void Bakery::addStock()
{
	clrscr();
	int CODE,found=0, QTY;
	Bakery b;
	fstream f1;
	f1.open("bake.dat", ios::binary | ios::in | ios::out);

	menu(20,3,60,14,1);
	gotoxy(36,4);
	cout<<"Add Stock";

	gotoxy(30,7);
	cout<<"Enter Code  : ";
	cin>>CODE;

	while(f1.read((char*)&b, sizeof(b)))
	{
		if(CODE==b.code)
		{
			found=1;
			gotoxy(30,9);
			cout<<"Description : "<<b.desc;

			found=1;
			gotoxy(30,10);
			cout<<"Old Quantity: "<<b.qty;

			gotoxy(30,11);
			cout<<"Enter QTY.  : ";
			cin>>QTY;
			b.qty=b.qty+QTY;

			gotoxy(30,12);
			cout<<"New QTY. is : "<<b.qty;

			int n=-sizeof(b);
			f1.seekp(n, ios::cur);
			f1.write((char*)&b, sizeof(b));
		}
	}

	f1.close();

	if(found==0)
	{
		gotoxy(32,14);
		cout<<"No such Record!!!";
	}
	gotoxy(26,15);
	cout<<"<Press any key to continue!!!>";
	getch();
}

void codeGenScr()
{
	Bakery b;
	int ch;
	clrscr();
	menu(20,3,60,15,1);
	gotoxy(30,4);
	cout<<"New Code Generation";
	gotoxy(30,7);
	cout<<"1. Generate a Code";
	gotoxy(30,9);
	cout<<"2. Modify a Code";
	gotoxy(30,11);
	cout<<"0. Back";
	gotoxy(30,13);
	cout<<"Enter choice :";
	cin>>ch;
	switch(ch)
	{
		case 1:	b.genCode();
						break;

		case 2:	b.modifyCode();
						break;
	}
	getch();
}

void reportScr()
{
	int ch;
	Bakery b;
	Invoice i;
	clrscr();
	menu(20,3,60,17,1);
	gotoxy(36,4);
	cout<<"Reports";
	gotoxy(28,7);
	cout<<"1. List of Items";
	gotoxy(28,9);
	cout<<"2. Search by code";
	gotoxy(28,11);
	cout<<"3. Total Sales";
	gotoxy(28,13);
	cout<<"0. Exit";
	gotoxy(28,15);
	cout<<"Enter choice : ";
	cin>>ch;
	switch(ch)
	{
		case 1: b.showItemList();
						break;

		case 2:	b.searchByCode();
							break;

		case 3:	i.salesTillDate();
						break;
	}
	getch();
}

void Bakery::showItemList()
{
	Bakery b;
	int ch, row=5, ctr=0;
	clrscr();
	gotoxy(33,1);
	cout<<"List of Items";
	menu(15,2,65,20,1);
	gotoxy(17,3);
	cout<<"Code    Description           Price        Qty";
	fstream fin(mainFile, ios::binary | ios::in);

	while(fin.read((char*)&b, sizeof(b)))
	{
		ctr++;
		gotoxy(18,row);
		cout<<b.code;

		gotoxy(25,row);
		cout<<b.desc;

		gotoxy(48,row);
		cout<<b.price;

		gotoxy(60,row);
		cout<<b.qty;

		row++;
	}
	fin.close();

	gotoxy(28,22);
	cout<<"Total number of Records :"<<ctr;
	gotoxy(26,23);
	cout<<"<press any key to continue!!!>";
}

void Bakery::searchByCode()
{
	Bakery b;
	int ch, CODE, found=0;
	clrscr();
	gotoxy(33,6);
	cout<<"Search Item by Code";
	menu(23,7,58,17,0);
	gotoxy(27,9);
	cout<<"Enter code to be searched : ";
	cin>>CODE;

	fstream fin(mainFile, ios::binary | ios::in);

	while(fin.read((char*)&b, sizeof(b)))
	{
		if(b.code==CODE)
		{
			found=1;
			gotoxy(30,11);
			cout<<"Desc : "<<b.desc;

			gotoxy(30,13);
			cout<<"Price: "<<b.price;

			gotoxy(30,15);
			cout<<"Qty. : "<<b.qty;
		}
	}
	fin.close();

	if(found==0)
	{
		gotoxy(35,10);
		cout<<"No such Code!!!";
	}

	gotoxy(26,19);
	cout<<"<press any key to continue!!!>";
}

void Invoice::raiseBill()
{
	Invoice I,iObj[10];
	Bakery b,bk;
	int ch, found,n,row=6, BNO=0,CODE,PRICE,QTY,Qt,AMT,TOTAL;
	char DESC[15];
	clrscr();
	{
		Invoice in;
		fstream fin1(salesFile, ios::binary | ios::in);
		while(fin1.read((char*)&in, sizeof(in)))
			BNO=in.ibno;

		BNO++;
		fin1.close();
	}
	gotoxy(33,1);
	cout<<"Invoicing";
	gotoxy(15,2);
	cout<<"Bill No :"<<BNO;
	menu(15,18,65,18,0);
	menu(15,3,65,20,1);
	gotoxy(17,4);
	cout<<"Code    Description        U/Price  Qty  Amount";

	TOTAL=0;
	n=0;
	do
	{
		gotoxy(18,row);
		cin>>CODE;
		bk=b.retObject(CODE, found);

		if(found==1)
		{

			Qt=bk.retQty();
			gotoxy(17,21);
			cout<<"Present Qty="<<Qt;

			strcpy(DESC,bk.retDesc());
			gotoxy(25,row);
			cout<<DESC;

			PRICE=bk.retPrice();
			gotoxy(44,row);
			cout<<PRICE;

			gotoxy(53,row);
			cin>>QTY;

			AMT=PRICE*QTY;
			gotoxy(59,row);
			cout<<AMT;

			TOTAL+=AMT;
			gotoxy(59,19);
			cout<<TOTAL;

			iObj[n].ibno=BNO;
			iObj[n].Icode=CODE;
			strcpy(iObj[n].Idesc,DESC);
			iObj[n].Iprice=PRICE;
			iObj[n].Iqty=QTY;
			iObj[n].Iamount=AMT;
			n++;

			row++;
		}
		else if(found==0 && CODE!=0)
		{
			gotoxy(18,row);
			cout<<"   ";

			gotoxy(35,21);
			cout<<"Wrong code!!!";
			getch();
		}
	}while(CODE!=0);

	char yn;
	gotoxy(22,22);
	cout<<"If you want to SAVE this Bill(y/n)?:";
	cin>>yn;

	if(yn=='y'||yn=='Y')
	{
		Bakery b;
		int C,Q;
		fstream fout(salesFile, ios::binary | ios::app);
		for(int i=0; i<n; i++)
		{
			fout.write((char*)&iObj[i], sizeof(iObj[i]));
			b.updateRec(iObj[i].Icode, iObj[i].Iqty);
		}

		fout.close();
	}
}

Bakery Bakery::retObject(int CODE, int &found)
{
	Bakery b;
	found=0;
	fstream fin(mainFile, ios::binary | ios::in);
	while(fin.read((char*)&b, sizeof(b)))
	{
		if(CODE==b.code)
		{
			found=1;
			break;
		}
	}
	fin.close();
	return b;
}

void Bakery::updateRec(int CD, int QT)
{
	Bakery b;

	fstream f1(mainFile, ios::binary | ios::in | ios::out);
	while(f1.read((char*)&b, sizeof(b)))
	{
		if(b.code==CD)
		{
			int n=-sizeof(b);
			f1.seekp(n, ios::cur);
			b.qty=b.qty-QT;
			f1.write((char*)&b, sizeof(b));
		}
	}
	f1.close();
}

void Invoice::salesTillDate()
{
	Invoice I;
	int total=0;
	clrscr();
	menu(25,5,55,9,0);
	fstream fin(salesFile, ios::binary | ios::in);

	while(fin.read((char*)&I, sizeof(I)))
		total+=I.Iamount;

	gotoxy(29,7);
	cout<<"Total Sales Rs.: "<<total<<"/-";
	fin.close();
}
