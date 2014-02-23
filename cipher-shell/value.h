/* value.h a part of cipher language, by Tsuguo Mogami  */
#include <stdlib.h>

typedef struct {
	int size;
	double* v;
} DblArray;

typedef struct {
	int size;
	int* v;
} IntArr;

typedef struct {
	int size;
	char* v;
} ByteArr;

typedef struct {
	int size;
	obj *v;
} Array;

typedef struct {
	short size1;
	short size2;
	double* v;
} DblArr2;

typedef struct {
	obj rator;
	obj rand;
} opExp;

// from tokenizer
template <class T> class array {
public:
	int size;
	T* a;
	array();
	~array();
	void append(T c);
};
#define MINALLOC0 8
template <class T> array<T>::array(){
	a = (T*)malloc(sizeof(T)*MINALLOC0);
	size = 0;
}

inline bool is2n(int x){
	return !(x & (x-1));
}

template <class T> void array<T>::append(T c){
	int len = size;
	if(len+1 >= MINALLOC0 && is2n(len+1)){
        a = (T*)realloc ((void*)a, (len+1)*2*sizeof(T));
	}
	*(a+len) = c;
	size = len+1;
	return;
}

template <class T> array<T>::~array(){
	if(a) free(a);
}

typedef enum {
	INT = 1,
	tDouble,
	tChar,	//inte
	STRING,	//string
	tNull,
// vector type
	tDblArray,	//dbl_arr
	tIntArr,	//int_arr
	LIST,		//list
	tArray,	//array
	tHash,
// vector derivative type
	tDblAr2,	//dbl_ar2
	tLAVec,	//dbl_arr
	IMAGE,	//array of dbl_arr
	tCImg,	//3-array of array of dbl_arr
	tSpVec,	//spvec
// expression type
	tSymbol,	//string
	tOp,		//op
	POW,		//list-2
	MULT,	//list
	DIVIDE,	//list
	ARITH,	//list
	CONDITION,	//list
	tAssign,	//op
	tDefine,	//list-3
	tSyntaxDef,	//list-3
	tIf,		//list-3
	tWhile,		//op
	tReturn,	//ref
	tBreak,
	tSeq,		//not used
	tAnd,		//list-2
	tInd,		//op
	tAssoc,	//list of list-2
	tSyntaxLam,//list-2, similar to lambda
	tMeth,	//list-2
	tMinus,	//obj
	tExec,	//list
	tType,	// op
	tArrow,	// list
	tClosure,// list-2,3
	tCurry,	// list
	tScope,	// op
// naibu
	tInternalFn,//func
	tSpecial,	//func
	TOKEN,		//int
	tRef,		//ref, 
	tCont,		//ref
	tSigRet,	//ref
// naibude (shell) tsukau
	FRACTION,	//list-2
	SuperScript,//list
	SubScript,	// list
	tShow,		// list
	tHide,		// list
	tIns,		// list
	tDel,		// intv
	tMove,	// list
// graphics
	tPlot,	// dbl_arr
	tCanvas,	// list
	tLast	// 52
} ValueType;

//struct value {
class value {
public:
	int	refcount;
	ValueType	type;
	virtual ~value() {}
	void*operator new(size_t size);
	void operator delete(void* val, size_t size);
};

class int_: public value {
public:
	int		intv;
//	int_(int i){type=INT; intv=i;}
	int_(int i):intv(i){type=INT;}
};
#define uint(v) (((int_*)v)->intv)

class dbl_: public value {
public:
	double	dblv;
//	double double(v){return dblv;}
};

class capsl: public value {
public:
	obj		ref;
};
#define uref(v) (((capsl*)v)->ref)

#define uda2(v) (((dblar2*)v)->dbl_ar2)
#define udar(v) (((dblarr*)v)->dbl_arr)
#define uiar(v) (((intarr*)v)->int_arr)
#define udbl(v) (((dbl_*)v)->dblv)

class dblar2: public value {
public:
	DblArr2	dbl_ar2;
};
class intarr: public value {
public:
	IntArr	int_arr;
};
class dblarr: public value {
public:
	DblArray	dbl_arr;

	dblarr(int n);
/*	inline dblarr(int n) {
		type = tDblArray; 
		dbl_arr.size = n;
		dbl_arr.v = (double *)my_malloc(sizeof(double)*n);
	}//*/
};
class str_: public value {
public:
	char*		string;
};
#define ustr(v) (((str_*)v)->string)

class hash_: public value {
public:
	class hash*	hash;
};
#define uhash(v) (((hash_*)v)->hash)

class spvec_: public value {
public:
	class spvec*	spv;
};
#define uspv(v) (((spvec_*)v)->spv)

class infn: public value {
public:
	obj	(*fn)(obj);
};
#define ufn(v) (((infn*)v)->fn)

class list_: public value {
public:
	list		list;
	list_(ValueType type, node<obj>* l);
};
#define ul(ex)	(((list_*)ex)->list)
//inline List& ul(obj ex){return ex->u.list;}

class opr: public value {
public:
	opExp		ope;
};

class arr: public value {
public:
	Array		array;
	inline obj& operator[](int i){return array.v[i];}
};
#define uar(ex)	(((arr*)ex)->array)

class gr {
public:
	virtual void drawAt(float x, float y, class canvas* cv){}
};

class gr_line: public gr {
public:
	float	width;
	arr*	pts;
	gr_line(arr* pts, float width):pts(pts),width(width){}
	~gr_line(){release(pts);}
	void drawAt(float x, float y, class canvas* cv);
};
class gr_line3d: public gr {
public:
	float	width;
	arr*	pts;
	gr_line3d(arr* pts, float width):pts(pts),width(width){}
	~gr_line3d(){release(pts);}
	void drawAt(float x, float y, class canvas* cv);
};

class canvas: public value {
public:
	array<gr*> grs;
	DblArray cam_pos;
	canvas(){
		type = tCanvas;
		cam_pos.size = 3;
		cam_pos.v = new double[3];
		cam_pos.v[0] = 1;
		cam_pos.v[1] = 2;
		cam_pos.v[2] = 2;
	}
	~canvas(){
		delete cam_pos.v;
	}
};
//static_assert(sizeof(canvas)<=sizeof(opr), "");


inline ValueType type(ref v) {return v->type;};
//void fill_pool();
/*inline obj alloc(){
	if(!pool) fill_pool();
	obj r = pool;
	pool = pool->u.ope.rand;
	r->refcount=1;
	return r;
}//*/
obj alloc();
obj Assoc();
obj Token(int i);
double v2Double(obj v);	//cast to double
char* copyString(const char* str);
str_* cval(char* str);	// taking
obj cString(const char* st, const char* en);
obj aString(int n);	//alloc string
obj Symbol(const char* s);
obj Int(int i);
obj Double(double d);
inline dblarr* dblArray(int n){return new dblarr(n);}
obj intArray(int n);
arr* aArray(int n);
arr* cArray(obj v[], int n);
obj vector(int n);
inline list_* render(ValueType t, list l){return new list_(t, l);}
inline list_* create(ValueType t, list l){return render(t, l);}
obj encap(ValueType t, obj v);
list_* List2v(list l);
bool isToken(obj v, int tk);
obj copy(obj v);
int vrInt(obj v);		// value-release to Int
void print_vector(DblArray v);
void print_array(DblArray ar);
void print_list(list lis);
void print_image(obj v);
void print(obj v);

obj inv(obj v);	// in matrix.c

void set(DblArray* a, int i, double d);
obj	add(obj lt, obj r);
obj	uMinus(obj left);
obj	divide(obj lt, obj rt);
obj	power(obj lt, obj rt);
obj	mult(obj lt, obj rt);
obj	and1(obj lt, obj rt);	//releasing
bool equal(obj left, obj right);
obj ccgt(obj lt, obj rt);
obj cclt(obj lt, obj rt);
obj ccge(obj lt, obj rt);
obj ccle(obj lt, obj rt);

//---------------
#define ult(ex)	(((opr*)ex)->ope.rator)
#define urt(ex)	(((opr*)ex)->ope.rand)

inline obj& car(obj s){return ((opr*)s)->ope.rator;}
inline obj& cdr(obj s){return ((opr*)s)->ope.rand;}

inline obj operate(ValueType op, obj lt, obj rt){
	opr* rr = (opr*)alloc();
	rr->type=op;
	rr->ope.rator=lt;
	rr->ope.rand=rt;
	return (obj)rr;
}
inline obj op(obj lt, obj rt){
	opr* r = (opr*) alloc();
	r->type = tOp;
	r->ope.rator = lt;
	r->ope.rand  = rt;
	return (obj)r;
}

#define  em0(ex) first(ul(ex))
#define  em1(ex) second(ul(ex))
#define  em2(ex) third(ul(ex))

/*inline obj capstr(char* str){	// taking the string
	str_* r = (str_*)alloc();
	r->type = STRING;
	r->string = str;	
	return (obj)r;
}*/

double iprod(DblArray v1, DblArray v2);
DblArray multAA(DblArray *v1, DblArray *v2);
DblArray multDV(double d1, DblArray v2);
inline DblArray operator*(DblArray v1, DblArray v2){return multAA(&v1, &v2);}
inline DblArray operator*(double d1, DblArray v2){return multDV(d1, v2);}
inline DblArray operator*(DblArray v1, double d2){return multDV(d2, v1);}
inline DblArray operator/(DblArray v1, double d2){return multDV(1/d2, v1);}
DblArray addVV(DblArray v1, DblArray v2, int plusminus);
DblArray addDA(double d1, DblArray v2, int plusminus);
inline DblArray operator-(DblArray v1, DblArray v2){return addVV(v1, v2, -1);}
inline DblArray operator-(double d1, DblArray v2){return addDA( d1, v2, -1);}
inline DblArray operator-(DblArray v1, double d2){return addDA(-d2, v1, +1);}
