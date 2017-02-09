#include <iostream>		// 標準入出力
#include <iomanip>		// 入出力操作
#include <string>		// 文字列
using namespace std;		// デフォルトの名前空間を std に設定

// ----------------------------------------
// 関数ヘッダ
// ----------------------------------------
// 顧客情報の出力
ostream& show_client(ostream& os, const string& name, int age, bool is_male);


// ----------------------------------------
// メイン関数
// ----------------------------------------
int main(void)
{
  // 名前を格納する変数
  string name1, name2, name3, name4, name5, name6, name7;
  // 年齢を格納する変数
  int age1, age2, age3, age4, age5, age6, age7;
  // 性別を格納する変数
  bool is_male1, is_male2, is_male3, is_male4, is_male5, is_male6, is_male7;

  // 1人目の顧客情報
  name1 = "Alice";
  age1 = 23;
  is_male1 = false;

  // 2人目の顧客情報
  name2 = "Bob";
  age2 = 17;
  is_male2 = true;

  /*
    以下, 3人目以降を代入
    :
  */

  // 顧客情報の表示
  show_client( cout, name1, age1, is_male1 ); // 1人目
  show_client( cout, name2, age2, is_male2 ); // 2人目
  /*
    以下, 3人目以降を出力
    :
  */

  return 0;
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
  /*
    string型は & を使った参照渡しにしている.
    関数内で値が変更されないことを保証するために const をつけている.
    setw(10) は文字数, left は左寄せ, right は右寄せ, dec は10進数, endl は改行を表す操作子.
    性別は3項演算子を使って is_male が true なら "male" そうでなければ "female" を表示.
  */
}
