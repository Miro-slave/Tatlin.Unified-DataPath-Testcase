# Tatlin.Unified-DataPath-Testcase

## CLI usage options:

```
  tape_app <input fle path> <output file path>
```

```
  tape_app <input fle path> <output file path> <config file path>
```

| Parameter | File extension     | Description                |
| :-------- | :------- | :------------------------- |
| `input file path` | `.csv` | **Required**. File with numbers to sort |
| `output file path` | `.csv` | **Required**. File to write result |
| `config file path` | `.json` | Optional. File with tape operations duration time |

You can find example files in the ./samples directory.

## Build:

Project uses Conan for package management.

You can build project via build_unix.sh and build_windows.sh scripts correspondingly.

(build_windows.sh works with visual studio 15 toolchain)

## Dependencies:

gtest/1.17.0

nlohmann_json/3.12.0


## Example of work:

<img width="1050" height="119" alt="yadro-testcase-program-output_screenshot" src="https://github.com/user-attachments/assets/1ac06e07-3e37-4937-81e7-4d95a288cd43" />
