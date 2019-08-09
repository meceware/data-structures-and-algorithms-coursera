#include <iostream>
#include <stack>
#include <string>

struct Bracket {
  Bracket(char type, int position):
    type(type),
    position(position)
  {}

  bool match(char c) {
    if (type == '[' && c == ']')
      return true;
    if (type == '{' && c == '}')
      return true;
    if (type == '(' && c == ')')
      return true;
    return false;
  }

  char type;
  int position;
};

int main() {
  std::string text;
  getline(std::cin, text);

  std::stack <Bracket> brackets;

  for (int position = 0; position < text.length(); ++position) {
    char next = text[position];

    if (next == '(' || next == '[' || next == '{') {
      brackets.push( { next, position } );
    }

    if (next == ')' || next == ']' || next == '}') {
      if ( brackets.empty() ) {
        std::cout << position + 1;
        return 0;
      }

      Bracket& bracket = brackets.top();
      brackets.pop();
      if ( ! bracket.match( next ) ) {
        std::cout << position + 1;
        return 0;
      }
    }
  }

  if ( brackets.empty() ) {
    std::cout << "Success";
  } else {
    std::cout << brackets.top().position + 1;
  }

  return 0;
}
