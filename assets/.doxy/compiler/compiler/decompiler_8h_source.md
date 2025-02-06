

# File decompiler.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**decompiler.h**](decompiler_8h.md)

[Go to the documentation of this file](decompiler_8h.md)


```C++
//
// Created by A-Karam on 2/2/2025.
//

#ifndef RESTRICTED_NL_DECOMPILER_H
#define RESTRICTED_NL_DECOMPILER_H


#include <string>
#include <expected>
#include "nlohmann/json.hpp"
#include "ast/AST.h"

using json = nlohmann::json;
using namespace std;

class decompiler {
private:
    const string ast;
    vector<string> errors;

    ActionNode* parseActionNode(const json &action);
    TestNode* parseTestNode(const json &test);

public:
    explicit decompiler(string&& ast);

    expected<AST, vector<string>> convert();
};


#endif //RESTRICTED_NL_DECOMPILER_H
```


