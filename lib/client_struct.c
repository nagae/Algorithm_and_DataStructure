#include "client_struct.h"

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

  // バッファからカンマで区切られたデータを取得する
  char *token;		    // トークン用のポインタ
  // 先頭から最初のカンマまでの文字列を顧客の名前とする
  if ( (token = strtok(buf, ",")) != NULL){
    strcpy(client->name, token);
  } else {
    return false; // 文字列が取得できなければ false を返す
  }
  // 2つ目のカンマまでの文字列から顧客の年齢を取得する
  if ( (token = strtok(NULL, ",")) != NULL ){
    client->age = atoi(token);	// 関数 atoi() で文字列型を int型に変換
  } else {
    return false; // 文字列が取得できなければ false を返す
  }
  // 最後までの文字列から顧客の性別を取得する
  if ( (token = strtok(NULL, "\n")) != NULL &&
       strstr(token, "male") ){
    // 文字列が female を含んでいなければ is_male を true にする
    client->is_male = ( !strstr(token, "female")  );
  } else {
    return false; // 文字列が取得できないか, "male" を含んでなければ false を返す
  }
  // 顧客データの全てが正常に読み取れたら true を返す
  return true;
}

// ----------------------------------------
// ファイルストリームからの顧客情報の読込み
// ----------------------------------------
bool read_client_from_txt(FILE *ifs, struct Client *client)
{
  char gender[7];		// 性別文字列
  int num_read = fscanf(ifs, "%s%d%s", client->name, &client->age, gender); // 読み取ったデータ
  // 3つのデータが読み取れなかったり, 読み取った性別文字列に "male" が含まれていなければ false を返す
  if ( num_read < 3 || !strstr(gender, "male") ){
    return false;
  }
  // 文字列が female を含んでいなければ is_male を true にする
  client->is_male = !strstr(gender, "female");
  return true;
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
