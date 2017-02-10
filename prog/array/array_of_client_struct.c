#include "../lib/client_struct.h"
#define CUSTOMER_SIZE 10	// 顧客数の最大値

// ----------------------------------------
// メイン関数
// ----------------------------------------
int main(void)
{
  // ----------------------------------------
  // 顧客データを格納する Client 型構造体の配列を宣言
  struct Client client[CUSTOMER_SIZE];

  // ----------------------------------------
  // 顧客情報の読込
  FILE *ifs;			// ファイルストリーム
  ifs = fopen("test_data.csv", "r");	// ファイルストリームを開く

  /*
    ファイルから1行づつバッファに取り込み, カンマ・空白で区切られた顧客データ(名前・年齢・性別)を格納する
  */
  int ID = 0;			// 次の顧客ID(=これまでに読み込んだ顧客数)
  char buf[BUFFER_SIZE] = {};	// 読み込んだ行を格納するバッファ
  while ( ID < CUSTOMER_SIZE && !feof(ifs) )
    {
      // ファイルストリームから顧客情報を読み取る
      if ( read_client_from_csv(ifs, &client[ID]) ){
	// 顧客情報が正常に読み取れたなら, 次の顧客ID(=読み込んだ顧客数)を増やす
	ID ++;
      } else {
	// 顧客情報の読み取りに問題があったなら, その顧客情報を無効(名前を空文字列)にして次の行へ
	client[ID].name[0] = '\0';
	continue;
      }
    }
  fclose(ifs);			// ファイルストリームを閉じる
    
  // ----------------------------------------
  // 顧客情報の表示
  for ( int ID = 0; ID < CUSTOMER_SIZE; ++ID )
  {
    // 名前が空だった場合はループを脱出
    if ( client[ID].name[0] == '\0' ) break;
    // 顧客情報を表示
    show_client( &client[ID] );
  }

  return 0;
}
