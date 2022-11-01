#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long btype;
typedef pair<int, int> ii;

const int BIGSIZE = 2;
const int BTYPESIZE = 60;

const int BASE_DIGITS = 9;
const int BASE = 1000000000;

struct BigInt 
{
	btype a[2];
};

bool operator<(const BigInt& a, const BigInt& b)
{
	if (a.a[1] == b.a[1])
	{
		return a.a[0] < b.a[0];
	}
	else
	{
		return a.a[1] < b.a[1];
	}
}
bool operator>(const BigInt& a, const BigInt& b)
{
	if (a.a[1] == b.a[1])
	{
		return a.a[0] > b.a[0];
	}
	else
	{
		return a.a[1] > b.a[1];
	}
}

BigInt operator+(const BigInt& a, const BigInt& b)
{
	BigInt res;
	res.a[0] = a.a[0] + b.a[0];
	int mask = 0;
	for (int i = 0; i < BTYPESIZE; i++) mask |= (1 << i);
	res.a[1] = (res.a[0] & (~mask)) >> BTYPESIZE;
	res.a[0] &= mask;
	res.a[1] += a.a[1] + b.a[1];
	return res;
}
BigInt operator-(const BigInt& a, const BigInt& b)
{
	BigInt res;
	res.a[1] = a.a[1] - b.a[1];
	bool flag = false;
	if (a.a[0] < b.a[0])
	{
		btype add = b.a[0] - a.a[0];
	}
	int mask = 0;
	for (int i = 0; i < BTYPESIZE; i++) mask |= (1 << i);
	res.a[1] = res.a[0] & (~mask);
	res.a[0] &= mask;
	res.a[1] += a.a[1] + b.a[1];
	return res;
}

    namespace MostSignificantBit {
        
        const int SIZE = 1 << 16;
        
        uint8_t table[SIZE];
        
        bool WasInitialized() { return table[2]; }
        
        bool Init() {
            for (int i = 1; i < SIZE; ++i) {
                for (uint8_t pow = 0; pow < 16; ++pow) {
                    if ((i >> pow) & 1) {
                        table[i] = pow;
                    }
                }
            }
            return true;
        }
        
        int Get(int value) { return WasInitialized() || Init(), table[value & (SIZE-1)]; }
    }
    
    struct uint128_t {
        
        uint64_t high, low;
        
        uint128_t(uint64_t high_, uint64_t low_) : high(high_), low(low_) { }
        
        uint128_t(uint64_t low_ = 0) : high(0), low(low_) { }
    };
    
    bool operator==(uint128_t lhs, uint128_t rhs) { return lhs.low == rhs.low && lhs.high == rhs.high; }
    bool operator<=(uint128_t lhs, uint128_t rhs) { return lhs.high < rhs.high || (lhs.high == rhs.high && lhs.low <= rhs.low); }
    bool operator>=(uint128_t lhs, uint128_t rhs) { return rhs <= lhs; }
    bool operator!=(uint128_t lhs, uint128_t rhs) { return !(lhs == rhs); }
    bool operator< (uint128_t lhs, uint128_t rhs) { return !(lhs >= rhs); }
    bool operator> (uint128_t lhs, uint128_t rhs) { return !(lhs <= rhs); }
    
    int mostSignificantBit32(uint32_t value) {
        return (value >> 16) ? MostSignificantBit::Get(value >> 16) + 16 : MostSignificantBit::Get(value);
    }
    
    int mostSignificantBit64(uint64_t value) {
        return (value >> 32) ? mostSignificantBit32(uint32_t(value >> 32)) + 32 : mostSignificantBit32(value & ~uint32_t(0));
    }
    
    int mostSignificantBit(uint128_t value) {
        return value.high ? mostSignificantBit64(value.high) + 64 : mostSignificantBit64(value.low);
    }
    
    uint128_t operator+(uint128_t lhs, uint128_t rhs) {
        uint128_t ret(lhs.high + rhs.high, lhs.low + rhs.low);
        ret.high += (ret.low < lhs.low);
        return ret;
    }
    
    uint128_t operator-(uint128_t lhs, uint128_t rhs) {
        uint128_t ret(lhs.high - rhs.high, lhs.low - rhs.low);
        ret.high -= (lhs.low < ret.low);
        return ret;
    }
    
    uint128_t& operator+=(uint128_t& lhs, uint128_t rhs) { return lhs = lhs + rhs; }
    uint128_t& operator-=(uint128_t& lhs, uint128_t rhs) { return lhs = lhs - rhs; }
    
    uint128_t operator<<(uint128_t lhs, int cnt) {
        if (cnt == 0) { return lhs; }
        if (cnt >= 64) { return uint128_t(lhs.low << (cnt - 64), 0); }
        return uint128_t((lhs.high << cnt) | (lhs.low >> (64-cnt)), lhs.low << cnt);
    }
    
    uint128_t operator>>(uint128_t lhs, int cnt) {
        if (cnt == 0) { return lhs; }
        if (cnt >= 64) { return uint128_t(lhs.high >> (cnt-64)); }
        return uint128_t(lhs.high >> cnt, (lhs.low >> cnt) | (lhs.high << (64 - cnt)));
    }
    
    uint128_t& operator>>=(uint128_t& lhs, int cnt) { return lhs = lhs >> cnt; }
    uint128_t& operator<<=(uint128_t& lhs, int cnt) { return lhs = lhs << cnt; }
    
    uint128_t operator*(uint128_t lhs, uint128_t rhs) {
        uint64_t a32 = lhs.low >> 32, a00 = lhs.low & 0xffffffff;
        uint64_t b32 = rhs.low >> 32, b00 = rhs.low & 0xffffffff;
        uint128_t ret(lhs.high * rhs.low + lhs.low * rhs.high + a32 * b32, a00 * b00);
        return ret + (uint128_t(a32 * b00) << 32) + (uint128_t(a00 * b32) << 32);
    }
    
    void DivMod(uint128_t a, uint128_t b, uint128_t &q, uint128_t &r) {
        assert(b.low | b.high);
        if (a < b) { q = 0, r = a; return; }
        if (a == b) { q = 1, r = 0; return; }
        const int shift = mostSignificantBit(a) - mostSignificantBit(b);
        q = 0, r = a, b <<= shift;
        for (int i = 0; i <= shift; ++i) {
            q <<= 1;
            if (r >= b) { r -= b; q.low |= 1; }
            b >>= 1;
        }
    }
    
    uint128_t operator/(uint128_t lhs, uint128_t rhs) {
        uint128_t div, rem;
        return DivMod(lhs, rhs, div, rem), div;
    }
    
    uint128_t operator%(uint128_t lhs, uint128_t rhs) {
        uint128_t div, rem;
        return DivMod(lhs, rhs, div, rem), rem;
    }
    
    uint128_t& operator/=(uint128_t &lhs, uint128_t rhs) { return lhs = lhs / rhs; }
    uint128_t& operator%=(uint128_t &lhs, uint128_t rhs) { return lhs = lhs % rhs; }
    uint128_t gcd(uint128_t a, uint128_t b)
    {
	    if (b > a) swap(a, b);
	    if (b == 0) return a;
	    else return gcd(b, a % b);
    }

typedef uint128_t ll;

struct rational
{
	ll p;
	ll q;
	rational(){};
	rational(ll _p, ll _q)
	{
		/*bool sign = false;
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
		}*/
		/*ll dupa = gcd(_p, _q);
		p = _p / dupa;
		q = _q / dupa;*/
		p = _p;
		q = _q;
		/*if (sign)
			p *= -1;*/
	}
};
rational operator*(const rational &a, const rational &b)
{
	return rational(a.p * b.p, a.q * b.q);
}
rational operator+(const rational &a, const rational &b)
{
	ll denominator_gcd = (a.q, b.q);
	ll new_q = (max(a.q, b.q) / denominator_gcd) * min(a.q, b.q);
	ll new_p = a.p * (new_q / a.q) + b.p * (new_q / b.q);
	return rational(new_p, new_q);
}
rational operator+(ll a, const rational &b)
{
	ll new_p = a * b.q + b.p;
	return rational(new_p, b.q);
}
rational operator+(const rational &b, ll a)
{
	ll new_p = a * b.q + b.p;
	return rational(new_p, b.q);
}
rational operator-(ll a, const rational &b)
{
	ll new_p = a * b.q - b.p;
	return rational(new_p, b.q);
}
rational operator-(const rational &b, ll a)
{
	ll new_p = b.p -a * b.q;
	return rational(new_p, b.q);
}
void operator+=(rational &a, const rational &b)
{
	ll denominator_gcd = gcd(a.q, b.q);
	ll new_q = (max(a.q, b.q) / denominator_gcd) * min(a.q, b.q);
	ll new_p = a.p * (new_q / a.q) + b.p * (new_q / b.q);
	a = rational(new_p, new_q);
}
void operator-=(rational &a, const rational &b)
{
	ll denominator_gcd = gcd(a.q, b.q);
	ll new_q = (max(a.q, b.q) / denominator_gcd) * min(a.q, b.q);
	ll new_p = a.p * (new_q / a.q) - b.p * (new_q / b.q);
	a = rational(new_p, new_q);
}
rational operator-(const rational &a, const rational &b)
{
	ll denominator_gcd = gcd(a.q, b.q);
	ll new_q = (max(a.q, b.q) / denominator_gcd) * min(a.q, b.q);
	ll new_p = a.p * (new_q / a.q) - b.p * (new_q / b.q);
	return rational(new_p, new_q);
}
rational operator*(const rational &a, ll b)
{
	return rational(a.p * b, a.q);
}
rational operator*(ll b, const rational &a)
{
	return rational(a.p * b, a.q);
}
rational operator/(const rational &a, ll b)
{
	return rational(a.p, a.q * b);
}
rational operator/(ll b, const rational &a)
{
	return rational(a.q * b, a.p);
}
rational operator/(const rational &a, const rational &b)
{
	return rational(a.p * b.q, b.p * a.q);
}
bool operator<(const rational &a, const rational &b)
{
	return a.p * b.q < b.p * a.q;
}
bool operator>(const rational &a, const rational &b)
{
	return a.p * b.q > b.p * a.q;
}
bool operator<=(const rational &a, const rational &b)
{
	return a.p * b.q <= b.p * a.q;
}
bool operator>=(const rational &a, const rational &b)
{
	return a.p * b.q >= b.p * a.q;
}

struct car
{
	ll pos;
	ll len;
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

vector<ll> len_sum;
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
	if (dsu[x].parent == -1)
		return x;
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

inline ll lensum(int l, int r)
{
	if (l == 0)
		return len_sum[r];
	return len_sum[r] - len_sum[l - 1];
}

__int128 read()
{
	__int128 x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
	{
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	long long _D, _W, _M;
	cin >> n >> _D >> _W >> _M;
	ll D, W, M;
	D = _D;
	W = _W;
	M = _M;
	/*n = read();
	D = read();
	W = read();
	M = read();*/
	car bajtazar = {0, D, rat(W, M)};
	vector<car> trucks(n);
	vector<rat> collision_time;
	vector<rat> collision_speed;
	len_sum.resize(n);
	blockidx.resize(n);
	block.reserve(n);
	pierdolniecie.resize(n);
	t.resize(5 * n);
	dsu.resize(n);
	przylaczenia.reserve(n);
	for (int i = 0; i < n; i++)
		makeset(i, {rat(0, 1), i});
	for (int i = 0; i < n; i++)
	{
		if (i != 0)
			len_sum[i] += len_sum[i - 1];
		long long _x, _d, _w, _m;
		cin >> _x >> _d >> _w >> _m;
		/*x = read();
		d = read();
		w = read();
		m = read();*/
		ll x, d, w, m;
		x = _x;
		d = _d;
		w = _w;
		m = _m;
		trucks[i] = {x, d, rat(w, m)};
		len_sum[i] += d;
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
				if (trucks[front_truck].speed >= trucks[i].speed)
					l = s;
				else
					r = s - 1;
				continue;
			}
			else
			{
				front_truck = przylaczenia[dupa - s].second;
				before_t = przylaczenia[dupa - s].first;
			}
			rat left_truck_pos = before_t * trucks[i].speed + trucks[i].pos;
			rat block_pos = before_t * trucks[front_truck].speed + trucks[front_truck].pos - lensum(i + 1, front_truck);
			if (left_truck_pos <= block_pos)
				l = s;
			else
				r = s - 1;
		}
		if (l == przylaczenia.size())
		{
			przylaczenia.clear();
			przylaczenia.push_back({rational(0, 1), i});
			pierdolniecie[i] = {rat(0, 1), i, i};
		}
		else
		{
			int cnt = l + 1;
			int front_truck = przylaczenia[dupa - l].second;
			rat before_t = przylaczenia[dupa - l].first;
			ll left_truck_pos = trucks[i].pos;
			ll block_pos = trucks[front_truck].pos - lensum(i + 1, front_truck);
			rat t = (block_pos - left_truck_pos) / (trucks[i].speed - trucks[front_truck].speed);
			ri new_entry = {t, front_truck};
			if (t.q >= 1e6 || t.p >= 1e14 || t.p < 0 || t.q < 0)
			{
				int chuj = 5 + 5;
			}
			while (cnt--)
			{
				przylaczenia.erase(przylaczenia.end() - cnt - 1);
			}
			przylaczenia.push_back(new_entry);
			przylaczenia.push_back({rat(0, 1), i});
			pierdolniecie[i] = {t, i, front_truck};
		}
	}
	//to jest czesc do liczenia wymijen
	int res = 1;
	sort(pierdolniecie.begin(), pierdolniecie.end());
	rat prev_bajtazar_pos = rat(0, 1);
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
				if (right_truck_pos - left_truck_pos >= rat(bajtazar.len, 1))
					res++;
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
	while (truck_idx < n)
	{
		if (dsufind(truck_idx) != dsufind(truck_idx - 1))
		{
			int front_truck = dsu[dsufind(truck_idx)].val.second;
			rat t = (trucks[front_truck].pos - lensum(truck_idx, front_truck)) / (bajtazar.speed - trucks[front_truck].speed);
			rat right_truck_pos = t * trucks[front_truck].speed + trucks[front_truck].pos - lensum(truck_idx, front_truck);
			rat left_truck_pos = trucks[truck_idx - 1].speed * t + trucks[truck_idx - 1].pos;
			if (right_truck_pos - left_truck_pos >= rat(bajtazar.len, 1))
				res++;
		}
		truck_idx++;
	}
	cout << res << '\n';
	return 0;
}