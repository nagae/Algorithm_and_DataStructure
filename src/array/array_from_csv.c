#include <stdio.h>		// 標準入出力
#include <stdlib.h>		// 各種ユーティリティを含む標準ライブラリ
#include <string.h>		// 文字列操作
#include <stdbool.h>		// ブール型

#define NAME_MAXLEN 12		// 名前の最大長
#define GENDER_MAXLEN 100	// 性別文字列の最大長
#define CUSTOMER_SIZE 10	// 顧客数の最大値
#define BUFFER_SIZE 100		// ファイル読み込み時のバッファサイズ

// ----------------------------------------
// 関数ヘッダ
// ----------------------------------------
// ファイルストリームへの顧客情報の出力
void show_client(FILE *ofs, char name[], int age, bool is_male);
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
  char name[CUSTOMER_SIZE][NAME_MAXLEN]; // 名前
  int age[CUSTOMER_SIZE];	       //年齢
  bool is_male[CUSTOMER_SIZE];	       //性別

  // ----------------------------------------
  // 顧客情報の読込
  FILE *ifs;			// ファイルストリーム
  ifs = fopen("test_data.csv", "r");	// ファイルストリームを開く

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
    show_client( stdout, name[ID], age[ID], is_male[ID] );
    printf("\n");
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
    // バッファが取得できなければその顧客データを無効(名前を空字列)にして無効にして false を返す
    name[0] = '\0';
    return false;
  }

  char *token;		    // トークン用のポインタ
  // 先頭から最初のカンマまでの文字列を顧客の名前とする
  if ( (token = strtok(buf, ",")) != NULL){
    strcpy(name, token);
  } else {
    // 文字列が取得できなければその顧客データを無効(名前を空字列)にして無効にして false を返す
    name[0] = '\0';
    return false;
  }
  // 2つ目のカンマまでの文字列から顧客の年齢を取得する
  if ( (token = strtok(NULL, ",")) != NULL ){
    *age = atoi(token);	// 関数 atoi() で文字列型を int型に変換
  } else {
    // 文字列が取得できなければその顧客データを無効(名前を空字列)にして無効にして false を返す
    name[0] = '\0';
    return false;
  }
  // 最後までの文字列から顧客の性別を取得する
  if ( (token = strtok(NULL, "\n")) != NULL &&
       strstr(token, "male") ){
    // 文字列が female を含んでいなければ is_male を true にする
    *is_male = ( !strstr(token, "female")  );
  } else {
    // 文字列が取得できないか, "male" を含んでなければその顧客データを無効にして false を返す
    name[0] = '\0';
    return false;
  }
  // 顧客データの全てが正常に読み取れたら true を返す
  return true;
}

// ----------------------------------------
// ファイルストリームからの顧客情報の読込み
// ----------------------------------------
bool read_client_from_txt(FILE *ifs, char name[], int *age, bool *is_male)
{
  char gender[GENDER_MAXLEN];	// 性別文字列
  int num_read = fscanf(ifs, "%s%d%s", name, age, gender); // 読み取ったデータ
  // 3つのデータが読み取れなかったり, 読み取った性別文字列に "male" が含まれていなければ false を返す
  if ( num_read < 3 || !strstr(gender, "male") ){
    return false;
  }
  // 文字列が female を含んでいなければ is_male を true にする
  *is_male = !strstr(gender, "female");
  // 顧客データの全てが正常に読み取れたら true を返す
  return true;
}

// ----------------------------------------
// ファイルストリームに顧客情報を出力
// ----------------------------------------
void show_client(FILE *ofs, char name[], int age, bool is_male)
{
  fprintf(ofs, "| %-10s | %3d | %-6s |",
	  name, age,
	  (is_male) ? "male" : "female");
}
