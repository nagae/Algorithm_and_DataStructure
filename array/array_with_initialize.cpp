#include <iostream>		// 標準入出力
#include <iomanip>		// 入出力操作
#include <string>		// 文字列
using namespace std;		// デフォルトの名前空間を std に設定

const int CUSTOMER_SIZE = 10;	// 確保しておく顧客データのサイズ

// ----------------------------------------
// 関数ヘッダ
// ----------------------------------------
// 出力ストリームに顧客情報を出力
ostream& show_client(ostream& os, const string& name, int age, bool is_male);


// ----------------------------------------
// メイン関数
// ----------------------------------------
int main(void)
{
  // ----------------------------------------
  // 名前・年齢・性別を格納する配列を宣言し, 同時に初期化
  // 名前
  string name[CUSTOMER_SIZE] =
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
    if ( name[ID] == "" ) break;
    // 顧客情報を表示
    show_client( cout, name[ID], age[ID], is_male[ID] );
  }
}



// ----------------------------------------
// 出力ストリームに顧客情報を出力
// ----------------------------------------
ostream& show_client(ostream& os, const string& name, int age, bool is_male)
{
  os << "| "
       << setw(10) << left << name << " | "
       << setw(3) << right << dec << age << " | "
       << setw(6) << left << ( (is_male) ? "male" : "female" ) << " |"
       << endl;
  return os;
}
