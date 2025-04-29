//==========LIMITATIONS==========
/* only produces output for n <= 23
 * and i hope to improve upon that
 */

#include <stdio.h>

typedef struct {
		int a;
		int b;
} frac_t;

int gcd(int a, int b) {
		if(b==0)
				return a;
		
		if(a > b)
				return gcd(b, a%b);
		else if(a < b)
				return gcd(a, b%a);

		return a;
}


void reduce(frac_t *x) {
		int cd = gcd(x->a, x->b);
		x->a /= cd;
		x->b /= cd;
}


frac_t add_frac(frac_t x, frac_t y) {
		frac_t res;
		res.a = x.a * y.b + x.b * y.a;
		res.b = x.b * y.b;
		reduce(&res);
		
		return res;
}


frac_t sum9(int n) {
		if(n==1) return (frac_t){1, 1};
		
		frac_t tmp = {1, n};
		return add_frac(tmp, sum9(n-1));
}

int main() {
		printf("hello world\n");

		int n;
		printf("Enter n: ");
		scanf("%d", &n);
		frac_t ans = sum9(n);

		printf("n == %d gives %d/%d\n", n, ans.a, ans.b);

//		printf("============GCD==========\n");
//		int a = 48, b = 18;
//		printf("GCD(%d, %d) = %d\n", a, b, gcd(a, b));

		return 0;
}
