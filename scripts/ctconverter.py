import argparse
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
    default="models/ct2-ll7m",
)

args = parser.parse_args()

output_path: str = args.output
exec_path: str = "output"
symlink_path: str = Path.joinpath(Path(exec_path), Path(output_path)).absolute()

converters.TransformersConverter(
    args.model, load_as_float16=args.load_as_float16
).convert(output_path, quantization=args.quantization, force=True)

Path(exec_path).joinpath(output_path.split("/")[0]).mkdir(parents=True, exist_ok=True)

if not Path(symlink_path).exists(follow_symlinks=False):
    Path(symlink_path).symlink_to(Path(output_path).absolute())
