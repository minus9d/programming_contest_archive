#include <stdio.h>
#include <vector>
#include <deque>
#include <queue>
#include <map>
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>

using namespace std;

int LX, RX, UX, DX;
const int MAX_W = 6;
const int MAX_H = 6;
const char WALL = '=';
const char SPACE = '0';

struct moveCount_t {
  moveCount_t(void) : l(0), r(0), u(0), d(0) {};
  int l;
  int r;
  int u;
  int d;
};

struct coord_t {
  int x;
  int y;
};

typedef vector< char > line_t;
typedef vector< vector< char > > cells_t;
struct board_t {
  board_t(void) : width(0), height(0), cells(0), point(0) {};
  ~board_t(void) {}

  void printBoard(void)
  {
    for (cells_t::iterator j = cells.begin(); j != cells.end(); ++j) {
      fprintf(stderr, "  ");
      line_t line = (*j);
      for (line_t::iterator i = line.begin(); i != line.end(); ++i) {
	fprintf(stderr, "%c", *i);
      }
      fprintf(stderr, "\n");
    }
    fprintf(stderr, "  history = %s\n", moveHistory.c_str());
    fprintf(stderr, "  point = %d\n", point);
  }

  bool canMoveU(void)
  {
    // Åöé∏îsÇæÇ¡ÇΩÇ©ÅH
    if (moveHistory.length() != 0 && moveHistory.at( moveHistory.length() - 1 ) == 'D') {
      return false;
    }
    
    if (cells[ space.y - 1][ space.x ] != WALL) {
      return true;
    }
    else {
      return false;
    }
  }

  bool canMoveD(void)
  {
    if (moveHistory.length() != 0 && moveHistory.at( moveHistory.length() - 1 ) == 'U') {
      return false;
    }

    if (cells[ space.y + 1][ space.x ] != WALL) {
      return true;
    }
    else {
      return false;
    }
  }

  bool canMoveL(void)
  {
    if (moveHistory.length() != 0 && moveHistory.at( moveHistory.length() - 1 ) == 'R') {
      return false;
    }

    if (cells[ space.y ][ space.x - 1 ] != WALL) {
      return true;
    }
    else {
      return false;
    }
  }

  bool canMoveR(void)
  {
    if (moveHistory.length() != 0 && moveHistory.at( moveHistory.length() - 1 ) == 'L') {
      return false;
    }

    if (cells[ space.y ][ space.x + 1 ] != WALL) {
      return true;
    }
    else {
      return false;
    }
  }

  void moveU(void) {
    char temp = cells[space.y][space.x];
    cells[space.y][space.x] = cells[space.y - 1][space.x];
    cells[space.y - 1][space.x] = temp;
    moves.u++;
    space.y--;
    moveHistory += "U";
    estimatePoint();
  }

  void moveD(void) {
    char temp = cells[space.y][space.x];
    cells[space.y][space.x] = cells[space.y + 1][space.x];
    cells[space.y + 1][space.x] = temp;
    moves.d++;
    space.y++;
    moveHistory += "D";
    estimatePoint();
  }

  void moveL(void) {
    char temp = cells[space.y][space.x];
    cells[space.y][space.x] = cells[space.y][space.x - 1];
    cells[space.y][space.x - 1] = temp;
    moves.l++;
    space.x--;
    moveHistory += "L";
    estimatePoint();
  }

  void moveR(void) {
    char temp = cells[space.y][space.x];
    cells[space.y][space.x] = cells[space.y][space.x + 1];
    cells[space.y][space.x + 1] = temp;
    moves.r++;
    space.x++;
    moveHistory += "R";	
    estimatePoint();
  }

  char getNextChar(char ch)
  {
    if (('1' <= ch && ch <= '8') || ('A' <= ch && ch <= 'Y') ){
      return (ch + 1);
    }
    else if (ch == '9') {
      return 'A';
    }
    // undefined
    else {
      return '0';
    }
  }

  bool reachGoal(void)
  {
    bool isNotGoal = false;
    char ch = '1';

    for (int j = 1; j < height - 1; ++j) {
      if (isNotGoal) {
	break;
      }

      for (int i = 1; i < width - 1; ++i) {
	char cell = cells[j][i];
	if (cell == WALL) {
	  ch = getNextChar(ch);
	}
	else if(i == width - 2 && j == height - 2) {
	  if (cell != SPACE) {
	    isNotGoal = true;
	    break;
	  }
	}
	else {
	  if (cells[j][i] != ch) {
	    isNotGoal = true;
	    break;
	  }
	  else {
	    ch = getNextChar(ch);
	  }
	}
      }
    }

    return !isNotGoal;
  }

  void estimatePoint(void) {
    point = 0;
    char ch = '1';
    int pointW = -1;
    int miniPointW = 0;
    bool endFlagW = false;
    for (int j = 1; j < height - 1; ++j) {
      if (endFlagW) {
	break;
      }
      pointW++;

      for (int i = 1; i < width - 1; ++i) {
	char cell = cells[j][i];
	if (cell == WALL) {
	  // do nothing
	}
	else {
	  if (cells[j][i] == ch) {
	  }
	  else {
	    miniPointW = (i == width - 2) ? 0 : i - 1;
	    endFlagW = true;
	    break;
	  }
	}
	ch = getNextChar(ch);
      }
    }

    int pointH = -1;
    int miniPointH = 0;
    bool endFlagH = false;
    for (int i = 1; i < width - 1; ++i) {
      ch = '1' + (i - 1);
      if (endFlagH) {
	break;
      }
      pointH++;

      for (int j = 1; j < height - 1; ++j) {
	char cell = cells[j][i];
	if (cell == WALL) {
	  // do nothing
	}
	else {
	  if (cells[j][i] == ch) {
	  }
	  else {
	    miniPointH = (j == height - 2) ? 0 : j - 1;
	    endFlagH = true;
	    break;
	  }
	}

	for (int cnt = 0; cnt < width - 2; cnt++) {
	  ch = getNextChar(ch);
	}
      }
    }

    point = pointW * 10 + pointH * 10 + miniPointW + miniPointH;
  }

  string toStr(void) {
    string ret;
    for (int j = 0; j < height; ++j) {
      for (int i = 0; i < width; ++i) {
	ret += cells[j][i];
      }
    }
    return ret;
  }

  int width;
  int height;
  coord_t space;
  cells_t cells;
  moveCount_t moves;
  string moveHistory;
  int point;  
};

template<class T>
struct func : binary_function<T, T, bool> {
  bool operator()(const T& X, const T& Y) const{
    return (X.point < Y.point);
  }
};

//typedef deque<board_t> boardContainer_t;
typedef priority_queue< board_t, deque<board_t>,  func<board_t> > boardContainer_t;

class sortClass {
public:
	bool operator()(board_t& x, board_t& y) const {
	  return x.point > y.point;
	}
};

board_t makeBoard(int w, int h, string boardStr)
{
  board_t ret;
  int ptr = 0;
  
  ret.width = w + 2;
  ret.height = h + 2;
  ret.cells.resize(ret.height, line_t(ret.width));

  for (int j = 0; j < ret.height; ++j) {
    for (int i = 0; i < ret.width; ++i) {
      if (j == 0 || j == ret.height - 1) {
	ret.cells[j][i] = WALL;
      }
      else {
	if (i == 0 || i == ret.width - 1) {
	  ret.cells[j][i] = WALL;
	}
	else {
	  ret.cells[j][i] = boardStr[ptr];
	  ptr++;
	}

	if (ret.cells[j][i] == SPACE) {
	  ret.space.x = i;
	  ret.space.y = j;
	}
      }
    }
  }
  
  return ret;
}

void pushUnappearedBoard(board_t &board, map<string, int> &appeared, boardContainer_t &remains) {
  string boardStr = board.toStr();
  if (!appeared.count( boardStr )) {
    //		remains.push_back(board);
    remains.push(board);
    appeared[ boardStr ] = 1;
  }
}

void solve(void)
{
  static int questionNumber = 0;
  int w = 0;
  int h = 0;
  string boardStr;
  char dummy;

  questionNumber++;
  cin >> w >> dummy >> h >> dummy >> boardStr;

  board_t board = makeBoard(w, h, boardStr);

  // ñ‚ëËÇ™ëÂÇ´Ç¢èÍçáÇÕí˙ÇﬂÇÈ
//   if (w * h > 16) {
//     fprintf(stderr, "give up\n");
//     printf ("\n");
//     return;
//   }

  fprintf(stderr, "question No. %d is: \n", questionNumber);
  board.printBoard();


  // ìØàÍã«ñ Çó}êß
  map<string, int> appeared;
  appeared[ board.toStr() ] = 1;


  boardContainer_t remains;
  //remains.push_back(board);
  remains.push(board);
  bool endFlag = false;

  int loopCounter = 0;

  while(!endFlag && remains.size() != 0) {
    
    loopCounter++;

    // ç≈å„ÇÃóvëfÇÇ–Ç∆Ç¬Ç∆Ç¡ÇƒÇ≠ÇÈÅiècå^Åj
    //board_t board = remains.back();
    //remains.pop_back();

    // ó\ëzÉSÅ[ÉãÇ…ãﬂÇ¢èáÇ…ï¿Ç—ë÷Ç¶(ïKóvÇ»ÇÃÇÕç≈èâÇÃÇPå¬ÇæÇØ)
    //partial_sort( remains.begin(), remains.begin() + 1, remains.end(), sortClass() );

    // ç≈èâÇÃóvëfÇÇ–Ç∆Ç¬Ç∆Ç¡ÇƒÇ≠ÇÈÅiâ°å^Åj
    //board_t board = remains.front();
    //remains.pop_front();
    board_t board = remains.top();
    remains.pop();

//     if (
// 	(board.cells[1][1] == '1')
// 	&& (board.cells[1][2] == '2')
// 	&& (board.cells[1][3] == '3')
// 	) {
//       fprintf(stderr, "bubuntekini atteru\n");
//       board.printBoard();
//     }

    // check if reach the goal
    if ((board).reachGoal()) {
      (board).printBoard();
      fprintf(stderr, "solved!!!!!\n");
      fprintf(stderr, "loopcounter = %d, size = %d\n", loopCounter, remains.size());
      fprintf(stderr, "lrud = %d %d %d %d\n", (board).moves.l, (board).moves.r, (board).moves.u, (board).moves.d);
      printf("%s\n", (board).moveHistory.c_str());
      endFlag = true;
      break;
    }

    if (loopCounter % 100000 == 0) {
      fprintf(stderr, "loopCounter %d, popped is:\n", loopCounter);
      (board).printBoard();
    }

    //fprintf(stderr, "now size = %d.\n", remains.size());

    // ÉTÉCÉYÇ™àÍíËó Çí¥Ç¶ÇΩÇÁí˙ÇﬂÇÈ
    if (remains.size() > 500000) {
      fprintf(stderr, "size over: \n");
      printf("\n");
      break;
    }

    // í∑Ç≥Ç™àÍíËó Çí¥Ç¶ÇΩÇÁí˙ÇﬂÇÈ
    if ((board).moveHistory.length() > 80) {
      continue;
    }

    // ÉãÅ[ÉvâÒêîÇ™àÍíËó Çí¥Ç¶ÇΩÇÁí˙ÇﬂÇÈ
    if (loopCounter > 100000) {
      fprintf(stderr, "loop num over\n");
      printf("\n");
      break;
    }

    if ((board).canMoveU()) {
      board_t clone = (board);
      clone.moveU();
      
      pushUnappearedBoard(clone, appeared, remains);
    }
    if ((board).canMoveD()) {
      board_t clone = (board);
      clone.moveD();
      
      pushUnappearedBoard(clone, appeared, remains);
    }
    if ((board).canMoveL()) {
      board_t clone = (board);
      clone.moveL();
      
      pushUnappearedBoard(clone, appeared, remains);
    }
    if ((board).canMoveR()) {
      board_t clone = (board);
      clone.moveR();
      
      pushUnappearedBoard(clone, appeared, remains);
    }
  }
}

int main(void)
{
  int N, n;
  scanf("%d %d %d %d", &LX, &RX, &UX, &DX);
  scanf("%d", &N);
  
  for(n = 0; n < N; n++) {
    solve();
  }
}
