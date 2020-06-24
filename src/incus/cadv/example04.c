/*@file: src/incus/cadv/example04.c
 *@brief: function pointer example
 */
int f (double param) { printf("f(%f)\n", param); return 123; }
int g (double param) { printf("g(%f)\n", param); return 234; }
int h (double param) { printf("h(%f)\n", param); return 356; }

/*! Takes function pointer to function taking double and returning int
 */
static void ftp (int(*param)(double)) {
	int r = param(12.34);
	printf("r = %d\n", r);
}

/*! Takes a double and returns a function taking a double and returning an int
 */
static int(*frp(void))(double) {
	//hardcoded to return f
    	return f;
}

/*! Takes a number of functions taking doubles and returning ints
 */
static void ftfa (int(*param[])(double), int count) {
   printf("ftfa doing it's thing...\n");
   for (int i = 0; i < count; ++i)
      printf("aof[%d] = %d\n", i, param[i](123.456));
   }
/*! Main example driver function
 */
void example04(void){	
   int r = f(12.34);			// simply using a funciton
   printf("r = %d\n", r);		// print the result
   int (*pf)(double) = f;		// pf is a function pointer to a function taking double returning int
   					// initialized to f
   r = pf(12.34);			// assign to r result of call operator on pf with 12.34
   ftp(pf); ftp(f);			// call ftp,pass pf, call ftp, pass f
   pf = frp();				//
   r = pf(23.45);			//
   r = frp()(23.45);			//
   int(*aof[3])(double) = { f, g, h };	//
   for (int i = 0; i < 3; ++i)		//
      r = aof[i](123.456);		//
   ftfa(aof, 3);			//
}

