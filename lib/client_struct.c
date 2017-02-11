#include "client_struct.h"

// ----------------------------------------
// 顧客情報をセット. 顧客情報が不適切な場合は顧客情報を無効(名前を空文字列)にして false を返す
// ----------------------------------------
bool set_client(struct Client *client, char name[], int age, char gender[])
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
bool read_client_from_csv(FILE *ifs, struct Client *client)
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
bool read_client_from_txt(FILE *ifs, struct Client *client)
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
