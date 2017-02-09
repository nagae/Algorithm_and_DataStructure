#include <stdio.h>		// 標準入出力
#include <string.h>		// 文字列操作
#include <stdbool.h>		// ブール型
#define buf_name 12		// 名前の長さの最大値
#define mem_size 10		// 確保しておく顧客データのサイズ

// 
// 標準出力に顧客情報を出力
// 
void show_client(char *name, int age, bool is_male)
{
  printf("| %-10s | %3d | %-6s |\n",
	 name, age,
	 (is_male) ? "male" : "female");
}


// 
// メイン関数
// 
int main(void)
{
  // ----------------------------------------
  // 名前・年齢・性別を格納する配列を宣言し, 同時に初期化
  // 名前
  char name[mem_size][buf_name] =
    { "Alice", "Bob", "Cathy", "David", "Ethan", "Flank", "Gina" };
  // 年齢
  int age[mem_size] =
    { 23, 17, 32, 25, 48, 27, 42 };
  // 性別
  bool is_male[mem_size] =
    { false, true, false, true, true, true, false};

  // ----------------------------------------
  // 顧客情報の表示
  for ( int ID = 0; ID < mem_size; ++ID )
  {
    // 名前が空だった場合はループを脱出
    if ( name[ID][0] == '\0' ) break;
    // 顧客情報を表示
    show_client( name[ID], age[ID], is_male[ID] );
  }
  
}
