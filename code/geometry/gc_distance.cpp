ld gc_distance(ld pLat, ld pLong, ld qLat, ld qLong, ld r) {
	pLat *= pi / 180; pLong *= pi / 180;
	qLat *= pi / 180; qLong *= pi / 180;
	return r * acos(cos(pLat)*cos(qLat)*cos(pLong - qLong) + sin(pLat)*sin(qLat)); }
