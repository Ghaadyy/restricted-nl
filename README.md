# Restricted Natural Language Compiler

## About the Project

This project contains the source code for the compiler of the restricted natural language for automated web testing.
The compiler generates a scripts for libraries such as Selenium (support for other libraries is coming soon).

## Example

Writing a library-agnostic script is straightforward.

The primary goals of this language are:
- Write library-agnostic scripts easily
- Readable like plain English
- Robust tests with **Smart Web Element Locators**

This simple script goes to the GitHub home page and tries to sign in with a dummy account.

```
githubSignIn {
   visit "https://github.com"
   click link with description "sign in present in the top right corner"
   check if image with description "GitHub logo" is displayed
   type "johndoe" on input with description "the username input field"
   type "secretpassword" on input with description "the password input filed"
   click button with description "sign in button"
}
```

## Grammar

You can find below the LL(1) grammar of the language.

```
program -> test program | epsilon
test -> TEST_NAME { body }
body -> action body | epsilon
action -> click | check | type | visit
elem_type -> BUTTON | LINK | TEXT | IMAGE | INPUT

visit -> VISIT URL
click -> CLICK elem_type WITH_DESC NLD
check -> CHECK_IF elem_type WITH_DESC NLD state
type -> TYPE CONTENT ON elem_type WITH_DESC NLD

state -> DISPLAYED | HIDDEN
```

`UPPER_CASE` refers to terminals, `lower_case` refers to non-terminals.

We aim to support more actions in the future, however, the possible actions for at the moment are: click, type _(with visit and check being meta actions useful for testing)_.

## Getting Started

### Prerequisites

In order to use the compiler on your machine or within another project, you will need a stable C++ compiler such as `gcc` and [CMake](https://cmake.org), a minimum working version is 3.10.

### Building the project

```bash
git clone https://github.com/Ghaadyy/restricted-nl.git
cd restricted-nl/
./install.sh
```

### Using the compiler

```
$ rnlc -i in.txt -o out.js -t selenium

Compiled successfully
```

### CLI arguments

```
$ rnlc --help

Restricted Natural Language Compiler
Usage: rnlc [OPTIONS]

Options:
  -h,--help                         Print this help message and exit
  -i,--input TEXT REQUIRED          Input file path
  -o,--output TEXT REQUIRED         Output file path
  -t,--target TEXT:{json,selenium}  [selenium] 
                                    Output target (json, selenium)
  --keep-xpath [0]                  Keep XPATH instead of natural description (use this for testing purposes only)
```