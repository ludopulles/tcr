typedef complex<double> cpx;
const int LOGN = 19, MAXN = 1 << LOGN;

int rev[MAXN];
cpx rt[MAXN], a[MAXN] = {}, b[MAXN] = {};

void fft(cpx *A) {
	REP(i, MAXN) if (i < rev[i]) swap(A[i], A[rev[i]]);
	for (int k = 1; k < MAXN; k *= 2)
		for (int i = 0; i < MAXN; i += 2*k) REP(j, k) {
				cpx t = rt[j + k] * A[i + j + k];
				A[i + j + k] = A[i + j] - t;
				A[i + j] += t;
			}
}

void multiply() { // a = convolution of a * b
	const ld PI = acos(-1.0);
	rev[0] = 0; rt[1] = cpx(1, 0);
	REP(i, MAXN) rev[i] = (rev[i/2] | (i&1)<<LOGN)/2;
	for (int k = 2; k < MAXN; k *= 2) {
		cpx z(cos(PI/k), sin(PI/k));
		rep(i, k/2, k) rt[2*i]=rt[i], rt[2*i+1]=rt[i]*z;
	}
	fft(a); fft(b);
	REP(i, MAXN) a[i] *= b[i] / (double)MAXN;
	reverse(a+1,a+MAXN); fft(a);
}
