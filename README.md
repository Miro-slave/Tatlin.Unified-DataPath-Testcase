# Tatlin.Unified-DataPath-Testcase

## CLI usage options:

```http
  tape_app <input fle path> <output file path>
```

```http
  tape_app <input fle path> <output file path> <config file path>
```

| Parameter | File extension     | Description                |
| :-------- | :------- | :------------------------- |
| `input file path` | `.csv` | **Required**. File with numbers to sort |
| `output file path` | `.csv` | **Required**. File to write result |
| `config file path` | `.json` | Optional. File with tape operations duration time |

## Build:

Project uses Conan for package management.

You can build project via build_unix.sh and build_windows.sh script correspondingly.

(build_windows.sh works with visual studio 15 toolchain)

## Dependencies:

gtest/1.17.0

nlohmann_json/3.12.0


## Example of work:

<img width="1065" height="83" alt="image" src="https://github.com/user-attachments/assets/8b70876c-4c92-4cc4-b708-2c413eae92ec" />
<br></br>
You can find example files in the ./samples directory.
