#include <stdio.h>		// 標準入出力
#include <string.h>		// 文字列操作
#include <stdbool.h>		// ブール型
#define buf_name 12		// 名前の長さの最大値

// 
// 標準出力に顧客情報を出力
// 
void show_client(char *name, int age, bool is_male)
{
  printf("| %-10s | %3d | %-6s |\n",
	 name, age,
	 (is_male) ? "male" : "female");
  // 文字列は * を使ったポインタ渡しにしている.
  // %-10s は左詰めで10文字の文字列を表す書式.
  // 性別は3項演算子を使って is_male が true なら "male" そうでなければ "female" を表示.
}


// 
// メイン関数
// 
int main(void)
{
  // 名前を格納する変数
  char name1[buf_name], name2[buf_name], name3[buf_name],
    name4[buf_name], name5[buf_name], name6[buf_name], name7[buf_name];
  // 年齢を格納する変数
  int age1, age2, age3, age4, age5, age6, age7;
  // 性別を格納する変数
  bool is_male1, is_male2, is_male3, is_male4, is_male5, is_male6, is_male7;

  // 1人目の顧客情報
  strcpy( name1, "Alice" );
  age1 = 23;
  is_male1 = false;

  // 2人目の顧客情報
  strcpy( name2, "Bob" );
  age2 = 17;
  is_male2 = true;

  // 以下, 3人目以降を代入
  // :

  // 顧客情報の表示
  show_client( name1, age1, is_male1 ); // 1人目
  show_client( name2, age2, is_male2 ); // 2人目
  // 以下, 3人目以降を出力
  // :

  return 0;
}