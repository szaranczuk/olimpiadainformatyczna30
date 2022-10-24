#include <bits/stdc++.h>

using namespace std;


typedef long long ll;
typedef pair<int, int> ii;

const ll INF = 1e13;

struct rational
{
	ll p;
	ll q;
	rational() {};
	rational(ll _p, ll _q)
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
		ll dupa = __gcd(_p, _q);
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
	ll denominator_gcd = __gcd(a.q, b.q);
	ll new_q = (max(a.q, b.q) / denominator_gcd) * min(a.q, b.q);
	ll new_p = a.p * (new_q / a.q) + b.p * (new_q / b.q);
	return rational(new_p, new_q);
}
rational operator+(ll a, const rational& b)
{
	ll new_p = a * b.q + b.p;
	return rational(new_p, b.q);
}
rational operator+(const rational& b, ll a)
{
	ll new_p = a * b.q + b.p;
	return rational(new_p, b.q);
}
rational operator-(ll a, const rational& b)
{
	ll new_p = a * b.q - b.p;
	return rational(new_p, b.q);
}
rational operator-(const rational& b, ll a)
{
	ll new_p = -a * b.q + b.p;
	return rational(new_p, b.q);
}
void operator+=(rational& a, const rational& b)
{
	ll denominator_gcd = __gcd(a.q, b.q);
	ll new_q = (max(a.q, b.q) / denominator_gcd) * min(a.q, b.q);
	ll new_p = a.p * (new_q / a.q) + b.p * (new_q / b.q);
	a = rational(new_p, new_q);
}
void operator-=(rational& a, const rational& b)
{
	ll denominator_gcd = __gcd(a.q, b.q);
	ll new_q = (max(a.q, b.q) / denominator_gcd) * min(a.q, b.q);
	ll new_p = a.p * (new_q / a.q) - b.p * (new_q / b.q);
	a = rational(new_p, new_q);
}
rational operator-(const rational& a, const rational& b)
{
	ll denominator_gcd = __gcd(a.q, b.q);
	ll new_q = (max(a.q, b.q) / denominator_gcd) * min(a.q, b.q);
	ll new_p = a.p * (new_q / a.q) - b.p * (new_q / b.q);
	return rational(new_p, new_q);
}
rational operator*(const rational&a, ll b)
{
	return rational(a.p * b, a.q);
}
rational operator*(ll b, const rational& a)
{
	return rational(a.p * b, a.q);
}
rational operator/(const rational&a, ll b)
{
	return rational(a.p, a.q * b);
}
rational operator/(ll b, const rational& a)
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
	ll pos;
	ll len;
	rational speed;
};
typedef rational rat;
typedef pair<rat, int> ri;

vector<ll> len_sum;
vector<ri> t;
vector<ll> blockidx;
vector<ii> block;
vector<ri> pierdolniecie;
int blockcnt = 0;

inline ll lensum(ll l, ll r)
{
	if (l == 0) return len_sum[r];
	return len_sum[r] - len_sum[l - 1];
}

ri getmax(int l, int r, int tl, int tr, ll v)
{
	if (tr < l || tl > r) return {rational(-INF, 1), -INF};
	else if (l <= tl || tr <= r) return t[v];
	else
	{
		int tm = (tl + tr) / 2;
		ri res1 = getmax(l, r, tl, tm, 2*v);
		ri res2 = getmax(l, r, tm + 1, tr, 2*v+1);
		if (res1.first > res2.first) return res1;
		return res2;
	}
}

void timeupdate(int pos, ri val, int tl, int tr, ll v)
{
	if (tl == tr) t[v] =val;
	else
	{
		int tm = (tl + tr) /2;
		if (pos <= tm) timeupdate(pos, val, tl, tm, 2*v);
		else timeupdate(pos, val, tm + 1, tr, 2 * v + 1);
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	ll n, D, W, M;
	cin >> n >> D >> W >> M;
	car bajtazar = {0, D, rat(W, M)};
	vector<car> trucks(n);
	vector<rat> collision_time;
	vector<rat> collision_speed;
	len_sum.resize(n);
	blockidx.resize(n);
	block.reserve(n);
	pierdolniecie.assign(n, {rational(INF, 1), -1});
	t.resize(5*n);
	for (int i = 0; i < n; i++)
	{
		if (i != 0) len_sum[i] += len_sum[i - 1];
		ll x, d, w, m;
		cin >> x >>  d >> w >> m;
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
	for (int i = n - 2; i >= 0; i--)
	{
		if (i == block[blockidx[i]].second)
		{
			continue;
		}
		int l = i + 1;
		int r = block[blockidx[i]].second;
		while (r > l)
		{
			int s = (l + r) / 2;
			ri dupa = getmax(i + 1, s, 0, n - 1, 1); //naprawic - jezeli brak kolizji to zwraca 0/0 i sie wypierdala
			int guwno = dupa.second;
			if (trucks[guwno].pos + dupa.first * trucks[guwno].speed - lensum(i + 1, guwno) > trucks[i].pos + dupa.first * trucks[i].speed)
			{
				l = s + 1;
			}
			else
			{
				r = s;
			}
		}
		ri dupa = pierdolniecie[l];
		int guwno = pierdolniecie[l].second;
		rat truck_pos = trucks[i].pos + dupa.first * trucks[i].speed;
		rat block_pos = trucks[guwno].pos + dupa.first * trucks[guwno].speed - lensum(i + 1, guwno);
		rat t = (block_pos - truck_pos) / (trucks[i].speed - trucks[guwno].speed);
		pierdolniecie[i] = {t, guwno};
		timeupdate(i, pierdolniecie[i], 0, n - 1, 1);
	}
	ll res = 1ll;
	for (int i = 1; i < n; i++)
	{
		rat t = (trucks[i].pos - trucks[i].len + bajtazar.pos) / (bajtazar.speed - trucks[i].speed);
		if (t > pierdolniecie[i].first)
		{

		}
		rat pos = bajtazar.pos + bajtazar.speed * t;
		rat backpos;
		if (t > pierdolniecie[i - 1].first)
		{
			backpos = trucks[pierdolniecie[i - 1].second].pos + trucks[pierdolniecie[i - 1].second].speed * t - lensum(i, pierdolniecie[i - 1].second);
		}
		else
		{
			backpos = trucks[i - 1].pos + trucks[i - 1].speed * t;
		}
		if (pos - backpos >= rational(bajtazar.len, 1)) res++;
	}
	cout << res << '\n';
}