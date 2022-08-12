#ifndef __STRING_H__
#define __STRING_H__

#include "Base.h"

/*
 */
class String;
template <int Capacity = 256> class StringStack;
template <int Capacity = 256> class StringArray;

/*
 */
class String {
		
	public:
		
		//! default constructor
		String();
		//! copy constructor
		String(const String &s);
		//!  copy constructor 
		explicit String(const char *s);
		~String();
		
		//! set data to const char array
		String &operator=(const char *s);
		//! copy data from string
		String &operator=(const String &s);
		
		//! append data by char
		String &operator+=(char c);
		//! append data by const char array
		String &operator+=(const char *s);
		//! append data by string
		String &operator+=(const String &s);
		
		//! get data pointer
		INLINE const char *get() const { return data; }
		//! get data pointer
		INLINE operator const char*() const { return data; }
		//! get data pointer
		INLINE operator const void*() const { return data; }
		
		//! get char by given index
		INLINE char &get(int index) {
			assert((unsigned int)index < (unsigned int)length && "String::get(): bad index");
			return data[index];
		}
		//! get char by given index
		INLINE char get(int index) const {
			assert((unsigned int)index < (unsigned int)length && "String::get(): bad index");
			return data[index];
		}
		
		//! get char by given index
		INLINE char &operator[](int index) {
			assert((unsigned int)index < (unsigned int)length && "String::operator[](): bad index");
			return data[index];
		}
		//! get char by given index
		INLINE char operator[](int index) const {
			assert((unsigned int)index < (unsigned int)length && "String::operator[](): bad index");
			return data[index];
		}
		
		//! get string size
		INLINE int size() const { return length; }
		//! return true if string size == 0
		INLINE bool empty() const { return (length == 0); }
		
		// allocate size string, set length to size
		void resize(int size);
		// if size + 1> capacity assign new memory(size+1) and copy data
		void allocate(int size);
		// if size > capacity assign new memory(2*size+1) and copy data
		void reserve(int size);
		
		//! set length to 0
		void clear();
		//! set length to 0, free memory
		void destroy();
		
		//! find char in string and return index
		int find(char c) const;
		//! find char array in string and return index
		int find(const char *s) const;
		//! find string in string and return index
		int find(const String &s) const;
		
		//! returns the index of the last occurrence of the char c
		int rfind(char c) const;
		//! returns the index of the last occurrence of the char array s
		int rfind(const char *s) const;
		//! returns the index of the last occurrence of the string s
		int rfind(const String &s) const;

		//! copy len chars from char array s, set length to len
		void copy(const char *s,int len = -1);
		//! copy len chars from string s, set length to len
		void copy(const String &s,int len = -1);
		
		//! append char
		void append(char c);
		//! append len chars from char array s
		void append(const char *s,int len = -1);
		//! append len chars from string 
		void append(const String &s,int len = -1);
		
		//! append char at given position
		void append(int pos,char c);
		//! append len chars from char array s at given position
		void append(int pos,const char *s,int len = -1);
		//! append len chars from string at given position
		void append(int pos,const String &s,int len = -1);
		
		//! remove char at end (decrement length)
		void remove();
		//! remove len chars from pos 
		void remove(int pos,int len = 1);
		
		//! transfer to  lowercase (works only on A-Z)
		void lower();
		//! transfer to  uppercase (works only on a-z)
		void upper();
		

		void vprintf(const char *format,va_list argptr);
		void printf(const char *format,...);
		
		int vscanf(const char *format,va_list argptr);
		int scanf(const char *format,...);
		
		//! return true if code is 0-9
		INLINE static bool isdigit(int code);
		//! return true if code is a-z
		INLINE static bool islower(int code);
		//! return true if code is A-Z
		INLINE static bool isupper(int code);
		//! return true if code is a-z or A-Z
		INLINE static bool isalpha(int code);
		
		static int atoi(const char *str);
		static long long atol(const char *str);
		static float atof(const char *str);
		static double atod(const char *str);
		
		//! memory size format (with Kb, Mb)
		static String memory(size_t memory);
		
		//! Returns a lowercase copy of the char array
		static String lower(const char *str);
		//! Returns a uppercase copy of the char array
		static String upper(const char *str);
		
		static String format(const char *format,va_list argptr);
		static String format(const char *format,...);

		static int vsscanf(const char *str,const char *format,va_list argptr);
		static int sscanf(const char *str,const char *format,...);

		//! returns a string that has symbols removed from the start and the end.
		static String trim(const char *str,const char *symbols = 0);
		//! replace in str string before with after
		static String replace(const char *str,const char *before,const char *after);
		
		static StringArray<> split(const char *str,const char *delimiters);
		//! return substring of str starting in pos and given len
		static String substr(const char *str,int pos,int len = -1);
		//! Returns a string with backslashes before characters that need to be escaped. These characters are double quote ("), backslash (\), tabulation symbol (\t), new line symbol (\\n), carriage return symbol (\r). 
		static String addslashes(const char *str);
		//! Un-escapes a string quoted with addslashes(). 
		static String stripslashes(const char *str);

		//! Simple string matching, which is faster than RegExp-based ones. Some wildcards are supported in the pattern: \n
		//! ?: any single symbol \n
		//! *: any string of arbitrary length. \n
		//! |: OR statement; e.g.: "red|white" pattern matchs both "red" and "white" strings. \n
		//! \return 1 if match is found, 0 otherwise. 
		static int match(const char *pattern,const char *str);
		
		static const String null;
		
	protected:
		
		enum {
			CAPACITY = 4,
			DYNAMIC_FLAG = (int)(1 << (sizeof(int) * 8 - 1)),
			CAPACITY_MASK = ~(int)DYNAMIC_FLAG,
		};
		
		void do_copy(const char *s,int len);
		void do_append(int pos,char c);
		void do_append(int pos,const char *s,int len);
		void do_memcpy(char *dest,const char *src,int size);
		
		int length;
		int capacity;
		char *data;
		
		char stack_data[CAPACITY];
};

/*
 */
class StringPtr {
		
	public:
		
		StringPtr();
		StringPtr(const String &s);
		StringPtr(const StringPtr &s);
		explicit StringPtr(const char *s);
		~StringPtr();
		
		StringPtr &operator=(const char *s);
		StringPtr &operator=(const String &s);
		StringPtr &operator=(const StringPtr &s);
		
		StringPtr &operator+=(const char *s);
		StringPtr &operator+=(const String &s);
		
		INLINE const char *get() const { return (string) ? string->get() : String::null; }
		INLINE const String &getString() const { return (string) ? *string : String::null; }
		INLINE operator const char*() const { return (string) ? string->get() : String::null; }
		INLINE operator const void*() const { return (string) ? string->get() : String::null; }
		
		INLINE int size() const { return (string) ? string->size() : 0; }
		INLINE int empty() const { return (string) ? string->empty() : 1; }
		
		INLINE void clear() { delete string; string = 0; }
		
	private:
		
		String *string;
};

/*
 */
template <int Capacity> class StringStack : public String {
		
	public:
		
		StringStack() {
			capacity = Capacity;
			data = stack_data;
			data[length] = '\0';
		}
		StringStack(const String &s) {
			capacity = Capacity;
			data = stack_data;
			copy(s);
		}
		StringStack(const StringStack &s) {
			capacity = Capacity;
			data = stack_data;
			copy(s);
		}
		explicit StringStack(const char *s) {
			capacity = Capacity;
			data = stack_data;
			copy(s);
		}
		~StringStack() { }
		
		StringStack &operator=(const char *s) {
			if(data == s) return *this;
			copy(s);
			return *this;
		}
		StringStack &operator=(const String &s) {
			if(this == &s) return *this;
			copy(s);
			return *this;
		}
		StringStack &operator=(const StringStack &s) {
			if(this == &s) return *this;
			copy(s);
			return *this;
		}
		
	private:
		
		char stack_data[Capacity];
};

/*
 */
template <int Capacity> class StringArray {
		
	private:
		
		friend class String;
		
		StringArray(int size) : data_length(size), data(stack_data), indices_length(0), indices_capacity(Capacity), indices(stack_indices) {
			if(data_length + 1 > Capacity) {
				data = new char[data_length + 1];
			}
			data[data_length] = '\0';
		}
		
		void append(int index) {
			if(indices_length + 1 > indices_capacity) {
				indices_capacity = (indices_length + 1) * 2;
				int *new_indices = new int[indices_capacity];
				for(int i = 0; i < indices_length; i++) {
					new_indices[i] = indices[i];
				}
				if(indices != stack_indices) delete [] indices;
				indices = new_indices;
			}
			indices[indices_length++] = index;
		}
		
	public:
		
		StringArray(const StringArray &s) : data_length(s.data_length), data(stack_data), indices_length(s.indices_length), indices_capacity(Capacity), indices(stack_indices) {
			if(data_length + 1 > Capacity) {
				data = new char[data_length + 1];
			}
			for(int i = 0; i < data_length; i++) {
				data[i] = s.data[i];
			}
			data[data_length] = '\0';
			if(indices_length > indices_capacity) {
				indices_capacity = indices_length;
				indices = new int[indices_capacity];
			}
			for(int i = 0; i < indices_length; i++) {
				indices[i] = s.indices[i];
			}
		}
		~StringArray() {
			if(data != stack_data) delete [] data;
			if(indices != stack_indices) delete [] indices;
		}
		
		INLINE const char *operator[](int index) const {
			assert((unsigned int)index < (unsigned int)indices_length && "StringArray::operator[](): bad index");
			return data + indices[index];
		}
		
		INLINE int size() const { return indices_length; }
		INLINE int empty() const { return (indices_length == 0); }
		
	private:
		
		int data_length;
		char *data;
		char stack_data[Capacity];
		
		int indices_length;
		int indices_capacity;
		int *indices;
		int stack_indices[Capacity];
};

/*
 */
StringStack<> operator+(const String &s0,const String &s1);
StringStack<> operator+(const String &s0,const char *s1);
StringStack<> operator+(const char *s0,const String &s1);
StringStack<> operator+(const String &s0,char c1);
StringStack<> operator+(char c0,const String &s1);

/*
 */
int operator==(const String &s0,const String &s1);
int operator==(const String &s0,const char *s1);
int operator==(const char *s0,const String &s1);

int operator!=(const String &s0,const String &s1);
int operator!=(const String &s0,const char *s1);
int operator!=(const char *s0,const String &s1);

int operator<(const String &s0,const String &s1);
int operator<(const String &s0,const char *s1);
int operator<(const char *s0,const String &s1);

int operator>(const String &s0,const String &s1);
int operator>(const String &s0,const char *s1);
int operator>(const char *s0,const String &s1);

int operator<=(const String &s0,const String &s1);
int operator<=(const String &s0,const char *s1);
int operator<=(const char *s0,const String &s1);

int operator>=(const String &s0,const String &s1);
int operator>=(const String &s0,const char *s1);
int operator>=(const char *s0,const String &s1);

/*
 */
int operator==(const StringPtr &s0,const StringPtr &s1);
int operator==(const StringPtr &s0,const char *s1);
int operator==(const char *s0,const StringPtr &s1);

int operator!=(const StringPtr &s0,const StringPtr &s1);
int operator!=(const StringPtr &s0,const char *s1);
int operator!=(const char *s0,const StringPtr &s1);

#endif /* __STRING_H__ */
