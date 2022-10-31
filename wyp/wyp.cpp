#include <bits/stdc++.h>
#define EL printf("\n")
#define pb push_back
#define FOR(i,l,r) for (int i=l;i<=r;i++)
#define FORD(i,r,l) for (int i=r;i>=l;i--)
#define Integer(x) bigint(x)

using namespace std;


typedef int64_t int64;
typedef int64_t ll;
typedef pair<int, int> ii;
const int bignumlen = 2200;
const int Blen = 8;


const ll INF = 1e13;
const int base = 1000000000;
const int base_digits = 9; 
struct bigint {
	vector<int> a;
	int sign;
	/*<arpa>*/
	int size(){
		if(a.empty())return 0;
		int ans=(a.size()-1)*base_digits;
		int ca=a.back();
		while(ca)
			ans++,ca/=10;
		return ans;
	}
	bigint operator ^(const bigint &v){
		bigint ans=1,a=*this,b=v;
		while(!b.isZero()){
			if(b%2)
				ans*=a;
			a*=a,b/=2;
		}
		return ans;
	}
	string to_string(){
		stringstream ss;
		ss << *this;
		string s;
		ss >> s;
		return s;
	}
	int sumof(){
		string s = to_string();
		int ans = 0;
		for(auto c : s)  ans += c - '0';
		return ans;
	}
	/*</arpa>*/
	bigint() :
		sign(1) {
	}
 
	bigint(long long v) {
		*this = v;
	}
 
	bigint(const string &s) {
		read(s);
	}
 
	void operator=(const bigint &v) {
		sign = v.sign;
		a = v.a;
	}
 
	void operator=(long long v) {
		sign = 1;
		a.clear();
		if (v < 0)
			sign = -1, v = -v;
		for (; v > 0; v = v / base)
			a.push_back(v % base);
	}
 
	bigint operator+(const bigint &v) const {
		if (sign == v.sign) {
			bigint res = v;
 
			for (int i = 0, carry = 0; i < (int) max(a.size(), v.a.size()) || carry; ++i) {
				if (i == (int) res.a.size())
					res.a.push_back(0);
				res.a[i] += carry + (i < (int) a.size() ? a[i] : 0);
				carry = res.a[i] >= base;
				if (carry)
					res.a[i] -= base;
			}
			return res;
		}
		return *this - (-v);
	}
 
	bigint operator-(const bigint &v) const {
		if (sign == v.sign) {
			if (abs() >= v.abs()) {
				bigint res = *this;
				for (int i = 0, carry = 0; i < (int) v.a.size() || carry; ++i) {
					res.a[i] -= carry + (i < (int) v.a.size() ? v.a[i] : 0);
					carry = res.a[i] < 0;
					if (carry)
						res.a[i] += base;
				}
				res.trim();
				return res;
			}
			return -(v - *this);
		}
		return *this + (-v);
	}
 
	void operator*=(int v) {
		if (v < 0)
			sign = -sign, v = -v;
		for (int i = 0, carry = 0; i < (int) a.size() || carry; ++i) {
			if (i == (int) a.size())
				a.push_back(0);
			long long cur = a[i] * (long long) v + carry;
			carry = (int) (cur / base);
			a[i] = (int) (cur % base);
			//asm("divl %%ecx" : "=a"(carry), "=d"(a[i]) : "A"(cur), "c"(base));
		}
		trim();
	}
 
	bigint operator*(int v) const {
		bigint res = *this;
		res *= v;
		return res;
	}
 
	void operator*=(long long v) {
		if (v < 0)
			sign = -sign, v = -v;
		if(v > base){
			*this = *this * (v / base) * base + *this * (v % base);
			return ;
		}
		for (int i = 0, carry = 0; i < (int) a.size() || carry; ++i) {
			if (i == (int) a.size())
				a.push_back(0);
			long long cur = a[i] * (long long) v + carry;
			carry = (int) (cur / base);
			a[i] = (int) (cur % base);
			//asm("divl %%ecx" : "=a"(carry), "=d"(a[i]) : "A"(cur), "c"(base));
		}
		trim();
	}
 
	bigint operator*(long long v) const {
		bigint res = *this;
		res *= v;
		return res;
	}
 
	friend pair<bigint, bigint> divmod(const bigint &a1, const bigint &b1) {
		int norm = base / (b1.a.back() + 1);
		bigint a = a1.abs() * norm;
		bigint b = b1.abs() * norm;
		bigint q, r;
		q.a.resize(a.a.size());
 
		for (int i = a.a.size() - 1; i >= 0; i--) {
			r *= base;
			r += a.a[i];
			int s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];
			int s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
			int d = ((long long) base * s1 + s2) / b.a.back();
			r -= b * d;
			while (r < 0)
				r += b, --d;
			q.a[i] = d;
		}
 
		q.sign = a1.sign * b1.sign;
		r.sign = a1.sign;
		q.trim();
		r.trim();
		return make_pair(q, r / norm);
	}
 
	bigint operator/(const bigint &v) const {
		return divmod(*this, v).first;
	}
 
	bigint operator%(const bigint &v) const {
		return divmod(*this, v).second;
	}
 
	void operator/=(int v) {
		if (v < 0)
			sign = -sign, v = -v;
		for (int i = (int) a.size() - 1, rem = 0; i >= 0; --i) {
			long long cur = a[i] + rem * (long long) base;
			a[i] = (int) (cur / v);
			rem = (int) (cur % v);
		}
		trim();
	}
 
	bigint operator/(int v) const {
		bigint res = *this;
		res /= v;
		return res;
	}
 
	int operator%(int v) const {
		if (v < 0)
			v = -v;
		int m = 0;
		for (int i = a.size() - 1; i >= 0; --i)
			m = (a[i] + m * (long long) base) % v;
		return m * sign;
	}
 
	void operator+=(const bigint &v) {
		*this = *this + v;
	}
	void operator-=(const bigint &v) {
		*this = *this - v;
	}
	void operator*=(const bigint &v) {
		*this = *this * v;
	}
	void operator/=(const bigint &v) {
		*this = *this / v;
	}
 
	bool operator<(const bigint &v) const {
		if (sign != v.sign)
			return sign < v.sign;
		if (a.size() != v.a.size())
			return a.size() * sign < v.a.size() * v.sign;
		for (int i = a.size() - 1; i >= 0; i--)
			if (a[i] != v.a[i])
				return a[i] * sign < v.a[i] * sign;
		return false;
	}
 
	bool operator>(const bigint &v) const {
		return v < *this;
	}
	bool operator<=(const bigint &v) const {
		return !(v < *this);
	}
	bool operator>=(const bigint &v) const {
		return !(*this < v);
	}
	bool operator==(const bigint &v) const {
		return !(*this < v) && !(v < *this);
	}
	bool operator!=(const bigint &v) const {
		return *this < v || v < *this;
	}
 
	void trim() {
		while (!a.empty() && !a.back())
			a.pop_back();
		if (a.empty())
			sign = 1;
	}
 
	bool isZero() const {
		return a.empty() || (a.size() == 1 && !a[0]);
	}
 
	bigint operator-() const {
		bigint res = *this;
		res.sign = -sign;
		return res;
	}
 
	bigint abs() const {
		bigint res = *this;
		res.sign *= res.sign;
		return res;
	}
 
	long long longValue() const {
		long long res = 0;
		for (int i = a.size() - 1; i >= 0; i--)
			res = res * base + a[i];
		return res * sign;
	}
 
	friend bigint gcd(const bigint &a, const bigint &b) {
		return b.isZero() ? a : gcd(b, a % b);
	}
	friend bigint lcm(const bigint &a, const bigint &b) {
		return a / gcd(a, b) * b;
	}
 
	void read(const string &s) {
		sign = 1;
		a.clear();
		int pos = 0;
		while (pos < (int) s.size() && (s[pos] == '-' || s[pos] == '+')) {
			if (s[pos] == '-')
				sign = -sign;
			++pos;
		}
		for (int i = s.size() - 1; i >= pos; i -= base_digits) {
			int x = 0;
			for (int j = max(pos, i - base_digits + 1); j <= i; j++)
				x = x * 10 + s[j] - '0';
			a.push_back(x);
		}
		trim();
	}
 
	friend istream& operator>>(istream &stream, bigint &v) {
		string s;
		stream >> s;
		v.read(s);
		return stream;
	}
 
	friend ostream& operator<<(ostream &stream, const bigint &v) {
		if (v.sign == -1)
			stream << '-';
		stream << (v.a.empty() ? 0 : v.a.back());
		for (int i = (int) v.a.size() - 2; i >= 0; --i)
			stream << setw(base_digits) << setfill('0') << v.a[i];
		return stream;
	}
 
	static vector<int> convert_base(const vector<int> &a, int old_digits, int new_digits) {
		vector<long long> p(max(old_digits, new_digits) + 1);
		p[0] = 1;
		for (int i = 1; i < (int) p.size(); i++)
			p[i] = p[i - 1] * 10;
		vector<int> res;
		long long cur = 0;
		int cur_digits = 0;
		for (int i = 0; i < (int) a.size(); i++) {
			cur += a[i] * p[cur_digits];
			cur_digits += old_digits;
			while (cur_digits >= new_digits) {
				res.push_back(int(cur % p[new_digits]));
				cur /= p[new_digits];
				cur_digits -= new_digits;
			}
		}
		res.push_back((int) cur);
		while (!res.empty() && !res.back())
			res.pop_back();
		return res;
	}
 
	typedef vector<long long> vll;
 
	static vll karatsubaMultiply(const vll &a, const vll &b) {
		int n = a.size();
		vll res(n + n);
		if (n <= 32) {
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					res[i + j] += a[i] * b[j];
			return res;
		}
 
		int k = n >> 1;
		vll a1(a.begin(), a.begin() + k);
		vll a2(a.begin() + k, a.end());
		vll b1(b.begin(), b.begin() + k);
		vll b2(b.begin() + k, b.end());
 
		vll a1b1 = karatsubaMultiply(a1, b1);
		vll a2b2 = karatsubaMultiply(a2, b2);
 
		for (int i = 0; i < k; i++)
			a2[i] += a1[i];
		for (int i = 0; i < k; i++)
			b2[i] += b1[i];
 
		vll r = karatsubaMultiply(a2, b2);
		for (int i = 0; i < (int) a1b1.size(); i++)
			r[i] -= a1b1[i];
		for (int i = 0; i < (int) a2b2.size(); i++)
			r[i] -= a2b2[i];
 
		for (int i = 0; i < (int) r.size(); i++)
			res[i + k] += r[i];
		for (int i = 0; i < (int) a1b1.size(); i++)
			res[i] += a1b1[i];
		for (int i = 0; i < (int) a2b2.size(); i++)
			res[i + n] += a2b2[i];
		return res;
	}
 
	bigint operator*(const bigint &v) const {
		vector<int> a6 = convert_base(this->a, base_digits, 6);
		vector<int> b6 = convert_base(v.a, base_digits, 6);
		vll a(a6.begin(), a6.end());
		vll b(b6.begin(), b6.end());
		while (a.size() < b.size())
			a.push_back(0);
		while (b.size() < a.size())
			b.push_back(0);
		while (a.size() & (a.size() - 1))
			a.push_back(0), b.push_back(0);
		vll c = karatsubaMultiply(a, b);
		bigint res;
		res.sign = sign * v.sign;
		for (int i = 0, carry = 0; i < (int) c.size(); i++) {
			long long cur = c[i] + carry;
			res.a.push_back((int) (cur % 1000000));
			carry = (int) (cur / 1000000);
		}
		res.a = convert_base(res.a, 6, base_digits);
		res.trim();
		return res;
	}
};

typedef bigint BigInt;

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
rational operator*(rational a, rational b)
{
	return rational(a.p * b.p, a.q * b.q);
}
rational operator+(rational a, rational b)
{
	BigInt denominator_gcd = gcd(a.q, b.q);
	BigInt dupa = max(a.p, b.q);
	BigInt new_q = (dupa / denominator_gcd) * min(a.q, b.q);
	BigInt new_p = a.p * (new_q / a.q) + b.p * (new_q / b.q);
	return rational(new_p, new_q);
}
rational operator+(BigInt a, const rational b)
{
	BigInt new_p = a * b.q + b.p;
	return rational(new_p, b.q);
}
rational operator+(const rational b, BigInt a)
{
	BigInt new_p = a * b.q + b.p;
	return rational(new_p, b.q);
}
rational operator-(BigInt a, const rational b)
{
	BigInt new_p = a * b.q - b.p;
	return rational(new_p, b.q);
}
rational operator-(rational b, BigInt a)
{
	BigInt new_p = b.p - a * b.q;
	return rational(new_p, b.q);
}
void operator+=(rational& a, rational b)
{
	BigInt denominator_gcd = gcd(a.q, b.q);
	BigInt dupa = max(a.q, b.q);
	BigInt new_q = (dupa / denominator_gcd) * min(a.q, b.q);
	BigInt new_p = a.p * (new_q / a.q) + b.p * (new_q / b.q);
	a = rational(new_p, new_q);
}
void operator-=(rational& a, rational b)
{
	BigInt denominator_gcd = gcd(a.q, b.q);
	BigInt dupa = max(a.q, b.q);
	BigInt new_q = (dupa / denominator_gcd) * min(a.q, b.q);
	BigInt new_p = a.p * (new_q / a.q) - b.p * (new_q / b.q);
	a = rational(new_p, new_q);
}
rational operator-(rational a, rational b)
{
	BigInt denominator_gcd = gcd(a.q, b.q);
	BigInt dupa = max(a.q, b.q);
	BigInt new_q = (dupa / denominator_gcd) * min(a.q, b.q);
	BigInt new_p = a.p * (new_q / a.q) - b.p * (new_q / b.q);
	return rational(new_p, new_q);
}
rational operator*(rational a, BigInt b)
{
	return rational(a.p * b, a.q);
}
rational operator*(BigInt b, rational a)
{
	return rational(a.p * b, a.q);
}
rational operator/(rational a, BigInt b)
{
	return rational(a.p, a.q * b);
}
rational operator/(BigInt b, rational a)
{
	return rational(a.q * b, a.p);
}
rational operator/(rational a, rational b)
{
	return rational(a.p * b.q, b.p * a.q);
}
bool operator<(rational a, rational b)
{
	return (a - b).p < 0;
}
bool operator>(rational a, rational b)
{
	return (a - b).p > 0;
}
bool operator<=(rational a, rational b)
{
	return (a - b).p <= 0;
}
bool operator>=(rational a, rational b)
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