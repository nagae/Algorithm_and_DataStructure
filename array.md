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

ナイーブな方法としては,

```c++
#include <string>
string name1, name2, name3, name4, name5, name6, name7;
int age1, age2, age3, age4, age5, age6, age7;
bool is_male1, is_male2, is_male3, is_male4, is_male5, is_male6, is_male7;

name1 = "Alice";
age1 = 23;
is_male1 = false;
```

などとして, 1番目の顧客の名前

を用意するものが考えられるが, 顧客が増えるたびに変数を用意しなければならず, 
