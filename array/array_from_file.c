#include <stdio.h>		// 標準入出力
#include <string.h>		// 文字列操作
#include <stdbool.h>		// ブール型
#define buf_name 12		// 名前の長さの最大値
#define mem_size 10		// 確保しておく顧客データのサイズ

// 
// 標準出力に顧客情報を出力
// 
void show_client(char *name, int age, bool is_male)
{
  printf("| %-10s | %3d | %-6s |\n",
	 name, age,
	 (is_male) ? "male" : "female");
}


// 
// メイン関数
// 
int main(void)
{
  // ----------------------------------------
  // 名前・年齢・性別を格納する配列を宣言
  char name[mem_size][buf_name]; // 名前
  int age[mem_size];		 //年齢
  bool is_male[mem_size];	 //性別

  // ----------------------------------------
  // 顧客情報の読込
  FILE *ifs;			// ファイルストリーム
  ifs = fopen("data.txt", "r");	// ファイルストリームを開く
  int ID = 0;			// 次に入力する顧客のID(=現時点での顧客数)
  while ( !feof(ifs)  && ID < mem_size )
    {
      char gender[7];		// 一時的に性別文字列を格納
      // (性別文字列に格納するのは最大でも "female" の 6個の char と 文字列終端'\0'
      // なので必要な配列のサイズは7)
      // fscanf を用いてファイルから顧客データを読込む
      int num = fscanf( ifs, "%s%d%s", name[ID], &age[ID], gender );
      // 3つのデータを読み込めなかった場合は, その顧客データを無効(顧客名を空)にする
      if ( num < 3 ) name[ID][0]='\0';
      // is_male は tmp_gender が "male" なら true, そうでなければ false.
      is_male[ID] = ( strcmp(gender, "male") == 0 );

      ID++;			// 顧客数を増やす
    }
  fclose(ifs);			// ファイルストリームを閉じる
    
  // ----------------------------------------
  // 顧客情報の表示
  for ( int ID = 0; ID < mem_size; ++ID )
  {
    // 名前が空だった場合はループを脱出
    if ( name[ID][0] == '\0' ) break;
    // 顧客情報を表示
    show_client( name[ID], age[ID], is_male[ID] );
  }
  
}
