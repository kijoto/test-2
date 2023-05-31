#include <iostream>
#include <string>
#include <fstream>
using namespace std;

	
void cognom(string s, string &c){
	for(int i=0;i<20;i++){
		c=c+s[i+1];
		}
}

void scritt(int n,string s,string &nome,string &cognome){
			ofstream file("nomi.txt");
			cout<<"Quanti nomi vuoi inserire?: ";
			cin>>n;
			cout<<"Inserisci nome e cognome, spaziati da ;"<<endl;
			for(int i=0;i<20;i++){
				cin>>s;
				file<<s;
			}
			file.close();
			ifstream file1("nomi.txt");
			for(int i=0;i<20;i++){
				file1>>s;
				if(s==";"){
					cognom(s,cognome);
				}
				else{
					nome=nome+s[i];
				}
			}
			file1.close();

}

void lett(int n,string string){
			ifstream file2("nomi.txt");
			for(int j=0;j<n;j++){
				file2>>string;
				for(int i=0;i<20;i++){
					if(string!=";"){
						cout<<string[i];
					}
				}
				cout<<endl;				
			}
			file2.close();

}


int main(){
	int n,c;
	string nome,cognome,string,ris;
	cout<<"Inserisci 1 per scrivere e 0 per chiudere il programma: ";
	cin>>c;
	while(c!=0||c!=1){
		cout<<"ERRORE"<<endl;
		cout<<"Reinserire risposta: ";
		cin>>c;
	}
	do{
		if(c==0){
			return 0;
		}
		if(c==1){
			scritt(n,string,nome,cognome);
		}
		if(c==2){
			lett(n,string);
			
		}
		cout<<"Desideri compiere un'altra azione?: ";
		cin>>ris;
		if(ris=="si"||ris=="Si"){
		cout<<"Inserisci 1 per scrivere, 2 per leggere, 0 per chiudere: ";
		cin>>c;		
		}
		else{
			cout<<nome<<endl;
			cout<<cognome<<endl;
			return 0;
		}

	}while(ris=="Si"||ris=="si");
	return 0;

	
}
