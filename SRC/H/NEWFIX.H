//DeadCode JIM 11Aug00 #include <malloc.h>
//DeadCode JIM 11Aug00 inline	void	*operator	new(size_t s)
//DeadCode JIM 11Aug00 {
//DeadCode JIM 11Aug00 	return	malloc(s);
//DeadCode JIM 11Aug00 }
//DeadCode JIM 11Aug00 inline	void	*operator	new[](size_t s)
//DeadCode JIM 11Aug00 {
//DeadCode JIM 11Aug00 	return	malloc(s);
//DeadCode JIM 11Aug00 }
//DeadCode JIM 11Aug00 inline	void	operator	delete(void* v)
//DeadCode JIM 11Aug00 {
//DeadCode JIM 11Aug00 	free(v);
//DeadCode JIM 11Aug00 }
//DeadCode JIM 11Aug00 inline	void	operator	delete[](void* v)
//DeadCode JIM 11Aug00 {
//DeadCode JIM 11Aug00 	free(v);
//DeadCode JIM 11Aug00 }

