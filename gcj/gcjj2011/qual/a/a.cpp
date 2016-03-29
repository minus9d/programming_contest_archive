#include <cstdio>
#include <vector>
#include <deque>
#include <queue>
#include <map>
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>

using namespace std;
typedef map<int, int> cards_t;

void printTable(cards_t &cards)
{
  printf("--table--\n");
  for(cards_t::iterator itr = cards.begin(); itr != cards.end(); ++itr){
    printf("key %d, value %d\n", itr->first, itr->second);
  }
  printf("------\n");      
}

int getValue(cards_t &cards, int index)
{
  cards_t::iterator itr;
  itr = cards.lower_bound(index);

  //printf("index %d, key %d, value %d\n", index, itr->first, itr->second);

  if (itr != cards.end() && itr->first == index) {
    return itr->second;
  }
  else {
    --itr;
    return (index - itr->first) + itr->second;
  }
}

void printCards(cards_t &cards, int num)
{
  printf("cards = ");
  for(int m = 0; m < num; m++){
    printf("%d, ", getValue(cards, m));
  }
  printf("\n");
}

void shuffle(cards_t &cards, int a, int b, int M)
{
  if (a == 1){
    return;
  }

  cards_t newCards;
  int aIndex = a - 1;

  // 前に移動してきた分
  newCards[0] = getValue(cards, aIndex);
  cards_t::iterator itr = cards.lower_bound(aIndex);
  while(itr != cards.end()){
    if (itr->first - aIndex + 1 <= b){
      newCards[itr->first - aIndex] = itr->second;
      ++itr;
    }
    else{
      break;
    }
  }

  // 後ろにずれた分
  itr = cards.begin();
  while(itr->first < aIndex && itr != cards.end()) {
    newCards[itr->first + b] = itr->second;
    ++itr;
  }

  // 新しいインデックスが増える場合
  if (cards.find(aIndex + b) == cards.end() && aIndex + b < M) {
    newCards[aIndex + b] = getValue(cards, aIndex + b);
  }

  // 残りの分
  itr = cards.lower_bound(aIndex + b);
  while(itr != cards.end()){
    newCards[itr->first] = itr->second;
    ++itr;
  }

  cards = newCards;
}

void solve(void)
{
  static int qNo = 1;
  int M, C, W;
  cin >> M >> C >> W;

  cards_t cards;
  cards[0] = 1;

  for(int c = 0; c < C; c++){
    int a, b;
    cin >> a >> b;

    shuffle(cards, a, b, M);

    //printf("table size = %d\n", cards.size());
    //printTable(cards);
    //    printCards(cards, M);
    //printf("---\n");
  }

  printf("Case #%d: %d\n", qNo++, getValue(cards, W - 1));
}

int main(void)
{
  int N, n;
  scanf("%d", &N);
  
  for(n = 0; n < N; n++) {
    solve();
  }
}
