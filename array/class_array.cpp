#include <iostream>		// 標準入出力
#include <iomanip>		// 入出力操作
#include <fstream>		// ファイル入出力
#include <sstream>		// 文字列ストリーム
#include <string>		// 文字列
using namespace std;		// デフォルトの名前空間を std に設定

const int CUSTOMER_SIZE = 10;	// 確保しておく顧客データのサイズ
const int BUFFER_SIZE = 100;	// ファイル読み込み時のバッファサイズ

// ----------------------------------------
// 顧客データを格納するクラス
// ----------------------------------------
class Client
{
public:	     // public: とすることで, 以下のメンバ変数に自由にアクセス
  string name;			// 名前
  int age;			// 年齢
  bool is_male;			// 性別
};


// ----------------------------------------
// 関数ヘッダ
// ----------------------------------------
// 出力ストリームに顧客情報を出力
ostream& show_client(ostream& os, const Client& client);
// バッファからの顧客情報の読込み
istream& read_client(istream& iss, Client& client);
// <<演算子 の overload による顧客データの書き出し
ostream& operator<<(ostream& os, const Client& client);
// >>演算子 の overload による顧客データの読み取り
istream& operator>>(istream& is, Client& client);


// ----------------------------------------
// メイン関数
// ----------------------------------------
int main(void)
{
  // ----------------------------------------
  // 顧客情報を格納する Client 型の配列を宣言
  Client client[CUSTOMER_SIZE];

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
      iss >> client[ID];       // >>演算子の overload により簡潔に記述できる
      // 読み取った顧客情報が有効なら, 次の顧客ID(=読み込んだ顧客数)を増やす
      if ( client[ID].name != "" ){ 
	ID ++;
      }
    }
  ifs.close();		// 入力ファイルストリームを閉じる

  // ----------------------------------------
  // 顧客データを表示
  for (int ID = 0; ID < CUSTOMER_SIZE; ++ID)
    {
      // 顧客の名前が空白ならループを脱出
      if (client[ID].name == "") break;
      // 顧客情報を表示
      cout << client[ID] << endl; // <<演算子の overload により簡潔に記述できる
    }
}


// ----------------------------------------
// <<演算子 の overload による顧客データの出力
// ----------------------------------------
ostream& operator<<(ostream& os, const Client& client) // os, c ともに参照渡し
{
  os << "| "
     << setw(10) << left << client.name << " | "
     << setw(3) << right << dec << client.age << " | "
     << setw(6) << left << ( ( client.is_male) ? "male" : "female" ) << " |";
  return os;
}


// ----------------------------------------
// >>演算子 の overload による顧客データの読み取り
// ----------------------------------------
istream& operator>>(istream& is, Client& client)
{
  return read_client(is, client);
}


// ----------------------------------------
// 入力ストリームからの顧客情報の読込み
// ----------------------------------------
istream& read_client(istream& is, Client& client)
{
  string token;
  // 先頭から最初のカンマまでの文字列を顧客の名前とする
  if ( getline(is, token, ',') ){
    client.name = token;
  } else {
    // 文字列が取得できなければその顧客データを無効(名前を空字列)にして return
    client.name = "";
    return is;
  } 
  
  // 2つ目のカンマまでの文字列から顧客の年齢を取得する
  if ( getline(is, token, ',') ) {
    client.age = stoi(token);	// 関数 stoi() で string型を int型に変換
  } else {
    // 文字列が取得できなければその顧客データを無効(名前を空字列)にして return
    client.name = "";
    return is;
  }
  
  // 最後までの文字列から顧客の性別を取得する
  if ( getline(is, token, '\n') &&
       token.find("male") < string::npos ){
    // token が "female" を含まないなら is_male を true にする.
    client.is_male = ( token.find("female") == string::npos );
  } else {
    // 文字列が取得できないか, "male" を含んでなければその顧客データを無効にして return
    client.name = "";
    return is;
  }
  return is;
}

// ----------------------------------------
// 出力ストリームに顧客情報を出力
// ----------------------------------------
ostream& show_client(ostream& os, const Client& client)
{
  os << "| "
     << setw(10) << left << client.name << " | "
     << setw(3) << right << dec << client.age << " | "
     << setw(6) << left << ( (client.is_male) ? "male" : "female" ) << " |"
     << endl;
  return os;
}
