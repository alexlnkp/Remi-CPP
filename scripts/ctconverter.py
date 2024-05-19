import ctranslate2.converters as converters
import argparse

parser = argparse.ArgumentParser(prog="ctconverter", description="CTranslate2 converter")

parser.add_argument("--load_as_float16", "-f", action="store_true", help="load model as float16", default=False)
parser.add_argument("--quantization", "-q", type=str, choices=["int8_float16", "int8", "int16"], help="quantization mode", default="int8")
parser.add_argument("--model", "-m", metavar="[Model Name | Model Path]", type=str, help="model name or path", default="JosephusCheung/LL7M")
parser.add_argument("--output", "-o", metavar="[Model Name | Model Path]", type=str, help="output model name", default="models/ct2-ll7m")

args = parser.parse_args()

"""
This is a helper script used for converting models from transformers to CTranslate2.
WARNING: This script does NOT guarantee that every model WILL work with CTranslate2.

Usage:

    python scripts/converter.py

    python scripts/converter.py --load_as_float16

    python scripts/converter.py --quantization int8_float16

    python scripts/converter.py --load_as_float16 --quantization int8_float16
"""

converters.TransformersConverter(
    args.model,
    load_as_float16=args.load_as_float16
).convert(
    args.output,
    quantization=args.quantization,
    force=True
)
