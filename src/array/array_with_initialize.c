#include <stdio.h>		// 標準入出力
#include <string.h>		// 文字列操作
#include <stdbool.h>		// ブール型

#define NAME_MAXLEN 12		// 名前の最大長
#define CUSTOMER_SIZE 10	// 顧客数の最大値
#define BUFFER_SIZE 100		// ファイル読み込み時のバッファサイズ

// ----------------------------------------
// 関数ヘッダ
// ----------------------------------------
// 顧客情報の出力
void show_client(char name[], int age, bool is_male);


// ----------------------------------------
// メイン関数
// ----------------------------------------
int main(void)
{
  // ----------------------------------------
  // 名前・年齢・性別を格納する配列を宣言し, 同時に初期化
  // 名前
  char name[CUSTOMER_SIZE][NAME_MAXLEN] =
    { "Alice", "Bob", "Cathy", "David", "Ethan", "Flank", "Gina" };
  // 年齢
  int age[CUSTOMER_SIZE] =
    { 23, 17, 32, 25, 48, 27, 42 };
  // 性別
  bool is_male[CUSTOMER_SIZE] =
    { false, true, false, true, true, true, false};

  // ----------------------------------------
  // 顧客情報の表示
  for ( int ID = 0; ID < CUSTOMER_SIZE; ++ID )
  {
    // 名前が空だった場合はループを脱出
    if ( name[ID][0] == '\0' ) break;
    // 顧客情報を表示
    show_client( name[ID], age[ID], is_male[ID] );
  }
  
}



// ----------------------------------------
// 標準出力に顧客情報を出力
// ----------------------------------------
void show_client(char name[], int age, bool is_male)
{
  printf("| %-10s | %3d | %-6s |\n",
	 name, age,
	 (is_male) ? "male" : "female");
}
