# Unicode & UTF-8 Testing

A collection of tests I did for Windows and Linux to test UTF-8 encoding and the ability to correctly display and use Unicode characters. <br><br>
Mainly a save-state for myself if I forgot how to deal with this later.

## ⚠️ Precaution

On Windows 10 the terminal is configured with a standard font that cannot display Unicode characters. The terminal won't display them correctly and interpret the characters as with their individual 8-bit aligned values. <br><br>
Although the terminal can't display them correctly, piping them to a file as output will create a correctly formatted file (if the bit-wise representation of the output is correct!). <br><br>
As I want to find an easy way to display Unicode chars correctly with UTF-8 encoding there will be no reconfiguration taking place. <br>
Therefore users can use these methods out-of-the-box for each OS.

## Prerequisites

* C++ toolchain, supporting **C++-20**
* CMake (>= 3.10)

## Methotology

C++-20 is chosen as C++ standard because two major dealbreakers that need to be covered:
1. support for filesystem access (through the standard template library)
2. support for `char8_t` type inside `path`-objects

---

OS's tested:
* Windows 10
* Debian / Ubuntu (22.04.1)

Compiler:
* gcc/g++ (Ubuntu) - 11.4.0
* MSVC (Windows) - 17.8.3
* mingw-gcc (Windows) - 13.2

With MSVC compile option `\utf-8` **needs** to be enabled!<br>
(Otherwise double-conversion for each UTF-8 character inside the source code will occur)

---

Several tests are chosen, only valid results for all cases are reported as functional (still commented in source how it failed).

Tested stuff:
* string literals
* `std::string`, `std::u8string`
* filepaths
* file-read
* file-write
  
---

Testing is checked for:
* 🖥️ terminal display-ability and
* 📄 piping to a file as output.

Output via:
* `stdout` - with cout
* `fprintf` - printing to stdout

Test-case characters are chosen in 3 different categories:
* basic ASCII characters (upto 127 as binary value, Unicode codepoint Ux007F) <br>
    👉 basic latin text
* characters upto 16-bit (represantable with UTF-16, Unicode codepoint Ux07FF) <br>
    👉 greek letters or something 
* characters beyond 16-bit (representation with atleast 3-byte wide UTF-8 encoded values, upto 0x10FFFF theoretically) <br>
    👉 CJK-stuff, japanese or emojies 🙃

## Tests

### string literals

🟩 **Best-case** is achieved with simple `const char*` arrays

Initialize simply with: `"Hello World! This will be fine π は 👌"`

🟧 **Optionally** use `const char8_t*` with `u8""` string literal

**BUT** output via reformatting to `reinterpret_cast<const char*>()`

🟥 **DON'T** use any `wchar_t*` - far to complicated and not flexible for inter-OS compatabilty

---

### string-library

🟩 **Best-case** also with simple `std::string` and `""` initialization

Initialize with: `std::string test("Hello World! ~insert random emoji~")` <br>
or from `const char*`

🟧 **Optionally** use `std::u8string` and `u8""` literal

**BUT** outputting via `cout` **doesn't** work <br>
👉 always convert with `reinterpret_cast<const char*>`

🟥 **DON'T** use `std::wstring`

---

### filepaths, containing Unicode characters (greek, CJK, etc.)

1. When constructing from **outside source** (e.g. file-read paths)

🟩 **Best-case**: <br>
* Initialize the outside string with `std::u8string`
* Use standard `std::filesystem::path` for path object
* **Always** access filepath via `mypath.u8string()` (not checked syntactically and can therefore crash your program)

🟥 **DON'T**:

Everything else. On Linux many options also work (simple string-constructed path, etc.) but on Windows nothing else works (as usual).

2. When using **string-literals** for path construction

🟩 **Best-case**: <br>
* Construct literal with `u8"my/fancy/path.DAT"`
* Use standard `std::filesystem::path`
* Access via `myfile.u8string()`

🟥 **DON'T**:

Every other combination (they work on Linux, but surprisingly not on Windows).

---

### file-read

Reading from a file should be always done via unformatted `read()` into a char-like buffer. This is then just a simple binary storage container for the file content. Formatting this content can be done later.

🟩 **Best-case**: <br>
* Read into 8-bit container (in my case `char readBuf[4096]`) with `read()`
* Construct either `std::string` **OR** `std::u8string`
* Printing `std::u8string` via conversion with `reinterpret_case<const char*>`

For outputting to console both options work flawlessly on all OSs.

---

### file-write

Writing to a file should also be done similar to reading. Therefore the unformatted output option `write()` is chosen to write to the file. In this case also a `binary`-mode is used when creating the file.

🟩 **Best-case**: <br>
* Create a buffer containing the data <br>
  Can be `char`-type **OR** `basic_string`
* **BOTH** options `const char*` and `const char8_t*` are valid as storage <br>
  aswell as `std::string` and `std::u8string`
* **BUT** for writing with `write` a conversion needs also to take place via `reinterpret_cast<const char*>`

Probably the easiest test as every combination of specific UTF-8 type or basic type works.

## Development
Simple `cmake` invoke

```bash
cmake -S . -B build
cmake --build build
```