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
// 入力ストリームからの顧客情報の読込み
istream& read_client(istream& iss, string& name, int& age, bool& is_male);


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
  ifstream ifs("data.txt"); // 入力ファイルストリームを開く
  int ID = 0;		    // 次の顧客ID(=これまでに読み込んだ顧客数)
  string buf;		    // 読み込んだ行を格納するバッファ
  while ( ID < CUSTOMER_SIZE &&
	  getline(ifs, buf) )	// ファイルストリームから1行読み込んで buf に格納
    {
      // buf から顧客情報を読み取る
      istringstream iss(buf);
      read_client(iss, name[ID], age[ID], is_male[ID]);
      // 読み取った顧客情報が有効なら, 次の顧客ID(=読み込んだ顧客数)を増やす
      if ( name[ID] != "" ){ 
	ID ++;
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
// 入力ストリームからの顧客情報の読込み
// ----------------------------------------
istream& read_client(istream& is, string& name, int& age, bool& is_male)
{
  string token;
  // 先頭から最初のカンマまでの文字列を顧客の名前とする
  if ( getline(is, token, ',') ){
    name = token;
  } else {
    // 文字列が取得できなければその顧客データを無効(名前を空字列)にして return
    name = "";
    return is;
  } 
  
  // 2つ目のカンマまでの文字列から顧客の年齢を取得する
  if ( getline(is, token, ',') ) {
    age = stoi(token);	// 関数 stoi() で string型を int型に変換
  } else {
    // 文字列が取得できなければその顧客データを無効(名前を空字列)にして return
    name = "";
    return is;
  }
  
  // 最後までの文字列から顧客の性別を取得する
  if ( getline(is, token, '\n') &&
       token.find("male") < string::npos ){
    // token が "female" を含まないなら is_male を true にする.
    is_male = ( token.find("female") == string::npos );
  } else {
    // 文字列が取得できないか, "male" を含んでなければその顧客データを無効にして return
    name = "";
    return is;
  }
  return is;
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
