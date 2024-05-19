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
2. Not done yet

## License

This project is licensed under the **MIT** License - see the [LICENSE](LICENSE) file for details.

## TODO

1. [ ] A working inference
2. [ ] Adapter loader
3. [ ] A working fine-tuner

## Misc

### CTranslate2 installation

1. Recursively clone [CTranslate2](https://github.com/OpenNMT/CTranslate2) repository `git clone --recursive https://github.com/OpenNMT/CTranslate2.git`
2. Enter the cloned repository.
3. Create `build` directory and enter it. `mkdir build && cd build`
4. Run `cmake ..`
5. Run `cmake --install .`

### CTConverter script

1. Create a virtual environment using `python -m venv .venv`
2. Activate the virtual environment using `source .venv/bin/activate` (Linux) or `. .venv/Scripts/activate` (Windows)
3. Install requirements using `pip install -r scripts/converter.req`
4. Run the script using `python scripts/ctconverter.py`
