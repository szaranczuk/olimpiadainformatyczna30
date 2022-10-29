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
	string to_print()
	{
		stringstream ss;
		ss << p << "/" << q;
		return ss.str();
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
	pierdolniecie.resize(n);
	t.resize(5*n);
	dsu.resize(n);
	for (int i = 0; i < n; i++) makeset(i, {rat(0, 1), i});
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
	//to jest czesc do liczenia pierdolniec
	for (int i = n - 1; i >= 0; i--)
	{
		/*if (i == block[blockidx[i]].second)
		{
			continue;
		}
		else if (i == block[blockidx[i]].second - 1)
		{
			rat truck_pos = rational(trucks[i].pos, 1);
			rat block_pos = rational(trucks[i + 1].pos - trucks[i + 1].len, 1);
			rat t = (block_pos - truck_pos) / (trucks[i].speed - trucks[i + 1].speed);
			pierdolniecie[i] = {t, i + 1};
			timeupdate(i, pierdolniecie[i], 0, n - 1, 1);
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
		timeupdate(i, pierdolniecie[i], 0, n - 1, 1);*/
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
				before_t = rat(INF, 1);
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
			przylaczenia.push_back({rational(0, 1), i});
			pierdolniecie[i] = {rat(INF, 1), i, i};
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
			przylaczenia.push_back({rat(0, 1), i});
			pierdolniecie[i] = {before_t + t, i, front_truck};
		}
	}
	//to jest czesc do liczenia wymijen
	ll res = 1ll;
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
				if (right_truck_pos - left_truck_pos >= rat(bajtazar.len, 1)) res++;
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
	/*for (int i = 1; i < n; i++)
	{
		rat t = (trucks[i].pos - trucks[i].len + bajtazar.pos) / (bajtazar.speed - trucks[i].speed);
		rat pos = bajtazar.pos + bajtazar.speed * t;
		rat backpos;
		if (t > pierdolniecie[i - 1].first)
		{
			backpos = trucks[pierdolniecie[i - 1].second].pos + trucks[pierdolniecie[i - 1].second].speed * t - lensum(i, pierdolniecie[i - 1].second);
		}
		else
		{
			backpos = trucks[i - 1].pos + trucks[i - 1].speed * t - trucks[i - 1].len;
		}
		if (pos - backpos >= rational(bajtazar.len, 1)) res++;
	}*/
	cout << res << '\n';
}