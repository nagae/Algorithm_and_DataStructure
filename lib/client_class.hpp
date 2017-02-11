#ifndef CLIENT_CLASS_HPP
#define CLIENT_CLASS_HPP

#include <iostream>		// 標準入出力
#include <iomanip>		// 入出力操作
#include <fstream>		// ファイル入出力
#include <sstream>		// 文字列ストリーム
#include <string>		// 文字列
using namespace std;		// デフォルトの名前空間を std に設定

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

#endif
