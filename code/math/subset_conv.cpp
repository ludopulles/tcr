for (int b = 1; b < (1 << k); b <<= 1)
	for (int i = 0; i < (1<<k); i++)
		if (!(i & b)) a[i | b] += a[i];
// inv: if (!(i & b)) a[i | b] -= a[i];
