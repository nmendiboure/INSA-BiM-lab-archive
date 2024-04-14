#include "MyString.h"

// ###################   Student A  ######################

MyString::MyString(const MyString &string){  
/*copy constructor, takes a MyString Object and return a new Object with the same content*/
//tested
	const char* Cstring = string.c_str();
	length_ = len_(Cstring) + 1;
	string_ = new char[length_];
	memcpy(string_, Cstring, length_);
};

char* MyString::c_str() const { 
/* getter which return an array of characters */
//tested
	return string_;
};


size_t MyString::size() const{
/*Return the size of the content, same as the length() method*/
	size_t i = 0;
	while(string_[i]!='\0'){
		i++;
	}
	return i ;
};



void MyString::clear(){
/* 
Clear the content of a MyString Object, 
void * memset ( void * ptr, int value, size_t num  -> Fill block of memory; */

	memset (string_, 0, MyString::size() + 1);
};

/* Assignement operator that works with one char*/
MyString MyString::operator=(char c){
	if(c!='\0'){
		length_ = 2;
		string_  = new char[length_];
		string_[0] = c;
		string_[1] = '\0';
	return *this;
	} else {
	string_=new char[0];
	string_[0]='\0';
	return *this;
	};
};
/* Concatenation operator that works with one tab of characters*/
MyString MyString::operator+(const char* str){
	length_ = MyString::length();
	unsigned i = 0;
	while(str[i]!='\0'){
		i++;
	};
	if (length_ +i+1< MyString::max_size()){
		char* c_ = new char[length_+i+1];
		for(unsigned u=0; u < length_ ; u++){
			c_[u]=string_[u];
		}
		for(unsigned u=0; u < i; u++){
			c_[u+length_]=str[u];
		}
		c_[i+length_]='\0';
		MyString My_New_String (c_);
		return My_New_String;
	} else {
		MyString My_New_String (string_);
		return My_New_String;
		};
};


// ############### STUDENT B ##################

MyString::MyString(){ 
/* Default Constructor which creates a array of chars "Hello World"*/ 
	size_t length_=12;
	string_=new char[12];
	string_[0]='H';
	string_[1]='e';
	string_[2]='l';
	string_[3]='l';
	string_[4]='o';
	string_[5]=' ';
	string_[6]='W';
	string_[7]='o';
	string_[8]='r';
	string_[9]='l';
	string_[10]='d';
	string_[11]='\0';
};



MyString::MyString(const char* str){
/*Constructor that initializes a MyString object from a c-string passed as argument */

	 if ((str != NULL) && (str[0] != '\0')){
		size_t n = len_(str);
		string_ = new char[n+1];
		for (unsigned i=0; i < n+1; i++){
			string_[i] = str[i];
		}
		string_[n+1]='\0';
	}	
	else {
		string_ = new char[1];
		string_[0] = '\0';
		}
};


size_t MyString::max_size() const {
/* We fixed the maximun length of the content to 100*/
	return 100;
};


size_t MyString::len_(const char* str) const{
/*return the size for a c_string*/
	int i =0;
	while (str[i] != '\0'){
		i++;
	}
	return i;
};

size_t MyString::length() const{
//same as the size() method

	size_t i =0;
	while (string_[i] != '\0'){
		i++;
	}
	return i;

};


void MyString::resize(size_t n,char c){
/*
Resizes the string to a length of n characters.

If n is smaller than the current string length, the current value is shortened to its first n character, removing the characters beyond the nth.

If n is greater than the current string length, the current content is extended by inserting at the end as many characters as needed to reach a size of n. If c is specified, the new elements are initialized as copies of c, otherwise, they are value-initialized characters (null characters).

see more on http://www.cplusplus.com/reference/string/string/resize/
*/
	if (c !='\0'){
		if (n <= MyString::max_size()){
			if (MyString::length() <= n){

				char* My_New_String = new char [n];
				memcpy(My_New_String, string_, n);

			 	size_t i = MyString::length();
				while(i < n){
					My_New_String[i] = c;
					i++;
				}
				My_New_String[n] = '\0';
				string_ = new char[n];
				memcpy(string_, My_New_String, n);
			}
			else {
				char* My_New_String = new char[n+1];
				memcpy(My_New_String, string_, n+1);
				My_New_String[n] = '\0';
				string_ = new char[n+1];
				memcpy(string_, My_New_String, n+1);
			}
		}
	}

	else {
		if (n <= MyString::max_size()){
			if (MyString::length() >= n){
				char* My_New_String = new char[n+1];
				memcpy(My_New_String, string_, n);
				My_New_String[n+1] = '\0';
				string_ = new char[n+1];
				memcpy(string_, My_New_String, n+1);
			} else {  
				char* My_New_String = new char [n+1];
				memcpy(My_New_String, string_, n);

			 	size_t i = MyString::length();
				while(i < n){
					My_New_String[i] = ' ';
					i++;
				}
				My_New_String[n+1] = '\0';
				string_ = new char[n+1];
				memcpy(string_, My_New_String, n+1);				
				


			}
		} 
	}
};





//assignement operator from one table of characters
MyString MyString::operator=(const MyString &string){
	if(this == &string){
		return *this;
	}
	else {
		length_ = len_(string.c_str());
		string_  = new char[length_];
		for (unsigned i=0; i < length_; i++){
		   	string_[i] = string.c_str()[i];
		}
	}
    return *this;
};


//concatenation operator with one character
MyString MyString::operator+(char c){
	length_ = MyString::length();
	if (length_ +1 < MyString::max_size() && c!='\0'){
		char* c_ = new char[length_+2];
		for (unsigned i=0; i < length_ +2; i++){
		   	c_[i] = string_[i];
		}
			c_[length_] = c;
			c_[length_+1] = '\0';
			MyString My_New_String (c_);
			return My_New_String;
	}
	MyString My_New_String (string_);
	return My_New_String;
}; 



// ##################   Student C  #################

MyString::~MyString(){
	delete [] string_;
};























