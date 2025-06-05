#include<stdio.h>
#define XMAX 100
#define YMAX 100
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)
struct point {
	int x;
	int y;
};
struct rect {
	struct point pt1;
	struct point pt2;
};
struct point makepoint(int x, int y);
struct point addpoint(struct point p1, struct point p2);
int ptinrect(struct point p, struct rect r);
struct rect canonrect(struct rect r);
int main()
{
	struct rect screen;
	struct point middle;
	screen.pt1 = makepoint(0, 0);
	screen.pt2 = makepoint(XMAX, YMAX);
	middle = makepoint((screen.pt1.x + screen.pt2.x) / 2, (screen.pt1.y + screen.pt2.y) / 2);
	printf("Middle point's x=%d,y=%d\n", middle.x, middle.y);
	struct point test = { 20,1000 };
	int flag;
	flag = ptinrect(test, screen);
	if (flag)
		printf("point is in rectangle.\n");
	else
		printf("point is not in rectangle.\n");
	struct rect test1;
	test1.pt1 = makepoint(10, 2);
	test1.pt2 = makepoint(2, 10);
	test1 = canonrect(test1);
	printf("point1 x=%d,y=%d; point2 x=%d, y=%d.\n", test1.pt1.x, test1.pt1.y, test1.pt2.x, test1.pt2.y);
	struct point* pp;
	pp = &middle;
	printf("middle point x=%d,y=%d.\n", (*pp).x, (*pp).y); 
	printf("middle point x=%d,y=%d.\n", pp->x, pp->y);
}
//makepoint: make a point from x and y components
struct point makepoint(int x, int y)
{
	struct point temp;
	temp.x = x;
	temp.y = y;
	return temp;
}
//addpoint: add two points
struct point addpoint(struct point p1, struct point p2)
{
	p1.x += p2.x;
	p1.y += p2.y;
	return p1;
}
//ptinrect: return 1 if p in r, 0 if not.
int ptinrect(struct point p, struct rect r)
{
	return p.x >= r.pt1.x && p.x < r.pt2.x && p.y >= r.pt1.y && p.y < r.pt2.y;
}
//canonrect:canonicalize coordinates of rectangles
struct rect canonrect(struct rect r)
{
	struct rect temp;
	temp.pt1.x = min(r.pt1.x, r.pt2.x);
	temp.pt1.y = min(r.pt1.y, r.pt2.y);
	temp.pt2.x = max(r.pt1.x, r.pt2.x);
	temp.pt2.y = max(r.pt1.y, r.pt2.y);
	return temp;
}