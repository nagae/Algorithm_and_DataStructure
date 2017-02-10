#include "client_class.hpp"

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
