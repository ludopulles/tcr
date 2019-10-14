ld perimeter(point a, point b, point c) {
  return dist(a, b) + dist(b, c) + dist(c, a); }

ld area(ld ab, ld bc, ld ca) {
 // Heron's formula
  ld s = 0.5 * (ab+bc+ca);
  return sqrt(s)*sqrt(s-ab)*sqrt(s-bc)*sqrt(s-ca);
}
ld area(point a, point b, point c) {
  return area(dist(a, b), dist(b, c), dist(c, a));
}
ld rInCircle(ld ab, ld bc, ld ca) {
  return area(ab,bc,ca)*2.0 / (ab+bc+ca);
}

ld rInCircle(point a, point b, point c) {
  return rInCircle(dist(a,b),dist(b,c),dist(c,a));
}
// assumption: the required points/lines functions
// have been written.
// Returns if there is an inCircle center
// if it returns TRUE, ctr will be the inCircle
// center and r is the same as rInCircle
int inCircle(point p1, point p2, point p3, point &ctr, ld &r) {
  r = rInCircle(p1, p2, p3);
  if (fabs(r) < EPS) return false;

  line l1, l2; // compute these two angle bisectors
  ld ratio = dist(p1, p2) / dist(p1, p3);
  point p = translate(p2,
    scale(toVec(p2, p3), ratio / (1 + ratio)));
  pointsToLine(p1, p, l1);

  ratio = dist(p2, p1) / dist(p2, p3);
  p = translate(p1,
    scale(toVec(p1, p3), ratio / (1 + ratio)));
  pointsToLine(p2, p, l2);
  // get their intersection point:
  areIntersect(l1, l2, ctr);
  return true;
}

ld rCircumCircle(ld ab, ld bc, ld ca) {
  return ab * bc * ca / (4.0 * area(ab, bc, ca)); }

ld rCircumCircle(point a, point b, point c) {
  return rCircumCircle(
      dist(a,b), dist(b,c), dist(c,a));
}

// assumption: the required points/lines functions
// have been written.
// Returns 1 iff there is a circumCenter center
// if this function returns 1, ctr will be the
// circumCircle center and r = rCircumCircle
bool circumCircle(point p1, point p2, point p3, point &ctr, ld &r){
  ld a = p2.x - p1.x, b = p2.y - p1.y;
  ld c = p3.x - p1.x, d = p3.y - p1.y;
  ld e = a * (p1.x + p2.x) + b * (p1.y + p2.y);
  ld f = c * (p1.x + p3.x) + d * (p1.y + p3.y);
  ld g = 2.0 * (a * (p3.y-p2.y) - b * (p3.x-p2.x));
  if (fabs(g) < EPS) return false; 

  ctr.x = (d*e - b*f) / g;
  ctr.y = (a*f - c*e) / g;
  r = dist(p1, ctr); // r = dist(center, p_i)
  return true;
}

// returns if pt d is inside the circumCircle
// defined by a,b,c
bool inCircumCircle(point a, point b,
    point c, point d) {
  vec va=toVec(a,d), vb=toVec(b,d), vc=toVec(c,d);
  return 0 <
   va.x * vb.y * (vc.x*vc.x + vc.y*vc.y) +
   va.y * (vb.x*vb.x + vb.y*vb.y) * vc.x +
   (va.x*va.x + va.y*va.y) * vb.x * vc.y -
   (va.x*va.x + va.y*va.y) * vb.y * vc.x -
   va.y * vb.x * (vc.x*vc.x + vc.y*vc.y) -
   va.x * (vb.x*vb.x+vb.y*vb.y) * vc.y;
}

bool canFormTriangle(ld a, ld b, ld c) {
  return a+b > c && a+c > b && b+c > a; }
