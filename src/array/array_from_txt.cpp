#include <iostream>		// 標準入出力
#include <iomanip>		// 入出力操作
#include <fstream>		// ファイル入出力
#include <sstream>		// 文字列ストリーム
#include <string>		// 文字列
using namespace std;		// デフォルトの名前空間を std に設定

const int CUSTOMER_SIZE = 10;	// 確保しておく顧客データのサイズ
const int BUFFER_SIZE = 100;	// ファイル読み込み時のバッファサイズ

// ----------------------------------------
// 関数ヘッダ
// ----------------------------------------
// 出力ストリームに顧客情報を出力
ostream& show_client(ostream& os, const string& name, int age, bool is_male);
// ファイルストリームからの顧客情報の読込み
bool read_client_from_txt(ifstream& ifs, string& name, int& age, bool& is_male);


// ----------------------------------------
// メイン関数
// ----------------------------------------
int main(void)
{
  // ----------------------------------------
  // 名前・年齢・性別を格納する配列を宣言
  string name[CUSTOMER_SIZE];	// 名前
  int age[CUSTOMER_SIZE];	// 年齢
  bool is_male[CUSTOMER_SIZE];	// 性別

  // ----------------------------------------
  // 顧客情報の読込
  ifstream ifs("test_data.txt"); // 入力ファイルストリームを開く
  int ID = 0;		    // 次の顧客ID(=これまでに読み込んだ顧客数)
  while ( ID < CUSTOMER_SIZE && !ifs.eof() )
    {
      // 入力ファイルストリームから顧客情報を読み取る
      if ( read_client_from_txt(ifs, name[ID], age[ID], is_male[ID]) ){
	// 顧客情報が正常に読み取れたなら, 次の顧客ID(=読み込んだ顧客数)を増やす
	ID ++;
      } else {
	// 顧客情報の読み取りに問題があったなら, その顧客情報を無効(名前を空文字列)にして次の行へ
	name[ID] = "";
	continue;
      }
    }
  ifs.close();			// ファイルストリームを閉じる
    
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
// ファイルストリームからの顧客情報の読込み
// ----------------------------------------
bool read_client_from_txt(ifstream& ifs, string& name, int& age, bool& is_male)
{
  string gender = "";		// 性別文字列
  ifs >> name >> age >> gender;

  // gender までのデータが読み取れなかったり, 読み取った性別文字列に "male" が含まれていなければ false を返す
  if ( gender.find("male")==string::npos ){
    return false;
  }
  // gender が "female" を含まないなら is_male を true にする.
  is_male = ( gender.find("female") == string::npos );
  // 顧客データの全てが正常に読み取れたら true を返す
  return true;
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
