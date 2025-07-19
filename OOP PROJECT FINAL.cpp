#include<iostream>
#include <stdexcept>
#include<conio.h>
#include<windows.h>
#include<fstream>
#include<cstdlib>
#include<time.h>
#include<iomanip>
#include<cstring>
#include<stdio.h>
#include<Wininet.h>
using namespace std;
#pragma comment(lib, "wininet.lib")

#define password 2345

void gotoxy(int x, int y);

class characteristics{
	public:
	void recordVeh();
	void booths();
	void emergency();
	void control();
};

class Display{
	public:
	void certified();
	void loadscreen();
	void menu();
};

class vehicleData{
	protected:
	unsigned long long int ownerNum;
	int seater, generation, RTONum;
	char vehicleType[10],ownerName[50],fuelType[10],address[100], issuedDate[20],vehicleNo[15];
    public:
    	vehicleData( ){strcpy(vehicleNo,"xxxxxxxxxx");}
		void header();
    	void readData();
		int storeData();
		void viewData();
		virtual void showData();
		void Searching(char *s);
		void Deleting(char *s);
		void Updation(char *s);
};

class GPS {
	private:
    string fetchHTTP(const string& url) {
        HINTERNET hInternet = InternetOpenA("HTTPGET", INTERNET_OPEN_TYPE_PRECONFIG, 0, 0, 0);
        if (!hInternet) {
            throw runtime_error("Failed to open Internet connection.");
        }
        HINTERNET hConnect = InternetOpenUrlA(hInternet, url.c_str(), 0, 0, INTERNET_FLAG_RELOAD, 0);
        if (!hConnect) {
            InternetCloseHandle(hInternet);
            throw runtime_error("Failed to open URL.");
        }
        string response;
        const int bufferSize = 1024;
        char buffer[bufferSize];
        DWORD bytesRead = 0;
        while (InternetReadFile(hConnect, buffer, bufferSize, &bytesRead) && bytesRead > 0) {
            response.append(buffer, bytesRead);
        }
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return response;
    }
    double stringToDouble(const string& str) {
        char* endptr;
        double result = strtod(str.c_str(), &endptr);
        if (endptr == str.c_str()) {
            throw invalid_argument("Cannot convert string to double.");
        }
        return result;
    }
public:
    void getCurrentLocation(double& latitude, double& longitude) {
        const string url = "http://ip-api.com/json";
        string response = fetchHTTP(url);
        size_t latPos = response.find("\"lat\":") + 6;
        size_t lonPos = response.find("\"lon\":") + 6;
        latitude = stringToDouble(response.substr(latPos, response.find(",", latPos) - latPos));
        longitude = stringToDouble(response.substr(lonPos, response.find("}", lonPos) - lonPos));
    }

};

class Vehicle : public vehicleData{
private:
    double latitude;
    double longitude;

public:
    Vehicle(double lat, double lon) : latitude(lat), longitude(lon) {}
    void showData() {
        cout << "Latitude: " << latitude << endl;
        cout << "Longitude: " << longitude << endl;
    }
};

void Display::certified() {
	characteristics c;
	system("color 0B");
	int key;
	system("cls");
	gotoxy(45, 11);
	for(int i=0;i<26;i++)
	  cout<<"\xD";
	  cout<<endl;
	  gotoxy(50,14);
	  cout<<"Authentication......";
	  gotoxy(66,15);
	  for(int i=0;i<26;i++)
	  cout<<"\xD2";
	  gotoxy(45,21);
	  cout<<"\t ENTER THE PIN...";
	  static int i=3;
	  cin>>key;
	  if(key==password) {
        system("color 0A");
        loadscreen();
        menu();
	  }
	  else{
	  	system("color 04");
	  	gotoxy(51,26);
	  	cout<<"OOPS! WE ARE SORRY, YOU ARE NOT AUTHORISED....";
	  	cout<<"NO OF ATTEMPTS LEFT="<<i;
	  	i--;
	  	cin.get();
	  	if(i==-1)
	  	exit(0);
	  	certified();
	    } 
}

void Display::loadscreen(){
	system("cls");
	int j,p;
	gotoxy(82,20);
	cout<<"LOADING THE SCREEN.........";
	gotoxy(71,21);
	for(j=0;j<30;j++){
		for(p=0;p<=90;p++)
		  printf("%c",177);
	}
}

void Display::menu(){
	system("cls");
	char search[20];
	characteristics c;
	vehicleData vehicle;
	system("color 8");
	gotoxy(66,6);
	for(int i=0;i<=39;i++)
	cout<<" \xB2";
	cout<<endl;
	gotoxy(90,8);
	cout<<" TRAFFIC MANAGEMENT SYSTEM...";
	gotoxy(66,10);
	for(int i=0;i<=39;i++)
	cout<<" \xB2";
	cout<<endl;
	gotoxy(25,14);
	cout<<"1.RECORDS OF VEHICLE...";
	gotoxy(25,15);
	cout<<"2.RECORDS OF CHALLAN...";
	gotoxy(25,16);
	cout<<"3.SEARCHING FOR RECORDS OF VEHICLE...";
	gotoxy(25,17);
	cout<<"4.SHOW TRAFFIC BOOTH INFORMATION...";
	gotoxy(25,18);
	cout<<"5.INFORMATION OF HELPLINES AND NEAREST HOSPITALS...";
	gotoxy(25,19);
	cout<<"6.TRAFFIC CONTROL...";
	gotoxy(25,20);
	cout<<"7.EXIT...";
	gotoxy(25,21);
	int ch;
	while(ch!=7){
		gotoxy(25,23);
		cout<<"ENTER THE CHOICE OF YOUR OWN....";
		cin>>ch;
		switch(ch){
			case 1:
				c.recordVeh();
				break;
			case 2:
				vehicle.viewData();
				break;
			case 3:
				{ system("cls");
				  gotoxy(51,23);
				  cout<<"ENTER THE NO OF VEHICLE YOU WANT TO SEARCH";
				  cin.ignore();
				  cin.getline(search,19);
				  system("cls");
				  vehicle.Searching(search);
				  break;
				}	
			case 4:
			   c.booths();
			   break;
			case 5:
				c.emergency();
				break;
			case 6:
				c.control();
				break;
			case 7:
				{
					gotoxy(46,31);
				    cout<<"THANKYOU FOR USING AND BELIEVING IN OUR SERVICE";
				    cin.get();
				    exit(0);
				    break;
				}
		}
	}
}

void vehicleData::header(){
	cout<<endl;
	cout<<setw(14)<<"VEHICLE NUMBER"<<setw(16)<<"VEHICLE TYPE"<<setw(19)<<"OWNER NAME"
	<<setw(19)<<"PHONE NUMBER"<<setw(15)<<"NO OF SEATS"<<setw(16)<<"GENERATION"<<setw(11)
	<<"FUEL"<<setw(11)<<"RTO NO"<<setw(36)<<"ADRESS"<<setw(21);
	for(int i=0;i<180;i++){
		cout<<"-";
	}
	cout<<endl;
}

void vehicleData::showData(){
	cout<<"\n\n"<<setw(14)<<vehicleNo<<setw(16)<<vehicleType<<setw(19)<<ownerName
	<<setw(19)<<ownerNum<<setw(15)<<seater<<setw(16)<<generation<<setw(11)
	<<fuelType<<setw(11)<<RTONum<<setw(36)<<address<<setw(21);
}
int vehicleData::storeData(){
	if(strlen(vehicleNo)==0){
		cout<<"\n NO DATA HAS STORED ";
	} else {
		ofstream fout;
		fout.open("storevehicle.dat",ios :: app|ios :: binary);
		fout.write((char*)this, sizeof(*this));
		fout.close();
		cout << "\n Data has been stored !!";
	}
	cout << "\n Press any key to proceed...";
	cin.get();
	return 0;
}

void vehicleData::readData(){
	system("cls");
	gotoxy(65, 1); 
	cout << "***PLEASE ENTER DETAILS FOR THE VEHICLE RECORD***\n\n";
	int t;
	cout<<"\n\tNUMBER OF VEHICLE :";
	cin.ignore();
	cin.getline(vehicleNo,14);
	cout<<"Types of wheeler: \n\t1.Two Wheeler (Bike)\t2. Three Wheeler (Auto)\t3. Four Wheeler (Car)\n\n\tEnter type of vehicle: ";
	cin>>t;
	if(t==1) strcpy(vehicleType, " Bike ");
	else if(t==2) strcpy(vehicleType, " Auto");
	else if(t==3) strcpy(vehicleType, " Car ");
	else strcpy(vehicleType, "unavailable type");
	cout << " Name of Owner: ";
    cin.ignore();
    cin.getline(ownerName, 49);
    cout << " Mobile Number : ";
    cin >> ownerNum;
    cout << " Seater : ";
    cin >> seater;
    cout << " Generation : ";
    cin >> generation;
    cout << " Desiel or Petrol : ";
    cin.ignore();
    cin.getline(fuelType, 9);
    cout << " RTO No : ";
    cin >> RTONum;
	cout << " Address : ";
    cin.ignore();
    cin.getline(address, 99);
}

void characteristics::recordVeh(){
	system("cls");
	Display d;
	vehicleData veh;
	GPS g;
	char get[15];
	gotoxy(65,5);
	cout<<" **** CHOOSE ANY OPTION **** ";
	gotoxy(55,10);
	cout << "**  1. Add a Record"; gotoxy(55, 12);
	cout << "**  2. Delete a Record"; gotoxy(55, 14);
	cout << "**  3. Update a Record"; gotoxy(55, 16);
	cout << "**  4. Gps of a Vehicle"; gotoxy(55,18);
	cout << "**  5. Back to Main Menu"; 
	int choice;
	while(choice != 4) {
		gotoxy(55, 22);
		cout << "Enter your choice : ";
		cin >> choice;
		switch(choice) {
			case 1: {
				veh.readData();
				veh.storeData();
				break;
			}
			case 2: {
				system("cls");
				gotoxy(65, 1); cout << "*** Delete Record ***\n\n";
				gotoxy(50, 22);
				cout << "Enter the Vehicle No to delete : ";
				cin.ignore();
    			cin.getline(get, 14);
				veh.Deleting(get);
				break;
			}
			case 3: {
				system("cls");
				gotoxy(65, 1); cout << "*** Update Record ***\n\n";
				gotoxy(50, 22);
				cout << "Enter the Vehicle No to Update : ";
				cin.ignore();
    			cin.getline(get, 14);
				veh.Updation(get);
				break;
			}
			case 4:{
				system("cls");
                gotoxy(65, 1); 
                cout << "*** Fetching Current Location ***\n\n";
                double lat, lon;
                GPS g;
                g.getCurrentLocation(lat, lon);
                Vehicle vehicle(lat,lon);
                cout << "\nGPS Data for Vehicle:" << endl;
                vehicle.showData();
                break;
			}
			case 5:
				d.menu();
			 
		}
	}
}

void vehicleData::Deleting(char *s){
   	characteristics c;
   	int count=0;
   	ifstream fin;
   	ofstream fout;
   	fin.open("storevehicle.dat",ios::in|ios::binary);
   	if(!fin)
   	    cout<<"\tCAN'T FIND THE FILE."<<endl;
   	else {
   		fout.open("temporaryfile.dat", ios::out|ios::binary);
   		fin.read((char*)this,sizeof(*this));
   		while(!fin.eof()){
   			if(strcmp(s,vehicleNo)){
   				fout.write((char*)this,sizeof(*this));
   				count++;
			   }
			   fin.read((char*)this,sizeof(*this));
		   }
		   fin.close();
           fout.close();
           remove("storevehicle.dat");
           rename("temporaryfile.dat","storevehicle.dat");
   		gotoxy(51,26);
   		if(count==0){
   			cout<<"\tCAN'T DELETE."<<endl;
		   }
		   else{
		   	cout<<"\n\tDELETED SUCCESSFULLY."<<endl;
		   }
		}
		gotoxy(51,27);
		cout<<"\n\tPRESS KEY TO CONTINUE THE PROGRAM..";
		cin.get();
		c.recordVeh();
   }

void vehicleData::viewData(){
	system("cls");
	gotoxy(65,1);
	cout << "***RECORDS OF THE CHALLAN DONE***\n\n";
	header();
	ifstream fin;
	fin.open("storevehicle.dat",ios::in|ios::binary);
	if(!fin){
		cout<<"\n Unavailabe file! \n";
	} else {
		fin.read((char*)this, sizeof(*this));
		while(!fin.eof()) {
			showData();
			fin.read((char*)this, sizeof(*this));	
		}
		fin.close();
	}
	cout << "\n Press any key to proceed...";
	cin.get();
}

void vehicleData::Searching(char *s){
   	Display d;
   	gotoxy(68,2);
   	cout<<" \t SEARCH RECORDS "<<endl;
   	header();
	int count=0;
	ifstream fin;
	fin.open("storevehicle.dat",ios::in|ios::binary);
	if(!fin){
		cout<<"\n\tCAN'T FIND FILE"<<endl;
	} 
	else{
		fin.read((char*)this,sizeof(*this));
		while(!fin.eof()){
		if(!strcmp(s,vehicleNo)) {
			showData();
			count++;
		}
		fin.read((char*)this,sizeof(*this));
		}
		if(count==0){
			cout<<"\n\tRECORDS ARE NOT FOUND..";
		}
		fin.close();
	}
	cout<<"\n\tPRESS KEY TO CONTINUE THE PROGRAM..";
	cin.get();
	d.menu();
}

void vehicleData::Updation(char *s){
	characteristics c;
	int find=0;
	fstream filee;
	filee.open("storevehicle.dat",ios::in|ios::out|ios::ate|ios::binary);
	filee.seekg(0);
	filee.read((char*)this,sizeof(*this));
	while(!filee.eof()){
   			if(strcmp(s,vehicleNo)){
   				readData();
   				int position=(int)filee.tellg()-sizeof(*this);
   				filee.seekp(position,ios::beg);
   				filee.write((char*)this,sizeof(*this));
   				find++;
	   		}
	   		filee.read((char*)this,sizeof(*this));
   	    }
   	    filee.close();
   	    if(find==0){
   	       cout<<"\n\tUPDATION NOT POSSIBLE\n";	
		   }
		   else{
		   	cout<<"\n\tUPDATION SUCCESSFULLY DONE\n";
		   }
		   cout<<"\n\tPRESS KEY TO CONTINUE THE PROGRAM...\n";
		   cin.get();
		   c.recordVeh();
    } 
    
void characteristics::booths() {
	system("cls");
	system("color 6");
	Display d;
	gotoxy(65, 3);
	cout << "******  Traffic Control Booth  ******\n\n\n"; 
	char ch;
	ifstream fin;
	fin.open("controlBooth.dat");
	while(!fin.eof()) {
		ch = fin.get();
		if(ch == '*') cout << "***";
		else cout << ch;
	}
	fin.close();
	cout << "\n\n\n\t\tPress any key to continue...";
	getch();
	d.menu();
}

void characteristics::emergency() {
	system("cls");
	Display d;
	gotoxy(65, 3);
	cout << "*****  For Emergency Services  *****\n\n\n"; 
	char ch;
	ifstream fin;
	fin.open("helpline.dat");
	while(!fin.eof()) {
		ch = fin.get();
		if(ch == '*') cout << "***";
		else cout << ch;
	}
	fin.close();
	cout << "\n\n\n\t\tPress any key to continue...";
	getch();
    d.menu();
}

void characteristics::control() {
	system("cls");
	Display d;
	gotoxy(65, 3);
	cout << "******  Control of Traffic ****** \n\n\n"; 
	char ch;
	ifstream fin;
	fin.open("control.dat");
	while(!fin.eof()) {
		ch = fin.get();
		if(ch == '*') cout << "\xB2";
		else cout << ch;
	}
	fin.close();
	cout << "\n\n\n\t\tPress any key to continue...";
	getch();
	d.menu();
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main(){
	Display D;
	cout<<"PRESS F11..";
	D.certified();
	return 0;
}
