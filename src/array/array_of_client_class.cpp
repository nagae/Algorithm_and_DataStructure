#include <iostream>
#include <sstream>
#include <fstream>

#include "../../lib/client_class.hpp"
#include "../../lib/client_class.hpp"

const int CUSTOMER_SIZE = 10;	// 確保しておく顧客データのサイズ
const int BUFFER_SIZE = 100;	// ファイル読み込み時のバッファサイズ

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
