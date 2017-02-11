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
// <<演算子 の overload による顧客データの書き出し
ostream& operator<<(ostream& os, const Client& client);
// ファイルストリームからの顧客情報の読込み
bool read_client_from_txt(ifstream& ifs, Client& client);
// CSVファイルストリームからの顧客情報の読込み
bool read_client_from_csv(ifstream& ifs, Client& client);


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
  ifstream ifs("test_data.csv"); // 入力ファイルストリームを開く
  int ID = 0;		    // 次の顧客ID(=これまでに読み込んだ顧客数)
  string buf;		    // 読み込んだ行を格納するバッファ
  while ( ID < CUSTOMER_SIZE && !ifs.eof() )
    {
      // 入力ファイルストリームから顧客情報を読み取る
      if ( read_client_from_csv(ifs, client[ID]) ) {
	// 顧客情報が正常に読み取れたなら, 次の顧客ID(=読み込んだ顧客数)を増やす
	ID ++;
      } else {
	// 顧客情報の読み取りに問題があったなら, その顧客情報を無効(名前を空文字列)にして次の行へ
	client[ID].name = "";
	continue;
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

  return 0;
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
// CSVファイルストリームからの顧客情報の読込み
// ----------------------------------------
bool read_client_from_csv(ifstream& ifs, Client& client)
{
  // ファイルストリームから1行読み込んで buf に格納
  string buf;			// 読み込んだ行を格納するバッファ
  if ( !getline(ifs, buf) ){
    return false;		// 読み込めなければ false を返す
  }
  
  // バッファからカンマで区切られたデータを取得する
  istringstream iss(buf);	// バッファからstring入力ストリームを構築
  string token;			// トークン用のstring
  // 先頭から最初のカンマまでの文字列を顧客の名前とする
  if ( getline(iss, token, ',') ){
    client.name = token;
  } else {
    return false; // 文字列が取得できなければ false を返す
  }
  // 2つ目のカンマまでの文字列から顧客の年齢を取得する
  if ( getline(iss, token, ',') ) {
    client.age = stoi(token);	// 関数 stoi() で string型を int型に変換
  } else {
    return false; // 文字列が取得できなければ false を返す
  }
  // 最後までの文字列から顧客の性別を取得する
  if ( getline(iss, token, '\n') &&
       token.find("male") < string::npos ){
    // token が "female" を含まないなら is_male を true にする.
    client.is_male = ( token.find("female") == string::npos );
  } else {
    return false; // 文字列が取得できないか, "male" を含んでなければ false を返す
  }
  // 顧客データの全てが正常に読み取れたら true を返す
  return true;
}


// ----------------------------------------
// ファイルストリームからの顧客情報の読込み
// ----------------------------------------
bool read_client_from_txt(ifstream& ifs, Client& client)
{
  string gender = "";		// 性別文字列
  ifs >> client.name >> client.age >> gender;

  // gender までのデータが読み取れなかったり, 読み取った性別文字列に "male" が含まれていなければ false を返す
  if ( gender.find("male")==string::npos ){
    return false;
  }
  // gender が "female" を含まないなら is_male を true にする.
  client.is_male = ( gender.find("female") == string::npos );
  // 顧客データの全てが正常に読み取れたら true を返す
  return true;
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
