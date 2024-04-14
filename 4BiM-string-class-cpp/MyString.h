class MyString {
	
	protected : 
		char* string_; // Pointer to the characters contained in the String
		size_t length_; // Number of characters allocated in data

	public :
		//Student A : copy - constructor
		MyString (const MyString &string);
		char * c_str() const;
		void clear();
		size_t size() const; 
		MyString operator=(char c);
		MyString operator+(const char* str);

		//Student B : constructor from a c-string
		MyString(); 	
		MyString(const char* str); 
		size_t length() const; 
		size_t len_(const char* str) const ;
		size_t max_size() const;
		void resize(size_t n, char c);
		MyString operator=(const MyString &string);
		MyString operator+(char c);

		//Student C : Destructor
		~MyString();	
	
};
