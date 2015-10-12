#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include <set>
#include <string>
#include <vector>

using namespace std;
#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair
#define mt make_tuple


const int W = 35;
const int H = 20;

struct P {
	int x;
	int y;
public:
	bool operator==(const P& p) const {
		return p.x == x && p.y == y;
	}
	bool operator!=(const P& p) const {
		return !(p == *this);
	}
};

const P nothing{ -1, -1 };
typedef vector<string> Cells;

std::mt19937 randomizer(777);

class UnionFind
{
public:
	UnionFind(){};
	~UnionFind(){};

	void Init(int num_entries) {
		num_entries_ = num_entries;
		par_.resize(num_entries_);
		rank_.resize(num_entries_, 0);
		for (int i = 0; i < num_entries_; ++i)
		{
			par_[i] = i;
		}
	}
	int Find(int x) {
		if (par_[x] == x)
		{
			return x;
		}
		else
		{
			return par_[x] = Find(par_[x]);
		}
	}

	void Unite(int x, int y) {
		x = Find(x);
		y = Find(y);
		if (x == y) return;

		if (rank_[x] < rank_[y])
		{
			par_[x] = y;
		}
		else
		{
			par_[y] = x;
			if (rank_[x] == rank_[y])
			{
				rank_[x]++;
			}
		}
	}
	bool Same(int x, int y) {
		return Find(x) == Find(y);
	}

private:
	int num_entries_;
	std::vector<int> par_;
	std::vector<int> rank_;
};

class Player
{
public:
	int x;
	int y;
	int backInTimeLeft;
	int score; // 自分で計算
};

class State
{
public:
	int opponentCount;
	int gameRound;
	Player me;
	vector<Player> opponents;
	Cells cells;
	Cells cellsEx;  ///< 盤面の周囲に、門番として'z'を置いたものを考える

	vector<P> goals;
};

void printCells(const Cells& cells) {
	for (const auto& line : cells) cerr << line << endl;
}

int cropX(int x)
{
	return max(0, min(W - 1, x));
}

int cropY(int y)
{
	return max(0, min(H - 1, y));
}

P cropP(const P& p)
{
	return P{ cropX(p.x), cropY(p.y) };
}

void printP(const P& p)
{
	cout << p.x << " " << p.y << endl;
}

/**
* Auto-generated code below aims at helping you parse
* the standard input according to the problem statement.
**/

bool isOutOfRange(int x, int y)
{
	return (x < 0 || x >= W || y < 0 || y >= H);
}

P findNearestEmptyCell(const Cells& cells, const P& pos, bool random = false)
{
	auto x1 = pos.x;
	auto y1 = pos.y;

	int sign[] = { 1, -1 };
	vector<P> cands;
	REP(d, W + H + 1) {
		FOR(y, -d, d + 1) {
			for (auto s : sign)  {
				auto xDiff = d - abs(y);
				int x2 = x1 + s * xDiff;
				int y2 = y1 + y;
				if (isOutOfRange(x2, y2)) continue;
				if (cells[y2][x2] == '.') cands.push_back(P{ x2, y2 });
			}
		}
		if (cands.size() > 0) break;
	}

	if (cands.size() > 0) {
		if (random) return cands[randomizer() % cands.size()];
		else return cands[0];
	}

	// 近くにまったく空白セルがない！
	return pos;
}

void decideGoal(const Cells& cells, const P& pos, P& goal, P& base)
{
	const int squareSize = 5;
	auto x1 = pos.x;
	auto y1 = pos.y;
	int dx[] = { 1, 1, -1, -1 };
	int dy[] = { 1, -1, 1, -1 };

	int bestCnt = -1;
	int bestD = -1;
	P bestGoal;

	cerr << "now: " << x1 << "," << y1 << endl;
	REP(d, 4) {
		cerr << "direction " << d << ":" << endl;
		int x2 = x1 + dx[d] * squareSize;
		int y2 = y1 + dy[d] * squareSize;
		x2 = cropX(x2);
		y2 = cropY(y2);

		cerr << "(x2,y2) = " << x2 << "," << y2 << endl;
		int cnt = 0;
		// 四角を描いて確実に増える分だけ数える
		int chance = 0;
		FOR(x, min(x1, x2), max(x1, x2) + 1) {
			FOR(y, min(y1, y2), max(y1, y2) + 1) {
				cerr << "x,y,x1,x2,y1,y2 = " << x << "," << y << endl;
				if (x == x1 || x == x2 || y == y1 || y == y2) {
					++chance;
					cnt += (cells[y][x] == '.');
				}
			}
		}
		cerr << "chance:" << chance << endl;
		if (cnt > bestCnt) {
			bestCnt = cnt;
			bestD = d;
			bestGoal = P{ x2, y2 };
		}

		cerr << "dir " << d << ":  cnt = " << cnt << endl;
	}


	if (bestCnt > squareSize * 2) {
		goal = bestGoal;
		base = pos;
	}
	// まわりによい四角形がない場合→もっとも近くにある空白マスに移動
	else {
		goal = findNearestEmptyCell(cells, pos);
		base = nothing;
	}

	cerr << "goal is decided. " << goal.x << "," << goal.y << endl;
}

int toIdx(int x, int y, int width) {
	return y * width + x;
}

// 盤面からplayer(e.g. '0')のスコアを計算する
int calcScore(const Cells& cellsEx, const char player)
{
	// まず空白セルの連結領域を列挙する
	// 連結領域について、塗りつぶせるかどうか判定する

	// 4近傍で連結処理
	UnionFind uf;
	uf.Init((W + 2) * (H + 2));
	FOR(h, 1, H + 1) {
		FOR(w, 1, W + 1) {
			if (cellsEx[h][w] == cellsEx[h][w + 1]) uf.Unite(toIdx(w, h, W + 2), toIdx(w + 1, h, W + 2));
			if (cellsEx[h][w] == cellsEx[h + 1][w]) uf.Unite(toIdx(w, h, W + 2), toIdx(w, h + 1, W + 2));
		}
	}

	// 空白セルの連結処理を見ていく
	// 単純に'0'があればカウントする
	set<int> candidates;  // 空白セルの連結領域
	set<int> badCandidates;  // '0'で囲えていないことが判明した連結領域
	map<int, int> counter; // 各idの登場回数
	int dw[] = { -1, 0, 1, 1, 1, 0, -1, -1 }; // 左上から時計回り
	int dh[] = { -1, -1, -1, 0, 1, 1, 1, 0 };
	FOR(h, 1, H + 1) {
		FOR(w, 1, W + 1) {
			auto& ch = cellsEx[h][w];

			if (ch == '.') {
				auto idx = toIdx(w, h, W + 2);
				auto ufIdx = uf.Find(idx);

				candidates.insert(ufIdx);
				++counter[ufIdx];

				// 既にbadであるならこれ以上調べる必要ない
				if (badCandidates.count(ufIdx)) continue;


				// 空白セルの周囲８近傍は'.'か'0'でないといけない。他のがあれば即NG
				REP(d, 8) {
					auto ch2 = cellsEx[h + dh[d]][w + dw[d]];

					// 異なるidの空白セルはNG
					// １１１１
					// ００空１
					// ０空０１  ←この空白セルは囲ったことにならない
					// ０００１
					if (ch2 == '.') {
						auto ufIdx2 = uf.Find(toIdx(w + dw[d], h + dh[d], W + 2));
						if (ufIdx != ufIdx2) {
							badCandidates.insert(ufIdx);
							break;
						}
					}
					else if (ch2 == player) {
						// do nothing
					}
					else {
						badCandidates.insert(ufIdx);
					}
				}
			}
		}
	}

	int ret = 0; // 囲うことによる増分
	for (auto& c : candidates) {
		if (!badCandidates.count(c)) {
			ret += counter[c];
		}
	}

	return ret;
}

P canLargeSquare(const State& s)
{
	int goLeft[] = { 1, -1 };
	int goUpper[] = { 1, -1 };

	// 左回り
	int dx[] = { 1, 0, -1, 0 };
	int dy[] = { 0, -1, 0, 1 };

	// 

	for (auto& left : goLeft) {
		for (auto& upper : goUpper) {
			FOR(d, 3, 6) {


			}
		}
	}
	return nothing;
}

P canEnlargeAreas(const State& s)
{
	// 盤面の周囲に、門番として'z'を置いたものを考える

	// 現状でのスコア
	int bestScore = 0;
	int bestDir = -1;
	P ret = nothing;


	// 4方向への延伸を考える
	int dx[] = { 0, 0, 1, -1 };
	int dy[] = { 1, -1, 0, 0 };
	const int distanceMax = 10;
	REP(dir, 4) {
		auto cellsEx = s.cellsEx; // コピー

		FOR(dis, 1, distanceMax + 1) {
			// 盤面を拡張しているのを忘れずに1を足す
			int x2 = s.me.x + 1 + dx[dir] * dis;
			int y2 = s.me.y + 1 + dy[dir] * dis;

			// 延伸しすぎ
			if (x2 <= 0 || x2 >= W + 2 || y2 <= 0 || y2 >= H + 2) break;

			// 延伸した分を塗る
			if (cellsEx[y2][x2] == '.') cellsEx[y2][x2] = '0';
		}

		// debug
		cerr << "cellsEx dir " << dir << ":" << endl;
		printCells(cellsEx);

		auto score = calcScore(cellsEx, '0');

		// debug
		cerr << "enclosure score dir " << dir << ": " << score << endl;

		if (score > bestScore) {
			bestScore = score;
			bestDir = dir;
			ret = P{ s.me.x + dx[bestDir], s.me.y + dy[bestDir] };
		}
	}

	return ret;
}

void setGoals(State& s)
{
	bool isUpper = s.me.y < H / 2;
	bool isLefter = s.me.x < W / 2;

	// 最初は、↑または↓に移動
	const int heightSize = 5;
	const int widthSize = 7;

	P p1{ s.me.x, s.me.y + (isUpper ? 1 : -1) * heightSize };
	P p2{ s.me.x + (isLefter ? 1 : -1) * widthSize, p1.y };
	P p3{ p2.x, s.me.y - (isUpper ? 1 : -1) };


	P p5{ s.me.x - (isLefter ? 1 : -1) * widthSize, p3.y };
	P p6{ p5.x, p1.y + (isUpper ? 1 : -1) };
	P p7{ p1.x, p6.y };


	P p8{ s.me.x, s.me.y + (isUpper ? 1 : -1) * heightSize * 2 };
	P p9{ p2.x + (isLefter ? 1 : -1), p8.y };
	P p10{ p9.x, p2.y };

	P p11{ p10.x + (isLefter ? 1 : -1) * widthSize, p10.y };
	P p12{ p11.x, p9.y + (isLefter ? 1 : -1) };
	P p13{ p9.x, p12.y };

	s.goals.push_back(cropP(p1));
	s.goals.push_back(cropP(p2));
	s.goals.push_back(cropP(p3));

	//s.goals.push_back(cropP(p4)); // 欠番

	s.goals.push_back(cropP(p5));
	s.goals.push_back(cropP(p6));
	s.goals.push_back(cropP(p7));
	s.goals.push_back(cropP(p8));
	s.goals.push_back(cropP(p9));
	s.goals.push_back(cropP(p10));
	s.goals.push_back(cropP(p11));
	s.goals.push_back(cropP(p12));
	s.goals.push_back(cropP(p13));

	cerr << "goals:" << endl;
	for (auto e : s.goals) {
		cerr << e.x << ", " << e.y << endl;
	}
}


P getUnfinishedGoalIfAny(const State& s)
{
	for (auto& g : s.goals)
	{
		if (s.cells[g.y][g.x] == '.') return g;
	}
	return nothing;

	//// 最初のゴール未達ならそこに行く
	//if (s.cells[s.goals[0].y][s.goals[0].x] != '0')
	//{
	//	return s.goals[0];
	//}

	//REP(i, SIZE(s.goals) - 1){
	//	P g1 = s.goals[i];
	//	P g2 = s.goals[i+1];

	//	// 隣合うゴール間でまだいけてないマスがあるか？
	//	int maxx = max(g1.x, g2.x);
	//	int minx = min(g1.x, g2.x);
	//	int maxy = max(g1.y, g2.y);
	//	int miny = min(g1.y, g2.y);

	//	FOR(y, miny, maxy + 1) {
	//		FOR(x, minx, maxx + 1) {
	//			if (s.cells[y][x] == '.') return g2;
	//		}
	//	}
	//}

	//return nothing;
}

P solve(State& s)
{
	P pos{ s.me.x, s.me.y };

	// 書きかけ
	{
		// 開始間もないときは大きなのを狙いに行く
		// 最初に、適当な矩形を描くことを考える　その目標点をgoalsとして設定
		if (s.gameRound == 1){
			setGoals(s);
		}
		// まだ誰にも塗られていないgoalがある場合、それを目指す
		auto goal = getUnfinishedGoalIfAny(s);
		if (goal != nothing) {
			return goal;
		}
	}

	// 3頂点の移動により大きな面積を得られるときはそれを狙う
	auto p1 = canLargeSquare(s);
	if (p1 != nothing)
	{
		cerr << "try to get square" << endl;
		return p1;
	}


	// 直線移動により囲えるときは積極的に囲う
	auto p = canEnlargeAreas(s);
	if (p != nothing)
	{
		cerr << "try to enclose" << endl;
		return p;
	}

	// 自分の周囲のうち最も近い空白セルを見つけて移動
	// たまにランダムに移動
	auto val = randomizer() % 100;
	// 完全ランダム
	if (val < 7) {
		cerr << "completely random" << endl;
		int dx[] = { 0, 0, 1, -1 };
		int dy[] = { 1, -1, 0, 0 };
		auto x2 = s.me.x + dx[val % 4];
		auto y2 = s.me.y + dy[val % 4];
		x2 = cropX(x2);
		y2 = cropY(y2);
		return P{ x2, y2 };
	}
	// もっとも近い空白セルに移動
	else
	{
		cerr << "nearest empty cell" << endl;
		auto goal = findNearestEmptyCell(s.cells, pos, true);
		return goal;
	}

}

void getInfoFromStdin(State& s)
{
	cin >> s.gameRound; cin.ignore();
	cin >> s.me.x >> s.me.y >> s.me.backInTimeLeft; cin.ignore();
	// cerr << "backInTimeLeft: " << backInTimeLeft << endl;
	for (int i = 0; i < s.opponentCount; i++) {
		Player oppo;
		cin >> oppo.x >> oppo.y >> oppo.backInTimeLeft;
		cin.ignore();
		s.opponents.push_back(oppo);
	}
	for (int i = 0; i < 20; i++) {
		string line; // One line of the map ('.' = free, '0' = you, otherwise the id of the opponent)
		cin >> s.cells[i];
		cin.ignore();
	}
}

void extractInfo(State& s)
{
	// 全プレイヤーのスコアを計算
	map<char, int> scores;
	REP(h, H) REP(w, W) ++scores[s.cells[h][w]];
	s.me.score = scores['0'];
	REP(i, s.opponentCount) {
		s.opponents[i].score = scores['1' + i];
	}

	// 拡張盤面作成
	s.cellsEx.clear();
	s.cellsEx.push_back(string(W + 2, 'z'));
	REP(h, H) s.cellsEx.push_back('z' + s.cells[h] + 'z');
	s.cellsEx.push_back(string(W + 2, 'z'));
}

int bestOpponentScore(const State& s)
{
	int ret = 0;
	for (auto& p : s.opponents)
		ret = max(ret, p.score);
	return ret;
}

int main()
{
	State s;
	cin >> s.opponentCount; cin.ignore();
	s.cells.resize(H);

	// game loop
	P goal(nothing);
	P base(nothing);
	while (1) {
		getInfoFromStdin(s);
		extractInfo(s);

		// 1位プレイヤーとの点数差が一定以上付いた場合に25戻る
		auto bestScore = bestOpponentScore(s);
		if (bestScore > s.me.score + 20 && s.me.backInTimeLeft > 0) {
			cout << "BACK 25" << endl;
			continue;
		}


		P goal = solve(s);

		// 本当はこれをそのままprintすればよいはずだが、誤った値のことがある
		if (isOutOfRange(goal.x, goal.y)) {
			cerr << "answer is out of range. will be fixed." << endl;
		}
		goal.x = cropX(goal.x);
		goal.y = cropY(goal.y);
		printP(goal);
	}
}
