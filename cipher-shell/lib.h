/* part of cipher language, by Tsuguo Mogami  */
char* read(long* bytes, obj fileName);	//returns bytes
void write(char* str, long bytes, obj fileName);

struct funcbind {
	const char* fname;
	obj (*fn)(obj v);
};

obj (*searchFunc (obj id, struct funcbind fnbind[]))(obj);
extern struct funcbind infnbind[];
