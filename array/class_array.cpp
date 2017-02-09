#include <iostream>		// 標準入出力
#include <iomanip>		// 入出力操作
#include <fstream>		// ファイル入出力
#include <string>		// 文字列
using namespace std;		// 名前空間 std を利用

// 
// 顧客データを格納するクラス
// 
class Client
{
public:	     // public: とすることで, 以下のメンバ変数に自由にアクセス
  string name;			// 名前
  int age;			// 年齢
  bool is_male;			// 性別
};


// 
// <<演算子 の overload による顧客データの出力
// 
ostream& operator<<(ostream& os, const Client& client) // os, c ともに参照渡し
{
  os << "| "
     << setw(10) << left << client.name << " | "
     << setw(3) << right << dec << client.age << " | "
     << setw(6) << left << ( ( client.is_male) ? "male" : "female" ) << " |";
  return os;
}


// 
// >>演算子 の overload による顧客データの読み取り
// 
istream& operator>>(istream& is, Client& client)
{
  string gender = "";		   // 一時的に性別文字列を格納
  is >> client.name >> client.age >> gender; // 入力ストリームから顧客データを読み取る
  // 性別は性別文字列が "male" か否かで判断.
  // ただし, 性別文字列が "male" でも "female" でも無かった場合はその顧客データを無効(顧客名を空)にする.
  if ( gender == "male" || gender == "female" ){
      client.is_male = (gender == "male"); 
  } else {
    client.name = "";
  }
  return is;
}


// 
// メイン関数
// 
int main(void)
{
  // ----------------------------------------
  // 顧客データを格納する配列を定義
  const int mem_size = 10;
  Client client[mem_size];

  // ----------------------------------------
  // 顧客情報の読込
  ifstream ifs("data.txt"); // 入力ファイルストリームを開く
  int ID = 0;			// 次に入力する顧客のID(=現時点での顧客数)
  while ( !ifs.eof() && ID < mem_size )
    {
      ifs >> client[ID];       // >>演算子の overload により簡潔に記述できる
      ID++;		       // 顧客数を増やす
    }
  ifs.close();		// 入力ファイルストリームを閉じる

  // ----------------------------------------
  // 顧客データを表示
  for (int ID = 0; ID < mem_size; ++ID)
    {
      // 顧客の名前が空白ならループを脱出
      if (client[ID].name == "") break;
      // 顧客情報を表示
      cout << client[ID] << endl; // <<演算子の overload により簡潔に記述できる
    }
}
