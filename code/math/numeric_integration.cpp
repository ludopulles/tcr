ld numint(ld (*f)(ld), ld a, ld b, ld EPS = 1e-6) {
	ld ba = b - a, m=(a+b)/2;
	return abs(ba) < EPS
		? ba/8*(f(a)+f(b)+f(a+ba/3)*3+f(b-ba/3)*3)
		: numint(f,a,m,EPS) + numint(f,m,b,EPS);
}
