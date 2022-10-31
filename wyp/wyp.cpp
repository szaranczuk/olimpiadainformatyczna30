#include <bits/stdc++.h>
#define EL printf("\n")
#define pb push_back
#define FOR(i,l,r) for (int i=l;i<=r;i++)
#define FORD(i,r,l) for (int i=r;i>=l;i--)

using namespace std;


typedef int64_t ll;
typedef pair<int, int> ii;
typedef vector<int> BigInt;


const ll INF = 1e13;
const int base = 1e9;


void Set(BigInt &a) {
    while (a.size() > 1 && a.back() == 0) a.pop_back();
}

void Print(BigInt a) {
    Set(a);
    printf("%d", (a.size() == 0) ? 0 : a.back());
    FORD(i,a.size()-2,0) printf("%09d", a[i]); EL;
}

BigInt Integer(string s) {
    BigInt ans;
    if (s[0] == '-') return ans;
    if (s.size() == 0) {ans.pb(0); return ans;}
    while (s.size()%9 != 0) s = '0'+s;
    for (int i=0;i<s.size();i+=9) {
        int v = 0;
        for (int j=i;j<i+9;j++) v = v*10+(s[j]-'0');
        ans.insert(ans.begin(),v);
    }
    Set(ans);
    return ans;
}

BigInt Integer(char c[]) {
    string s = "";
    FOR(i,0,strlen(c)-1) s = s + c[i];
    return Integer(s);
}

BigInt Integer(ll x) {
    string s = "";
    while (x > 0) s = char(x%10+'0') + s, x /= 10;
    return Integer(s);
}

BigInt Integer(int x) {
    return Integer((ll) x);
}

void operator >> (istream &in, BigInt &a) {
    string s;
    getline(cin, s);
    a = Integer(s);
}

void operator << (ostream &out, BigInt a) {
    Print(a);
}

bool operator < (BigInt a, BigInt b) {
    Set(a);
    Set(b);
    if (a.size() != b.size()) return (a.size() < b.size());
    FORD(i,a.size()-1,0)
        if (a[i] != b[i]) return (a[i] < b[i]);
    return false;
}

bool operator > (BigInt a, BigInt b) {
    return (b < a);
}

bool operator == (BigInt a, BigInt b) {
    return (!(a < b) && !(b < a));
}

bool operator <= (BigInt a, BigInt b) {
    return (a < b || a == b);
}

bool operator >= (BigInt a, BigInt b) {
    return (b < a || b == a);
}

bool operator < (BigInt a, int b) {
    return (a < Integer(b));
}

bool operator > (BigInt a, int b) {
    return (a > Integer(b));
}

bool operator == (BigInt a, int b) {
    return (a == Integer(b));
}

bool operator >= (BigInt a, int b) {
    return (a >= Integer(b));
}

bool operator <= (BigInt a, int b) {
    return (a <= Integer(b));
}

BigInt max(BigInt a, BigInt b) {
    if (a > b) return a;
    return b;
}

BigInt min(BigInt a, BigInt b) {
    if (a < b) return a;
    return b;
}

BigInt operator + (BigInt a, BigInt b) {
    Set(a);
    Set(b);
    BigInt ans;
    int carry = 0;
    FOR(i,0,max(a.size(), b.size())-1) {
        if (i < a.size()) carry += a[i];
        if (i < b.size()) carry += b[i];
        ans.pb(carry%base);
        carry /= base;
    }
    if (carry) ans.pb(carry);
    Set(ans);
    return ans;
}

BigInt operator + (BigInt a, int b) {
    return a + Integer(b);
}

BigInt operator ++ (BigInt &a) { // ++a
    a = a + 1;
    return a;
}

void operator += (BigInt &a, BigInt b) {
    a = a + b;
}

void operator += (BigInt &a, int b) {
    a = a + b;
}

BigInt operator- (BigInt a, BigInt b) {
    Set(a);
    Set(b);
    BigInt ans;
    int carry = 0;
    FOR(i,0,a.size()-1) {
        carry += a[i] - (i < b.size() ? b[i] : 0);
        if (carry < 0) ans.pb(carry+base), carry = -1;
        else ans.pb(carry), carry = 0;
    }
    Set(ans);
    return ans;
}

BigInt operator-  (BigInt a, int b) {
    return a - Integer(b);
}

void operator -- (BigInt &a) { // --a
    a = a - 1;
}

void operator -= (BigInt &a, BigInt b) {
    a = a - b;
}

void operator -= (BigInt &a, int b) {
    a = a - b;
}

BigInt operator * (BigInt a, BigInt b) {
    Set(a);
    Set(b);
    BigInt ans;
    ans.assign(a.size()+b.size(), 0);
    FOR(i,0,a.size()-1) {
        ll carry = 0ll;
        for (int j=0;j<b.size() || carry > 0;j++) {
            ll s = ans[i+j] + carry + (ll)a[i]*(j<b.size()?(ll)b[j]:0ll);
            ans[i+j] = s%base;
            carry = s/base;
        }
    }
    Set(ans);
    return ans;
}

BigInt operator * (BigInt a, int b) {
    return a * Integer(b);
}

void operator *= (BigInt &a, BigInt b) {
    a = a * b;
}

void operator *= (BigInt &a, int b) {
    a = a * b;
}



BigInt operator / (BigInt a, BigInt b) {
    Set(a);
    Set(b);
    if (b == Integer(0)) return Integer("-1");
    BigInt ans, cur;
    FORD(i,a.size()-1,0) {
        cur.insert(cur.begin(), a[i]);
        int x = 0, L = 0, R = base;
        while (L <= R) {
            int mid = (L+R)>>1;
            if (b*Integer(mid) > cur) {
                x = mid;
                R = mid-1;
            }
            else
                L = mid+1;
        }
        cur = cur - Integer(x-1)*b;
        ans.insert(ans.begin(),x-1);
    }
    Set(ans);
    return ans;
}

BigInt operator / (BigInt a, int b) {
    Set(a);
    BigInt ans;
    ll cur = 0ll;
    FORD(i,a.size()-1,0) {
        cur = (cur*(ll)base + (ll)a[i]);
        ans.insert(ans.begin(),cur/b);
        cur %= b;
    }
    Set(ans);
    return ans;
}

void operator /= (BigInt &a, BigInt b) {
    a = a / b;
}

void operator /= (BigInt &a, int b) {
    a = a / b;
}

BigInt operator % (BigInt a, BigInt b) {
    Set(a);
    Set(b);
    if (b == Integer(0)) return Integer("-1");
    BigInt ans;
    FORD(i,a.size()-1,0) {
        ans.insert(ans.begin(), a[i]);
        int x = 0, L = 0, R = base;
        while (L <= R) {
            int mid = (L+R)>>1;
            if (b*Integer(mid) > ans) {
                x = mid;
                R = mid-1;
            }
            else
                L = mid+1;
        }
        ans = ans - Integer(x-1)*b;
    }
    Set(ans);
    return ans;
}

int operator % (BigInt a, int b) {
    Set(a);
    if (b == 0) return -1;
    int ans = 0;
    FORD(i,a.size()-1,0)
        ans = (ans*(base%b) + a[i]%b)%b;
    return ans;
}

void operator %= (BigInt &a, BigInt b) {
    a = a % b;
}

void operator %= (BigInt &a, int b) {
    a = a % Integer(b);
}

BigInt gcd(BigInt a, BigInt b) {
    Set(a);
    Set(b);
    while (b > Integer(0)) {
        BigInt r = a%b;
        a = b;
        b = r;
    }
    Set(a);
    return a;
}

BigInt lcm(BigInt a, BigInt b) {
    return (a*b/gcd(a,b));
}


BigInt sqrt(BigInt a) {
    BigInt x0 = a, x1 = (a+1)/2;
    while (x1 < x0) {
        x0 = x1;
        x1 = (x1+a/x1)/2;
    }
    return x0;
}

BigInt pow(BigInt a, BigInt b) {
    if (b == Integer(0)) return Integer(1);
    BigInt tmp = pow(a, b/2);
    if (b%2 == 0) return tmp * tmp;
    return tmp * tmp * a;
}

BigInt pow(BigInt a, int b) {
    return pow(a,(Integer(b)));
}

int log(int n, BigInt a) { // log_n(a)
    Set(a);
    int ans = 0;
    while (a > Integer(1)) {
        ans++;
        a /= n;
    }
    return ans;
}


struct rational
{
	BigInt p;
	BigInt q;
	rational() {};
	rational(BigInt _p, BigInt _q)
	{
		bool sign = false;
		if (_p < 0 && _q < 0)
		{
			_p *= -1;
			_q *= -1;
		}
		else if (_q < 0)
		{
			_q *= -1;
			sign = true;
		}
		else if (_p < 0)
		{
			_p *= -1;
			sign = true;
		}
		BigInt dupa = gcd(_p, _q);
		p = _p / dupa;
		q = _q / dupa;
		if (sign) p *= -1;
	}
};
rational operator*(const rational& a, const rational& b)
{
	return rational(a.p * b.p, a.q * b.q);
}
rational operator+(const rational& a, const rational& b)
{
	BigInt denominator_gcd = gcd(a.q, b.q);
	BigInt new_q = (max(a.q, b.q) / denominator_gcd) * min(a.q, b.q);
	BigInt new_p = a.p * (new_q / a.q) + b.p * (new_q / b.q);
	return rational(new_p, new_q);
}
rational operator+(BigInt a, const rational& b)
{
	BigInt new_p = a * b.q + b.p;
	return rational(new_p, b.q);
}
rational operator+(const rational& b, BigInt a)
{
	BigInt new_p = a * b.q + b.p;
	return rational(new_p, b.q);
}
rational operator-(BigInt a, const rational& b)
{
	BigInt new_p = a * b.q - b.p;
	return rational(new_p, b.q);
}
rational operator-(const rational& b, BigInt a)
{
	BigInt new_p = b.p - a * b.q;
	return rational(new_p, b.q);
}
void operator+=(rational& a, const rational& b)
{
	BigInt denominator_gcd = gcd(a.q, b.q);
	BigInt new_q = (max(a.q, b.q) / denominator_gcd) * min(a.q, b.q);
	BigInt new_p = a.p * (new_q / a.q) + b.p * (new_q / b.q);
	a = rational(new_p, new_q);
}
void operator-=(rational& a, const rational& b)
{
	BigInt denominator_gcd = gcd(a.q, b.q);
	BigInt new_q = (max(a.q, b.q) / denominator_gcd) * min(a.q, b.q);
	BigInt new_p = a.p * (new_q / a.q) - b.p * (new_q / b.q);
	a = rational(new_p, new_q);
}
rational operator-(const rational& a, const rational& b)
{
	BigInt denominator_gcd = gcd(a.q, b.q);
	BigInt new_q = (max(a.q, b.q) / denominator_gcd) * min(a.q, b.q);
	BigInt new_p = a.p * (new_q / a.q) - b.p * (new_q / b.q);
	return rational(new_p, new_q);
}
rational operator*(const rational&a, BigInt b)
{
	return rational(a.p * b, a.q);
}
rational operator*(BigInt b, const rational& a)
{
	return rational(a.p * b, a.q);
}
rational operator/(const rational&a, BigInt b)
{
	return rational(a.p, a.q * b);
}
rational operator/(BigInt b, const rational& a)
{
	return rational(a.q * b, a.p);
}
rational operator/(const rational& a, const rational& b)
{
	return rational(a.p * b.q, b.p * a.q);
}
bool operator<(const rational& a, const rational& b)
{
	return (a - b).p < 0;
}
bool operator>(const rational& a, const rational& b)
{
	return (a - b).p > 0;
}
bool operator<=(const rational& a, const rational& b)
{
	return (a - b).p <= 0;
}
bool operator>=(const rational& a, const rational& b)
{
	return (a - b).p >= 0;
}

struct car
{
	BigInt pos;
	BigInt len;
	rational speed;
};
typedef rational rat;
typedef pair<rat, int> ri;
typedef tuple<rat, int, int> rii;

struct dsu_s
{
	int parent;
	int rank;
	ri val;
};

vector<BigInt> len_sum;
vector<ri> t;
vector<ll> blockidx;
vector<ii> block;
vector<rii> pierdolniecie;
vector<ri> przylaczenia;
vector<dsu_s> dsu;

void makeset(int x, const ri val)
{
	dsu[x].parent = -1;
	dsu[x].rank = 0;
	dsu[x].val = val;
}
int dsufind(int x)
{
	if (dsu[x].parent == -1) return x;
	else
	{
		dsu[x].parent = dsufind(dsu[x].parent);
		return dsu[x].parent;
	}
}
void dsuunion(int x, int y, const ri val)
{
	int xp = dsufind(x);
	int yp = dsufind(y);
	if (dsu[xp].rank > dsu[yp].rank)
	{
		dsu[yp].parent = xp;
		dsu[xp].val = val;
	}
	else if (dsu[xp].rank < dsu[yp].rank)
	{
		dsu[xp].parent = yp;
		dsu[yp].val = val;
	}
	else if (xp != yp)
	{
		dsu[yp].parent = xp;
		dsu[xp].rank++;
		dsu[xp].val = val;
	}
}
int blockcnt = 0;

inline BigInt lensum(ll l, ll r)
{
	if (l == 0) return len_sum[r];
	return len_sum[r] - len_sum[l - 1];
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	ll n, D, W, M;
	cin >> n >> D >> W >> M;
	car bajtazar = {Integer(0), Integer(D), rat(Integer(W), Integer(M))};
	vector<car> trucks(n);
	vector<rat> collision_time;
	vector<rat> collision_speed;
	len_sum.resize(n);
	blockidx.resize(n);
	block.reserve(n);
	pierdolniecie.resize(n);
	t.resize(5*n);
	dsu.resize(n);
	for (int i = 0; i < n; i++) makeset(i, {rat(Integer(0), Integer(1)), i});
	for (int i = 0; i < n; i++)
	{
		if (i != 0) len_sum[i] += len_sum[i - 1];
		ll x, d, w, m;
		cin >> x >>  d >> w >> m;
		trucks[i] = {Integer(x), Integer(d), rat(Integer(w), Integer(m))};
		len_sum[i] += Integer(d);
	}
	blockidx[0] = 0;
	block.push_back({0, 0});
	for (int i = 1; i < n; i++)
	{
		if (trucks[i].speed < trucks[i - 1].speed)
		{
			block[blockcnt].second = i;
		}
		else
		{
			blockcnt++;
			block.push_back({i, i});
		}
		blockidx[i] = blockcnt;
	}
	//to jest czesc do liczenia pierdolniec
	for (int i = n - 1; i >= 0; i--)
	{
		int l = 0;
		int r = przylaczenia.size();
		int dupa = przylaczenia.size() - 1;
		while (r > l)
		{
			int s = (l + r + 1) / 2;
			int front_truck;
			rat before_t;
			if (s == przylaczenia.size())
			{
				front_truck = przylaczenia[0].second;
				before_t = rat(Integer(INF), Integer(1));
			}
			else
			{
				front_truck = przylaczenia[dupa - s].second;
				before_t = przylaczenia[dupa - s].first;
			}
			rat left_truck_pos = before_t * trucks[i].speed + trucks[i].pos;
			rat block_pos = before_t * trucks[front_truck].speed + trucks[front_truck].pos - lensum(i + 1, front_truck);
			if (left_truck_pos <= block_pos) l = s;
			else r = s - 1;
		}
		if (l == przylaczenia.size())
		{
			przylaczenia.clear();
			przylaczenia.push_back({rational(Integer(0), Integer(1)), i});
			pierdolniecie[i] = {rat(Integer(INF), Integer(1)), i, i};
		}
		else
		{
			int cnt = l + 1;
			int front_truck = przylaczenia[dupa - l].second;
			rat before_t = przylaczenia[dupa - l].first;
			rat left_truck_pos = before_t * trucks[i].speed + trucks[i].pos;
			rat block_pos = before_t * trucks[front_truck].speed + trucks[front_truck].pos - lensum(i + 1, front_truck);
			rat t = (block_pos - left_truck_pos) / (trucks[i].speed - trucks[front_truck].speed);
			ri new_entry = {before_t + t, front_truck};
			while (cnt--)
			{
				przylaczenia.erase(przylaczenia.begin() + cnt);
			}
			przylaczenia.push_back(new_entry);
			przylaczenia.push_back({rat(Integer(0), Integer(1)), i});
			pierdolniecie[i] = {before_t + t, i, front_truck};
		}
	}
	//to jest czesc do liczenia wymijen
	ll res = 1ll;
	sort(pierdolniecie.begin(), pierdolniecie.end());
	rat prev_bajtazar_pos = rat(Integer(0), Integer(1));
	int truck_idx = 1;
	for (int i = 0; i < n; i++)
	{
		rat t = get<0>(pierdolniecie[i]);
		int back_truck = get<1>(pierdolniecie[i]);
		int front_truck = get<2>(pierdolniecie[i]);
		rat bajtazar_pos = bajtazar.speed * t;
		ri dupa = dsu[dsufind(truck_idx)].val;
		rat last_truck_pos = trucks[dupa.second].speed * t + trucks[dupa.second].pos - lensum(truck_idx, dupa.second);
		while (truck_idx < n && last_truck_pos <= bajtazar_pos)
		{
			if (dsufind(truck_idx) != dsufind(truck_idx - 1))
			{
				int front_truck = dsu[dsufind(truck_idx)].val.second;
				rat t = (trucks[front_truck].pos - lensum(truck_idx, front_truck)) / (bajtazar.speed - trucks[front_truck].speed);
				rat right_truck_pos = t * trucks[front_truck].speed + trucks[front_truck].pos - lensum(truck_idx, front_truck);
				rat left_truck_pos = trucks[truck_idx - 1].speed * t + trucks[truck_idx - 1].pos;
				if (right_truck_pos - left_truck_pos >= rat(bajtazar.len, Integer(1))) res++;
			}
			truck_idx++;
			if (truck_idx < n)
			{
				dupa = dsu[dsufind(truck_idx)].val;
				last_truck_pos = trucks[dupa.second].speed * t + trucks[dupa.second].pos - lensum(truck_idx, dupa.second);
			}
		}
		dsuunion(back_truck, front_truck, {t, front_truck});
	}
	cout << res << '\n';
}