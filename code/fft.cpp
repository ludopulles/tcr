typedef complex<double> cpx;
const int logmaxn = 20, maxn = 1 << logmaxn;

cpx a[maxn] = {}, b[maxn] = {}, c[maxn];

void fft(cpx *src, cpx *dest) {
	for (int i = 0, rep = 0; i < maxn; i++, rep = 0) {
		for (int j = i, k = logmaxn; k--; j >>= 1) rep = (rep << 1) | (j & 1);
		dest[rep] = src[i];
	}
	for (int s = 1, m = 1; m <= maxn; s++, m *= 2) {
		cpx r = exp(cpx(0, 2.0 * PI / m));
		for (int k = 0; k < maxn; k += m) {
			cpx cr(1.0, 0.0);
			for (int j = 0; j < m / 2; j++) {
				cpx t = cr * dest[k + j + m / 2]; dest[k + j + m / 2] = dest[k + j] - t;
				dest[k + j] += t; cr *= r;
			}
		}
	}
}

void multiply() {
	fft(a, c); fft(b, a);
	for (int i = 0; i < maxn; i++) b[i] = conj(a[i] * c[i]);
	fft(b, c);
	for (int i = 0; i < maxn; i++) c[i] = conj(c[i]) / (1.0 * maxn);
}
