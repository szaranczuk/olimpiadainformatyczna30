#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<int, bool> ib;

vector<vector<ii>> board;

struct coord
{
	ll y;
	ll x;
};

coord operator+(const coord &a, const coord &b) { return {a.y + b.y, a.x + b.x}; }

queue<coord> q;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	ll m, p, n;
	cin >> m >> p >> n;
	board.resize(n);
	for (int i = 0; i < m; i++)
		board[i].assign(m, {-1, -1});
	for (int i = 0; i < p; i++)
	{
		ll w, k, c;
		cin >> w >> k >> c;
		w--;
		k--;
		board[w][k] = {c, -1};
	}
	coord head = {0, 0};
	coord tail = {0, 0};
	int cnt = 1;
	int wonsz_size = 1;
	vector<int> wonsz = {0};
	wonsz.reserve(p + 1);
	board[0][0] = {0, 1};
	while (n--)
	{
		char type;
		cin >> type;
		if (type != 'Z')
		{
			cnt++;
			coord move;
			if (type == 'G')
			{
				move = {-1, 0};
			}
			if (type == 'D')
			{
				move = {1, 0};
			}
			if (type == 'L')
			{
				move = {0, -1};
			}
			if (type == 'P')
			{
				move = {0, 1};
			}
			head = head + move;
			q.push(move);
			if (board[head.y][head.x].first != -1 && board[head.y][head.x].second == -1)
			{
				wonsz_size++;
				wonsz.push_back(board[head.y][head.x].first);
			}
			else
			{
				coord rev_move = q.front();
				q.pop();
				tail = tail + rev_move;
			}
			board[head.y][head.x].second = cnt;
		}
		else
		{
			int y, x;
			cin >> y >> x;
			y--;
			x--;
			int idx = cnt - board[y][x].second;
			if (idx >= wonsz_size) cout << "-1\n";
			else cout << wonsz[wonsz_size - idx - 1] << '\n';
		}
	}
	return 0;
}