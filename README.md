# Remi-CPP

## Getting started

### Prerequisites

- C/C++ compiler {`gcc`, `clang`}
- CMake `3.29` or higher
- CTranslate2 (refer to
  [CTranslate2 installation](#ctranslate2-installation))

### Building

1. Recursively clone this repository `git clone --recursive https://github.com/alexlnkp/remi-cpp.git`
2. Enter the cloned repository.
3. Run `chmod +x autobuild` to make the build script script executable.
4. Run `./autobuild` to build with a single click.

### Usage

1. Make sure your model is compatible with CTranslate2. If it isn't - use the [CTConverter script](#ctconverter-script)
   - Refer to [CTranslate2 documentation](https://opennmt.net/CTranslate2/guides/transformers.html) for list of conversion-compatible models.
2. Tweak the `config.json` file accordingly to modify the inference parameters.
3. So far you need to change source code to modify prompt, but soon (when i fix the broken generation) you won't have to.
4. Enjoy... I guess? Most of the results so far are stuff like this:
```txt
## Response:
Assistant: 2147453983566521C*24...722-2262609322,CM2x3XP (5241)41D832MC

177333323C7
-5476193
```

## License

This project is licensed under the **MIT** License - see the [LICENSE](LICENSE) file for details.

## TODO

1. [ ] A working inference
2. [ ] Adapter loader
3. [ ] A working fine-tuner

## Credit
- [Hedley](https://nemequ.github.io/hedley/) made by [nemequ](https://github.com/nemequ)
- [CTranslate2](https://opennmt.net/CTranslate2) made by [OpenNMT](https://github.com/OpenNMT)
- [JSON](https://json.nlohmann.me/) library made by [Nlohmann](https://github.com/nlohmann)

## Misc

### NLohmann's JSON library installation
1. Clone [Nlohmann/JSON](https://github.com/nlohmann/json) repository `git clone https://github.com/nlohmann/json.git`
2. Enter the cloned repository.
3. Run `cmake -B build`
4. Run `cmake --install build`

### CTranslate2 installation

1. Recursively clone [CTranslate2](https://github.com/OpenNMT/CTranslate2) repository `git clone --recursive https://github.com/OpenNMT/CTranslate2.git`
2. Enter the cloned repository.
3. Run `cmake -B build`
4. Run `cmake --build build`
5. Run `cmake --install build`

### CTConverter script

1. Create a virtual environment using `python -m venv .venv`
2. Activate the virtual environment using `source .venv/bin/activate` (Linux) or `. .venv/Scripts/activate` (Windows)
3. Install requirements using `pip install -r scripts/converter.req`
4. Run the script using `python scripts/ctconverter.py`
