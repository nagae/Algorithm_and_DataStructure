#include "../../lib/client_struct.h"
#include "../../lib/client_struct.h"
#define CUSTOMER_SIZE 10	// 顧客数の最大値

// ----------------------------------------
// 関数ヘッダ
// ----------------------------------------
int read_client_set(char fname[], Client client[]);
void show_client_set(Client client[]);

// ----------------------------------------
// メイン関数
// ----------------------------------------
int main(int argc, char **argv)
{
  // ----------------------------------------
  // 顧客データを格納する Client 型構造体の配列を宣言
  Client client[CUSTOMER_SIZE];
  // ----------------------------------------
  // 顧客情報の読込
  if (argc > 1) {
    int num_client_set = read_client_set(argv[1], client);
    printf("num client:%d\n", num_client_set);
  }
		    
  // ----------------------------------------
  // 顧客情報の表示
  show_client_set(client);
  
  return 0;
}


// ----------------------------------------
// 指定したファイルから顧客データを読込む
// ----------------------------------------
int read_client_set(char fname[], Client client[])
{
  FILE *ifs;			// ファイルストリーム
  ifs = fopen(fname, "r");	// ファイルストリームを開く

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
  return ID;			// 読み込んだ顧客数を返す
}

// ----------------------------------------
// 全顧客データを標準出力に表示
// ----------------------------------------
void show_client_set(Client client[])
{
  for ( int ID = 0; ID < CUSTOMER_SIZE; ++ID )
  {
    // 名前が空だった場合はループを脱出
    if ( client[ID].name[0] == '\0' ) break;
    // 顧客情報を表示
    show_client( &client[ID] );
  }
}
