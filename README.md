# osu-db-parser
A small C++17 header-only utility for parsing the binary osu `db` files.

## Usage
Just copy the `OsuDBParser.hpp` to your project.
This small utility include parsing all 3 osu! `db` files. All classes are under `namepsace Db`.
- `Db::Osu` -> `osu!.db`
- `Db::Collections` -> `collection.db`
- `Db::Scores` -> `scores.db`

All the above can be construct in 3 ways:
- Passing in a raw pointer (`unsigned char*`) to the buffer that has content of the files
- Passing in a smart pointer (`std::unique_ptr<unsigned char[]>`) to the buffer that has the content of the files
- Passing in a `std::ifstream`, opened in binary mode

## Example
```cpp
Db::Osu db{ std::ifstream{ "osu!.db", std::ios_base::binary } };
std::cout << "Parsed "<< db.beatmaps.size() << " maps\n";
```