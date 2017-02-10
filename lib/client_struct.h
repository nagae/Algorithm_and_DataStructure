#include <stdio.h>		// 標準入出力
#include <stdlib.h>		// 各種ユーティリティを含む標準ライブラリ
#include <string.h>		// 文字列操作
#include <stdbool.h>		// ブール型

#define NAME_SIZE 12		// 名前長の最大値
#define BUFFER_SIZE 100		// ファイル読み込み時のバッファサイズ

// ----------------------------------------
// 顧客データを格納する構造体
// ----------------------------------------
struct Client
{
  char name[NAME_SIZE];		// 名前
  int age;			// 年齢
  bool is_male;			// 性別
};


// ----------------------------------------
// 関数ヘッダ
// ----------------------------------------
// 顧客情報の出力
void show_client(struct Client *client);
// ファイルストリームからの顧客情報の読込み
bool read_client_from_txt(FILE *ifs, struct Client *client);
// CSVファイルストリームからの顧客情報の読込み
bool read_client_from_csv(FILE *ifs, struct Client *client);
