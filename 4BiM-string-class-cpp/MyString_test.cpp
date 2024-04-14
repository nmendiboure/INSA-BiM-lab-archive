#include "gtest/gtest.h"
#include "MyString.cpp"
#include <iostream>
TEST(GTestTests, DefautlConstructorTest) {
	MyString def;
	const char* Cstring = def.c_str();
	EXPECT_STREQ(Cstring, "Hello World");
};

TEST(GTestTests, CopyConstructorTest) {
	MyString string("Hello World");
	MyString cpy_string(string);
	EXPECT_STREQ(string.c_str(), cpy_string.c_str());

	MyString empty_string("");
	MyString cpybis_string(empty_string);
	EXPECT_STREQ(empty_string.c_str(), cpybis_string.c_str());
};

TEST(GTestTests, CStrTest) {
	MyString cStr("Hello World");
	EXPECT_STREQ(cStr.c_str(), "Hello World");
};

TEST(GTestTests, SizeTest) {
	MyString sizeT("Hello World");
	EXPECT_EQ(sizeT.size(), 11);
};


TEST(GTestTests, ClearTest) {
	MyString clearedStr("Hello World");
	clearedStr.clear();
	EXPECT_STREQ(clearedStr.c_str(), "");
	size_t expected_size = 0;
	EXPECT_EQ(clearedStr.size(), expected_size);
};


TEST(GTestTests, CharAssignementOperatorTest) {
	MyString assignedStr;
	assignedStr='c';
	EXPECT_STREQ(assignedStr.c_str(), "c");
	assignedStr='\0';
	EXPECT_STREQ(assignedStr.c_str(), "");
};


TEST(GTestTests, StringConcatenationOperatorTest) {
	MyString conStr1("AZERTYUIOP");
	char* addedStr=new char[100000];
	for(int i=0;i<100000;i++){
		addedStr[i]='a';
	}
	addedStr[100000]='\0';
	MyString test=conStr1+addedStr;
	
	EXPECT_STREQ(test.c_str(), "AZERTYUIOP");

	char* addedStr2=new char[5];
	for(int i=0;i<5;i++){
		addedStr2[i]='a';
	}
	addedStr2[5]='\0';
	MyString test2=conStr1+addedStr2;
	EXPECT_STREQ(test2.c_str(), "AZERTYUIOPaaaaa");

};

TEST(GTestTests, ConstructorStringTest) {
	MyString cStr("AZERTYUIOP");
	EXPECT_STREQ(cStr.c_str(), "AZERTYUIOP");
	MyString leer("");
	EXPECT_STREQ(leer.c_str(), "");
};

TEST(GTestTests, MaxSizeStringTest) {
	MyString lambda;
	EXPECT_EQ(lambda.max_size(), 100);
};

TEST(GTestTests, LengthStringTest) {
	MyString alphabet("abcdefghijklmnopqrstuvwxyz");
	EXPECT_EQ(alphabet.length(), 26);
	MyString empty("");
	EXPECT_EQ(empty.length(), 0);
};

TEST(GTestTests, ResizeStringTest) {
	MyString str1("azertyuiopqsdfghjklmwxcvbn");
	str1.resize(4,'c');
	EXPECT_STREQ(str1.c_str(), "azer");

	MyString str2("azertyuiop");
	str2.resize(12,'q');
	EXPECT_STREQ(str2.c_str(), "azertyuiopqq");	
	
	str2.resize(100000000,'w');
	EXPECT_STREQ(str2.c_str(), "azertyuiopqq");

	str2.resize(14,'\0');
	EXPECT_STREQ(str2.c_str(), "azertyuiopqq  ");
	
	MyString str3("aqwzsxedc");
	str3.resize(9,'\0');
	EXPECT_STREQ(str3.c_str(), "aqwzsxedc");

	str3.resize(5,'\0');
	EXPECT_STREQ(str3.c_str(), "aqwzs");
	

};

TEST(GTestTests, MyStringAssignementOperatorTest) {
	MyString assignStr1;
	MyString assignStr2("AZERTYUIOP");
	assignStr1=assignStr2;
	EXPECT_STREQ(assignStr2.c_str(), assignStr1.c_str());
	EXPECT_STREQ(assignStr1.c_str(), "AZERTYUIOP");
};

TEST(GTestTests, CharConcatenationOperatorTest) {
	MyString concStr1("AZERTYUIOP");
	concStr1=concStr1+'z';
	EXPECT_STREQ(concStr1.c_str(), "AZERTYUIOPz");
	MyString concStr2("AZERTYUIOP");
	concStr2=concStr2+'\0';
	EXPECT_STREQ(concStr2.c_str(), "AZERTYUIOP");
};

