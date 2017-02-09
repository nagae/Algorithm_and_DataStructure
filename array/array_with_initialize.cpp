#include <iostream>		// 標準入出力
#include <iomanip>		// 入出力操作
#include <string>		// 文字列
using namespace std;		// デフォルトの名前空間を std に設定

// 
// 標準出力に顧客情報を出力
// 
void show_client(const string& name, int age, bool is_male)
{
  cout << "| "
       << setw(10) << left << name << " | "
       << setw(3) << right << dec << age << " | "
       << setw(6) << left << ((is_male) ? "male" : "female") << " |"
       << endl;
}


// 
// メイン関数
// 
int main(void)
{
  // ----------------------------------------
  // 名前・年齢・性別を格納する配列を宣言し, 同時に初期化
  const int mem_size = 10; 	// 確保しておく顧客データのサイズ
  // 名前
  string name[mem_size] =
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
    if ( name[ID] == "" ) break;
    // 顧客情報を表示
    show_client( name[ID], age[ID], is_male[ID] );
  }
}
