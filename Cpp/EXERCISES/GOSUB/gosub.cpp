
/* original idea by Bisqwit:  youtube/bisqwit */

#include <cstdio>
#include <stack>
static std::stack<void*> __gosub_sp;

int main(void)
{

	#define GOSUB(x) { __label__ n; __gosub_sp.push(&&n); goto x; n: ; }
	#define RETURN_FROM_LABEL() do { if(! __gosub_sp.size() ) break; void*r = __gosub_sp.top(); __gosub_sp.pop(); goto *r; }while(0);


	GOSUB(print_A);
	std::puts("Second Line");




	print_A:
		std::puts("Firts Line");
		RETURN_FROM_LABEL();


}
