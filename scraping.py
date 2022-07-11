import requests as req
import json
import time
import re
import string
import nltk
nltk.download('punkt')


with open('BeeMovie.txt', 'rt') as f:
    line = f.read().replace('\n','')
    line = line.lower()
    print(line)

all_punctuation = string.punctuation
print(f"input string:{line}")

clean_comment = line

for p in all_punctuation:
    clean_comment = clean_comment.replace(p,'')

print(f"clean string: {clean_comment}")


from nltk.tokenize import word_tokenize
tokens = word_tokenize(clean_comment)
print(tokens)
