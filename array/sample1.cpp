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
    std::string name1, name2, name3, name4, name5, name6, name7;
    int age1, age2, age3, age4, age5, age6, age7;
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
