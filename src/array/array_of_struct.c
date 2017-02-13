#include <stdio.h>		// 標準入出力
#include <stdlib.h>		// 各種ユーティリティを含む標準ライブラリ
#include <string.h>		// 文字列操作
#include <stdbool.h>		// ブール型

#define NAME_MAXLEN 12		// 名前の最大長
#define GENDER_MAXLEN 100	// 性別文字列の最大長
#define CUSTOMER_SIZE 10	// 顧客数の最大値
#define BUFFER_SIZE 100		// ファイル読み込み時のバッファサイズ

// ----------------------------------------
// 顧客データを格納する構造体
// ----------------------------------------
typedef struct
{
  char name[NAME_MAXLEN];	// 名前
  int age;			// 年齢
  bool is_male;			// 性別
} Client;


// ----------------------------------------
// 関数ヘッダ
// ----------------------------------------
// 顧客情報をセット. 顧客情報が不適切な場合は顧客情報を無効(名前を空文字列)にして false を返す
bool set_client(Client *client, char name[], int age, char gender[]);
// ファイルストリームへの顧客情報の出力
void show_client(FILE *ofs, Client client);
// ファイルストリームからの顧客情報の読込み
bool read_client_from_txt(FILE *ifs, Client *client);
// CSVファイルストリームからの顧客情報の読込み
bool read_client_from_csv(FILE *ifs, Client *client);


// ----------------------------------------
// メイン関数
// ----------------------------------------
int main(void)
{
  // ----------------------------------------
  // 顧客データを格納する Client 型構造体の配列を宣言
  Client client[CUSTOMER_SIZE];

  // ----------------------------------------
  // 顧客情報の読込
  FILE *ifs;			// ファイルストリーム
  ifs = fopen("test_data.csv", "r");	// ファイルストリームを開く

  int ID = 0;			// 次の顧客ID(=これまでに読み込んだ顧客数)
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
    show_client( stdout, client[ID] );
    printf("\n");
  }

  return 0;
}


// ----------------------------------------
// 顧客情報をセット. 顧客情報が不適切な場合は顧客情報を無効(名前を空文字列)にして false を返す
// ----------------------------------------
bool set_client(Client *client, char name[], int age, char gender[])
{
  // 名前文字列が空文字列だったり, 性別文字列に "male" が含まれていなければ
  // 顧客情報を無効(名前を空文字列)にして false を返す
  if ( name[0] == '\0' || !strstr(gender, "male") ){
    client->name[0] = '\0';
    return false;
  }

  // client の各メンバ変数に顧客情報をセット
  strcpy(client->name, name);
  client->age = age;
  client->is_male = !( strstr(gender, "female") );
  // 顧客情報の全てが適切なら true を返す
  return true;  
}

// ----------------------------------------
// CSVファイルストリームからの顧客情報の読込み
// ----------------------------------------
bool read_client_from_csv(FILE *ifs, Client *client)
{
  // ファイルストリームから1行読み込んでバッファに格納
  char buf[BUFFER_SIZE] = {};	// 読み込んだ行を格納するバッファ
  if ( fgets(buf, BUFFER_SIZE, ifs) == NULL  ){ 
    return false;		// 読み込めなければ false を返す
  }

  // 一時格納用変数
  char name[NAME_MAXLEN];	// 名前
  int age;			// 年齢
  char gender[GENDER_MAXLEN];	// 性別文字列

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
    age = atoi(token);	// 関数 atoi() で文字列型を int型に変換
  } else {
    return false; // 文字列が取得できなければ false を返す
  }
  // 最後までの文字列から顧客の性別を取得する
  if ( (token = strtok(NULL, " \n")) != NULL ){
    strcpy(gender, token);
  } else {
    return false; // 文字列が取得できなければ false を返す
  }
  // set_client を呼び出して顧客情報をセットする. 顧客情報が適切でなければ false を返す.
  return set_client(client, name, age, gender);
}

// ----------------------------------------
// ファイルストリームからの顧客情報の読込み
// ----------------------------------------
bool read_client_from_txt(FILE *ifs, Client *client)
{
  // 一時格納用変数
  char name[NAME_MAXLEN];	// 名前
  int age;			// 年齢
  char gender[GENDER_MAXLEN];	// 性別文字列

  // fscan を使ってファイルストリームから name, age, gender を読み取り,
  // set_client を使って顧客情報を格納する.
  // 読み取れたデータが3個に満たない場合は顧客情報を無効(名前を空文字列)にして false を返す
  if ( fscanf(ifs, "%s%d%s", name, &age, gender) < 3 ){
    client->name[0] = '\0';
    return false;
  }
  // set_client を呼び出して顧客情報をセットする. 顧客情報が適切でなければ false を返す.
  return set_client(client, name, age, gender);
}

// ----------------------------------------
// 標準出力に顧客情報を出力
// ----------------------------------------
void show_client(FILE *ofs, Client client)
{
  printf("| %-10s | %3d | %-6s |",
	 client.name, client.age,
	 ( client.is_male ) ? "male" : "female");
}
