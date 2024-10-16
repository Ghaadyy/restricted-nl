#include "src/scanner.h"
#include "src/parser.h"

int main() {
  std::string s = R"(discordSignIn {
    visit url
    click button with description "Login button at the top right of the screen"
    type "username" on input with description "username field with placeholder username"
    type "password" on input with description "password field with placeholder password"
    click button with description "Login button under the password field"
})";

  parser p(std::move(s));

  if (p.parse()) {
    cout << "Compiled successfully" << endl;
  } else {
    cout << "Failed to compile" << endl;
  }

  return 0;
}