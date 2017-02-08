# 配列
下記のような顧客の名前, 年齢, 性別を管理したい.

| name  | age | gender |
|-------|-----|--------|
| Alice | 23  | female |
| Bob   | 17  | male   |
| Cathy | 32  | female |
| David | 25  | male   |
| Ethan | 48  | male   |
| Flank | 27  | male   |
| Gina  | 42  | female |

## ナイーブな方法
以下のように人数分の名前・年齢・性別を格納するための変数を用意することもできるが, 
顧客が増減するたびに膨大なソース・コードの修正が必要であり, とても現実的ではない.

```c++
#include <iostream>
#include <string>

// 標準出力に顧客情報を出力
void show_client(std::string name, int age, bool is_male)
{
  std::cout << "name:" << name << "\t"
	    << "age:" << age << "\t"
	    << "gender:" << ((is_male) ? "male" : "female")
	    << std::endl;
}

// メイン関数
int main(void)
{
  // 名前を格納する変数
  std::string name1, name2, name3, name4, name5, name6, name7;
  // 年齢を格納する変数
  int age1, age2, age3, age4, age5, age6, age7;
  // 性別を格納する変数
  bool is_male1, is_male2, is_male3, is_male4, is_male5, is_male6, is_male7;
  
  // 1人目の顧客情報
  name1 = "Alice";
  age1 = 23;
  is_male1 = false;
  
  // 2人目の顧客情報
  name2 = "Bob";
  age2 = 17;
  is_male2 = true;
  
  // 以下, 3人目以降を代入
  // :
  
  // 顧客情報の表示
  show_client(name1, age1, is_male1); // 1人目
  show_client(name2, age2, is_male2); // 2人目
  // 以下, 3人目以降を出力
}
```

## 配列を使う
こうした多くのデータを取り扱うには **配列** を用いるのが一般的. 
以下では, 名前・年齢・性別のそれぞれを配列で格納している.
関数 `show_client` にはこれらの配列の **ポインタ** (変数名に `*` をつけている)を
渡していることに注意されたい.

``` c++
#include <iostream>
#include <string>

// 標準出力に顧客情報を出力
void show_client(int ID,		 // 出力する顧客のID
		 std::string * name_list, // 名前・年齢・性別の各リストのポインタを渡す
		 int * age_list,		 // 
		 bool * is_male_list)	 // 
{
  std::cout << "name:" << name_list[ID] << "\t"
	    << "age:" << age_list[ID] << "\t"
	    << "gender:" << ((is_male_list[ID]) ? "male" : "female")
	    << std::endl;
}

// メイン関数
int main(void){
  // 確保しておく顧客データのサイズ
  const int mem_size = 10;
  // 名前・年齢・性別を格納する配列を宣言し, 同時に初期化している
  // 名前
  std::string name_list[mem_size] =
    { "Alice", "Bob", "Cathy", "David", "Ethan", "Flank", "Gina" };
  // 年齢
  int age_list[mem_size] =
    { 23, 17, 32, 25, 48, 27, 42 };
  // 性別
  bool is_male_list[mem_size] =
    { false, true, false, true, true, true, false};
  
  // 顧客情報の表示
  int ID;
  for (ID = 0; ID < mem_size; ++ID){
    // 名前が空だった場合はループを脱出
    if (name_list[ID] == "")
      {
	break;
      }
    // 顧客情報を表示
    show_client(ID, name_list, age_list, is_male_list);
  }
}
```

## 構造体の配列を使う
