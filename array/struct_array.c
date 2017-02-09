#include <stdio.h>		// 標準入出力
#include <string.h>		// 文字列操作
#include <stdbool.h>		// ブール型
#define buf_name 12		// 名前の長さの最大値
#define mem_size 10		// 確保しておく顧客データのサイズ

//
// 顧客データを格納する構造体
//
struct Client
{
  char name[buf_name];		// 名前
  int age;			// 年齢
  bool is_male;			// 性別
};


// 
// 標準出力に顧客情報を出力
// 
void show_client(struct Client *client)
{
  printf("| %-10s | %3d | %-6s |\n",
	 client->name, client->age,
	 ( client->is_male ) ? "male" : "female");
  // Client 型構造体は * を使ったポインタ渡しにしている.
  // client->name, client->age とするとポインタ client が示す構造体 *client のメンバに
  // アクセスできる. これらは client が指す実体 *client を使った
  // (*client).name, (*client).age などの表現と等価.
}


// 
// メイン関数
// 
int main(void)
{
  // ----------------------------------------
  // 顧客データを格納する Client 型の配列を宣言
  struct Client client[mem_size];

  // ----------------------------------------
  // 顧客情報の読込
  FILE *ifs;			// ファイルストリーム
  ifs = fopen("data.txt", "r");	// ファイルストリームを開く
  int ID = 0;			// 次に入力する顧客のID(=現時点での顧客数)
  while ( !feof(ifs) && ID < mem_size )
    {
      char tmp_gender[7];	// 一時的に性別文字列を保管
      // (性別文字列に格納するのは最大でも "female" の 6個の char と 文字列終端'\0'
      // なので必要な配列のサイズは7)
      // fscanf を用いてファイルから顧客データを読込む
      int num = fscanf( ifs, "%s%d%7s", client[ID].name, &client[ID].age, tmp_gender );
      // 3つのデータを読み込めなかった場合は, 当該顧客データを無効(顧客名を空)にする
      if ( num < 3 ) client[ID].name[0]='\0';
      // is_male は tmp_gender が "male" なら true, そうでなければ false.
      client[ID].is_male = ( strcmp(tmp_gender, "male") == 0 );
 
      ID++;			// 顧客数を増やす
    }
  fclose(ifs);			// ファイルストリームを閉じる
    
  // ----------------------------------------
  // 顧客情報の表示
  for ( int ID = 0; ID < mem_size; ++ID )
  {
    // 名前が空だった場合はループを脱出
    if ( client[ID].name[0] == '\0' ) break;
    // 顧客情報を表示
    show_client( &client[ID] );
  }
  
}
