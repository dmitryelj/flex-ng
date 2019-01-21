//struct BCHCode;

#ifndef BCHCODE
#define BCHCODE

struct BCHCode {
	int * p;         // coefficients of primitive polynomial used to generate GF(2**5)
	int m;           // order of the field GF(2**5) = 5
	int n;           // 2**5 - 1 = 31
	int k;           // n - deg(g(x)) = 21 = dimension
	int t;           // 2 = error correcting capability
	int * alpha_to;  // log table of GF(2**5)
	int * index_of;  // antilog table of GF(2**5)
	int * g;         // coefficients of generator polynomial, g(x) [n - k + 1]=[11]
	int * bb;        // coefficients of redundancy polynomial ( x**(10) i(x) ) modulo g(x)
};


struct BCHCode *   BCHCode_New(int *p, int m, int n, int k, int t);
void               BCHCode_Delete(struct BCHCode * BCHCode_data);
void               BCHCode_Encode(struct BCHCode * BCHCode_data, int data[]);
int                BCHCode_Decode(struct BCHCode * BCHCode_data, int recd[]);

#endif
