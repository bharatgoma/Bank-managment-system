
                                     /*BANK MANAGEMENT SYSTEM*/

#include<iostream>
#include<iomanip>
#include<cctype>
#include<fstream>

using namespace std;

/******CLASS******/

class bank
{
   private:
   	        int acn;
   	       char name[50];
   	       char type;
   	       int balance;
   	    
   	       
   	       
   	       
   public:
          void create_account();
	      void display();
	      void deposit_money(int);
	      void withdraw_money(int);
		  void tabular() const;
		  int return_acn() const;
		  int return_balance() const;
		  char return_type() const;
		  	
        	
};



 void intro()
 {
 	cout<<"\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t_______________________________";
 	cout<<"\n\n\n\t\t\t\t\t    BANK MANAGEMENT SYSTEM ";
 	cout<<"\n\n\t\t\t\t\t_______________________________";
 	cin.get();
 }

 /*******FUNCTIONS******/
 

  void bank:: create_account()
		     {
		  	    cout<<"\n\nEnter The Account No. : "<<endl;
		  	    cin>>acn;
		  	    cout<<"Enter The Name Of Account Holder :  "<<endl;
		  	    cin.ignore();
		        cin.getline(name,50);
		  	    cout<<"What Type Of Account Do You Want To Open : MIN=500 for Saving(s) or MIN=5000 for Current(c)  : "<<endl;
		  	    cin>>type;
		  	    type=toupper(type);
		  	    cout<<"Enter The Initial Amount To Deposit : "<<endl;
		  	    cin>>balance;
		  	    cout<<"Your Account Is Created... "<<endl;
		  	
		     }	
		 
			 
		 
		 void bank:: display()
		 {
		 	cout<<"Your Details -> "<<endl;
		 	cout<<"Account No. : "<<acn<<endl;
		 	cout<<"Account Holder Name : "<<name<<endl;
		 	cout<<"Your Account Type : "<<type<<endl;
		 	cout<<"Your Total Balance : "<<balance<<endl;
		 }
		 
	
		 	
		 
		  void bank::deposit_money(int x)
		 {
		 	
		 	balance+=x;
		 
		 } 
		 
		 void bank:: withdraw_money(int x)
		 {
		 	
		 	balance-=x;
		 
		 }
		 
		 
		  void bank:: tabular() const
		  {
		  	 cout<<acn<<setw(20)<<name<<setw(7)<<type<<setw(8)<<balance<<endl;
		  }
		  
		  int bank:: return_acn() const
		  {
		  	
			  return acn;
		  	
		  }
		  
		   int bank:: return_balance() const
		  {
		  	
		  	return balance;
		  	
		  }
		  
		   char bank:: return_type() const
		  {
		  	
		  	return type;
		  	
		  }
		  
		  
   /** ************FILE HANDLING****************/
   
   
  /*function to write in file*/
   
     void write_f()
	 {
	    
	    bank b;
	    ofstream fout;
		fout.open("banksystem.dat",ios::binary|ios::app);
		b.create_account();
		fout.write(reinterpret_cast<char *> (&b), sizeof(bank));
		fout.close();
	 	
     }  
     
   /* function to read record from file */  
	  
	 void display_f(int n)
	 {
	    bank b;
	 	bool flag=false;
	 	ifstream fin;
	 	fin.open("banksystem.dat",ios::binary);
	 	if(!fin)
	 	  {
	 	  	cout<<"File Could Not Be Open!!";
	 	  	return;
		  }
		  
		  cout<<"\n BANK DETAILS"<<endl;
		  
		
		while(fin.read(reinterpret_cast<char *>(&b), sizeof(bank)))
		{
		      	if(b.return_acn()==n)
			    {
				   b.display();
				   flag=true;
			    }
			    
		}  
		fin.close();
		if(flag==false)
		cout<<"Account No. Does Not Exist!";
		
	 } 
	 
	/* function to display all accounts */
	
	void display_all()
	{
		bank b;
		ifstream fin;
		fin.open("banksystem.dat",ios::binary);
		if(!fin)
		{
			cout<<"File Could Not Be Open!!";
			return;
		}
		cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	    cout<<"====================================================\n";
	    cout<<"A/c no.      NAME           Type  Balance\n";
	    cout<<"====================================================\n";
		
		while(fin.read(reinterpret_cast<char *> (&b), sizeof(bank)))
		{
			b.tabular();
		}
	     fin.close();
		 	
	 } 
	 
	 /*function to delete account*/
	 
	 void delete_account (int n)
	 {
	 	bank b;
	 	ifstream fin;
	 	ofstream fout;
	 	fin.open("banksystem.dat",ios::binary);
	 	if(!fin)
	      	{
	 		  cout<<"File Could Not Be Open!";
	 		  return;
		    }
		 fout.open("NEW.dat",ios::binary);
		 fin.seekg(0,ios::beg);   
		    
		 while(fin.read(reinterpret_cast<char *> (&b), sizeof(bank))) 
		    {
		 	if(b.return_acn()!=n)
		         	{
		 		        fout.write(reinterpret_cast<char *> (&b), sizeof(bank));
		 		        
			        }
			        
			 }
		 fin.close();
		 fout.close();
		 remove("banksystem.dat");
		 rename("NEW.dat","banksystem.dat");
		 cout<<"Account Deleted...";
		 	 
			 
		   }  
	
	/*function to depost and withdraw amount*/
	
	void deposit_withdraw(int n,int option)
	{
		bank b;
		int amount;
		bool found=false;
		fstream f;
		f.open("banksystem.dat",ios::binary|ios::in|ios::out);
		if(!f)
		{
			cout<<"File Could Not Be Open!";
	 		  return;
		}
		while(!f.eof() && found==false)
		{
			f.read(reinterpret_cast<char *> (&b), sizeof(bank));	
			if(b.return_acn()==n)
				{
					b.display();
					
					if(option==1)
					{
						cout<<"Enter The Amount To Be Deposited : "<<endl;
						cin>>amount;
						b.deposit_money(amount);
						
					}
					
					if(option==2)
					  {
						cout<<"Enter The Amount To Be Withdraw : "<<endl;
						cin>>amount;
						int total=b.return_balance()-amount;
						if((total<500 && b.return_type()=='S') || (total<5000 && b.return_type()=='C'))
						cout<<"INSUFFICIENT AMOUNT";
						
						else
						 b.withdraw_money(amount);
					  }
						int pos=(-1)*static_cast<int>(sizeof(b));
		              	f.seekp(pos,ios::cur);
			            f.write(reinterpret_cast<char *> (&b), sizeof(bank));
			            cout<<"\n\n\t Record Updated";
			            found=true;
			      	
			}
		
		}
		f.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}
	
		   
	
	 
	 

int main()
{
	intro();
    bank b;
    int ch;
    int num;
	
	do{
		system("cls");
	
	cout<<"\n\n\n\t*** MAIN MENU ***"<<endl;
	cout<<"\n\t01. NEW ACCOUNT"<<endl;
	cout<<"\t02. DEPOSIT AMOUNT"<<endl;
	cout<<"\t03. WITHDRAW AMOUNT"<<endl;
	cout<<"\t04. BALANCE ENQUIRY"<<endl;
	cout<<"\t05. ALL ACCOUNT HOLDER LIST"<<endl;
	cout<<"\t06. CLOSE AN ACCOUNT"<<endl;
	cout<<"\t07. Exit"<<endl;
	cout<<"\n\tSelect a option from above : ";
	cin>>ch;
	
	system("cls");
      
      
     switch(ch)	
	 {
	 	case 1:
	 		 cout<<"<-- NEW ACCOUNT -->"<<endl;
	 		 write_f();
	 		 break;
	 	
 	    case 2:
		      cout<<"<-- DEPOSIT AMOUNT -->"<<endl;
		      cout<<"\n\n\tEnter The account No. : "<<endl;
		      cin>>num;
		      deposit_withdraw(num,1);
			  break;
		
		case 3:
		      cout<<"<-- WITHDRAW AMOUNT -->"<<endl;
		      cout<<"\n\n\tEnter The account No. : "<<endl;
		      cin>>num;
			  deposit_withdraw(num,2);
			  break;
			  
		case 4:
		       cout<<"<-- BALANCE ENQUIRY -->"<<endl;
		       cout<<"\n\n\tEnter The account No. : "<<endl;
		       cin>>num;
		       display_f(num);
			   	  
		
		case 5:
		      cout<<"<-- DISPLAY ACCOUNT -->"<<endl;
			  display_all();
			  break;
			  
		case 6:
		      cout<<"\n\n\tEnter The account No. : "; cin>>num;
		     	delete_account(num);
			    break;	  
			  
			  
		case 7:
		      {
		      	cout<<"THANK YOU!";
		      	exit(1);
		    
	   		 }	  	  	  	 
	 	
	 	default:
	 		cout<<"Invalid option!"<<endl;
	 	}
	 	cin.ignore();
	 	cin.get();
	 }while(ch!='7');
	 return 0;
	 	
}

	
   
    


 
   

