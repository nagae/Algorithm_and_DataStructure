#include <stdio.h>		// 標準入出力
#include <stdlib.h>		// 各種ユーティリティを含む標準ライブラリ
#include <string.h>		// 文字列操作
#include <stdbool.h>		// ブール型

#define NAME_SIZE 12		// 名前長の最大値
#define CUSTOMER_SIZE 10	// 顧客数の最大値
#define BUFFER_SIZE 100		// ファイル読み込み時のバッファサイズ

// ----------------------------------------
// 関数ヘッダ
// ----------------------------------------
// 顧客情報の出力
void show_client(char name[], int age, bool is_male);
// ファイルストリームからの顧客情報の読込み
bool read_client_from_txt(FILE *ifs, char name[], int *age, bool *is_male);
// CSVファイルストリームからの顧客情報の読込み
bool read_client_from_csv(FILE *ifs, char name[], int *age, bool *is_male);


// ----------------------------------------
// メイン関数
// ----------------------------------------
int main(void)
{
  // ----------------------------------------
  // 名前・年齢・性別を格納する配列を宣言
  char name[CUSTOMER_SIZE][NAME_SIZE]; // 名前
  int age[CUSTOMER_SIZE];	       //年齢
  bool is_male[CUSTOMER_SIZE];	       //性別

  // ----------------------------------------
  // 顧客情報の読込
  FILE *ifs;			// ファイルストリーム
  ifs = fopen("test_data.csv", "r");	// ファイルストリームを開く

  /*
    ファイルから1行づつバッファに取り込み, カンマ・空白で区切られた顧客データ(名前・年齢・性別)を格納する
  */
  int ID = 0;			// 次の顧客ID(=これまでに読み込んだ顧客数)
  while ( ID < CUSTOMER_SIZE && !feof(ifs) )
    {
      // ファイルストリームから顧客情報を読み取る
      if ( read_client_from_csv(ifs, name[ID], &age[ID], &is_male[ID]) ){
	// 顧客情報が正常に読み取れたなら, 次の顧客ID(=読み込んだ顧客数)を増やす
	ID ++;
      } else {
	// 顧客情報の読み取りに問題があったなら, その顧客情報を無効(名前を空文字列)にして次の行へ
	name[ID][0] = '\0';
	continue;
      }
    }
  fclose(ifs);			// ファイルストリームを閉じる
    
  // ----------------------------------------
  // 顧客情報の表示
  for ( int ID = 0; ID < CUSTOMER_SIZE; ++ID )
  {
    // 名前が空だった場合はループを脱出
    if ( name[ID][0] == '\0' ) break;
    // 顧客情報を表示
    show_client( name[ID], age[ID], is_male[ID] );
  }

  return 0;
}



// ----------------------------------------
// CSVファイルストリームからの顧客情報の読込み
// ----------------------------------------
bool read_client_from_csv(FILE *ifs, char name[], int *age, bool *is_male)
{
  // ファイルストリームから1行読み込んでバッファに格納
  char buf[BUFFER_SIZE] = {};	// 読み込んだ行を格納するバッファ
  if ( fgets(buf, BUFFER_SIZE, ifs) == NULL  ){ 
    return false;		// 読み込めなければ false を返す
  }
  
  // バッファからカンマで区切られたデータを取得する
  char *token;		    // トークン用のポインタ
  // 先頭から最初のカンマまでの文字列を顧客の名前とする
  if ( (token = strtok(buf, ",")) != NULL){
    strcpy(name, token);
  } else {
    return false; // 文字列が取得できなければ false を返す
  }
  // 2つ目のカンマまでの文字列から顧客の年齢を取得する
  if ( (token = strtok(NULL, ",")) != NULL ){
    *age = atoi(token);	// 関数 atoi() で文字列型を int型に変換
  } else {
    return false; // 文字列が取得できなければ false を返す
  }
  // 最後までの文字列から顧客の性別を取得する
  if ( (token = strtok(NULL, "\n")) != NULL &&
       strstr(token, "male") ){
    // 文字列が female を含んでいなければ is_male を true にする
    *is_male = ( !strstr(token, "female")  );
  } else {
    return false; // 文字列が取得できないか, "male" を含んでなければ false を返す
  }
  // 顧客データの全てが正常に読み取れたら true を返す
  return true;
}


// ----------------------------------------
// ファイルストリームからの顧客情報の読込み
// ----------------------------------------
bool read_client_from_txt(FILE *ifs, char name[], int *age, bool *is_male)
{
  char gender[7];		// 性別文字列
  int num_read = fscanf(ifs, "%s%d%s", name, age, gender); // 読み取ったデータ
  // 3つのデータが読み取れなかったり, 読み取った性別文字列に "male" が含まれていなければ false を返す
  if ( num_read < 3 || !strstr(gender, "male") ){
    return false;
  }
  // 文字列が female を含んでいなければ is_male を true にする
  *is_male = !strstr(gender, "female");
  return true;
}

// ----------------------------------------
// 標準出力に顧客情報を出力
// ----------------------------------------
void show_client(char name[], int age, bool is_male)
{
  printf("| %-10s | %3d | %-6s |\n",
	 name, age,
	 (is_male) ? "male" : "female");
}
