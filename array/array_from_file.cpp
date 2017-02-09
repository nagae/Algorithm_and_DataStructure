#include <iostream>		// 標準入出力
#include <iomanip>		// 入出力操作
#include <fstream>		// ファイル入出力
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
  // 名前・年齢・性別を格納する配列を宣言
  const int mem_size = 10;	// 確保しておく顧客データのサイズ
  string name[mem_size];	// 名前
  int age[mem_size];		// 年齢
  bool is_male[mem_size];	// 性別

  // ----------------------------------------
  // 顧客情報の読込
  ifstream ifs("data.txt"); // 入力ファイルストリームを開く
  int ID = 0;			// 次に入力する顧客のID(=現時点での顧客数)
  while ( !ifs.eof() && ID < mem_size )
    {
      string gender;		// 一時的に性別文字列を格納
      ifs >> name[ID] >> age[ID] >> gender;
      // 性別は性別文字列が "male" か否かで判断.
      // ただし, 性別文字列が "male" でも "female" でも無かった場合はその顧客データを無効(顧客名を空)にする
      if ( gender == "male" || gender == "female" ){
	is_male[ID] = (gender == "male"); 
      } else {
	name[ID] = "";
      }

      ID++;			// 顧客数を増やす
    }
  ifs.close();		// 入力ファイルストリームを閉じる
    
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
