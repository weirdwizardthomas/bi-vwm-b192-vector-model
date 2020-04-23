# author : koristo1@fit.cvut.cz
import argparse

from src.preprocessor import preprocess_collection

parser = argparse.ArgumentParser(description="Collection preprocessing")
parser.add_argument("-i", "--input", type=str, help="Path to the input collection directory")
parser.add_argument("-o", "--output", type=str, help="Path to the output database file")
parser.add_argument("-f", "--frequency", type=str, help="Path to the output frequency file")
args = parser.parse_args()
preprocess_collection(args.input, args.frequency, args.output)
