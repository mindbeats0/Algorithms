#include<cstdio>
#include<cstring>
#include<cmath>
#include<complex>
#include<map>
#include<vector>
#include<algorithm>
using namespace std ;

const double EPS = 1e-9;
const double PI = 3.14159265358979323846;
const int MAXN = 3e5;
const int MAXM = 1500;

typedef complex<double> Point;
#define X real()
#define Y imag()
#define rotate(v, theta) ((v) * exp(Point(0, theta)))
#define ang(v) atan2((v).Y, (v).X)
#define vec(a, b) ((b) - (a))
#define degree(a) ((a) * 180 / PI)
#define mid(a,b) (Point((a).X + (b).X, (a).Y + (b).Y) / 2.0)
#define dot(a,b) (conj(a) * (b)).X
#define dist(a,b) sqrt(dot(vec(a,b),vec(a,b)))

inline double lineAngle(const Point& p1, const Point& p2) {
    double a = ang(vec(p1,p2));
    if (a < -EPS) a += PI;
    return a;
}

class Cmp {
public:
    bool operator () (const pair<double, double> &a, const pair<double, double> &b) const {
        if (fabs(a.first - b.first) > EPS) return a.first < b.first;
        return a.second + EPS < b.second;
    }

};

class Circle {
public:
    int x,y,r;
    Circle(){}
    Circle(int x,int y,int r) : x(x),y(y),r(r){}
}circles[MAXM + 5];

bool valid(const Circle& c1, const Circle& c2) {
    if (c1.r != c2.r) return false;
    if (dist(Point(c1.x,c1.y),Point(c2.x,c2.y)) - EPS < c1.r + c2.r) return false;
    return true;
}

class Event {
public:
    enum Type {START = 1, END = 2, LINE = 0} type;
    double v;
    Event() {}
    Event(Type type, double v) : type(type), v(v) {}
    bool operator < (const Event& that) const {
        if (fabs(this->v - that.v) > EPS) return this->v < that.v;
        return this->type < that.type;
    }
};

map<pair<double, double>, int, Cmp> ix;
vector<Event> events[MAXN + 5];
int n,m;

int getIndex(double a, double y) {
    return ix.insert(make_pair(make_pair(a, y), ix.size())).first->second;
}

int main() {
//    freopen("owls.in","r",stdin);
    int c,c2;
    scanf("%d%d",&n,&m);
    for (c=0;c<n;c++) {
        int x1,y1,x2,y2;
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        double a = lineAngle(Point(x1,y1), Point(x2,y2));
        Point p1(rotate(Point(x1,y1), -a)), p2(rotate(Point(x2,y2), -a));
        if (p1.X > p2.X) swap(p1,p2);
        int i = getIndex(a, p1.Y);
        events[i].push_back(Event(Event::START, p1.X));
        events[i].push_back(Event(Event::END, p2.X));
    }
    for (c=0;c<m;c++) {
        int x,y,r;
        scanf("%d%d%d",&x,&y,&r);
        circles[c] = Circle(x,y,r);
    }
    for (c=0;c<m;c++) {
        for (c2=c+1;c2<m;c2++) {
            if (!valid(circles[c],circles[c2]))continue;
            Point p1(circles[c].x,circles[c].y), p2(circles[c2].x, circles[c2].y);
            double a = lineAngle(p1 ,p2);
            if (a + EPS < PI / 2.0) a += PI / 2.0;
            else a -= PI / 2.0;
            p1 = rotate(p1, -a);
            p2 = rotate(p2, -a);
            double mid = mid(p1, p2).Y;
            if (ix.count(make_pair(a, mid)) == 0) continue;
            events[ix[make_pair(a, mid)]].push_back(Event(Event::LINE,p1.X));
        }
    }
    long long ret = 0;
    for (c=0;c<ix.size();c++) {
        sort(events[c].begin(), events[c].end());
        int open = 0;
        for (c2=0;c2<events[c].size();) {
            int l = 0;
            double v = events[c][c2].v;
            for (;c2 < events[c].size() && fabs(events[c][c2].v - v) < EPS
                && events[c][c2].type == Event::LINE;c2++,l++);
            for (;c2 < events[c].size() && fabs(events[c][c2].v - v) < EPS
                && events[c][c2].type == Event::START;c2++,open++);
            ret += 1LL * open * l;
            for (;c2 < events[c].size() && fabs(events[c][c2].v - v) < EPS
                && events[c][c2].type == Event::END;c2++,open--);
        }
    }
    printf("%I64d\n",ret);
    return 0;
}
