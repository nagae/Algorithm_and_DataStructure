#ifndef CLIENT_STRUCT_H
#define CLIENT_STRUCT_H

#include <stdio.h>		// 標準入出力
#include <stdlib.h>		// 各種ユーティリティを含む標準ライブラリ
#include <string.h>		// 文字列操作
#include <stdbool.h>		// ブール型

#define NAME_MAXLEN 12		// 名前の最大長
#define GENDER_MAXLEN 100	// 性別文字列の最大長
#define BUFFER_SIZE 100		// ファイル読み込み時のバッファサイズ

// ----------------------------------------
// 顧客データを格納する構造体
// ----------------------------------------
typedef struct
{
  char name[NAME_MAXLEN];	// 名前
  int age;			// 年齢
  bool is_male;			// 性別
} Client;


// ----------------------------------------
// 関数ヘッダ
// ----------------------------------------
// 顧客情報をセット. 顧客情報が不適切な場合は顧客情報を無効(名前を空文字列)にして false を返す
bool set_client(Client *client, char name[], int age, char gender[]);
// 顧客情報の出力
void show_client(Client *client);
// ファイルストリームからの顧客情報の読込み
bool read_client_from_txt(FILE *ifs, Client *client);
// CSVファイルストリームからの顧客情報の読込み
bool read_client_from_csv(FILE *ifs, Client *client);

#endif
