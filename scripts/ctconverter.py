import argparse
import json
from pathlib import Path

import ctranslate2.converters as converters

"""
This is a helper script used for converting models from transformers to CTranslate2.
WARNING: This script does NOT guarantee that every model WILL work with CTranslate2.

Usage:

    python scripts/converter.py

    python scripts/converter.py --load_as_float16

    python scripts/converter.py --quantization int8_float16

    python scripts/converter.py --load_as_float16 --quantization int8_float16
"""

parser = argparse.ArgumentParser(
    prog="ctconverter", description="CTranslate2 converter"
)

parser.add_argument(
    "--load_as_float16",
    "-f",
    action="store_true",
    help="load model as float16",
    default=False,
)
parser.add_argument(
    "--quantization",
    "-q",
    type=str,
    choices=["int8_float16", "int8_float32", "int8", "int16"],
    help="quantization mode",
    default="int8",
)
parser.add_argument(
    "--model",
    "-m",
    metavar="[Model Name | Model Path]",
    type=str,
    help="model name or path",
    default="JosephusCheung/LL7M",
)
parser.add_argument(
    "--output",
    "-o",
    metavar="[Model Name | Model Path]",
    type=str,
    help="output model name",
    default="assets/hftf/ct2-ll7m",
)
parser.add_argument(
    "--dry-run", "-d", action="store_true", help="dry run, don't convert the model"
)

args = parser.parse_args()

output_path: str = args.output
exec_path: str = "output"
conf_path: str = "config.json"
symlink_path: str = Path.joinpath(Path(exec_path), Path(output_path)).absolute()

if not args.dry_run:
    converters.TransformersConverter(
        args.model, load_as_float16=args.load_as_float16
    ).convert(output_path, quantization=args.quantization, force=True)

# split the output path and create all the directories except the last one, it will be symlinked.
# create dirs in order, so for dir1/dir2/dir3:
# 1. dir1 will be created on its own
# 2. dir1/dir2 will be created
# 3. dir1/dir2/dir3 will be created
for path in reversed(Path(exec_path).joinpath(output_path).parents[:-1]):
    path.mkdir(parents=True, exist_ok=True)

if not Path(symlink_path).exists(follow_symlinks=False):
    Path(symlink_path).symlink_to(Path(output_path).absolute())

Path(conf_path).touch()
with open("config.json", "w") as f:
    json.dump(
        {
            "model_info": {
                "model_path": output_path,
            },
            "tokenizer_info": {
                "tokenizer_path": exec_path,
            },
            "device": "cpu",
            "batch_size": 1,
            "max_seq_len": 1024,
        },
        f,
        indent=2,
    )
