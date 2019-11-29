# Header Only Tokenizer

## Installation

Simply add __tokenizer.hpp__ to your c++ project !

## Usage

```c++

// tokenizer initialization

tokenizer tok;

tok.set_dropped_delimiters(" \t\r\n");

tok.add_kept_delimiter("=");
tok.add_kept_delimiter("*");
tok.add_kept_delimiter("{");
tok.add_kept_delimiter("}");
tok.add_kept_delimiter("(");
tok.add_kept_delimiter(")");
tok.add_kept_delimiter(";");
tok.add_kept_delimiter("&");
tok.add_kept_delimiter("&&");
tok.add_kept_delimiter(":");
tok.add_kept_delimiter("::");
tok.add_kept_delimiter("\"");

// tokenize

tok.start(str);

while (!tok.finished())
{
    const std::string& token = tok.next();

    std::cout << token << "\n";
}

```

So the following input string :

```txt
class my_class
{
    private:
    int* iptr = nullptr;
    std::string str = "";

    my_class(std::string&& _str);
}
```

will inputs this tokens :

```txt
class
my_class
{
private
:
int
*
iptr
=
nullptr
;
std
::
string
str
=
"
"
;
my_class
(
std
::
string
&&
_str
)
;
}
```
