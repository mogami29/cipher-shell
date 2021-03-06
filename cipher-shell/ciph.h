/* part of cipher language, by Tsuguo Mogami  */
#ifndef PRIVATE_CIPH_H_INCLUDED
#define PRIVATE_CIPH_H_INCLUDED
#endif /* PRIVATE_CIPH_H_INCLUDED */

#define smaller(a, b) ((a) < (b) ? (a) : (b))
#define larger(a, b) ((a) > (b) ? (a) : (b))
 
typedef class value*	obj;
typedef const class value* ref;
typedef struct value*	rel;

/*class obj {
	value * a;
public:
	inline value* operator->(){return a;}
	inline value& operator*(){return *a;}
	inline obj(){};
	explicit obj(long p):	a((value*)p){}
	explicit operator long(){return (long)a;}
	inline obj(value*p):	a(p){}
	inline operator value*(){return (value*)a;}
	template <class T> explicit operator T*(){return (T*)a;}
};*/

class val {
	value * a;
public:
	inline value* operator->(){return a;}
	inline value& operator*(){return *a;}
	val();
//	val(double p):	a(nullptr){}
	explicit val(long p):	a((value*)p){}
	explicit operator long(){return (long)a;}
	explicit inline val(value*p):	a(p){}
//	inline operator value*(){return a;}
	inline operator obj()&&{value*p=a; a=nullptr; return p;}
	inline operator obj()& {return a;}
	template <class T> explicit operator T*(){return (T*)a;}
	val(const val& s):a(s.a){}	// copy constructor
	~val(void);
	val(val && r):a(r.a){ r.a = nullptr; }	// move constructor
};

/*typedef struct node* list;
/*/template <class T> class node;
typedef node<obj>* list;/**/

extern "C" {
typedef struct Interpreter_* Interpreter;
Interpreter create_interpreter(void);
void interpret(Interpreter interpreter, char* line);
void dispose_interpreter(Interpreter interpreter);
}   // Extern C

#ifdef GLOBAL_VARIABLE_DEFINE
#define GLOBAL
#else
#define GLOBAL extern
#endif

void	scroll();               // in appSpeci.c
void    scrollBy(int points);   // in appSpeci.c
void    addObjToText(struct value* line);	// in appSpeci.c, taking obj
void 	assert_func(const char* file, int line);
void 	error_func(const char *str, const char* file, int line);
void 	exit2shell();
void 	myPrintf(const char *fmt,...);// in main.c
//obj 	editline(obj );		// in appSpeci.c
//obj 	edit(obj);			// in appSpeci.c
obj 	parse(list line);			//in parser.c
obj 	parseString(char** string);	//in parser.c

#define error(string) 		(error_func(string,__FILE__, __LINE__))
#define assert(condition)	((condition) ? (void)(0) : assert_func(__FILE__, __LINE__))
#define nil	NULL

#ifdef PtoCstr	// a little hack to find CodeWarrior
	typedef int bool;
#endif

typedef struct {
	int size;
	char* s;
} string;

obj	yylex();			// in tokenizer.c
string nullstr();			// in tokenizer.c
void appendS(string* s, int c);// in tokenizer.c
void freestr(string* s);	// in tokenizer.c
char*next(char* st);		// in tokenizer.c
int readchar(char* st);		// in tokenizer.c
bool get_pat(unsigned char**pp, const char* s);	//get pattern in tokenizer.c

// in value.c
obj retain(obj);
void release(obj);
inline val::~val(){release(a);}

